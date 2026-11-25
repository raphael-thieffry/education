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

# Si si si !

Regardez l'exemple de ce petit programme où l'on introduit le `if` (si) pour tester une condition

```{code-cell} ipython3
from laby.global_fr import *
from random import randint
c = "r " if randint(0,1) == 1 else ". "
carte = "o o o o\n"
carte+= "o → " + c + " x\n"
carte+= "o o o o\n"
Laby(carte = carte)
```

```{code-cell} ipython3
if regarde() == Caillou:
    prend()
    avance()
    gauche()
    gauche()
    pose()
    droite()
    droite()
else:
    avance()
ouvre()
```

Ci-dessous, la grande toile bloque le passage mais pas la petite toile : elles ne sont pas toujours au même endroit. Utilisez `if` et `regarde()` pour trouver le bon passage.

    ???
    if regarde() == Toile:
        ???
    else:
        ???

```{code-cell} ipython3
from laby.global_fr import *
Laby(niveau = "3a")
```

```{code-cell} ipython3

```

```{code-cell} ipython3

```

```{code-cell} ipython3

```

```{code-cell} ipython3

```
