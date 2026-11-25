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

# Challenge

La commande ci-dessous crée un labyrinthe aléatoire. Il y a toujours un chemin vers la sortie et aucune boucle. Pouvez-vous écrire un programme qui vous sortira à tous les coup du labyrinthe ?

+++

## On commence petit...

```{code-cell} ipython3
from laby.global_fr import *
Laby(lignes = 2, colonnes = 2)
```

```{code-cell} ipython3
def mur():
    if regarde() == Mur:
        droite()
        if regarde() == Mur:
            gauche();
            gauche();
while regarde() != Sortie:
    mur()
    avance()
ouvre()
```

```{code-cell} ipython3
from laby.global_fr import *
Laby(lignes = 3, colonnes = 3)
```

```{code-cell} ipython3
while regarde() != Sortie:
    droite()
    if regarde() == Vide:
        avance()
    else:
        gauche()
        if regarde() == Vide:
            avance()
        else:
            gauche()
            if regarde() == Vide:
                avance()
            else:
                gauche()
                avance()
ouvre()
```

## Le vrai challenge

```{code-cell} ipython3
from laby.global_fr import *
Laby(lignes = 8, colonnes = 8)
```

```{code-cell} ipython3
while regarde() != Sortie:
    droite()
    if regarde() == Vide:
        avance()
    else:
        gauche()
        if regarde() == Vide:
            avance()
        else:
            gauche()
            if regarde() == Vide:
                avance()
            else:
                gauche()
                avance()
ouvre()
```

## Encore plus de challenge !

Il est possible de rajouter des options pour avoir des cailloux et des toiles !

Par exemple :

```{code-cell} ipython3
from laby.global_fr import *
Laby(lignes = 8, colonnes = 8, option = "fullRocks")
```

```{code-cell} ipython3
def caillou():
    prend()
    avance()
    a = 0
    while regarde()==Mur or regarde() == Caillou or regarde() == Sortie:
        droite()
        a=a+1
    pose()
    for i in range(a, 4):
        droite()
while regarde() != Sortie:
    droite()
    if regarde() == Sortie:
                break
    if regarde() == Caillou:
        caillou()
        if regarde() == Sortie:
            break
    else:
        gauche()
        if regarde() == Caillou:
            caillou()
            if regarde() == Sortie:
                break
        else:
            gauche()
            if regarde() == Caillou:
                caillou()
                if regarde() == Sortie:
                    break
            else:
                gauche()
                caillou()
                if regarde() == Sortie:
                    break
    
ouvre()
```

Options possible : rocks, webs, fullRocks, fullWebs, rocksAndWebs, fullRocksAndWebs
