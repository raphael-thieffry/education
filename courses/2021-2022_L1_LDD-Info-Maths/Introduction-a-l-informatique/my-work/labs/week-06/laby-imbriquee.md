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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1331bcc8e53f23e6fbce19d42db17a2f", "grade": false, "grade_id": "cell-b31ba63729e95016", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Boucles imbriquées

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8f5f24b64cf7e07a0d3902650585e7b6", "grade": false, "grade_id": "cell-8e4fbe3af67bde53", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:**

Dans cet exercice, nous utiliserons les boucles imbriquées pour dessiner en laby. On veut dessiner ligne par ligne avec la fourmi et l'instruction seme(). Commencez par exécuter les cellules ci-dessous pour comprendre ce que fait l'instruction seme().

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: dd787c75eda09db4fe44e3d2ad8fecb8
  grade: false
  grade_id: cell-b0d580c556865d98
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
editable: false
nbgrader:
  cell_type: code
  checksum: d6accadb3db8698eedc994a64cd0ea18
  grade: false
  grade_id: cell-b0d580c556865d96
  locked: true
  schema_version: 3
  solution: false
  task: false
---
avance();
avance();
seme();
avance();
avance();
seme();
seme();
seme();
avance();
avance();
seme();
avance();
seme();
avance();
seme();
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "522b73e959b6f892fb97a0b18333098f", "grade": false, "grade_id": "cell-8e4fbe3af67bde54", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On vous donne la fonction avance_tant_que_tu_peux qu'on a vue dans les premiers TPs, adaptée pour que la fourmi puisse revenir sur ses pas après avoir fini une ligne.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ac042bde59c385eef1c89c88681bbe66
  grade: false
  grade_id: cell-81a99c8f399b859d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <iostream>
#include <laby/global_fr.hpp>
#include <cstdlib>
using namespace std;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3aa1301c22feee0e33a895d03e16ac4b
  grade: false
  grade_id: cell-81a99c8f399b859e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/**Fait avancer la fourmi tant qu'elle a un espace vide devant elle.**/
void avance_tant_que_tu_peux() {
    while ( regarde() == Vide or regarde() == PetitCaillou ) {
        avance();
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d1819020d9f9c2f6edd9df7d3d0d42e2", "grade": false, "grade_id": "cell-fd0933aaa600036b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1. Écrivez une fonction `carre(int L)` qui prend en paramètre un entier L, et qui fait dessiner à la fourmi un carré plein avec côtés de longueur L. Par exemple, pour $L=5$, la fourmi dessinera:
        *****
        *****
        *****
        *****
        *****

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 67616729600b99f3d2914836bb54b4be
  grade: false
  grade_id: cell-b0d580c556865d9A
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
  checksum: 7ae252f1dc7055574ae8ffd36e12b406
  grade: true
  grade_id: cell-bf212efeb0472746
  locked: false
  points: 0
  schema_version: 3
  solution: true
  task: false
---
// Entrée : un entier L, correspondant à la longueur d'un côté de la trajectoire.
// Sortie : aucune, déplace la fourmi selon un carré de longueur L
void carre(int L){
    // VOTRE CODE ICI
    // VOTRE CODE ICI
}
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
  checksum: 962f5e80910cf020042ab2e32508ff9d
  grade: false
  grade_id: cell-61f6cbe5090c44f8
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre(1) // La fourmi doit tourner et dessiner sur elle-même.
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d6c2801c5d982ae88b23a6b862c3b218
  grade: false
  grade_id: cell-cd855fcd1a51f005
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre(5) // Dessin d'un carré plein avec côtés de longueur 5
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0672048d5edf4232cc82474fcb992d24", "grade": false, "grade_id": "cell-fd0933aaa600036c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2. Même question mais cette fois la fonction `carre_vide(int L)` affiche un carré vide. Pour l’exemple précédent, la fourmi dessinera:

        *****
        *   *
        *   *
        *   *
        *****

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b0949b406fc96af23521ad8ac5713e16
  grade: false
  grade_id: cell-b0d580c556865d99
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
  checksum: d91d02d07ebf160a29d8afe9f8f27a1c
  grade: true
  grade_id: cell-bf212efeb0472747
  locked: false
  points: 0
  schema_version: 3
  solution: true
  task: false
---
// Entrée : un entier L, correspondant à la longueur d'un côté de la trajectoire.
// Sortie : aucune, déplace la fourmi selon un carré de longueur L
void carre_vide(int L){
    // VOTRE CODE ICI
    // VOTRE CODE ICI
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0bf3d74a71340c8363f55644f8633a1e
  grade: false
  grade_id: cell-b7280173f444a975
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre_vide(0) // La fourmi ne fait rien
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: aab30c2f950f2b796bd72e8543711c47
  grade: false
  grade_id: cell-61f6cbe5090c44f7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre_vide(1) // La fourmi doit tourner et dessiner sur elle-même.
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f901988a796628455365e70062f5facb
  grade: false
  grade_id: cell-cd855fcd1a51f006
  locked: true
  schema_version: 3
  solution: false
  task: false
---
carre_vide(5) // Dessin d'un carré vide avec côtés de longueur 5
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5923eeaed6b47920d728db91e8982b69", "grade": false, "grade_id": "cell-d2be9b92b87f6618", "locked": true, "schema_version": 3, "solution": false, "task": false}}

3.  Écrire une fonction `triangle_rect(int h)` qui, pour un entier positif $h$ donné, affiche le triangle rectangle plein avec côtés de longueur $h$. Par exemple, pour $h=5$, la fourmi dessinera:
    ```
        *
        **
        ***
        ****
        *****
    ```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 78c47945c84070809371bca38ff53a45
  grade: false
  grade_id: cell-b0d580c556865d97
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
  checksum: dc06638c1dd0e88294f4dff38d98a709
  grade: true
  grade_id: cell-ed285270a4f27c05
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void triangle_rect(int h) {
    // VOTRE CODE ICI
    // VOTRE CODE ICI
}
```

```{code-cell}
triangle_rect(8)
```

```{code-cell}
triangle_rect(4)
```

```{code-cell}
triangle_rect(2)
```

```{code-cell}
triangle_rect(0)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0f636d8b6334b237aab990a5055ec98b", "grade": false, "grade_id": "cell-d2be9b92b87f6619", "locked": true, "schema_version": 3, "solution": false, "task": false}}

4. ♣ Écrire une fonction `triangle_iso(int h)` qui, pour un entier positif $h$ donné, affiche le triangle isocèle pointe en haut, de hauteur $h$ et de base $2h-1$. Par exemple, pour $h=5$, la fourmi dessinera:
    ```
            *
           * *
          *   *
         *     *
        *********
    ```

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
  checksum: b05a3e7ffa132b58386095f39ff74985
  grade: true
  grade_id: cell-ed285270a4f27c06
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void triangle_iso(int h) {
    // VOTRE CODE ICI
    // VOTRE CODE ICI
}
```

```{code-cell}
triangle_iso(4)
```

```{code-cell}
triangle_iso(2)
```

```{code-cell}
triangle_iso(1)
```

```{code-cell}
triangle_iso(0)
```
