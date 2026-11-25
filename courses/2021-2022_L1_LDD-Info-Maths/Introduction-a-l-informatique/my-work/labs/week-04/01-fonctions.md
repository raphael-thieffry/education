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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "76899a18198940168fdcb0d63ee07af4", "grade": false, "grade_id": "cell-a741e2baae8a5295", "locked": true, "schema_version": 3, "solution": false}}

# TP: Premières fonctions

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e943250e41c9b237026cd799125a5f76", "grade": false, "grade_id": "cell-8b56bb2323e686a8", "locked": true, "schema_version": 3, "solution": false}}

## Exercice 1 : renvoyer versus afficher

Exécutez les cellules suivantes qui définissent deux fonctions.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0309a270ad04fb5aa24f938960bea063
  grade: false
  grade_id: cell-7d3032978c91517b
  locked: true
  schema_version: 3
  solution: false
---
#include <iostream>
using namespace std;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 94d972927d024b043ba4bc8ff7e7d88d
  grade: false
  grade_id: cell-adbf3ea334252de8
  locked: true
  schema_version: 3
  solution: false
---
/** Une fonction qui calcule la valeur absolue
 * @param a, un entier
 * @return la valeur absolue de a
 **/
int abs(int a) {
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
editable: false
nbgrader:
  cell_type: code
  checksum: cb884979fd90eee42e816e70e5d0a33f
  grade: false
  grade_id: cell-7d7a9fa58c13128d
  locked: true
  schema_version: 3
  solution: false
---
/** Une fonction qui affiche la valeur absolue
 * @param a, un entier
 **/
void afficheAbs(int a) {
    if (a > 0) {
        cout << a << endl;
    } else {
        cout << -a << endl;
    }
}
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "968822a2ffd341012a16da276b25530b", "grade": true, "grade_id": "cell-ebbfec0d5cb0e626", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

Observez les appels suivants; y a-t-il une différence entre `abs` et `afficheAbs`?

Oui, afficheAbs affiche quoi qu'il arrive la valeur absolue, alors que abs revoie une valeur

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c5e8883c3f9a3939488c775eeff3823a
  grade: false
  grade_id: cell-96a8003bde332ef4
  locked: true
  schema_version: 3
  solution: false
---
abs(-3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e34051b5db2b78eebf0e4df9237f9b79
  grade: false
  grade_id: cell-acc035c120b5e1a5
  locked: true
  schema_version: 3
  solution: false
  task: false
---
abs(-3);
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1d9779641ca4534d57bd72865fe9e0f7
  grade: false
  grade_id: cell-525744fbd9aca5dd
  locked: true
  schema_version: 3
  solution: false
---
afficheAbs(-3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0f3b4ffc6d0179133c8bbb8f69474fc3
  grade: false
  grade_id: cell-525744fbd9aca5de
  locked: true
  schema_version: 3
  solution: false
---
afficheAbs(-3);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ed1517e1c1e04db83ad75809d23780c4", "grade": false, "grade_id": "cell-d95a34f5ac81eb33", "locked": true, "schema_version": 3, "solution": false}}

Essayez de deviner le résultat des appels suivants puis exécutez pour vérifier:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fef171ff6f17fe7d68c30130ba3fcca3
  grade: false
  grade_id: cell-6a55898a16557a96
  locked: true
  schema_version: 3
  solution: false
---
abs(-5) + abs(3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c2c79916db3967079effc25e0978340a
  grade: false
  grade_id: cell-866c4a0c9a4a6ab8
  locked: true
  schema_version: 3
  solution: false
---
afficheAbs(-5) + afficheAbs(3)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "88426bc01b00850d687ded1e671a66a7", "grade": true, "grade_id": "cell-6c7a39b6a3ef0358", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

La seconde cellule vous donne une **erreur**, comprenez-vous pourquoi ?

Car afficheAbs ne renvoie pas de valeur

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "858b6716957c6dde85695a02e8f9b718", "grade": false, "grade_id": "cell-5699e6d9d0f3d16a", "locked": true, "schema_version": 3, "solution": false}}

## Exercice: une fonction utilisant une fonction

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "172da47dfd0b173d75ad24012c00744e", "grade": false, "grade_id": "cell-b9cda32e468d6d8b", "locked": true, "schema_version": 3, "solution": false}}

