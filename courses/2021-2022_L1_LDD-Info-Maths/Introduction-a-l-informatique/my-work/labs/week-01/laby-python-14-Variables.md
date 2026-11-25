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

# Variables

En python, il est possible de stocker de l'information dans des variables

```{code-cell}
a = 3
```

```{code-cell}
a
```

```{code-cell}
a + 1
```

```{code-cell}
b = 5
```

```{code-cell}
if a > b:
    print("le max est ", a)
else:
    print("le max est ", b)
```

Dans le labyrinthe suivant, la position de la porte est stockée dans deux variables : $x$ et $y$

```{code-cell}
from laby.global_fr import *
from random import randint

x = randint(0,9)
y = randint(1,9)

carte = "o "*12 + "\n"
for i in range(9):
    carte += "o "
    for j in range(10):
        if x == j and y == (9 - i):
            carte += "x "
        else:
            carte += ". "
    carte += "o\n"
carte+= "o → " + ". " * 9 + "o \n"
carte+= "o "*12 + "\n"
Laby(carte = carte)
```

La position de la porte est donnée par

```{code-cell}
x
```

```{code-cell}
y
```

Comment sortir du labyrinthe ?

```{code-cell}

```
