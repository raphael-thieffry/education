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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "35f5770dacd83c1cdaa941baf058f895", "grade": false, "grade_id": "cell-b31ba63729e95016", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# ♣ Dessins géométriques

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "97abf3c1dcbe5ac1eb08bf73cd584372", "grade": false, "grade_id": "cell-8e4fbe3af67bde53", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:**

Dans cet exercice, nous utiliserons des affichages et auront donc
besoin de la bibliothèque C++ correspondante:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 879d06094a1ea8eac50797cbb7bcfb18
  grade: false
  grade_id: cell-81a99c8f399b859d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <iostream>
using namespace std;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5afe1e26280b3d972396257ad2992033", "grade": false, "grade_id": "cell-352f77c979379bf6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1.  Écrire une fonction `carre_plein` qui, pour un entier positif non nul $L$ donné,
    affiche sur la sortie standard un carré plein dont les côtés sont de
    longueur $L$ caractères. Par exemple, pour $L=5$, la fonction
    affichera:

        *****
        *****
        *****
        *****
        *****

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f53b90dc9fc8580b491db961ebcea44b
  grade: true
  grade_id: cell-aa60e6ba0f4ca604
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void carre_plein(int L) {
    for(int i = 1; i<=L; i++){
        for(int i = 1; i<=L; i++){
            printf("*");
        }
        printf("\n");
    }
}
```

```{code-cell}
carre_plein(5)
```

```{code-cell}
carre_plein(3)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "10e584212681419b1c71c96c357bc9cf", "grade": false, "grade_id": "cell-38495cd34c8d0e2c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2.  Même question mais cette fois la fonction affiche un carré vide.
    Pour l’exemple précédent, cela donne:

        *****
        *   *
        *   *
        *   *
        *****

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 159fc7ffc2099b2f6eae3d63854f6aeb
  grade: true
  grade_id: cell-e7cca0ee7af7856b
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void carre_vide(int L) {
   for(int i = 1; i<=L; i++){
        if(i == 1 or i == L){
            for(int i = 1; i<=L; i++){
                printf("*");
            }
        }else{
            printf("*");
            for(int i = 1; i<=L-2; i++){
                printf(" ");
            }
            printf("*");
        }
        printf("\n");
    }
}
```

```{code-cell}
carre_vide(5)
```

```{code-cell}
carre_vide(2)
```

```{code-cell}
carre_vide(1)
```

```{code-cell}
carre_vide(0)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7e5a84f4ce6e4d61231f1352fd94d89b", "grade": false, "grade_id": "cell-21ee6e6db6c72122", "locked": true, "schema_version": 3, "solution": false, "task": false}}

3.  Transformer votre fonction pour qu’il soit simple de remplacer le
    caractère * par un autre caractère `caractere`:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6369a52123c9b20aea49774daaccb2ac
  grade: true
  grade_id: cell-432dd624ee8d341f
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
void carre_vide(int L, string caractere) {
       for(int i = 1; i<=L; i++){
        if(i == 1 or i == L){
            for(int i = 1; i<=L; i++){
                cout << caractere;
            }
        }else{
                cout << caractere;
            for(int i = 1; i<=L-2; i++){
                printf(" ");
            }
            cout << caractere;
        }
        printf("\n");
    }
}
```

```{code-cell}
carre_vide(4, "#")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "17ea73c96952731ba89cc616b826eec3", "grade": false, "grade_id": "cell-d2be9b92b87f6618", "locked": true, "schema_version": 3, "solution": false, "task": false}}

4.  Écrire une fonction qui, pour un entier positif $h$ donné, affiche
    le triangle isocèle  pointe en haut  dont le contour est décrit par
    des étoiles, de hauteur $h$ et de base $2h-1$. Par exemple, pour
    $h=5$, la fonction affichera:
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
nbgrader:
  cell_type: code
  checksum: ba90939056fa142884dfd794dbce87ff
  grade: true
  grade_id: cell-ed285270a4f27c05
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void triangle(int h, string caractere="*") {
    int base = 2*h-1;
     for(int i = 1; i<=h; i++){
        if(i == h){
            for(int k = 1; k<=base; k++){
                cout << caractere;
            }
        }else if(i == 1){
            for(int u = 1; u<=base/2; u++){
                printf(" ");
            }
            cout << caractere;
        }else{
            for(int m = (base/2)-1; m>=1; m--){
                for(int i = 2; i<=m; i++){
                    printf(" ");
                }
            }
            cout << caractere;
            for(int m = 1; m<=base-1; m++){
                for(int i = 0; i<=m; i++){
                    printf(" ");
                }
            }
            cout << caractere;
        }
        printf("\n");
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c9664e01c60b8c90de718b2ea54c3f84", "grade": false, "grade_id": "cell-c684cbb420e12f44", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous noterez ci-dessous que l'on a donné une valeur par défaut pour `caractere`: `*`.
Du coup, on peut utiliser les deux formes suivantes:

```{code-cell}
triangle(4)
```

```{code-cell}
triangle(5, "#")
```

```{code-cell}
triangle(2)
```

```{code-cell}
triangle(1)
```

```{code-cell}
triangle(0)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c62dfc055c26bc55e2b87fe84e54e1c2", "grade": false, "grade_id": "cell-21a24a581169dd5f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

5.  Écrire une fonction qui affiche un losange. Par exemple, pour
    $h=5$, la fonction affichera:

            *
           * *
          *   *
         *     *
        *       *
         *     *
          *   *
           * *
            *

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6e079081d2266c43f8bfed6421bc7264
  grade: true
  grade_id: cell-b40856987b98d13d
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
void losange(int h, string caractere="*") {
    // VOTRE CODE ICI
}
```

```{code-cell}
losange(5)
```

```{code-cell}
losange(1)
```

```{code-cell}
losange(0)
```