Complétez la fonction ci-dessous dont on donne la *documentation*. 

⚠ **Vous devez utiliser un appel à l'une des deux fonctions précédentes, `afficheAbs` ou `abs`; laquelle faut-il choisir? Pourquoi?** ⚠

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f71c3d29d940ec65638f9a66928eb753
  grade: false
  grade_id: cell-ef47de23dc65918c
  locked: false
  schema_version: 3
  solution: true
---
/** Distance de deux points sur une droite
 * @param a un entier: la coordonnée du premier point
 * @param b un entier: la coordonnée du deuxième point
 * @return la valeur absolue de la différence entre a et b
 **/
int distance(int a, int b) {
    return abs(b-a);
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3b751430d919bba4c32ac054169c05b6", "grade": false, "grade_id": "cell-cf373e1ce7210f3a", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez son fonctionnement sur l'exemple ci-dessous et les tests qui le suivent. Comme d'habitude, ces tests doivent tous valoir `true`, si ce n'est pas le cas il y a une erreur dans le code de votre fonction.

```{code-cell}
distance(5,3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 01bf41a5374fd85045dc1ecac10625bb
  grade: false
  grade_id: cell-1468d3b77d12dfbb
  locked: true
  schema_version: 3
  solution: false
---
distance(5,3) == 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e1a95f5a8a681bd97cdec030b4f599b2
  grade: false
  grade_id: cell-fb7ffc1acf3cf457
  locked: true
  schema_version: 3
  solution: false
---
distance(-4,2) == 6
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: eb0feb62d6805cce13956c83fb65cade
  grade: false
  grade_id: cell-973b66f0d812df05
  locked: true
  schema_version: 3
  solution: false
---
distance(2,-5) == 7
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d1727e107df4f59b9889ee5789c47d29", "grade": false, "grade_id": "cell-d27b0a203d050706", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (à la maison)
Mêmes consignes que pour l'exercice précédent:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: dbcd8fc2cd51fd641e7410ec32b1524b
  grade: false
  grade_id: cell-a3cf80e3952bdd34
  locked: false
  schema_version: 3
  solution: true
---
/** somme des valeurs absolues (aussi appelée norme L1)
 * @param a un entier
 * @param b un entier
 * @return la somme des valeurs absolues de a et b
 **/
int sommeAbs(int a, int b) {
    return abs(a)+abs(b);
}
```

```{code-cell}
sommeAbs(5,-3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b932adcb116bc5d1b788b63a371b40e5
  grade: false
  grade_id: cell-6d67d87937dbe617
  locked: true
  schema_version: 3
  solution: false
---
sommeAbs(5,-3)  == 8
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8fdc77fae0f04f969ee5bc5fadb70753
  grade: false
  grade_id: cell-1cf910256b7ba798
  locked: true
  schema_version: 3
  solution: false
---
sommeAbs(-4,-2) == 6
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 985de6994cc90979fd7380dc7b744023
  grade: false
  grade_id: cell-b0072c6876feea78
  locked: true
  schema_version: 3
  solution: false
---
sommeAbs(2,5) == 7
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fc7f555f612afbb9aa9ca739962eb746", "grade": false, "grade_id": "cell-f389d530bfbe35e0", "locked": true, "schema_version": 3, "solution": false}}

## Exercice: tests automatiques
Essayez les exemples suivants qui illustrent l'utilisation de l'infrastructure vue en cours pour automatiser les tests. Si vous avez une erreur du type `no member named 'cerr'`, vous avez probablement redémarré le noyau en oubliant d'exécuter la première cellule de cette fiche contenant `#include <iostream>`.
 **Astuce** : À chaque fois que vous redémarrez le noyau, allez ensuite dans `Cellule` -> `Exécuter toutes les précédentes`. Cela exécute toutes les cellules qui sont avant celle où vous vous trouvez. Vous éviterez ainsi de perdre du temps à chercher où sont les cellules qu'il faut ré-exécuter.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0221e87f4b916f592a1fc11cebac8564
  grade: false
  grade_id: cell-409ed522d0d7ce28
  locked: true
  schema_version: 3
  solution: false
---
CHECK ( 1 < 2 );
CHECK ( 1 > 2 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7af8bff222fde65713642d6f6989e7ca", "grade": false, "grade_id": "cell-4f9b5f26274b8d47", "locked": true, "schema_version": 3, "solution": false}}

On remarque que si la condition en paramètre de `CHECK` est vraie, il n'y a aucun affichage. Par contre si la condition est fausse, un message d'erreur indiquant la condition fausse est affiché.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "957701be40a66e51a9ca0845f56c09b9", "grade": false, "grade_id": "cell-c7c30794bfe3d639", "locked": true, "schema_version": 3, "solution": false}}

