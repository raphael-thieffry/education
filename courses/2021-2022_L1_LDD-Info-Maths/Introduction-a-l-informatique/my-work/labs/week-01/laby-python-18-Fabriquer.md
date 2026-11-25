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

# Fabriquer

Vous pouvez utiliser les variables pour écrire des programmes qui fabriquent des labyrinthes !

Vous pouvez dessiner la carte et jouer avec vos propres labyrinthes.

Les symboles (à séparer par des espaces) :

    o               un mur
    .               une case vide
    ↑ → ↓ ←         la fourmi
    x               la porte
    r               un caillou
    R               un caillou aléatoire
    w               une toile
    W               une toile aléatoire

```{code-cell} ipython3
from laby.global_fr import *
carte ="""
o o o o o o o o
o . . . r o w x
o . o o . o . o
o ↑ . . . . . o
o o o o o o o o
"""
Laby(carte = carte)
```

```{code-cell} ipython3

```

Un labyrinthe peut être créé à partir d'une chaîne de caractère.

En python, on peut stocker les chaines dans des variables, les aditionner, les multiplier...

```{code-cell} ipython3
c = ". "
print(c)
```

```{code-cell} ipython3
deux_c = c + c
print(deux_c)
```

```{code-cell} ipython3
ligne = c * 10
print(ligne)
```

pour mettre deux lignes à la suite, il faut les séparer par le caractère de retour à la ligne `\n`

```{code-cell} ipython3
deux_lignes = ligne + "\n" + ligne
print(deux_lignes)
```

Que fait le programme suivant ?

```{code-cell} ipython3
murs = "o " * 12 + "\n"
ligne = "o " + ". " * 10 + "o \n"
carte = murs + ligne * 10 + murs
print(carte)
```

Cette carte n'est pas correcte car elle ne contient pas de fourmi ni de porte.

Copiez le programme et modifiez le pour ajouter la fourmi et la porte. Puis lancez le "vrai" labyrinthe avec la commande `Laby(carte = carte)`

```{code-cell} ipython3

```

```{code-cell} ipython3

```

Vous pouvez utiliser toutes les notions précédentes (boucles, if, variables, fonctions, etc.) pour fabriquer les labyrinthe et non plus seulement les résoudre.

* Pouvez-vous faire un serpent ?
* Une spirale ? 
* Un damier ?
* Une forme de votre choix ?

```{code-cell} ipython3

```
