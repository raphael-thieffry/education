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

# Comptons les cailloux

Regardez l'exemple suivant, on utilise une boucle `for` qui permet de répéter une action un nombre donné de fois.

```{code-cell}
from laby.global_fr import *
carte = """
o o o o o x o o o
o → . r r r r r o
o o o o o o o o o
"""
Laby(carte = carte)
```

```{code-cell}
avance()
for i in range(3):
    prend()
    droite()
    droite()
    pose()
    droite()
    droite()
    avance()
gauche()
ouvre()
```

De la même façon, résolvez le labyrinthe suivant

```{code-cell}
from laby.global_fr import *
Laby(niveau = "counting-the-rocks")
```

```{code-cell}

```
