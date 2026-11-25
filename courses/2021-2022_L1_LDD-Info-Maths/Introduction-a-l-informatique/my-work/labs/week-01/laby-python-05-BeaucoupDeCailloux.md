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

# Beaucoup de cailloux

Le même principe que tout à l'heure mais un peu plus diffile ! Là encore, la taille du labyrinthe varie !

```{code-cell} ipython3
from laby.global_fr import *
from random import randint
l = randint(1,20)
carte = "o " + "o " * (l + 3) + "o\n"
carte+= "o " + "→ " + ". " + "r " * l + ". " + "x\n"
carte+= "o " + "o " * (l + 3) + "o\n"
Laby(carte = carte)
```

```{code-cell} ipython3

```
