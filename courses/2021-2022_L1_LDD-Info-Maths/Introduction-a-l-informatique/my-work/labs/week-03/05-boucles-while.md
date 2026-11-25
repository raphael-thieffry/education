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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2acda9534112bb9934be39589a8f0bd1", "grade": false, "grade_id": "cell-fb970bd64e60242c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Exercices: les boucles `while`

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c3a36f6de89f06a297adac3c079cef50", "grade": false, "grade_id": "cell-5878847ca43abeac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans cette feuille, vous allez mettre en pratique la boucle `while`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "57bdfca6a7558f58aa55503dfabf0b24", "grade": false, "grade_id": "cell-846152f36fa6d1b5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: première boucle while

- Exécutez les cellules suivantes :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3a487892e8a1f743a8533b895f2728bf
  grade: false
  grade_id: cell-1880f11656147b47
  locked: true
  schema_version: 3
  solution: false
  task: false
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
  checksum: 7115d54d63ae4c5ddc8c44b02a63f891
  grade: false
  grade_id: cell-e39d736d09f14238
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int a,i;
```

```{code-cell}
a = 35;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a698003883efc6c36f5eea7b6b47f90e
  grade: false
  grade_id: cell-1fb1753a1b1cdb1a
  locked: true
  schema_version: 3
  solution: false
  task: false
