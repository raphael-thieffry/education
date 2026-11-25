---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0a15ddb6db175b9077cc40cc1329f7dd", "grade": false, "grade_id": "cell-64acacb345e940e0", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Laby: Compter les cailloux
Ce niveau se résout facilement quand on peut compter… La boucle «for» est là pour vous !

[Niveau précédent](4b.md), <!--[Liste des niveaux](index.md#ListeDesNiveaux), !-->[Niveau suivant](this-is-crazy.md), [Documentation](0b.md#Documentation)

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 10d050a6ba96c43f9d67257dbfae88ca
  grade: false
  grade_id: cell-ee3432e66e9fe991
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <laby/global_fr.hpp>
LABY("counting-the-rocks")
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a87ae4ac50b3c03f6a8553d54047e662
  grade: false
  grade_id: cell-dc0eba466ac0f400
  locked: false
  schema_version: 3
  solution: true
  task: false
---
debut();
avance();
for ( int i = 0 ; i <= 6 ; i++ ) {
    prend();
    droite();
    droite();
    pose();
    droite();
    droite();
    avance();
}
gauche();
while(regarde() == Vide){
    avance();
}
gauche();
while(regarde() == Vide){
    avance();
}
droite();
prend();
    droite();
    pose();
    droite();
    droite();
droite();
    avance();
for ( int i = 0 ; i <= 2 ; i++ ) {
    prend();
    droite();
    droite();
    pose();
    droite();
    droite();
    avance();
}
droite();
avance();
for ( int i = 0 ; i <= 4 ; i++ ) {
    prend();
    droite();
    droite();
    pose();
    droite();
    droite();
    avance();
}
gauche();
while(regarde() == Vide){
    avance();
}
ouvre();
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f4b82a934191003cd10a7d7a2d705325
  grade: true
  grade_id: cell-f81330eca20c0208
  locked: true
  points: 0
  schema_version: 3
  solution: false
  task: false
---
ASSERT( a_gagne() );
```

```{code-cell}

```
