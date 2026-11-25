"""Small, exact rule scorer for the course; this is not an AMIE implementation."""

from __future__ import annotations

from collections import defaultdict
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Literal

Triple = tuple[str, str, str]
Pair = tuple[str, str]
Binding = dict[str, str]


@dataclass(frozen=True)
class Atom:
    """A binary atom; variables start with a question mark."""

    relation: str
    left: str
    right: str


@dataclass(frozen=True)
class Rule:
    """A rule with a fixed binary head and a conjunctive body."""

    head: Atom
    body: tuple[Atom, ...]

    def label(self) -> str:
        """Return a stable human-readable label."""
        body = " & ".join(f"{a.relation}({a.left},{a.right})" for a in self.body)
        return f"{body} => {self.head.relation}({self.head.left},{self.head.right})"


@dataclass(frozen=True)
class Scores:
    """All denominators are explicit; support counts distinct head pairs."""

    support: int
    body_pairs: int
    pca_pairs: int
    head_pairs: int
    confidence: float | None
    pca_confidence: float | None
    head_coverage: float | None

    def as_dict(self) -> dict[str, int | float | None]:
        """Return values ready to write to JSON or a notebook table."""
        return asdict(self)


def read_triples(path: Path) -> set[Triple]:
    """Read headerless subject/relation/object TSV and remove duplicates."""
    triples: set[Triple] = set()
    for line_number, line in enumerate(path.read_text().splitlines(), 1):
        if not line.strip():
            continue
        parts = line.split("\t")
        if len(parts) != 3:
            raise ValueError(f"{path}:{line_number}: expected three TSV fields")
        triples.add((parts[0], parts[1], parts[2]))
    return triples


def relation_index(triples: set[Triple]) -> dict[str, set[Pair]]:
    """Index set-valued binary relations."""
    index: dict[str, set[Pair]] = defaultdict(set)
    for subject, relation, obj in triples:
        index[relation].add((subject, obj))
    return dict(index)


def match_body(body: tuple[Atom, ...], index: dict[str, set[Pair]]) -> list[Binding]:
    """Compute a natural join, including repeated variables and constants."""
    bindings: list[Binding] = [{}]
    for atom in body:
        next_bindings: list[Binding] = []
        for binding in bindings:
            for left, right in sorted(index.get(atom.relation, set())):
                candidate = dict(binding)
                for term, value in [(atom.left, left), (atom.right, right)]:
                    if term.startswith("?"):
                        if term in candidate and candidate[term] != value:
                            break
                        candidate[term] = value
                    elif term != value:
                        break
                else:
                    next_bindings.append(candidate)
        bindings = next_bindings
    return bindings


def project_head(rule: Rule, bindings: list[Binding]) -> set[Pair]:
    """Project the join to distinct head pairs; reject unsafe head variables."""
    body_variables = {
        term for atom in rule.body for term in (atom.left, atom.right) if term.startswith("?")
    }
    head_variables = {term for term in (rule.head.left, rule.head.right) if term.startswith("?")}
    if not head_variables <= body_variables:
        raise ValueError("Unsafe rule: a head variable is absent from the body")
    return {
        (
            binding[rule.head.left] if rule.head.left.startswith("?") else rule.head.left,
            binding[rule.head.right] if rule.head.right.startswith("?") else rule.head.right,
        )
        for binding in bindings
    }


def score_rule(
    rule: Rule,
    index: dict[str, set[Pair]],
    orientation: Literal["subject", "object"] = "subject",
) -> Scores:
    """Compute exact support, head coverage and both confidences."""
    if orientation not in ("subject", "object"):
        raise ValueError("PCA orientation must be subject or object")
    predicted = project_head(rule, match_body(rule.body, index))
    head = index.get(rule.head.relation, set())
    support = len(predicted & head)
    position = 0 if orientation == "subject" else 1
    documented = {pair[position] for pair in head}
    pca = {pair for pair in predicted if pair[position] in documented}
    return Scores(
        support=support,
        body_pairs=len(predicted),
        pca_pairs=len(pca),
        head_pairs=len(head),
        confidence=support / len(predicted) if predicted else None,
        pca_confidence=support / len(pca) if pca else None,
        head_coverage=support / len(head) if head else None,
    )


def candidate_rules(relations: list[str], target: str) -> list[Rule]:
    """Enumerate four fixed templates; not all binary closed rules of this length."""
    head = Atom(target, "?x", "?y")
    candidates: set[Rule] = set()
    for first in sorted(relations):
        candidates.add(Rule(head, (Atom(first, "?y", "?x"),)))
        for second in sorted(relations):
            for terms in [
                (("?x", "?z"), ("?z", "?y")),
                (("?z", "?x"), ("?z", "?y")),
                (("?x", "?z"), ("?y", "?z")),
            ]:
                body = (Atom(first, *terms[0]), Atom(second, *terms[1]))
                candidates.add(Rule(head, body))
    return sorted(candidates, key=lambda rule: rule.label())


def rank_predictions(
    rules: list[Rule], index: dict[str, set[Pair]], target: str
) -> list[tuple[Pair, float]]:
    """Rank unseen pairs by the maximum training PCA score; break ties by IDs."""
    ranked: dict[Pair, float] = {}
    for rule in rules:
        if rule.head.relation != target:
            raise ValueError("All rules must have the requested target head")
        confidence = score_rule(rule, index).pca_confidence
        if confidence is None:
            continue
        predicted = project_head(rule, match_body(rule.body, index))
        for pair in predicted - index.get(target, set()):
            ranked[pair] = max(confidence, ranked.get(pair, 0.0))
    return sorted(ranked.items(), key=lambda item: (-item[1], item[0]))


def evaluate_observed(
    ranking: list[tuple[Pair, float]], held_out: set[Pair], k: int
) -> dict[str, int | float]:
    """Measure recovery of recorded targets; unmatched predictions remain unknown."""
    if k <= 0:
        raise ValueError("k must be positive")
    top = [pair for pair, _ in ranking[:k]]
    hits = len(set(top) & held_out)
    recovered = len({pair for pair, _ in ranking} & held_out)
    return {
        "requested_k": k,
        "returned_k": len(top),
        "recorded_targets": len(held_out),
        "recorded_hits_at_k": hits,
        "recorded_hit_fraction_at_k": hits / len(top) if top else 0.0,
        "recorded_recall_at_k": hits / len(held_out) if held_out else 0.0,
        "recorded_candidate_recall": recovered / len(held_out) if held_out else 0.0,
    }
