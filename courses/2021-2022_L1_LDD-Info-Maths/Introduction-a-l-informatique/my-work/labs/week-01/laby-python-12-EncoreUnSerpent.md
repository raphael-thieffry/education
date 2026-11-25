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

# Encore un serpent

Il faut parcourir ce labyrinthe en serpent mais le nombre de lignes et de colonnes varie !

```{code-cell}
from laby.global_fr import *
from random import randint
n = randint(0,3)
m = randint(2, 20)
bloc_porte = "o " + "o " * m + "o\n"
bloc_porte+= "o " + ". " * m + "x\n"
bloc_porte+= "o . " + "o " * m + "\n"

bloc1 = "o " + ". " * m + "o\n"
bloc1+= "o " * m + ". o\n"

bloc2 = "o " + ". " * m + "o\n"
bloc2+= "o . " + "o " * m + "\n"

bloc_fourmi = "o " + "→ " + ". " * (m-1) + "o\n"
bloc_fourmi+= "o " + "o " * m + "o\n"

carte = bloc_porte + bloc1 + (bloc2 + bloc1) *n + bloc_fourmi
Laby(carte = carte)
```

```{code-cell}

```

```{code-cell}

```
