# Lecture 1 — First-order formulas and Prover9

After this lecture you can write an English sentence as a first-order formula, write it in
Prover9 syntax inside a `.in` file, install Prover9, run it, read its answer, and run a small
experiment on a set of problems.

Slides: `slides/en/lecture1.pdf` (French version: `../fr/`).

## Installing Prover9

Choose **one** method. All of them read the same files.

| Your machine | Method |
|---|---|
| Windows | the *Prover9-Mace4* package v0.5 |
| any, with Python 3 | `pip install pyprover9==0.0.32` (the Prover9 program is inside) |
| Linux, macOS, WSL | build LADR-2026 from source |
| macOS | `brew install prover9` |
| none | online: <https://prover9.org/webapps/combo/> |

### Windows: the Prover9-Mace4 package

Download `Prover9-Mace4-v05-setup.exe` from
<https://www.cs.unm.edu/~mccune/prover9/gui/v05.html> and install it. The command-line program is
then `C:\Program Files (x86)\Prover9-Mace4\bin-win32\prover9.exe`. In PowerShell:

```powershell
$P9 = "C:\Program Files (x86)\Prover9-Mace4\bin-win32\prover9.exe"
& $P9 -f files\socrates.in > socrates.out
$LASTEXITCODE          # 0 expected
```

To type just `prover9`, add the folder `bin-win32` to your `PATH`.

### Python: pyprover9

```sh
pip install -r ../../requirements.txt     # or: pip install pyprover9==0.0.32
```

On macOS, the program inside `pyprover9` is built for Apple chips (arm64). On an Intel Mac it does
not start, and Rosetta does not help: build Prover9 from source (next section) or use
`brew install prover9`.

### Linux, macOS, WSL: build from source

```sh
URL=https://github.com/AlgorithmicTruth/Prover9/archive/refs/tags
wget -O LADR-2026-8A.tar.gz $URL/LADR-2026-8A.tar.gz   # macOS: curl -L -o instead of wget -O
tar xzf LADR-2026-8A.tar.gz
cd Prover9-LADR-2026-8A
make all                              # needs a C compiler and make
export PATH="$PWD/bin:$PATH"          # in this terminal
# and in every new terminal (macOS: ~/.zshrc instead of ~/.bashrc)
echo "export PATH=\"$PWD/bin:\$PATH\"" >> ~/.bashrc
```

Source: <https://prover9.org/manual-2026/install.html>.

### Check

From this folder (`exercises/lecture1/en/`):

```sh
python p9.py check
```

```
Prover9 program: C:\Program Files (x86)\Prover9-Mace4\bin-win32\prover9.exe
Version:         Prover9 (32) version Dec-2007, Dec 2007.
Socrates test:   exit code 0 -> OK
```

`p9.py` looks for Prover9 in this order: the variable `PROVER9_BIN`, a `prover9` on your `PATH`,
the Windows package above, the program inside `pyprover9`.

## Running Prover9

By hand:

```sh
prover9 -f files/socrates.in > socrates.out
echo $?                     # Linux, macOS (PowerShell: $LASTEXITCODE)
```

With the helper (Python standard library only):

| Command | What it does |
|---|---|
| `python p9.py run FILE.in` | one run: exit code, its meaning, the proof |
| `python p9.py label FILE.in` | two runs (the goal, then its negation): `True`, `False` or `Uncertain` |
| `python p9.py experiment FOLDER --gold GOLD.csv --out results.csv` | every `.in` file of a folder, one line each, compared with gold labels |

`p9.py` adds two lines in front of every file: a time limit `assign(max_seconds, 10).` and
`clear(auto_denials).` (see the slide "A trap: a proof, and exit code 2").

### Exit codes

| Code | Meaning |
|---|---|
| 0 | `THEOREM PROVED`: the goal follows from the assumptions |
| 1 | error in the file (syntax, arity, non-ASCII character...) |
| 2 | `SEARCH FAILED` (sos_empty): the search finished, the goal does not follow from these assumptions |
| 4 | `SEARCH FAILED` (max_seconds): time out, we do not know |
| 3, 5, 6 | another limit reached (memory, given clauses, kept clauses): we do not know |

## The notebook

`lecture1.ipynb` follows the exercises of this lecture step by step, in this folder. Install Jupyter
once, from this folder:

```sh
pip install -r ../../requirements.txt
jupyter notebook lecture1.ipynb
```

Run the cells from top to bottom. The cells marked ✏️ are for you: replace every `???`, then run the
cell; your files go to the folder `work/`. The same exercises can also be done with the files and
the commands below.

## The files

| File | What it is |
|---|---|
| `files/socrates.in` | the first example, complete |
| `files/example_lewandowski.in` | the worked example of the slides (FOLIO example 240), complete |
| `files/demo_timeout.in` | a search stopped after 2 seconds (exit code 4), complete; with LADR-2026-8A, sometimes code 1 instead (an internal error of that version, not of the file) |
| `ex1_formulas.txt` | Exercise 1: 14 sentences to write as Prover9 formulas; check with `python check_formulas.py` |
| (copies of `files/socrates.in`) | Exercise 2: predict, then run |
| `files/ex3_all_some.in` | Exercise 3: "all" and "some" |
| `files/ex4_quantifier_order.in` | Exercise 4: the order of quantifiers |
| `files/ex5_galette.in` | Exercise 5: the galette des rois |
| `files/ex6_experiment/` | Exercise 6: 10 FOLIO problems (`problems/*.in`, 5 to translate) and `gold.csv` |
| `files/bonus_consistency.in` | Bonus: is a text consistent? |
| `p9.py` | helper: check, run, label, experiment |
| `check_formulas.py` | the checker of Exercise 1 |

In the files to complete, replace every `???`. As long as a `???` remains, Prover9 reports an
error (exit code 1).

The checker of Exercise 1 compares your formula with the expected one **by asking Prover9**:
any formula that is logically equivalent is accepted. `too strong`: your formula says more than
the sentence; `too weak`: it says less.

## Translation reminders

- `all` goes with `->`, `exists` goes with `&`.
- A name that starts with `u`, `v`, `w`, `x`, `y` or `z` and has no quantifier is a **variable**:
  `colleague(victor, lea).` means "everybody is a colleague of Lea". Rename: `p_victor`.
- One arity per symbol, ASCII only, a period after each formula, one goal per file.
- "All A are B" does not say that an A exists.
