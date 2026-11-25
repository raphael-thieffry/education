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

# On regarde devant soi

Ici, plus de caillou. La fourmi doit parcourir un long couloir, comment faire ?

```{code-cell} ipython3
from laby.global_fr import *
Laby(niveau="2a")
```

```{code-cell} ipython3

```

Il est bien sûr possible de copier plusieurs fois la commande `avance()` mais il existe de meilleures solutions.

Ci dessous, on introduit une nouvelle commande et on vous montre un exemple d'utilisation


    regarde();      // Renvoie Vide, Caillou, Mur, Toile ou Sortie
                    // selon ce qui se trouve sur la case devant la fourmi

```{code-cell} ipython3
from laby.global_fr import *
carte = """
o o o
o ↓ x
o o o
"""
Laby(carte=carte)
```

```{code-cell} ipython3
while regarde() == Mur:
    droite()
ouvre()
```

La fonction `regarde()` permet de "regarder" ce qui est devant la fourmi, elle renvoie un objet python décrivant la case que l'on peut comparer à plusieurs variables prédéfinies.

```{code-cell} ipython3
Mur
```

```{code-cell} ipython3
Vide
```

```{code-cell} ipython3
Caillou
```

```{code-cell} ipython3
Mur
```

```{code-cell} ipython3
Toile
```

```{code-cell} ipython3
Sortie
```

On utilise ensuite une boucle `while` ce qui signifie `Tant que`

    while condition:
        instructions

Signifie : Tant que `condition` est vraie, on répète les `instructions`. Dans l'exemple précédent, le programme signifie "Tant que la fourmi regarde un mur, tourner à droite"

Ci-dessous un autre exemple

```{code-cell} ipython3
from laby.global_fr import *
carte = """
o o o
o ↓ x
o r o
o o o
"""
Laby(carte=carte)
```

```{code-cell} ipython3
while regarde() != Sortie:
    droite()
ouvre()
```

Ici le `!=` signifie "est différent de". Le programme se traduit donc par : "Tant que la fourmi ne regarde pas la porte, tourner à droite. Puis ouvrir la porte.". 

Attention aux détails :
* on met toujours ":" après la condition
* les instructions (pour l'instant une seule mais on peut en mettre plusieurs) s'écrivent sous le while en "indentant" le début des lignes avec 4 espaces
* ce qui est écrit au même nieau que le `while` (dans l'exemple, le `ouvre()`) s'exécute quand on est sorti de la boucle

En vous inspirant de ces exemples, résolvez le problème suivant, attention la taille du couloir n'est pas fixée ! Votre programme doit fonctionner dans tous les cas (exécutez plusieurs fois la cellule créant le labyrinthe, votre programme doit continuer de marcher.

```{code-cell} ipython3
from laby.global_fr import *
from random import randint
l = randint(2,20)
carte = "o " + "o " * l + "o\n"
carte+= "o " + "→ " + ". " * (l-1) + "x\n"
carte+= "o " + "o " * l + "o\n"
Laby(carte = carte)
```

```{code-cell} ipython3

```

```{code-cell} ipython3

```
