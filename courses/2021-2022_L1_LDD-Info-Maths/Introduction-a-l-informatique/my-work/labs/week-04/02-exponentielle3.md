---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++11
  language: C++11
  name: xcpp11
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "29b838de9b432f816f41b501737820c1", "grade": false, "grade_id": "cell-ffce5d69407bd085", "locked": true, "schema_version": 3, "solution": false}}

# TP: Implanter la fonction exponentielle (3/5)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a64f39a6b2890335f3eb64637915060d", "grade": false, "grade_id": "cell-ba70cc528a726649", "locked": true, "schema_version": 3, "solution": false}}

## Partie 3 : Comparaison de nombres flottants et précision relative

Sur les nombres flottants (`float` ou `double`) l'opérateur `==` n'est pas toujours très fiable à cause des erreurs d'arrondis:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1e636b99e82d325870440aed2894f08c
  grade: false
  grade_id: cell-357388e8811e8887
  locked: true
  schema_version: 3
  solution: false
---
1.0 + 1e20 - 1e20 == 1e20 - 1e20 + 1.0
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6d63a15e4288192f852cd08a31a0aeaf", "grade": true, "grade_id": "cell-2ba595671ff56d54", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

Exécutez les 5 cellules suivantes. Que constatez-vous ?

Il affiche une valeur arrondie de b, mais sait que b=/=16.0000, d'où a=/=b

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0aa154808a718050f75784ffd1e85186
  grade: false
  grade_id: cell-9822d857d4e81d79
  locked: true
  schema_version: 3
  solution: false
---
double a,b;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c20e8d87557a1145821afa8bdbd569fa
  grade: false
  grade_id: cell-d98a79aa643b191e
  locked: true
  schema_version: 3
  solution: false
---
a = 16;
b = 15.99999999999;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e91e01eba95383e91c63ae2b9fbf812d
  grade: false
  grade_id: cell-14c516a6791b2309
  locked: true
  schema_version: 3
  solution: false
---
a
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b80af210b01b89dea73d35fcd75ac953
  grade: false
  grade_id: cell-e1b28a8439e86689
  locked: true
  schema_version: 3
  solution: false
---
b
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: eb4acdc9ae85cfdafcb2d462375eccbb
  grade: false
  grade_id: cell-659691632843cfcb
  locked: true
  schema_version: 3
  solution: false
---
(a == b)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cd186c3034793ab0bd41f840be33b6ca", "grade": false, "grade_id": "cell-5017bdc388a2f6c4", "locked": true, "schema_version": 3, "solution": false}}

### Définition: *précision relative*
Aussi, chaque fois que l'on veut comparer deux nombres flottants, il faut spécifier avec quelle **précision** on veut les comparer. Comme on manipule certaines fois des nombres très grands et d'autres fois des nombres très petits, ce qui compte c'est la précision relative: le nombre de chiffres significatifs en communs.

Par exemple, si on veut comparer $x$ et $y$ avec une précision relative de cinq chiffres significatifs, on prendra $\varepsilon=10^{-5}=0,00001$, et on dira que $x$ est égal à $y$ à $\varepsilon$ près si:

$$ |x - y| < \varepsilon|x| \qquad \text{et} \qquad |x - y| < \varepsilon |y|$$

Moralement: la différence entre $x$ et $y$ est négligeable devant $x$ et devant $y$.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "99ca800ddd5223ccf0703a31ab738d55", "grade": false, "grade_id": "cell-55c9c5c79654d21b", "locked": true, "schema_version": 3, "solution": false}}

### Implantation
Implantez les deux fonctions suivantes dont on vous donne la documentation :
 * `abs` mais qui prend cette fois en paramètre un `double` et retourne un `double`
 * `egal` qui prend en paramètre les nombres $x$, $y$ et $\varepsilon$.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 7ad58ca1f06adf262b7fc77d33e2e7f7
  grade: false
  grade_id: cell-aa46c278f72ba400
  locked: false
  schema_version: 3
  solution: true
---
/** Valeur absolue pour type double
 * @param x un nombre de type double
 * @return la valeur absolue de x
**/
double abs(double a) {
    if (a > 0) {
        return a;
    } else {
        return -a;
    }
}
```

```{code-cell}
abs(-1.5)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7f53fec20e48a1316dcfdd00e15f8439
  grade: true
  grade_id: cell-abf252519d9a3950
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( abs(-1.5) == 1.5 );
CHECK( abs( 2.2) == 2.2 );
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1a8ce3571e39cfe79ea449331138c6c9
  grade: false
  grade_id: cell-f6efe81b76dfe516
  locked: false
  schema_version: 3
  solution: true
---
/** Égalité entre deux flottants avec précision relative
 * @param x un nombre de type double
 * @param y un nombre de type double
 * @param epsilon un nombre de type double
 * @return true si la valeur absolue de x - y est plus petite que epsilon * |x| et que epsilon * |y|
**/
bool egal(double x, double y, double eps){
    if(abs(x-y)<eps*abs(x)){
        return true;
    }
    else{
        return false;
    }
}
```

```{code-cell}
egal(15.999999, 16,0.00001)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0f578ae8c14b5acd577ddfcd5e49e9cc
  grade: true
  grade_id: cell-da8592649f3234ef
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( egal(15.999999, 16, 0.00001) == true  );
CHECK( egal(15.99, 16, 0.00001)     == false );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "32c93f4ba662cafc128c21462410cad9", "grade": false, "grade_id": "cell-29e58e1837c86ada", "locked": true, "schema_version": 3, "solution": false}}

Trouvez des valeurs de `epsilon` telles que les nombres ci-dessous soient considérés comme égaux par `egal`:

```{code-cell}
egal(15, 16, 0.001)
```

```{code-cell}
egal(0.0001, 0.002, 0.00001)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a1a220b4380b467735d1926fd32fdf4c", "grade": true, "grade_id": "cell-fd99a546db74023d", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

Que se passe-t-il lorsque $x$ ou $y$ valent 0 ?

false

```{code-cell}
egal(0.00001, 0, 0.0000001)
```

## Bilan de la partie 3
Maintenant que la notion de précision relative est bien définie, et que vous avez implanté la comparaison de nombres flottants avec une précision relative fixée, vous pouvez passer à la [partie 4](02-exponentielle4.md).
