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

# Compter

Le but à présent n'est plus que de sortir du labyrinthe mais aussi de compter les cailloux et de stocker le résultat dans la variable $nbcailloux$

```{code-cell}
from laby.global_fr import *
Laby(lignes = 1, colonnes = 10, option = "rocks")
```

```{code-cell}
nbcailloux = 0

```

```{code-cell}
nbcailloux # doit afficher le nombre de cailloux (calculé au dessus)
```

Pareil mais ici, on veut compter les cailloux ET les toiles

```{code-cell}
from laby.global_fr import *
Laby(lignes = 1, colonnes = 10, option = "rocksAndWebs")
```

```{code-cell}
nbcailloux = 0
nbwebs = 0

```

```{code-cell}
nbcailloux
```

```{code-cell}
nbwebs
```

```{code-cell}

```
