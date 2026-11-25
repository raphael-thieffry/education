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

# Premier exercice

Exécutez la cellule ci-dessous puis écrivez et exécutez le programme qui permet à la fourmi de sortir du labyrinthe. 

Vous pouvez utilisez les commandes suivantes :

    avance()       // Fait un pas vers l'avant
    droite()       // Fait pivoter la fourmi vers la droite
    gauche()       // ou la gauche
    ouvre()        // Ouvre la porte située devant la fourmi (fin du niveau)

```{code-cell} ipython3
from laby.global_fr import *
Laby(niveau="1a")
```

```{code-cell} ipython3
droite()
avance()
avance()
avance()
gauche()
avance()
avance()
ouvre()
```

```{code-cell} ipython3

```
