"""p9.py -- run Prover9 on .in files and record the results. Python standard library only.

Usage, from the folder exercises/lecture1/:

    python p9.py check                       is Prover9 installed? which program is used?
    python p9.py run   files/socrates.in     one run: exit code, meaning, proof
    python p9.py label files/socrates.in     two runs (goal, then its negation): True / False / Uncertain
    python p9.py experiment files/ex6_experiment/problems  [--gold FILE.csv] [--out FILE.csv]
                                             every .in file of a folder, one line per problem

Options for run, label and experiment:
    --max-seconds N    time limit of one run (default 10)
    --bin PATH         the Prover9 program to use (otherwise: see find_prover9 below)

You do not need to read this file to do the exercises. Everything it does, you can also do by hand
with  prover9 -f FILE.in : this script only saves typing when there are many files.
"""

import argparse
import csv
import os
import platform
import re
import shutil
import stat
import subprocess
import sys
import time
from importlib.util import find_spec

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

# Meaning of the exit codes of Prover9 (Prover9 manual, section "Exit codes").
EXIT_CODES = {
    0: "THEOREM PROVED (a proof was found)",
    1: "ERROR (the input file is not valid: syntax, arity, ...)",
    2: "SEARCH FAILED, sos_empty (the search is finished: no proof from these assumptions)",
    3: "SEARCH FAILED, max_megs (memory limit reached: we do not know)",
    4: "SEARCH FAILED, max_seconds (time limit reached: we do not know)",
    5: "SEARCH FAILED, max_given (limit on given clauses reached: we do not know)",
    6: "SEARCH FAILED, max_kept (limit on kept clauses reached: we do not know)",
    7: "SEARCH FAILED, action (stopped by an action)",
}

WINDOWS_GUI = r"C:\Program Files (x86)\Prover9-Mace4\bin-win32\prover9.exe"


# ----------------------------------------------------------------------------- finding Prover9

def find_prover9(explicit=None):
    """Return the path of the Prover9 program, looking in this order:

    1. the --bin option, or the environment variable PROVER9_BIN;
    2. a program called prover9 on your PATH (built from source, brew, apt, WSL...);
    3. the Windows GUI package Prover9-Mace4 v0.5, in its default folder;
    4. the program shipped inside the Python package pyprover9 (pip install pyprover9).
    """
    for path in (explicit, os.environ.get("PROVER9_BIN")):
        if path:
            if not os.path.exists(path):
                sys.exit(f"Prover9 not found at {path}")
            return path
    path = shutil.which("prover9")
    if path:
        return path
    if sys.platform.startswith("win") and os.path.exists(WINDOWS_GUI):
        return WINDOWS_GUI
    spec = find_spec("pyprover9")
    if spec and spec.submodule_search_locations:
        folder = os.path.join(list(spec.submodule_search_locations)[0], "executables")
        if sys.platform.startswith("linux"):
            name = "prover9-linux-elf-64" if platform.architecture()[0] == "64bit" else "prover9-linux-elf-32"
        elif sys.platform == "darwin":
            name = "prover9-MacOS-64"
        else:
            name = "prover9-windows-32.exe"
        path = os.path.join(folder, name)
        if os.path.exists(path):
            try:
                os.chmod(path, os.stat(path).st_mode | stat.S_IXUSR)
            except OSError:
                pass
            return path
    sys.exit("Prover9 not found. See exercises/lecture1/README.md, section 'Installing Prover9'.")


# ----------------------------------------------------------------------------- one run

def run_text(text, binary, max_seconds=10):
    """Run Prover9 on the content of a .in file. Returns (exit code, output, seconds).

    Two lines are added in front of the file:
      assign(max_seconds, N).   a time limit (an assign in the file itself comes later and wins);
      clear(auto_denials).      otherwise Prover9 sometimes looks for 2 proofs, finds 1, and exits
                                with code 2 although the output contains a proof (see the slides).
    The exit code returned is 0 whenever the output contains a proof.
    """
    text = f"assign(max_seconds, {int(max_seconds)}).\nclear(auto_denials).\n" + text
    start = time.perf_counter()
    try:
        done = subprocess.run([binary], input=text, capture_output=True, text=True,
                              encoding="utf-8", errors="replace", timeout=max_seconds + 10)
        code, output = done.returncode, done.stdout
    except subprocess.TimeoutExpired:
        code, output = 4, ""
    if "= PROOF =" in output:
        code = 0
    return code, output, time.perf_counter() - start


def proof_lines(output):
    """The numbered lines of the first proof, without the banners."""
    if "= PROOF =" not in output:
        return []
    body = output.split("= PROOF =", 1)[1].split("= end of proof =", 1)[0]
    return [line.strip() for line in body.splitlines() if line.strip()[:1].isdigit()]


def error_message(output):
    """Prover9's error message, on one line; the part it could not read is between >>> and <<<."""
    if "%%ERROR:" not in output:
        return ""
    message = output.split("%%ERROR:", 1)[1].split("Fatal error", 1)[0]
    message = message.replace("%%START ERROR%%", " >>> ").replace("%%END ERROR%%", " <<< ")
    return " ".join(message.split())


# ----------------------------------------------------------------------------- two runs: a label

def strip_comments(text):
    return "\n".join(line.split("%", 1)[0] for line in text.splitlines())


