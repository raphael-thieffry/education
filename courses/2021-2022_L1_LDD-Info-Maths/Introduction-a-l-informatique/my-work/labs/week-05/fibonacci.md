---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++11
  language: C++11
  name: xcpp11
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c9d522b181e17f49db45148082f0f9e1", "grade": false, "grade_id": "cell-b8ffd3e2724b20a4", "locked": true, "schema_version": 3, "solution": false}}

# Suite de Fibonacci
Dans cette feuille, vous allez implanter les trois algorithmes vus en TD pour calculer la suite de Fibonacci.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6abc94e6f60d4b65559aa19ff9bea687
  grade: false
  grade_id: cell-23c28693bb24e284
  locked: true
  schema_version: 3
  solution: false
---
#include <iostream>
#include <vector>
using namespace std;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "83c30cdfad513b3b9258975555e91210", "grade": false, "grade_id": "cell-c1cf4d9dd7f36f7a", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (Fibonacci, version tableau)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "116a7c11b4ffb1be62a837b89616a849", "grade": false, "grade_id": "cell-af9fdb729ae1af5e", "locked": true, "schema_version": 3, "solution": false}}

- Écrire la documentation puis implanter la fonction `fibonacciTableau`:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: bb9f62796ce5ec3fc6309d61a88a6792
  grade: true
  grade_id: cell-fe5ec9160e7fe4ed
  locked: false
  points: 1
  schema_version: 3
  solution: true
---
/** renvoie lentier numero n de la suite de fibonnacci
* @param n un entier
* @return l'element n de la suite de fibonacci
**/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: dce9fb860a743896f9fa7363bf531338
  grade: false
  grade_id: cell-3e99d334583cf0cf
  locked: false
  schema_version: 3
  solution: true
---
int fibonacciTableau(int n) {
    if(n == 1 or n == 2){
        return 1;
    }else{
        vector<int> t (n);
        t[0]=1;
        t[1]=1;
        for(int i=2; i<t.size();i++){
            t[i]=t[i-2]+t[i-1];
        }
        return t[n-1];
    }
    
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "dcd1bd0619b33082946d82eded78e986", "grade": false, "grade_id": "cell-3a5a77e9d38662a1", "locked": true, "schema_version": 3, "solution": false}}

- Vérifier que votre fonction passe les tests:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e2bab872eedc0eb8df1a699bb5d3e3ff
  grade: true
  grade_id: cell-de81c742ca06b1fe
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( fibonacciTableau(1) == 1 );
CHECK( fibonacciTableau(2) == 1 );
CHECK( fibonacciTableau(3) == 2 );
CHECK( fibonacciTableau(4) == 3 );
CHECK( fibonacciTableau(5) == 5 );
CHECK( fibonacciTableau(6) == 8 );
CHECK( fibonacciTableau(9) == 34 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f10985fb7a3d021593310005f435baa9", "grade": false, "grade_id": "cell-96df4c2d033a6499", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (Fibonacci, version trois variables)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c8796c470ea2f913e51c1eb4d55c95b0", "grade": false, "grade_id": "cell-769dae242b7fe173", "locked": true, "schema_version": 3, "solution": false}}

- Écrire la documentation puis implanter la fonction `fibonacciVariables`:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6ea39b45780586e23f8bac4e90dbee5f
  grade: true
  grade_id: cell-e9a26741525a8c7f
  locked: false
  points: 1
  schema_version: 3
  solution: true
---
/** renvoie lentier numero n de la suite de fibonnacci
* @param n un entier
* @return l'element n de la suite de fibonacci
**/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 773bed6526638aa68a6681672b568f50
  grade: false
  grade_id: cell-0293b05d6b32527e
  locked: false
  schema_version: 3
  solution: true
---
int fibonacciVariables(int n) {
    int imoins1 = 1;
    int imoins2 = 1;
    int res;
    if(n == 1 or n == 2){
        return 1;
    }else{
        for(int i = 3; i<=n;i++){
            res = imoins1+imoins2;
            imoins2=imoins1;
            imoins1=res;
        }
        return res;
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0e0ec37b8dc48f1d3d232ee77d1f726e", "grade": false, "grade_id": "cell-a58a9782a8e07d88", "locked": true, "schema_version": 3, "solution": false}}

- Tests :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 680abd6defdbd6e020821494f65b5e35
  grade: true
  grade_id: cell-64a1a8cdcb6263c0
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( fibonacciVariables(1) == 1 );
CHECK( fibonacciVariables(2) == 1 );
CHECK( fibonacciVariables(3) == 2 );
CHECK( fibonacciVariables(4) == 3 );
CHECK( fibonacciVariables(5) == 5 );
CHECK( fibonacciVariables(6) == 8 );
CHECK( fibonacciVariables(9) == 34 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "109018c54be48cf6ca9fe2035b3fb065", "grade": false, "grade_id": "cell-dca03131b57768e0", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (Fibonacci, version récursive)

- Écrire la documentation puis implanter la fonction `fibonacciRecursive`:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 61d2520d8a6012c21cc04c54da66c650
  grade: true
  grade_id: cell-c6bdea95ffb619b8
  locked: false
  points: 1
  schema_version: 3
  solution: true
---
/** renvoie lentier numero n de la suite de fibonnacci
* @param n un entier
* @return l'element n de la suite de fibonacci
**/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 5f91dde378eb809136385b2580573bf5
  grade: false
  grade_id: cell-06ce675728db14a4
  locked: false
  schema_version: 3
  solution: true
---
int fibonacciRecursive(int n) {
    if(n == 1 or n == 2){
        return 1;
    }else{
        return fibonacciRecursive(n-1)+fibonacciRecursive(n-2);
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "915ef8b631f036a710480b7efbdcf966", "grade": false, "grade_id": "cell-7433fd515737443c", "locked": true, "schema_version": 3, "solution": false}}

- Tests :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9f51a7caf0fd54250e8dea8b09aa6910
  grade: true
  grade_id: cell-f86b56741701c2a2
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( fibonacciRecursive(1) == 1 );
CHECK( fibonacciRecursive(2) == 1 );
CHECK( fibonacciRecursive(3) == 2 );
CHECK( fibonacciRecursive(4) == 3 );
CHECK( fibonacciRecursive(5) == 5 );
CHECK( fibonacciRecursive(6) == 8 );
CHECK( fibonacciRecursive(9) == 34 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0ef2d09428d0a67c4b807c318f8b16f3", "grade": false, "grade_id": "cell-c33cb1e5921e4f23", "locked": true, "schema_version": 3, "solution": false}}

- ♣ Exécuter la version récursive avec une grande valeur pour n (par exemple 200).

```{code-cell}
fibonacciRecursive(100)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3e0f304c1353521f0e8fd0da45717bd6", "grade": true, "grade_id": "cell-15aced9ad15bb5cd", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

- Que se passe-t-il?
  C'est tres long a calculer
- ♣ A votre avis, est-il possible de remédier à ce problème?

```{code-cell}

```
