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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2336ce41264c40d8c512d8e2fe046ad0", "grade": false, "grade_id": "cell-a5a96caf0e3314b2", "locked": true, "schema_version": 3, "solution": false}}

# TP: Implanter la fonction exponentielle (5/5)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "eb0107dc461b68a5cba9235d0a19ce08", "grade": false, "grade_id": "cell-bc097d26c9102dde", "locked": true, "schema_version": 3, "solution": false}}

## Partie 5 : Optimisation ♣

Dans ce cas précis, il n'est pas très efficace de réutiliser les fonctions `puissance` et `factorielle` : on effectue les calculs plusieurs fois !
En effet, tel que nous avons écrit notre fonction exponentielle, pour calculer $x^{r+1}$ on reprend le calcul du début (nouvel appel à la fonction puissance) sans utiliser le fait qu'on a déjà calculé $x^r$ (et de même pour le calcul de la factorielle qui est repris du début à chaque appel à la fonction factorielle).
On va écrire une nouvelle version plus efficace de la fonction exponentielle, qui ne fait pas appel aux fonctions puissance ou factorielle pour éviter ce problème de calculs faits plusieurs fois.

```{code-cell}
#include <iostream>
using namespace std;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d1ecf9c0bb7167f8a25b8c9ccccaf6aa", "grade": false, "grade_id": "cell-6d56e4530ad5eb9d", "locked": true, "schema_version": 3, "solution": false}}

Copier-collez ici les fonctions `abs` et `egal` de la [partie 3](02-exponentielle3.md):

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6de14db33a845deb5500f878f62f6ecb
  grade: false
  grade_id: cell-11c71a2c606e0da6
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
  checksum: 39ab74184fd198fa1490c9bb74504ee3
  grade: false
  grade_id: cell-f8b3f1f99b27afb6
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

Complétez la fonction ci-dessous qui calcule l'exponentielle à précision donnée **sans** utiliser de fonction annexe (sauf `egal`), et en procédant de façon plus efficace. Pour cela, vous aurez besoin de trois variables d'accumulations : celle de la puissance, celle de la factorielle et celle de l'exponentielle.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 9a4c8e16ee219529f794597c072cb244
  grade: false
  grade_id: cell-303a8716a80dcc32
  locked: false
  schema_version: 3
  solution: true
---
/** Calcul rapide de la fonction exponentielle à précision donnée
 * @param x un nombre de type double
 * @param epsilon un nombre de type double
 * @return e^x avec précision epsilon
**/
double expRapide(double x, double epsilon) {
    double exp=1;
    double ancExp;
    int i = 1;
    double px=x;
    double fac=1;
    while(egal(ancExp, exp, epsilon) == false){
        ancExp = exp;
        exp = exp+(px/fac);
        cout << fac << endl;
        cout << px << endl;
        cout << " " << endl;
        px=px*x;
        fac = fac*i;
        i++;
    }
    return exp;
}
```

```{code-cell}
expRapide(1,0.000000001) // 148.413159
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7411e87f385b8f8b237d2f53a23824b9
  grade: false
  grade_id: cell-c96d4c17c02ce941
  locked: true
  schema_version: 3
  solution: false
---
expRapide(5,0.000000001) // 148.413159
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 65cd6b5a81c9e8afc91c5e263025691d
  grade: false
  grade_id: cell-733b09f1d02a12cf
  locked: true
  schema_version: 3
  solution: false
---
expRapide(3,0.000000001) // 20.085537
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 97579d2c7037ada2ce18d21aa4f61fba
  grade: false
  grade_id: cell-54872c873b619fe1
  locked: true
  schema_version: 3
  solution: false
---
expRapide(1,0.000000001) // 2.718282
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "45dde1f04d3baf449a20e16eb06ed73e", "grade": false, "grade_id": "cell-765bea92acc94ff3", "locked": true, "schema_version": 3, "solution": false}}

Évaluez la performance de la fonction `expRapide` en utilisant à nouveau `timeit`. Est-ce vraiment plus rapide?

```{code-cell}
%timeit expRapide(10, 0.00000001);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "90b02bb8afc1820cf06dcb776212c83a", "grade": false, "grade_id": "cell-54073acf05987882", "locked": true, "schema_version": 3, "solution": false}}

## Bilan

Vous avez maintenant une implantation nettement plus rapide de la fonction exponentielle.
Faut il pour autant toujours tout réimplanter plutôt que de réutiliser? Non, surtout pas :

*«Early optimisation is the root of all evil»* (Donald Knuth)

Ici, on pourrait par exemple obtenir les même performances sans duplication de code par *mémoïsation* (conserver les valeurs déjà calculées de $n!$ et $x^n$ pour éviter de les recalculer). En général, c'est à traiter au cas par cas, en tenant compte du compromis entre temps de dévelopement et performances requises, des questions de complexité (cf cours à venir), etc.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f3313388c3a778384dc9d70cd75033d4", "grade": false, "grade_id": "cell-c367cfa1df22e874", "locked": true, "schema_version": 3, "solution": false}}

Vous pouvez maintenant passer à la [suite du TP](index.md).
