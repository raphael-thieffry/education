---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

# Toiles Et cailloux

Quand il y a une toile, on peut la recouvrir d'un caillou

```{code-cell}
from laby.global_fr import *
carte = """
o o o o o o
o → . r w x
o o o o o o
"""
Laby(carte = carte)
```

```{code-cell}
avance()
prend()
avance()
pose()
prend()
droite()
droite()
pose()
droite()
droite() 
avance()
ouvre()
```

Comment résoudre le labyrinthe suivant ?

Attention, le nombre de cailloux / toiles varie !

```{code-cell}
from laby.global_fr import *
Laby(lignes = 1, colonnes = 10, option="rocksAndWebs")
```

```{code-cell}

```
