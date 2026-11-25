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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1412fa8dba22a59e78085d1ef371cf70", "grade": false, "grade_id": "cell-05f3f0bf76964094", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Laby: C'est fou!

Les obstacles se multiplient pour un défi de plus.

[Niveau précédent](counting-the-rocks.md), <!--[Liste des niveaux](index.md#ListeDesNiveaux), !-->[Documentation](0b.md#Documentation)

```{code-cell}

```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: bc35b69bd1a771b374ded8ac10994819
  grade: false
  grade_id: cell-2d8f822c47ec883b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <laby/global_fr.hpp>
LABY("this-is-crazy")
```

```{code-cell}
void posecaillou(){
    int a = 0;
    while(regarde()==Mur || regarde() == Caillou || regarde() == Sortie){
        droite();
        a=a+1;
    }
    pose();
    for ( int i = a ; i <= 3 ; i++ ) {
    droite();
}
}
```

```{code-cell}
void cailloutoile() {
    if(regarde() == Toile){
    pose();
    prend();
    avance();
}
}
```

```{code-cell}
void mur() {
    if(regarde() == Mur){
        droite();
        if(regarde() == Mur){
            gauche();
            gauche();
        }
}
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ed3956dc6d566367f1863251306613bc
  grade: false
  grade_id: cell-6f9c72052cad1db8
  locked: false
  schema_version: 3
  solution: true
  task: false
---
debut();
avance();
while(regarde() == Vide){
    avance();
    gauche();
    avance();
}
while(regarde() != Caillou){
    droite();
    droite();
    avance();
    gauche();
    avance();
    avance();
    gauche();
    avance();
}
prend();
droite();
droite();
avance();
gauche();
while(regarde() != Toile){
    avance();
}
cailloutoile();
while(regarde() != Sortie){
    avance();
    mur();
    if(regarde() == Caillou){
        posecaillou();
        prend();
    }
    if(regarde() == Toile){
        cailloutoile();
    }
}
posecaillou();
ouvre();
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0b3258d7d7cce668e9d5c016c44cdb88
  grade: true
  grade_id: cell-5d7826a54cfe3158
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