---
i = 1;
while ( i < a ) {
    cout << i << endl;
    i = i*2;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "09c3096865fcf08a68407a7fbdec6570", "grade": false, "grade_id": "cell-12d88166a3fd3c9b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Modifiez la valeur de $a$ ci-dessus pour obtenir :
 * Exactement 1 affichage
 * Exactement 0 affichage
 * Exactement 4 affichages

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a2463c4e48e87a66dced67e4f71b87c7", "grade": false, "grade_id": "cell-6e951de52f28c316", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: Panique dans le noir

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c473dd015cd1b3fffd153d5d61a77b46", "grade": false, "grade_id": "cell-bab25da16aa4455a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Notre fourmi est perdue dans un labyrinthe plongé dans le noir.
Elle panique! Avant chaque pas, elle tourne aléatoirement
vers la gauche ou vers la droite. Va-t-elle trouver la sortie?

À vous de le découvrir en programmant ce comportement de la fourmi!

**Indications**:
- Vous pouvez utiliser la condition `regarde() != Sortie`;
- Pour tirer à pile ou face si la fourmi va tourner à gauche ou à droite,
  vous pouvez utiliser la fonction `rand()` qui renvoie un nombre
  entier aléatoire. Du coup, avec `rand() % 2` vous obtenez un
  entier qui vaut aléatoirement `0` ou `1`.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c3d9fbaa838a249e9e124edd37983362
  grade: false
  grade_id: cell-11ff4ac8db53cf33
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <laby/global_fr.hpp>
#include <stdlib.h>
LABY_BAR(u8"o o o o o o o\n"
         u8"o → . . . . o\n"
         u8"o . . . . . o\n"
         u8"o . . . . . o\n"
         u8"o . . . x . o\n"
         u8"o . . . . . o\n"
         u8"o o o o o o o\n")
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6efcfdf353f475526f0c3fcd8a511df8
  grade: false
  grade_id: cell-9ae17b16e4c34584
  locked: false
  schema_version: 3
  solution: true
  task: false
---
debut();
while(regarde() != Sortie){
    if(rand() % 2 == 0){
        droite();
    }else{
        gauche();
    }
    if(regarde() == Vide){
        avance();
    }
}
ouvre();
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b669df5ddab68645bc7b912fd76ea56c
  grade: true
  grade_id: cell-55ee502565fe62bd
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT(a_gagne());
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ef39adf190a1a1f3171b5329eed5cacf", "grade": false, "grade_id": "cell-dfe882b2f3d4d4fd", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: division euclidienne par soustraction

- Observez les cellules suivantes et **donnez des valeurs à $b$ et $c$ avec $b > c$ telles que, à la fin de la boucle, on ait $b=3$**:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a8a8a6e86127c3ab2edca5dd5870435a
  grade: false
  grade_id: cell-8fe0bd78375ff270
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int b,c;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a4da87d0f615e4fe47d457934b951267
  grade: false
  grade_id: cell-66fc1e139a8a5e29
  locked: false
  schema_version: 3
  solution: true
  task: false
---
c=26;
b=5*c+3;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b3c8e412964907e7368dce973cda2708
  grade: false
  grade_id: cell-53c2eeeab2fe5530
  locked: true
  schema_version: 3
  solution: false
  task: false
---
while ( b > c ) {
    b = b - c;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: dd172c95c536db0cc5d3fd5d9bbd4636
  grade: false
  grade_id: cell-92488e51123a90d6
  locked: true
  schema_version: 3
  solution: false
  task: false
---
b
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d786ee8f7a7b002b635824810b938258", "grade": false, "grade_id": "cell-7ac80b6a48ea28c7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Test automatique (ne doit rien afficher):

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9790b56a97a2d0e824b794b8026bdc6c
  grade: true
  grade_id: cell-9745ecb4ba87d5c8
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( b == 3 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0f4412c044fe165a24a579a5d30cb59b", "grade": false, "grade_id": "cell-c0b607a1647b25f7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Modifiez la cellule ci-dessous pour que la variable $k$ compte le nombre d'exécutions de la boucle;
- Donnez des valeurs à $b$ et $c$ telles que l'on ait $b=3$ et $k=5$ à la fin de la boucle.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9596cd287205a7734fb8cd0eac758afa
  grade: false
  grade_id: cell-59f25e846a1dc7ca
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int k;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 70637046b19805bb13ee0f86fb3d5cd9
  grade: true
  grade_id: cell-9df75cb01e7efbf3
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
c=825;
b=5*c+3;
k = 0;
while ( b > c ) {
    b = b - c;
    k++;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 774ff7faa8a493cb789267f2a95100ec
  grade: false
  grade_id: cell-95b7aee0b39f4c13
  locked: true
  schema_version: 3
  solution: false
  task: false
---
b     // doit afficher 3
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9e3a47790361920c8f53b91ceff4db5b
  grade: false
  grade_id: cell-ba01ba70e0237af3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
k     // doit afficher 5
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4abac077eef879c560b898b39f9f57de", "grade": false, "grade_id": "cell-e119e376c9c336b2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Tests automatiques:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 31313b904f1e62bd10cbe8bcb3978523
  grade: true
  grade_id: cell-0e30a8050f77f2eb
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( b == 3 );
ASSERT( k == 5 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8df4e701a4ce45532a871731cb90cac0", "grade": false, "grade_id": "cell-c30e45ce73de8c5f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: suite de Syracuse

- Exécutez, sans les modifier, les deux cellules ci-dessous puis trois fois la troisième cellule:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 79ef295eee2ad7246fe0db3bd12ef7a1
  grade: false
  grade_id: cell-37930a4a3f765bc0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <iostream>
using namespace std;
int d;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b4b0993f8781bad673e10969dda4e512
  grade: false
  grade_id: cell-673069e18045ce2f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
d = 5;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 7cdaea784dd1aded49a3781768c057bb
  grade: true
  grade_id: cell-1a8c990096f29a33
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
for(int i=0; i<3; i++){
    if ( d%2 == 0) {
        d = d/2;
    } else {
        d = 3*d+1;
    }
    cout << d << endl;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7f697477639b8179e09b914274f12fa5", "grade": false, "grade_id": "cell-84f1ecf621ccd00b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

  Vous noterez que lorsque le nombre $d$ est pair, on le divise par 2. Lorsqu'il est impair, on le multiplie par 3 et on ajoute 1. 

- Modifier la cellule pour que l'on répète cette action tant que le nombre $d$ est supérieur à 1. On veut afficher la valeur de $d$ à chaque fois. Si votre code est correct, il doit afficher 16 8 4 2 1 (en partant de d=5).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7703d1ff11c9e4781da3408eb17eb127", "grade": false, "grade_id": "cell-615fbe353a6d1b8c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice

- Obervez la fonction suivante et essayez de comprendre ce qu'elle calcule en lisant le code et en essayant plusieurs valeurs d'appel:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c54dbcf8aa8957f2002363da54671620
  grade: false
  grade_id: cell-a51788cc6416fa31
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int mystere(int n) {
    int k = 1;
    while ( k*k < n ) {
        k = k + 1;
    }
    return k;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ec25272108adf74b8dd72b5afdb38ef4
  grade: false
  grade_id: cell-7b9003dc6876c16b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
mystere(5)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e8665cfd2c62742c3737ffb0b53a4842", "grade": false, "grade_id": "cell-10317126f8f312ef", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Donnez un exemple tel que la valeur renvoyée soit 6:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 06ecf29262dcdbcbd014686c1b1de882
  grade: true
  grade_id: cell-9cb5ab15e3094248
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
mystere(35)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "09729907658420286d88627f583ee1f2", "grade": false, "grade_id": "cell-1da5f39e2279ad35", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Bilan

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "03e2e5b61b2d5062eb9b099b6f87de95", "grade": false, "grade_id": "cell-fe36a3aa0aa7120f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Passez maintenant à la [feuille d'exercices sur les boucles `for`](06-boucles-for.md). Vous pourrez, par la suite, aborder les exercices plus avancés ci-dessous.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9e84fe0d9ccde69b6bfe5a17a7e34c95", "grade": false, "grade_id": "cell-74d2f63d4e5fb7e7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice ♣

- Complétez le code de la fonction suivante pour qu'elle détermine si $n$ est un carré parfait. Dans ce cas, elle doit renvoyer `true`; sinon elle doit renvoyer `false`.

  **Rappel**: un *carré parfait* est un nombre qui peut s'écrire $k\times k$ avec $k$ un entier. Par exemple $16$ est un carré parfait car $16 = 4 \times 4$, mais $20$ n'est pas un carré parfait.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: fc3e63c832e2600ee4f6cee9929465d2
  grade: false
  grade_id: cell-adfbc5fdcab735d4
  locked: false
  schema_version: 3
  solution: true
  task: false
---
bool carreParfait(int n) {
    int i = 0;
    while(i<=n){
        if(n==i*i){
            return true;
        }else{i++;}
    }
    return false;
}
carreParfait(0)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5690a9fd50f9b52dd09b76d52fb9b90d", "grade": false, "grade_id": "cell-db645b450cb57c41", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Essayez votre fonction sur les exemples suivants:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 714077d82835c9f8fc2aeaf5daf989c1
  grade: false
  grade_id: cell-0360eb6fa7a5c845
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carreParfait(16)  // doit renvoyer true
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d9dcf97f1d749d3a4fc8c358da9bcecf
  grade: false
  grade_id: cell-e18681ca4661fd4d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carreParfait(20)  // doit renvoyer false
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0ac9890bbe8538425c1278ad17bca68f", "grade": false, "grade_id": "cell-2010b81e2fd4b599", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Vérifiez que votre fonction passe les tests automatiques suivants:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0a696c94c8530fe78cfcf8d06832d2f0
  grade: true
  grade_id: cell-435a1b0f1a805763
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( carreParfait(0) );
ASSERT( carreParfait(1) );
ASSERT( not carreParfait(2) );
ASSERT( not carreParfait(50) );
ASSERT( carreParfait(100) );
ASSERT( not carreParfait(250) );
```

```{code-cell}

```