def goals_of(text):
    """The formulas of the list formulas(goals). Returns (list of formulas, text before, text after)."""
    clean = strip_comments(text)
    match = re.search(r"formulas\(\s*goals\s*\)\s*\.(.*?)end_of_list\s*\.", clean, re.S)
    if not match:
        return [], clean, ""
    formulas = [f.strip() for f in match.group(1).split(".") if f.strip()]
    return formulas, clean[:match.start()], clean[match.end():]


def negated(text):
    """The same problem, with the goal replaced by its negation  -(goal)."""
    goals, before, after = goals_of(text)
    if len(goals) != 1:
        raise ValueError(f"a label needs exactly one goal, this file has {len(goals)}")
    return before + "formulas(goals).\n  -(" + goals[0] + ").\nend_of_list.\n" + after


def label_text(text, binary, max_seconds=10):
    """True / False / Uncertain (or ERROR / TIMEOUT), and the two exit codes."""
    code1, out1, t1 = run_text(text, binary, max_seconds)
    if code1 == 1:
        return "ERROR", code1, None, t1, error_message(out1)
    code2, out2, t2 = run_text(negated(text), binary, max_seconds)
    if code1 == 0 and code2 == 0:
        label = "Inconsistent"           # both proved: the assumptions contradict each other
    elif code1 == 0:
        label = "True"
    elif code2 == 0:
        label = "False"
    elif code1 == 2 and code2 == 2:
        label = "Uncertain"
    else:
        label = "TIMEOUT"                # at least one run stopped on a limit: we do not know
    return label, code1, code2, t1 + t2, error_message(out2)


# ----------------------------------------------------------------------------- commands

def cmd_check(args):
    binary = find_prover9(args.bin)
    print("Prover9 program:", binary)
    text = ("formulas(assumptions).\n  all x (man(x) -> mortal(x)).\n  man(socrates).\nend_of_list.\n"
            "formulas(goals).\n  mortal(socrates).\nend_of_list.\n")
    code, output, seconds = run_text(text, binary, 5)
    version = next((line.strip() for line in output.splitlines() if " version " in line), "?")
    print("Version:        ", version)
    print("Socrates test:   exit code", code, "->", "OK" if code == 0 else "PROBLEM")


def cmd_run(args):
    binary = find_prover9(args.bin)
    with open(args.file, encoding="utf-8") as f:
        text = f.read()
    code, output, seconds = run_text(text, binary, args.max_seconds)
    print(f"{args.file}: exit code {code} = {EXIT_CODES.get(code, 'unknown code')}  ({seconds:.2f} s)")
    if code == 1:
        print("  ", error_message(output))
    for line in proof_lines(output):
        print("  ", line)


def cmd_label(args):
    binary = find_prover9(args.bin)
    with open(args.file, encoding="utf-8") as f:
        text = f.read()
    label, code1, code2, seconds, message = label_text(text, binary, args.max_seconds)
    print(f"{args.file}: goal -> code {code1}, -(goal) -> code {code2}  =>  {label}  ({seconds:.2f} s)")
    if message:
        print("  ", message)


def cmd_experiment(args):
    binary = find_prover9(args.bin)
    files = sorted(f for f in os.listdir(args.folder) if f.endswith(".in"))
    gold = {}
    if args.gold:
        with open(args.gold, encoding="utf-8") as f:
            gold = {row["file"]: row["gold"] for row in csv.DictReader(f)}
    rows = []
    print(f"{'file':28} {'goal':>4} {'-goal':>5}  {'label':12} {'gold':10} {'seconds':>7}")
    for name in files:
        with open(os.path.join(args.folder, name), encoding="utf-8") as f:
            text = f.read()
        try:
            label, code1, code2, seconds, _ = label_text(text, binary, args.max_seconds)
        except ValueError as error:
            label, code1, code2, seconds = f"ERROR ({error})", None, None, 0.0
        want = gold.get(name, "")
        mark = "" if not want else ("ok" if want == label else "<-- differs")
        print(f"{name:28} {str(code1):>4} {str(code2):>5}  {label:12} {want:10} {seconds:7.2f} {mark}")
        rows.append({"file": name, "code_goal": code1, "code_negation": code2, "label": label,
                     "gold": want, "seconds": round(seconds, 3)})
    if gold:
        agree = sum(r["label"] == r["gold"] for r in rows if r["gold"])
        print(f"\nagreement with gold: {agree}/{sum(1 for r in rows if r['gold'])}")
    if args.out:
        with open(args.out, "w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(f, fieldnames=list(rows[0]) if rows else ["file"])
            writer.writeheader()
            writer.writerows(rows)
        print("results written to", args.out)


def main(argv=None):
    parser = argparse.ArgumentParser(description="Run Prover9 on .in files.")
    sub = parser.add_subparsers(dest="command", required=True)
    for name in ("check", "run", "label", "experiment"):
        p = sub.add_parser(name)
        p.add_argument("--bin", help="path of the Prover9 program")
        p.add_argument("--max-seconds", type=int, default=10)
        if name in ("run", "label"):
            p.add_argument("file")
        if name == "experiment":
            p.add_argument("folder")
            p.add_argument("--gold", help="CSV file with columns file,gold")
            p.add_argument("--out", help="CSV file to write the results to")
    args = parser.parse_args(argv)
    {"check": cmd_check, "run": cmd_run, "label": cmd_label, "experiment": cmd_experiment}[args.command](args)


if __name__ == "__main__":
    main()
