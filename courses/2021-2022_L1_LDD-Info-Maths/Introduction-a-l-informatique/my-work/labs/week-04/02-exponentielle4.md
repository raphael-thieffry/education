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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6028503cbab1f8d461036925bc3e8702", "grade": false, "grade_id": "cell-9aacd071eecda33d", "locked": true, "schema_version": 3, "solution": false}}

# TP: Implanter la fonction exponentielle (4/5)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bdfc060b3b76cb80649318d032bdab20", "grade": false, "grade_id": "cell-fd5a373907e22622", "locked": true, "schema_version": 3, "solution": false}}

## Partie 4  : Calcul de l'exponentielle avec une précision relative fixée ♣

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "035bf09e6f9057ebe62fc529bac4c120", "grade": false, "grade_id": "cell-0749edc234488c4e", "locked": true, "schema_version": 3, "solution": false}}

Vous aviez implanté une fonction `expRang` qui calcule une approximation de l'exponentielle en tronquant la somme à un certain rang décidé à l'avance. Cependant le rang nécessaire pour obtenir une bonne précision dépend du réel $x$ pour lequel on veut calculer $e^x$. On cherche maintenant à calculer une approximation de l'exponentielle en fixant la *précision* et non plus le rang. Pour cela on va écrire une nouvelle fonction d'approximation de l'exponentielle, dans laquelle le rang auquel on arrête la somme ne sera pas décidé à l'avance, mais dépendra de l'évolution du calcul qu'on est en train de faire.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b0e19c7fe2db8a17967b3cd5009f356a", "grade": false, "grade_id": "cell-3e4cb5925b030399", "locked": true, "schema_version": 3, "solution": false}}

Commencez par copier-coller dans les quatre cellules suivantes vos fonctions `puissance` et `factorielle` de la [partie 1](02-exponentielle1.md) ainsi que `abs` et `egal` de la [partie 3](02-exponentielle3.md):

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6164c09ae19d35cada09bfe47f2d2885
  grade: false
  grade_id: cell-26c2f80b0554f206
  locked: false
  schema_version: 3
  solution: true
---
double puissance(double x, int n) {
    double resultat = x;
    if(n!=0){
        for(int i=1; i<n; i++){
                resultat = resultat*x;
            }
        return resultat;
    }else{
        double un=1;
        return un;
    }
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 83e1148ea96c3a4f01d968121397cb4b
  grade: false
  grade_id: cell-7e5ba48349f32c00
  locked: false
  schema_version: 3
  solution: true
---
double factorielle(int n) {
    double resultat = 1;
    for(int i=1; i<=n; i++){
        resultat = resultat*i;
    }
    return resultat;
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 449d66382045a52a7718ce52c81a3d61
  grade: false
  grade_id: cell-40ce2ba5515a4b3f
  locked: false
  schema_version: 3
  solution: true
---
double abs(double a) {
    if (a > 0) {
        return a;
    } else {
        return -a;
    }
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: fbe0949f6693e012a0462dbdd4d748a6
  grade: false
  grade_id: cell-5658ebbda24de111
  locked: false
  schema_version: 3
  solution: true
---
bool egal(double x, double y, double eps){
    if(abs(x-y)<eps*abs(x)){
        return true;
    }
    else{
        return false;
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bfece4b5e757b01ae9127e2e0443bc09", "grade": false, "grade_id": "cell-d6b02ebdc5e27637", "locked": true, "schema_version": 3, "solution": false}}

Implantez une nouvelle fonction d'approximation de l'exponentielle qui somme les valeurs $\frac{x^i}{i!}$ jusqu'à ce que le résultat soit égal au précédent par rapport à la précision donnée:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: d45da285fab73ed31030894f6761b6e4
  grade: false
  grade_id: cell-5b6857150b2f0d95
  locked: false
  schema_version: 3
  solution: true
---
/** Calcul de la fonction exponentielle à precision fixée
 * @param x un nombre de type double
 * @param epsilon un nombre de type double
 * @return e^x avec précision epsilon
**/
double expPrecision(double x, double epsilon) {
    double exp=1;
    double ancExp;
    int i = 1;
    while(egal(ancExp, exp, epsilon) == false){
        ancExp = exp;
        exp = exp+(puissance(x,i)/factorielle(i));
        i++;
    }
    return exp;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c181420de39a3d84a7aa9da1c4024f6a
  grade: false
  grade_id: cell-acdedc110ac3a389
  locked: true
  schema_version: 3
  solution: false
  task: false
---
double epsilon = 0.000000001
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b6ff2b8ec9842c0de79e25ba0da4687c", "grade": false, "grade_id": "cell-83bc9f0ce83996e3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Le calcul suivant devrait renvoyer 2,718282:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 14805f291bc97cc06f4686c02635b0e1
  grade: false
  grade_id: cell-7c1f3a734b045e42
  locked: true
  schema_version: 3
  solution: false
---
expPrecision(1, epsilon)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5c0196e93f76ed9b14c58183c242195e", "grade": false, "grade_id": "cell-76536f0d66f087bc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Il n'y a pas forcément suffisament de chiffres significatifs affichés pour le vérifier. Faisons à la place un test:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ad957b9ca19bfdf630932a057e9e330f
  grade: true
  grade_id: cell-f21a4cde086edd2b
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( abs( expPrecision(1, epsilon) - 2.718282 ) < 1e-6 )
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ae1b6280dc9302354beee16c9d1bc0da
  grade: true
  grade_id: cell-4fb64a4278d2ce62
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( abs( expPrecision(5, epsilon) - 148.413159 ) < 1e-6 )
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: cf6fbf520ac152ac56303b9b4d622ef6
  grade: true
  grade_id: cell-9841d2b60ca74549
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( abs(expPrecision(3, epsilon) - 20.085537 ) < 1e-6 )
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b738d9b918e7ce9c5368d4baa51f02a7", "grade": false, "grade_id": "cell-f14c9177d33e54ce", "locked": true, "points": 1, "schema_version": 3, "solution": false, "task": true}}

Comparez vos résultat avec la fonction `exp` de C++ définie dans `cmath`

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2537f1aeb98505f096c75097b9b62f85
  grade: false
  grade_id: cell-2586899de62aebf4
  locked: true
  schema_version: 3
  solution: false
---
#include <cmath>
```

```{code-cell}
exp(5)
```

```{code-cell}
exp(3)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9c41f6e79d5b8a3a288214ba74592b17", "grade": false, "grade_id": "cell-9b25311fb953a3d7", "locked": true, "schema_version": 3, "solution": false}}

## Bilan de la partie 4
Très bien, vous avez implanté le calcul de la fonction exponentielle à précision fixée. Maintenant étudions sa performance en calculant son temps d'exécution:

```{code-cell}
%timeit expPrecision(10, 0.00000001);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5e622db0fba2ba43245fd90dbf6c5e2f", "grade": false, "grade_id": "cell-44bb7d35a9655256", "locked": true, "schema_version": 3, "solution": false}}

 Dans la [partie 5](02-exponentielle5.md), vous tenterez d'optimiser cette implantation.
