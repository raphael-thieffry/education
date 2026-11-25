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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "dba145ba7fe5603520a2fa27772e0a00", "grade": false, "grade_id": "cell-a7cb2ec64ca805b6", "locked": true, "schema_version": 3, "solution": false}}

# TP: Implanter la fonction exponentielle (2/5)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b1d16c683150469d403d88ba08fea79d", "grade": false, "grade_id": "cell-dfc454aa3b53f790", "locked": true, "schema_version": 3, "solution": false}}

## Partie 2 : Calculer une somme infinie ?

La définition mathématique de l'exponentielle suppose de calculer une *somme infinie*. Ce n'est pas possible en pratique ! On propose donc d'implanter la fonction suivante qui calcule une *approximation* de la fonction exponentielle obtenue en tronquant la somme à un certain rang $r$:
$e^x \approx \sum_{n=0}^r \frac{x^n}{n!}$

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9d9bc3381406e267b68649d5996e3385", "grade": false, "grade_id": "cell-b916e98c49f6f97c", "locked": true, "schema_version": 3, "solution": false}}

Copier-collez dans les deux cellules suivantes vos fonctions `puissance` et `factorielle` de la [partie 1](02-exponentielle1.md), puis complétez l'implantation de la fonction `expRang` et vérifiez qu'elle passe les tests fournis.

```{code-cell}
#include <iostream>
using namespace std;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: c917e34a852afa3dc1b961e1c37dfcd5
  grade: false
  grade_id: cell-ed4b87cdbd09b4b1
  locked: false
  schema_version: 3
  solution: true
---
/** Factorielle
 * @param n un entier
 * @return la valeur n! en tant que double
**/
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
  checksum: 6e7e77bc9e5e17aabfe2ee4462210aac
  grade: false
  grade_id: cell-40704048f0f43a58
  locked: false
  schema_version: 3
  solution: true
---
/** Puissance
 * @param x un nombre de type double
 * @param n un entier
 * @return le nombre x^n de type double
**/
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
puissance(2,20)
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 98791bb771932712f68b7f4622b267dc
  grade: false
  grade_id: cell-583ab182274bf121
  locked: false
  schema_version: 3
  solution: true
---
/** Exponentielle tronquée à un certain rang r
 * @param x un nombre à virgule flottante en double précision
 * @param r un nombre entier positif
 * @return 1 + x^1/1!  + x^2/2! + x^3/3! + ...  + x^r/r!
**/
double expRang(double x, int r) {
    double exp=1;
    for(int i=1; i<=r; i++){
        exp = exp+(puissance(x,i)/factorielle(i));
    }
    return exp;
}
```

```{code-cell}
expRang(5,1)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0f4a4207b13e8754bc0c314417e1a0ac
  grade: true
  grade_id: cell-0841e8afc22ba740
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( expRang(6, 0) == 1  ) // 6^0/1
CHECK( expRang(6, 1) == 7  ) // 6^0/1 + 6/1
CHECK( expRang(6, 2) == 25 ) // 6^0/1 + 6/1 + 36/2
CHECK( expRang(6, 3) == 61 );// 6^0/1 + 6/1 + 36/2 + 36*6/6
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0996a2167f70482f292dcfe6d4c12543", "grade": false, "grade_id": "cell-162792f03bec12d9", "locked": true, "schema_version": 3, "solution": false}}

Plus on augmente le rang, plus on se rapproche de la valeur de $e^6=403,429\cdots$.

Dans la cellule ci-dessous, calculez une approximation de la valeur de $e^{6}$ et **augmentez le rang jusqu'à ce que la valeur affichée ne change plus** (la valeur ajoutée est trop petite pour changer l'affichage)

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 90021c39c0f43bcd4b1ce30f1a5aa7a7
  grade: false
  grade_id: cell-c845f3c8812b2ff5
  locked: false
  schema_version: 3
  solution: true
---
expRang(6,24)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4f2d49c9914d84d9544490ee4ef53962", "grade": false, "grade_id": "cell-b586c5b168fc5914", "locked": true, "schema_version": 3, "solution": false}}

Calculez maintenant une approximation de la valeur de $e^{10}=22026,46\cdots$ avec le même rang:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: b8af63250912e653fb242674c633fdd9
  grade: false
  grade_id: cell-586d52cbad6530df
  locked: false
  schema_version: 3
  solution: true
---
expRang(10,24)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "31ea878d280ea08ef3464b5f1fcb635d", "grade": true, "grade_id": "cell-6e01d081ee0b9bd2", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

Que constatez vous?

Le meme rang qu'avant n'est pas suffisant pour des x plus grands

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8284f2f1ef7bc096cc8f01b527bd7fc2", "grade": false, "grade_id": "cell-e1f369de58992c8b", "locked": true, "schema_version": 3, "solution": false}}

Augmentez le rang jusqu'à ce que la valeur affichée ne change plus:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: c064a7b740dbd68953a93396d018ec89
  grade: false
  grade_id: cell-9ab12e4a0fe9cddb
  locked: false
  schema_version: 3
  solution: true
---
expRang(10,32)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7ca8d911ca8f801447268f43f347d58a", "grade": false, "grade_id": "cell-c9a5001fba7bb1a4", "locked": true, "schema_version": 3, "solution": false}}

## Bilan de la partie 2
Bravo, vous avez implanté une approximation de la fonction exponentielle en tronquant sa formule à un certain rang. Cependant, au vu des exemples ci-dessus, l'utilisateur souhaiterait spécifier non pas le *rang*, mais la *précision* qu'il souhaite obtenir. Pour cela il faut d'abord formaliser cette idée de précision. C'est l'objet de la [partie 3](02-exponentielle3.md).
