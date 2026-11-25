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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5109584ea226d15ce21ac1b38271de0a", "grade": false, "grade_id": "cell-5c4b0b2f0931e30a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Prélude: affichages

Comme dans le dernier amphi, nous aurons besoin dans ce TP d'afficher des informations pour tracer pas à pas l'exécution d'un programme. Nous vous donnons ici le minimum nécessaire pour cela. Nous reviendrons dessus plus en détail ultérieurement.

L'affichage à l'écran est une des façons de communiquer entre le programme et l'utilisateur. On a vu la semaine dernière que, lorsque l'on exécute une cellule dans Jupyter, la valeur de la *dernière expression* d'une cellule est affichée, avec son type, et précédée de `Out[...]`:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a719a9a91d58c5950c493585043d77a7
  grade: false
  grade_id: cell-19cd93362f420a66
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1+2;
3+4;
5+6
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0c4f2764034a3030b6f8d2c8b18d6be8", "grade": false, "grade_id": "cell-367e4b99458161a3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les autres calculs ont bien été effectués par la machine, mais sans montrer les valeurs obtenues.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "df1bc2629f40adbee535e52817118e16", "grade": false, "grade_id": "cell-367e4b99458161a4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons maintenant voir comment afficher des informations.
Tout d'abord, nous avons besoin d'exécuter la ligne suivante qui charge la bibliothèque `C++` d'*entrées / sorties* (nous reviendrons sur cette notion en cours).

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 055187c3467d7a5f823ee14d3ec0b7be
  grade: false
  grade_id: cell-7625170582ccbac3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <iostream>
using namespace std;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "11d3dc617436f2340215e4438ab9e449", "grade": false, "grade_id": "cell-c94dd426cd30fc59", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La ligne suivante affiche le résultat du calcul, suivi d'un retour à la ligne:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4b0fa1652ae6607442bf881e67e3018e
  grade: false
  grade_id: cell-026cd32f310cdcf6
  locked: true
  schema_version: 3
  solution: false
  task: false
---
cout << 1+2 << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7bd73f8b71b96c7f29d96b42387ba632", "grade": false, "grade_id": "cell-8213e311891544b5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Remarquez que, cette fois, ni le *type* ni `Out[...]` n'apparaissent.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "adb24c37f62b9ae155f0aa821bffc82d", "grade": false, "grade_id": "cell-8213e311891544b6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On peut afficher plusieurs valeurs à la suite.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d55fab22ee6473ae152b90e4f5d86480
  grade: false
  grade_id: cell-3c6a9159f8402f5e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
cout << 1+2 << endl;
cout << 3+4 << endl;
cout << 5+6 << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "40e496acb7e9efc4e5d7b5f991f97e7b", "grade": false, "grade_id": "cell-b86b795dcc6ef7ba", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On peut aussi afficher du texte (chaînes de caractères) en utilisant les guillemets:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2aa11d0f9907b8c3cc60fc9586afa19c
  grade: false
  grade_id: cell-6758df96fcdc4ca4
  locked: true
  schema_version: 3
  solution: false
  task: false
---
cout << "Bonjour, comment allez-vous ?" << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c349c22959b3978f1cda6d2e2730548a", "grade": false, "grade_id": "cell-992882d71d4cf502", "locked": true, "schema_version": 3, "solution": false, "task": false}}

♣ On peut mélanger texte et valeurs comme ci-dessous:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 80013d2679d7b0311783fc6b6e5f2891
  grade: false
  grade_id: cell-68e9d8e21f072ecf
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int age;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: deec6aca39365c83a4be40c965836cbf
  grade: false
  grade_id: cell-5642d7e1a8103e36
  locked: true
  schema_version: 3
  solution: false
  task: false
---
age = 32;
cout << "J'ai " << age << " ans." << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a5b84b7c0191badc1bc59843ebe241ac", "grade": false, "grade_id": "cell-63ee395ef8395a98", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice ♣**
1. Adaptez l'exemple précédent pour afficher votre age:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: d2f514ad6f10a3f4780d8817ac9119e7
  grade: true
  grade_id: cell-9314857feab44e21
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
age = 18;
cout << "J'ai " << age << " ans." << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "dba85bc0ec21e0fab16532b14645fb92", "grade": false, "grade_id": "cell-63ee395ef8395a99", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2. **Utilisez la variable `annee` ci-dessous pour afficher "Je suis né(e) en ****" où les **** sont votre année de naissance:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8f8fbc109383a5de2f7196a151bb95db
  grade: false
  grade_id: cell-a83264f8ccc04d6b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int annee;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 449317a87c62c900d0b1a72cf78bf80a
  grade: true
  grade_id: cell-c5e44d0cc9300b2c
  locked: false
  points: 0
  schema_version: 3
  solution: true
  task: false
---
annee = 2003;
cout << "Je suis ne en " << annee << "." << endl;
```

```{code-cell}

```

```{code-cell}

```

```{code-cell}

```

```{code-cell}

```
