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

# Avec un caillou

On rajoute une petite difficulté. Il faut maintenant déplacer le caillou qui se trouve en travers du chemin. On a de nouvelles commandes possibles :

    prend()        // Prend le caillou situé sur la case devant la fourmi
    pose()         // Pose le caillou devant la fourmi

Et bien sûr toujours

    avance()       // Fait un pas vers l'avant
    droite()       // Fait pivoter la fourmi vers la droite
    gauche()       // ou la gauche
    ouvre()        // Ouvre la porte située devant la fourmi (fin du niveau)
    
**Remarque** : la fourmi ne peut pas ouvrir la porte si elle porte le caillou

```{code-cell} ipython3
from laby.global_fr import *
Laby(niveau="1b")
```

```{code-cell} ipython3

```
