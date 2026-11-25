---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

# TP: Implanter les fonctions sinus et cosinus ♣

+++

Il est possible de calculer les fonctions sinus et cosinus de manière
analogue à l'exponentielle, avec les formules suivantes ($x$ est un
angle en radians):

$$\begin{aligned}
    \cos(x) &= 1 - \frac{x^2}{2!} + \frac{x^4}{4!} - \frac{x^6}{6!} + \dots = \sum_{n=0}^{\infty} (-1)^n\frac{x^{2n}}{(2n)!}\\
    \sin(x) &= x - \frac{x^3}{3!} + \frac{x^5}{5!} - \frac{x^7}{7!} + \dots = \sum_{n=0}^{\infty} (-1)^{n}\frac{x^{2n+1}}{(2n+1)!}
  \end{aligned}$$

1.  Copier-collez ici vos fonctions `abs`, `egal`, `factorielle` et `puissance`

```{code-cell}

```

2. Implantez des
   fonctions `sinPrecision` et `cosPrecision` sur le modèle de votre
   fonction `expPrecision`.

```{code-cell}

```

3.  Testez vos deux fonctions et comparez avec les fonctions `sin` et
    `cos` de `cmath`.

```{code-cell}

```

4.  Implantez des fonctions `sinRapide` et `cosRapide` qui n'utilisent
    pas les fonctions `puissance` et `factorielle`.

```{code-cell}

```
