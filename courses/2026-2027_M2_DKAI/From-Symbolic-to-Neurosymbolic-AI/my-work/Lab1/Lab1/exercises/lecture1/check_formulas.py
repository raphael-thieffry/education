"""check_formulas.py -- checks your answers to Exercise 1 (file ex1_formulas.txt).

    python check_formulas.py                     checks ex1_formulas.txt
    python check_formulas.py OTHER_FILE.txt      checks another file in the same format

A formula is accepted when it is LOGICALLY EQUIVALENT to the expected one. Prover9 itself does
the comparison: it tries to prove  (yours -> expected)  and  (expected -> yours).
So any correct way of writing the sentence passes.

    too strong   your formula says MORE than the sentence (yours -> expected is proved, not the converse)
    too weak     your formula says LESS than the sentence (expected -> yours is proved, not the converse)

The expected formulas are stored encoded, so that you do not read them by accident.
"""

import base64
import re
import sys

from p9 import error_message, find_prover9, run_text

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

VOCABULARY = {"student": 1, "smart": 1, "lazy": 1, "passes": 1, "knows": 2, "advisor": 1,
              "alice": 0, "bob": 0}

_EXPECTED = {
    "s1": "LWxhenkoYm9iKQ==",
    "s2": "YWxsIHggKHN0dWRlbnQoeCkgLT4gc21hcnQoeCkp",
    "s3": "ZXhpc3RzIHggKHN0dWRlbnQoeCkgJiBsYXp5KHgpKQ==",
    "s4": "YWxsIHggKChzdHVkZW50KHgpICYgbGF6eSh4KSkgLT4gLXBhc3Nlcyh4KSk=",
    "s5": "ZXhpc3RzIHggKHN0dWRlbnQoeCkgJiAtcGFzc2VzKHgpKQ==",
    "s6": "LShzbWFydChhbGljZSkgPC0+IGxhenkoYWxpY2UpKQ==",
    "s7": "cGFzc2VzKGJvYikgLT4gcGFzc2VzKGFsaWNlKQ==",
    "s8": "LWxhenkoYWxpY2UpIC0+IHBhc3NlcyhhbGljZSk=",
    "s9": "YWxsIHggKHBhc3Nlcyh4KSAtPiBzdHVkZW50KHgpKQ==",
    "s10": "YWxsIHggKHN0dWRlbnQoeCkgLT4gZXhpc3RzIHkgKHN0dWRlbnQoeSkgJiBzbWFydCh5KSAmIGtub3dzKHgsIHkpKSk=",
    "s11": "ZXhpc3RzIHkgYWxsIHggKHN0dWRlbnQoeCkgLT4ga25vd3MoeCwgeSkp",
    "s12": "YWxsIHggKHN0dWRlbnQoeCkgLT4gc21hcnQoYWR2aXNvcih4KSkp",
    "s13": "c3R1ZGVudChhbGljZSkgJiBzdHVkZW50KGJvYikgJiBhbGljZSAhPSBib2I=",
    "s14": "YWxsIHggYWxsIHkgKChzdHVkZW50KHgpICYgbGF6eSh4KSAmIHN0dWRlbnQoeSkgJiBsYXp5KHkpKSAtPiB4ID0geSk=",
}


def read_answers(path):
    """Lines 's3 = formula'. Lines starting with % are comments."""
    answers = {}
    with open(path, encoding="utf-8") as f:
        for line in f:
            match = re.match(r"\s*(s\d+)\s*=(.*)$", line)
            if match:
                answers[match.group(1)] = match.group(2).split("%", 1)[0].strip().rstrip(".").strip()
    return answers


def problem(text):
    return "formulas(assumptions).\nend_of_list.\nformulas(goals).\n  " + text + ".\nend_of_list.\n"


def proved(text, binary):
    code, output, _ = run_text(problem(text), binary, max_seconds=3)
    return code, output


def compare(student, expected, binary):
    """Returns (ok, message)."""
    if not student or "???" in student:
        return False, "not done yet"
    if any(ord(c) > 126 for c in student):
        return False, "use only ASCII characters (no accents, no logic symbols like ∀ or →)"
    text = "formulas(assumptions).\n  " + student + ".\nend_of_list.\n"
    code, output, _ = run_text(text, binary, max_seconds=3)
    if code == 1:
        return False, "syntax error -- " + error_message(output)
    bound = set(re.findall(r"\b(?:all|exists)\s+([a-z]\w*)", student))
    names = re.findall(r"\b([A-Za-z_]\w*)\s*(\(?)", student)
    for name, paren in names:
        if name in ("all", "exists") or name in bound:
            continue
        if name[0] in "uvwxyz":
            return False, (f"'{name}' starts with {name[0]}: without a quantifier Prover9 reads it as a "
                           f"VARIABLE. Write 'all {name} ...' or 'exists {name} ...'")
        if name not in VOCABULARY:
            return False, f"'{name}' is not in the vocabulary of the exercise (names are case-sensitive)"
    stronger, out1 = proved(f"({student}) -> ({expected})", binary)
    weaker, out2 = proved(f"({expected}) -> ({student})", binary)
    if 1 in (stronger, weaker):
        message = error_message(out1) or error_message(out2)
        return False, "Prover9 error -- " + message + " (did you use a function or a predicate with the wrong number of arguments?)"
    if stronger == 0 and weaker == 0:
        return True, ""
    if stronger == 0:
        return False, "too strong: your formula says more than the sentence"
    if weaker == 0:
        return False, "too weak: your formula says less than the sentence"
    return False, "this formula does not have the meaning of the sentence"


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "ex1_formulas.txt"
    binary = find_prover9()
    answers = read_answers(path)
    passed = 0
    for name, encoded in _EXPECTED.items():
        ok, message = compare(answers.get(name), base64.b64decode(encoded).decode("utf-8"), binary)
        passed += ok
        print(f"  [{'ok' if ok else '  '}] {name}" + ("" if ok else f": {message}"))
    if passed == len(_EXPECTED):
        print("SUCCESS")
        return True
    print(f"{passed}/{len(_EXPECTED)} correct -- fix the lines without [ok] and run again")
    return False


if __name__ == "__main__":
    sys.exit(0 if main() else 1)
