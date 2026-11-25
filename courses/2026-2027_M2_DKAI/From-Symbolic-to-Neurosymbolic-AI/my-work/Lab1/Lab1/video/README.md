# Videos / Vidéos

| File | Lecture | Language |
|---|---|---|
| `prover9_tutorial_en.mp4` | 1: Prover9 step by step | English captions |
| `prover9_tutorial_fr.mp4` | 1 : Prover9 pas à pas | sous-titres en français |
| `lecture2_tutorial_en.mp4` | 2: a language model as translator | English captions |
| `lecture2_tutorial_fr.mp4` | 2 : un modèle de langage comme traducteur | sous-titres en français |

Each video has its captions as a subtitle file with the same name (`.srt`). Captions only, no
voice. / Chaque vidéo a ses sous-titres dans un fichier du même nom (`.srt`). Sous-titres
seulement, sans voix.

The windows, the files, the prompts and the program output are in English in all videos. /
Les fenêtres, les fichiers, les prompts et les sorties des programmes sont en anglais dans toutes
les vidéos.

## English

### Lecture 1: Prover9 step by step (about 5 minutes)

**Part 1, the Prover9-Mace4 window.**
1. The *Formulas* tab: type the assumptions, then the goal.
2. *Well Formed?* checks the syntax.
3. Set the time limit and click *Start* under Prover9: the proof window opens (`deny`, `$F`).
4. *Show Current Input*: the text sent to Prover9 is exactly a `.in` file.
5. Delete the premise `man(socrates).` and run again: *Exhausted*, exit code 2.
6. *Start* under Mace4: a counter-model with two objects.
7. *File > Save Input* saves the formulas as a `.in` file.

**Part 2, the command line.**
1. `Get-Content files\socrates.in`: an input file.
2. `prover9 -f files\socrates.in > socrates.out`, then `$LASTEXITCODE`: 0.
3. `Select-String` finds the negated goal and `$F` in the output.
4. A file that still contains `???`: exit code 1 and the `%%ERROR` line.
5. `python p9.py check`, `run`, `label`.
6. `files\demo_timeout.in`: exit code 4 after 2 seconds.

### Lecture 2: a language model as translator (about 2 minutes)

1. `ollama list`, then a first question with `ollama run`.
2. `python nl2p9.py check`: Prover9, Ollama and the model answer.
3. `problems\p05.txt`, then `nl2p9.py translate` with `prompts\rules.txt`: the answer of the
   model, the formulas in `out\p05.in`, the label; `p9.py label out\p05.in` gives the same label.
4. `problems\p26.txt` with `--normalize`: Prover9 cannot read formula 2, status `ERROR`.
5. The same with `--refine 2`: the error message goes back to the model, which answers again.
   Read its new formula 2.
6. `nl2p9.py experiment` on the 30 problems.

The answers of the model in this video were recorded before (the folder `cache/`), so they
appear at once.

## Français

### Cours 1 : Prover9 pas à pas (environ 5 minutes)

**Partie 1, la fenêtre Prover9-Mace4.**
1. L'onglet *Formulas* : tapez les hypothèses, puis le but.
2. *Well Formed?* vérifie la syntaxe.
3. Fixez la limite de temps et cliquez sur *Start* sous Prover9 : la fenêtre de preuve s'ouvre
   (`deny`, `$F`).
4. *Show Current Input* : le texte envoyé à Prover9 est exactement un fichier `.in`.
5. Supprimez la prémisse `man(socrates).` et relancez : *Exhausted*, code de sortie 2.
6. *Start* sous Mace4 : un contre-modèle à deux objets.
7. *File > Save Input* enregistre les formules dans un fichier `.in`.

**Partie 2, la ligne de commande.**
1. `Get-Content files\socrates.in` : un fichier d'entrée.
2. `prover9 -f files\socrates.in > socrates.out`, puis `$LASTEXITCODE` : 0.
3. `Select-String` trouve le but nié et `$F` dans la sortie.
4. Un fichier qui contient encore `???` : code de sortie 1 et la ligne `%%ERROR`.
5. `python p9.py check`, `run`, `label`.
6. `files\demo_timeout.in` : code de sortie 4 après 2 secondes.

### Cours 2 : un modèle de langage comme traducteur (environ 2 minutes)

1. `ollama list`, puis une première question avec `ollama run`.
2. `python nl2p9.py check` : Prover9, Ollama et le modèle répondent.
3. `problems\p05.txt`, puis `nl2p9.py translate` avec `prompts\rules.txt` : la réponse du modèle,
   les formules dans `out\p05.in`, l'étiquette ; `p9.py label out\p05.in` donne la même étiquette.
4. `problems\p26.txt` avec `--normalize` : Prover9 ne peut pas lire la formule 2, statut `ERROR`.
5. La même commande avec `--refine 2` : le message d'erreur retourne au modèle, qui répond de
   nouveau. Lisez sa nouvelle formule 2.
6. `nl2p9.py experiment` sur les 30 problèmes.

Les réponses du modèle dans cette vidéo ont été enregistrées auparavant (le dossier `cache/`) :
elles s'affichent tout de suite.