Avec CHECK, les tests de la fonction `distance` se mettent sous la forme:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 956310f8b997c93c0ef30516de98e53b
  grade: true
  grade_id: cell-30fde9ec08937b80
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK ( distance(5,3)  == 2 );
CHECK ( distance(-4,2) == 6 );
CHECK ( distance(2,-5) == 7 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f26ab0e5548a3ba352d9ed7b5d520f8f", "grade": false, "grade_id": "cell-5a60b1893097e9fd", "locked": true, "schema_version": 3, "solution": false}}

Exécutez ces tests. Leur exécution ne devrait rien afficher.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "df44a992f4c41dd9bacba81eda55b846", "grade": false, "grade_id": "cell-6501a3f1941bd272", "locked": true, "schema_version": 3, "solution": false}}

## Exercice: suivre la documentation et les tests

Implantez la fonction `nombreSecondes` dont la documentation est donnée ci-dessous:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f8d13e6cded5a6f2dae77bf6ba6c436c
  grade: false
  grade_id: cell-0d59febaf9233496
  locked: false
  schema_version: 3
  solution: true
---
/** Renvoie en secondes la durée décrite en jours, heures, minutes, secondes
 * @param j un entier représentant le nombre de jours
 * @param h un entier représentant le nombre d heures
 * @param m un entier représentant le nombre de minutes
 * @param s un entier représentant le nombre de secondes
 * @return la durée totale en secondes
**/
int nombreSecondes(int j, int h, int m, int s){
    return s+m*60+h*60*60+j*24*60*60
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "de6d4a1eca17a94dd17a8712bed6330a", "grade": false, "grade_id": "cell-e103b2353b1c2e15", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez son fonctionnement sur les exemples et tests ci-dessous:

```{code-cell}
nombreSecondes(1,1,1,1)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 47ff5f144f91796cca062801d0d6cc26
  grade: true
  grade_id: cell-babf9ae1f3f02491
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( nombreSecondes(0,0,0,1)  == 1      );
CHECK( nombreSecondes(0,0,1,0)  == 60     );
CHECK( nombreSecondes(0,1,0,0)  == 3600   );
CHECK( nombreSecondes(1,0,0,0)  == 86400  );
CHECK( nombreSecondes(3,2,5,25) == 266725 );
```

## Bilan

Dans cette feuille, vous vous êtes familiarisés avec les fonctions:
distinction entre afficher et renvoyer, fonction appelant des
fonctions, documentation, tests, tests automatiques. Vous avez
maintenant le bagage requis pour la [suite du TP](index.md) où vous
implanterez la fonction exponentielle.
