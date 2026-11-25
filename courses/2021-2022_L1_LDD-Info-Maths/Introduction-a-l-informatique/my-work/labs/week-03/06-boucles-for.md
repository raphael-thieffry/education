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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b609400bdf841d440945ca64b9b3cb48", "grade": false, "grade_id": "cell-6b385bea40435793", "locked": true, "schema_version": 3, "solution": false}}

# Exercices: les boucles `for`

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9d70b87df572b02dc63d81b609997e5e", "grade": false, "grade_id": "cell-013e3488802326ac", "locked": true, "schema_version": 3, "solution": false}}

## Exercice: comptons!

- Exécuter les cellules suivantes et observer l'affichage produit.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: be1ba868c2cabb1408d65197c355a654
  grade: false
  grade_id: cell-d3c2a1007784aad7
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
  checksum: 572662649933b2253b0deab4f69e46e6
  grade: false
  grade_id: cell-d1f65b41ee196d6e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
for ( int i = 0; i < 10; i++ ) {
    cout << i << endl;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "62184c2ff26cb0a0489bbd4e185f031e", "grade": false, "grade_id": "cell-b85bc1dcbd057af3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

 * Remplacer `int i = 0` par `int i = 5` ci-dessous et exécuter; qu'est-ce qui change ?

```{code-cell}
for ( int i = 5; i < 10; i++ ) {
    cout << i << endl;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "aeef96a99617130f85d4a4789cf8aca5", "grade": false, "grade_id": "cell-b85bc1dcbd057af4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

 * Remplacer `i < 10` par `i <= 10` ci-dessous et exécuter; qu'est-ce qui change ?

```{code-cell}
for ( int i = 0; i <= 10; i++ ) {
    cout << i << endl;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "108937b65443eb7b4cf707ffb595e6b8", "grade": false, "grade_id": "cell-b85bc1dcbd057af2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

 * Remplacer `i++` par `i = i + 2` ci-dessous et exécuter; qu'est-ce qui change ?

```{code-cell}
for ( int i = 0; i < 10; i+=2 ) {
    cout << i << endl;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "88fb2df1cb7b1b74f4828e1fbe9fd5f0", "grade": false, "grade_id": "cell-497b9571a6608f4d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Rappel :** l'instruction `i++` est une écriture simplifiée pour `i = i + 1`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6247b4d7868b5f6b9f0eec5a91a9bec5", "grade": false, "grade_id": "cell-64e23e96bac664e7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Copier l'instruction `for` ci-dessous dans la cellule suivante, et remplacer les trois "?" par les valeurs appropriées pour afficher les entiers pairs entre 0 et 20 (0,2,4,...,20):

  ```
    for (int i = ?; i <= ?; i = ? ) {
        cout << i << endl;
    }
  ```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: cf731a80f0a70451e68d03ebfba7934e
  grade: true
  grade_id: cell-197e8a13ab933d54
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
  for (int i = 0; i <= 20; i+=2) {
      cout << i << endl;
  }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5101bb474eaa0172f2da71bf3be90a97", "grade": false, "grade_id": "cell-8f27451dcf8a9962", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Écrire des boucles `for` qui affichent les nombres suivants dans l'ordre donné :

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "12749c4135f14d0a58cec8e9f2014463", "grade": false, "grade_id": "cell-dc66ba064648240a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

`0, 3, 6, 9, 12` :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ac2c9e0e6bc8e4b4b1dca6eb65b5f73e
  grade: true
  grade_id: cell-0403b0717ee75f12
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
  for (int i = 0; i <= 12; i+=316) {
      cout << i << endl;
  }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e79ff3567b1705ba85ae2140bb51144a", "grade": false, "grade_id": "cell-d467a5322af6c861", "locked": true, "schema_version": 3, "solution": false, "task": false}}

`20, 21, 22, 23, 24, 25` :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 499fdbe838e711df3506b2df6b8c48b3
  grade: true
  grade_id: cell-bb29f7c60e0890ef
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
  for (int i = 20; i <= 25; i++) {
      cout << i << endl;
  }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8b2f12c0951af7afedc32d4e8e273eae", "grade": false, "grade_id": "cell-27a6a431fe02596d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

`10, 9, 8, 7, 6, 5, 4, 3, 2, 1` :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 87f4c006c6546b10829a91c73c7e93b7
  grade: true
  grade_id: cell-01de16c794abf858
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
for (int i = 10; i >= 1; i--) {
      cout << i << endl;
  }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ac247378e8cd06ffdc7cea3f16d858c7", "grade": false, "grade_id": "cell-117a4ab9b881f533", "locked": true, "schema_version": 3, "solution": false, "task": false}}

`2, 4, 8, 16, 32` :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a2ca76d852be34538d53da5c0bd55856
  grade: true
  grade_id: cell-82fe8beb79812aba
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
for (int i = 2; i <= 32; i=i*2) {
      cout << i << endl;
  }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1898e1be264c3f2d31312927984ef1a5", "grade": false, "grade_id": "cell-ed97db4d86ee7080", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: accumulons !

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "204186c487acf2f317a28a3c3a77d6d3", "grade": false, "grade_id": "cell-560788172824cc61", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Observer les cellules suivantes et deviner la valeur finale de la variable `c`; puis exécuter pour vérifier.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7fbc7a1574f74a3e89cc4cfa150ee01c
  grade: false
  grade_id: cell-6ec70e1f713f63db
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int c;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 828ff3b4a6842134c95d11706bd21805
  grade: false
  grade_id: cell-fda4a5905295a758
  locked: true
  schema_version: 3
  solution: false
  task: false
---
c = 0;
for (int i = 0; i < 6; i++) {
    c = i + c;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fe13effafcc7c010151961c567e3b488
  grade: false
  grade_id: cell-f75c84eb6d116fc4
  locked: true
  schema_version: 3
  solution: false
  task: false
---
c
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f6989f8d7f6a1d470ff47a66f4b690b9", "grade": false, "grade_id": "cell-742f622bc7056e10", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Recopier la boucle ci-dessous puis modifier la condition d'arrêt pour que la variable `c` soit égale à $36$ après l'exécution.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 65d668fdd94b9a08c96a845c983ab3bb
  grade: false
  grade_id: cell-9c0385060494fe0c
  locked: false
  schema_version: 3
  solution: true
  task: false
---
c = 0;
for (int i = 0; i < 9; i++) {
    c = i + c;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b9c2f4f87fca9eca5cf1636822202f13
  grade: false
  grade_id: cell-27c0da7d14f62d91
  locked: true
  schema_version: 3
  solution: false
  task: false
---
c   // doit valoir 36
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cdcc9171881fc49845b570a4ab8d9210", "grade": false, "grade_id": "cell-a92593ec6373f39d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La cellule suivante contient des tests automatisés; nous reviendrons dessus plus en détails par la suite; pour le moment, vous pouvez juste exécuter la cellule et vérifier qu'il n'y a pas de message d'erreur.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 057c1692dca756878697d6570e75a58d
  grade: true
  grade_id: cell-bf26103d9c19d6f5
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
ASSERT( c == 36 )
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4a1755d539775a2f8727c1cbb8ed5a2f", "grade": false, "grade_id": "cell-4e242b4c7dd64021", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Écrire ci-dessous un programme qui calcule la valeur de $n! = 1\times 2 \times \cdots \times n$ dans la variable `f`:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 237f6892b54a0ebe372af59b82b172ed
  grade: false
  grade_id: cell-b3947d8539dfc764
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int f,n;
```

```{code-cell}
n = 5
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: fb2edb66d6f0eed34580e07a1927df9e
  grade: false
  grade_id: cell-c0739002bc408396
  locked: false
  schema_version: 3
  solution: true
  task: false
---
int f;
for (int i = 1; i <= 100; i++) {
    int k = i;
    f=i
    cout << f << endl;
    f=i;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a4c08a39cdafca60b0c93e44e39d29bb
  grade: false
  grade_id: cell-a7fa6c68f7a8f078
  locked: true
  schema_version: 3
  solution: false
  task: false
---
f // 120 pour n = 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a39a18e5c43e354910455ddbf71cd886
  grade: true
  grade_id: cell-70156efdecd752af
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( f == 120 )
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4775fef4d202b7f409baedc6a872710b", "grade": false, "grade_id": "cell-262927f9eba5a9ae", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Reprendre votre programme pour le mettre sous la forme d'une *fonction* qui calcule $n!$:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: d3b96f90f7c7ff5b31a41eb208495fea
  grade: false
  grade_id: cell-59d27e7e46c6be00
  locked: false
  schema_version: 3
  solution: true
---
int factorielle(int n) {
    // VOTRE CODE ICI
    return f;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0d6d313d45dded61e10504aed22f4cb9", "grade": false, "grade_id": "cell-bbc3a5eababe0ebd", "locked": true, "schema_version": 3, "solution": false, "task": false}}

L'appel suivant à votre fonction devrait renvoyer 120:

```{code-cell}
factorielle(5)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8c3777bdb01476ceb8ed3ef7a1e6bbf7", "grade": false, "grade_id": "cell-57835c5482344135", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vérifiez votre fonction grâce aux tests suivants (ils doivent tous afficher `true`) :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 73cb9df6f9be087c9cb68d068d7e2472
  grade: false
  grade_id: cell-e8bde338e8e91293
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(5) == 120
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 428ca5eb393e8b981498cd1dee91e3c0
  grade: false
  grade_id: cell-0f480f455c001cb4
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(6) == 720
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fad43258d645e4c30365b17a0325e8c2
  grade: false
  grade_id: cell-c0e7b253d4de674e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(10) == 3628800
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 85affde691cbc8e7b5c4ef7ef7e3ff15
  grade: false
  grade_id: cell-1ee3df1dc7a458a7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(1) == 1
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 55b8cb46f885312bfcba1d860c798184
  grade: false
  grade_id: cell-142a1c4939f30f88
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(0) == 1 // convention mathématique
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1ec3beb76236fc0dd76ffb52d99c5e66", "grade": false, "grade_id": "cell-a49ebc122273ee08", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La cellule suivante contient des tests automatisés; nous reviendrons dessus plus en détails par la suite; pour le moment, vous pouvez juste exécuter la cellule et vérifier qu'il n'y a pas de message d'erreur.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 25eec2c495b8b951ddc0bc0f3fa1edd8
  grade: true
  grade_id: cell-a5be78a5a5a25142
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( factorielle(0) ==   1 );
ASSERT( factorielle(1) ==   1 );
ASSERT( factorielle(2) ==   2 );
ASSERT( factorielle(3) ==   6 );
ASSERT( factorielle(4) ==  24 );
ASSERT( factorielle(5) == 120 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4f7aa6d209c9151e4ef6cd7b09eb5118", "grade": false, "grade_id": "cell-1fe179818c6002ac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## ♣ Utilisation de la boucle for dans Laby

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9b7fdba5ef8f0ad7f6d33a5c6f7e1fa5", "grade": false, "grade_id": "cell-fd0933aaa600036b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1. ♣ Écrivez une fonction `carre(int L)` qui prends en paramètre un entier L, et qui fait faire à la fourmi une trajectoire carrée de côté L cases. La fourmi doit revenir à la case de départ à la fin de la fonction.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a925773535b684f1f0536fa900e9bf55
  grade: false
  grade_id: cell-b0d580c556865d95
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <laby/global_fr.hpp>
LABY_BAR(
u8"o o o o o o o o o o o o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o . . . . . . . . . . o\n"
u8"o ↑ . . . . . . . . . o\n"
u8"o o o o o o o o o o o o\n"
)
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3227282d162d920e726429192b3854df
  grade: true
  grade_id: cell-bf212efeb0472746
  locked: false
  points: 0
  schema_version: 3
  solution: true
  task: false
---
// Entrée : un entier L, correspondant à la longeur d'un côté de la trajectoire.
// Sortie : aucune, déplace la fourmi selon un carré de longueur L
// VOTRE CODE ICI
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 790c74491a9f86127655787f4a78934b
  grade: false
  grade_id: cell-b7280173f444a974
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre(0) // La fourmi ne fait rien
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0bbeaf630faf439145525022b5d4520c
  grade: false
  grade_id: cell-61f6cbe5090c44f7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre(1) // La fourmi doit faire un tour sur elle-même
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 956fc6d14423e1e6c6df21014b12c6ff
  grade: false
  grade_id: cell-cd855fcd1a51f005
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre(5) // Parcourt un carré de longueur 5 cases
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "02eb336e1a85b1d28174acb2cd542776", "grade": false, "grade_id": "cell-49a7205ebd424a67", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Fin de cette feuille

Dans cette feuille, vous avez mis en pratique la boucle `for` pour *compter* et *accumuler*. Vous avez maintenant les outils pour passer à la suite de la [fiche de TP](TP.pdf).
