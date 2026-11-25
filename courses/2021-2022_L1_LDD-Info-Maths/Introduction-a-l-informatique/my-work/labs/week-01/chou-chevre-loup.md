---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "33eb995cea5b47c3e2f11187c2f245cc", "grade": false, "grade_id": "cell-b5e341b0d197b93b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Chou chèvre loup
Faites traverser la rivière au chou, loup et chèvre,
sans laisser le loup seul avec la chèvre, ou la chèvre
seule avec le chou!

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7dab1af341eb1d1980e963b4395d57e8
  grade: false
  grade_id: cell-1011ecb37be8a8c9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
from ipywidgets_game_wolf_goat_cabbage.__global__.fr import *
charge = monter; traverse = traverser; décharge = descendre
JEUX()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3185e1ee63e16138964cd98c3243e523
  grade: false
  grade_id: cell-f0dcd60af1b24691
  locked: false
  schema_version: 3
  solution: true
  task: false
---
reset()
charge("Loup")
charge("Chou")
traverse()
décharge("Loup")
décharge("Chou")
traverse()
charge("Chèvre")
traverse()
décharge("Chèvre")
# YOUR CODE HERE
raise NotImplementedError()
```

```{code-cell} ipython3

```

```{code-cell} ipython3

```
