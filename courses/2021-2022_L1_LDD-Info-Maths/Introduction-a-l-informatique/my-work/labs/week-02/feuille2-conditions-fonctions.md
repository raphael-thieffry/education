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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "993e3cfc362c57fc3809a818ac2b70c5", "grade": false, "grade_id": "cell-de476e0d8337c0db", "locked": true, "schema_version": 3, "solution": false}}

# TP2 feuille 2 : conditions et premières fonctions

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fdd1740046149c33b94b86f6d3b71050", "grade": false, "grade_id": "cell-71cc9182de965b41", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

- Que fait le code suivant (les trois cellules) ?

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: cea9661da089f7afebaf8ebec4a38624
  grade: false
  grade_id: cell-b9e1d24aed7658a4
  locked: true
  schema_version: 3
  solution: false
---
int a, b;
a = 5;
b = 10;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9dc551fa6592c8801d633fe7255ec892
  grade: false
  grade_id: cell-972f8e6180e008b9
  locked: true
  schema_version: 3
  solution: false
---
int c;
if ( a < b ) {
    c = b;
} else {
    c = a;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a91a2c6707c349f864202ddd44e923cd
  grade: false
  grade_id: cell-ff3c107d4a62380f
  locked: true
  schema_version: 3
  solution: false
---
c
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f610d021e3a3edfbe328ce26c832667b", "grade": true, "grade_id": "cell-4c14fdec1b05b316", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

Il determine le plus grand entre a et b pour le mettre dans une variable c

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e6e41c38440a173ee00db100d85a72f9", "grade": false, "grade_id": "cell-1b21180343eef5af", "locked": true, "schema_version": 3, "solution": false}}

- Écrivez un code similaire tel qu'une nouvelle variable `d` prenne la valeur minimale entre `b` et `a`.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 20146c6e1ba5f634191658f17f18f58b
  grade: false
  grade_id: cell-9f01d2d5f5a65db2
  locked: false
  schema_version: 3
  solution: true
---
int d;
if ( a < b ) {
    d = a;
} else {
    d = b;
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 0ae71839d38900e8a8860c72c838b75f
  grade: false
  grade_id: cell-d24f3749b7709d50
  locked: false
  schema_version: 3
  solution: true
---
d
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c225ffefb51c39c998c73344841b177e", "grade": false, "grade_id": "cell-53017ddafd267e8e", "locked": true, "schema_version": 3, "solution": false}}

- Exécutez les cellules suivantes.<br>

  Vous remarquerez que l'on a réutilisé le même code mais en lui donnant un *nom* et en précisant le type de ses   **entrées** et **sorties**. C'est ce qu'on appelle une *fonction* (nous reviendrons sur cette notion en cours). Ici la fonction `max` renvoie en sortie un type `int` (ce qui est précisé par le premier mot) et prend deux variables `int` en entrée (ce qui est précisé dans la parenthèse).

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f683b7167cfaa4759c70b6a542e36ce6
  grade: false
  grade_id: cell-da4b804e4c504f3b
  locked: true
  schema_version: 3
  solution: false
---
int max(int a, int b) {
    if ( a < b ) {
        return b; 
    } else {
        return a;
    }
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1bb920df18ef4b27cabe495bab5dc26a
  grade: false
  grade_id: cell-061b2450140c8d2b
  locked: true
  schema_version: 3
  solution: false
---
max(5, 10)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 61e0333071f3741ecc6a8bd1d1a8dd17
  grade: false
  grade_id: cell-864163c71609cc37
  locked: true
  schema_version: 3
  solution: false
---
max(6, -2)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1d9ca7e7475aca7a78d29da966e449ea
  grade: false
  grade_id: cell-2d29f0e326a60e99
  locked: true
  schema_version: 3
  solution: false
---
max(-3, -4)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a71f0ceecaf1649599055d3dcbde1bec
  grade: false
  grade_id: cell-2de41b75efa47469
  locked: true
  schema_version: 3
  solution: false
---
max(5, max(-3, 8))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8d6476a23a7ecf4710f0ab2ac3819305", "grade": false, "grade_id": "cell-c3c70549ea20c619", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Dans cet exercice, vous allez **utiliser** la fonction `max` pour calculer le maximum de deux nombres, trois nombres et quatre nombres.

```{code-cell}
int n1 = -2;
int n2 = 6;
int n3 = 0;
int n4 = 7;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "59bf7d2328849c0cb61cf94d1d426c9b", "grade": false, "grade_id": "cell-e529e7d0d77620ae", "locked": true, "schema_version": 3, "solution": false}}

* Calculez le max de n1 et n2 (en utilisant la fonction `max`)

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 5f814350ac5549481ff6158e997c2c9e
  grade: false
  grade_id: cell-c4a618042a781fed
  locked: false
  schema_version: 3
  solution: true
---
max(n1,n2)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cfe5c3be2111e03b307f0aae6692bc30", "grade": false, "grade_id": "cell-5c05a59c77ec8231", "locked": true, "schema_version": 3, "solution": false}}

* Calculez le max de n1, n2 et n3.<br>
  **Indication:** utilisez plusieurs fois la fonction comme dans le dernier exemple de l'exercice précédent.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: c9453b31ec0f98da640cc6513d1b23e9
  grade: false
  grade_id: cell-d40620294a7adbf1
  locked: false
  schema_version: 3
  solution: true
---
max(n1,max(n2,n3))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ca714b110bd8cb21e4ca06f8f8083a96", "grade": false, "grade_id": "cell-4305307abaff6133", "locked": true, "schema_version": 3, "solution": false}}

* Calculez le max de n1, n2, n3 et n4 (toujours en utilisant la fonction `max`)

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 0572cada6eab58ce451d66814801ac25
  grade: false
  grade_id: cell-cf566142f5e7376f
  locked: false
  schema_version: 3
  solution: true
---
max(n1,max(n3,max(n4,n2)))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "57bda93ba3bd248f22ab98a5f82227bb", "grade": false, "grade_id": "cell-825c2c774b85287f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

* Changez les valeurs de n1, n2, n3 et n4 ci-dessus, re-exécutez les cellules et vérifiez les résultats.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "23c8f5fde3bf9b1b31241f7c436502d3", "grade": false, "grade_id": "cell-d42d794979b056e3", "locked": true, "schema_version": 3, "solution": false}}

* ♣ Écrivez une fonction `max4` prenant quatre entiers et calculant leur max

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 7d168cd158520b324efd03084cc877c6
  grade: false
  grade_id: cell-d06ab9fcabc0bdd7
  locked: false
  schema_version: 3
  solution: true
---
int max4(int n1,int n2,int n3,int n4){
    return max(n1,max(n3,max(n4,n2)));
}
```

* ♣ Utilisez votre fonction `max4` pour calculer le max de n1, n2, n3 et n4.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1f1e1a8f5af0e65b132deb41e21a1021
  grade: false
  grade_id: cell-935d42263c50bd62
  locked: false
  schema_version: 3
  solution: true
---
max4(n1,n2,n3,n4)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2566e705667554c1e9f89519ce77b424", "grade": false, "grade_id": "cell-88fe335b6a80af8e", "locked": true, "schema_version": 3, "solution": false}}

**Attention: une fonction -- une cellule**

L'interpréteur C++ que nous utilisons (```Cling``` dans ```Jupyter```)
est à l'heure actuelle plus restrictif que nécessaire: lorsque l'on
souhaite définir une fonction, il est impératif que la définition de
cette fonction apparaisse seule dans sa cellule. En particulier on ne
peux pas définir deux fonctions dans une même cellule, ni faire
précéder ou suivre la définition d'une fonction par des instructions.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3adc59e11b8ffce0a0fb70ad8f4efb9f", "grade": false, "grade_id": "cell-88fe335b6a80af8d", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Complétez la fonction `min` ci-dessous.
Si vous en avez besoin, vous pouvez consulter l'exemple de la fonction `max` plus haut et l'adapter.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 27a212f755ea8263c7f7fe617262e51c
  grade: false
  grade_id: cell-d05c19054e863b1c
  locked: false
  schema_version: 3
  solution: true
---
int min(int a, int b) {
    int d;
    if ( a < b ) {
        d = a;
    } else {
        d = b;
    }
    return d;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a9962b22efc2622872fdff8a93f6bbf8", "grade": false, "grade_id": "cell-335ba529033a10a5", "locked": true, "schema_version": 3, "solution": false}}

Essayez-la sur l'exemple suivant:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6eae8b5c9d5b71ad9850284084cce7ef
  grade: false
  grade_id: cell-10d050d483c93cd7
  locked: true
  schema_version: 3
  solution: false
---
min(2,3)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "25ed497bd5c0fd3200e698deb90b225b", "grade": false, "grade_id": "cell-f496843756eede97", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Essayez-la sur un exemple de votre choix:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: bcdd57485ded7639dad88ea167206566
  grade: true
  grade_id: cell-808d44894a51f3f4
  locked: false
  points: 1
  schema_version: 3
  solution: true
---
min(666,999)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bdcb3695207a19780df65af44de23b8e", "grade": false, "grade_id": "cell-3be968dce7d1c332", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez que tous les tests qui suivent ont bien la valeur `true`:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3161ae409b9766d84a219cfbc6b84305
  grade: false
  grade_id: cell-864715e989ece636
  locked: true
  schema_version: 3
  solution: false
---
min(5, 10) == 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2f1665623d0f2f7ba9df868b614567c2
  grade: false
  grade_id: cell-a17b42a9df6d167b
  locked: true
  schema_version: 3
  solution: false
---
min(6, -2) == -2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 70ddffc20f84d3079b194b4de945780c
  grade: false
  grade_id: cell-136fb2ebf376c119
  locked: true
  schema_version: 3
  solution: false
---
min(-3, -4) == -4
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 658e35f29cf208284efbb83bd1f1a9df
  grade: false
  grade_id: cell-ef7513acc702c796
  locked: true
  schema_version: 3
  solution: false
---
min(5, min(-3, 8)) == -3
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2ce7160fbd67860c203d9d76eca42dcf", "grade": false, "grade_id": "cell-71cd2f16555fbd37", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La cellule suivante contient des tests automatisés; nous reviendrons dessus plus en détails par la suite; pour le moment, vous pouvez juste exécuter la cellule et vérifier qu'il n'y a pas de message d'erreur.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3fe3beb24a841afd420abe698f3807e0
  grade: true
  grade_id: cell-38e9d387004e6252
  locked: true
  points: 2
  schema_version: 3
  solution: false
---
ASSERT( min(5, 10) ==  5 );
ASSERT( min(6, -2) == -2 );
ASSERT( min(2,  2) ==  2 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d216f44c1fc1bc1121d757bd10cdd58c", "grade": false, "grade_id": "cell-3191c619f079e667", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Complétez la fonction `abs` ci-dessous qui calcule la valeur absolue d'un nombre:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e5a5d4b3203b1a3ea5553afcfd302899
  grade: false
  grade_id: cell-095f41446daefada
  locked: false
  schema_version: 3
  solution: true
---
double abs(double a) {
    if(a < 0){
        a = a*(-1);
    }
    return a;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1fb2eaf342ea713d4883f066fd7ddccb", "grade": false, "grade_id": "cell-cfc4aa59131634f8", "locked": true, "schema_version": 3, "solution": false}}

Utilisez cette fonction pour calculer la valeur absolue de `-2.5` et vérifiez le résultat:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: da617e8de0ba70f4bf45b2fa5c2503f0
  grade: false
  grade_id: cell-9ac842906e6ff3ee
  locked: false
  schema_version: 3
  solution: true
---
abs(-2.5)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ee62278a6b0fe98384c2f1e6b95796b9", "grade": false, "grade_id": "cell-a740aa7154cadb16", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez que les tests qui suivent ont bien la valeur `true`:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: aba849e6f99e92f4ec1831e3283a0b6b
  grade: false
  grade_id: cell-4303deeab7d5a1fd
  locked: true
  schema_version: 3
  solution: false
---
abs(-5.1) == 5.1
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f81c7b4564d6ba23a7878ec5a0451759
  grade: false
  grade_id: cell-49c5c14d2f7bfe22
  locked: true
  schema_version: 3
  solution: false
---
abs(2.3) == 2.3
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d1a03c8e7868eddbee2544011283e73f
  grade: false
  grade_id: cell-85c826da5978f5a7
  locked: true
  schema_version: 3
  solution: false
---
abs(-3.4) == 3.4
```

Vérifiez que les tests automatisés ci-dessous ne produisent pas de message d'erreur:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c8d9e022a53dba23b334b3ff9dfa887e
  grade: true
  grade_id: cell-4303deeab7d5a1fc
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( abs( 0.0) == 0.0 );
ASSERT( abs( 2.3) == 2.3 );
ASSERT( abs(-3.4) == 3.4 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1b4e6166617973cda3a56fc8bba442e6", "grade": false, "grade_id": "cell-403dc8b8bb8d58c4", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Complétez la fonction ci-dessous qui calcule et renvoie le périmètre d'un cercle. Vous remarquez que la constante `pi` n'est pas passée en paramètre car c'est une variable de calcul interne à la fonction (une variable *locale*), et non une entrée de cette fonction.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 17be65caa36d6fae64fd1d08032f8b61
  grade: true
  grade_id: cell-292a7f3566822daf
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
double perimetre(double r) {
    double pi = 3.1415;
    return 2*pi*r;
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9cec06b28fad42f348ee83a080bb0424
  grade: false
  grade_id: cell-1e5f403ea97f610b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
perimetre(2) // environ 12.56
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 671905184bf05c08df4a941f107bb60f
  grade: false
  grade_id: cell-f97479572d518e78
  locked: true
  schema_version: 3
  solution: false
  task: false
---
perimetre(3) // environ 18.85
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2b1abd6e9fac47c73d1a13009f79b6be", "grade": false, "grade_id": "cell-e8cb8fec41aa1460", "locked": true, "schema_version": 3, "solution": false}}

Calculez le périmètre d'un disque de rayon 5 et vérifiez de tête le résultat

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 95c470b4ff7f93004252b1536fc99b10
  grade: false
  grade_id: cell-9c8c427308e28a15
  locked: false
  schema_version: 3
  solution: true
---
perimetre(5)
```

Vérifiez que les tests automatisés ci-dessous ne produisent pas de message d'erreur:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a24aa03978ff7aa617439f6e5f6388d9
  grade: true
  grade_id: cell-69ef785287a5d727
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( std::abs(perimetre( 10) - 62.83) < 0.1 );
ASSERT( std::abs(perimetre(100) - 628.3) < 0.1 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2af9a2d92f24a28ba727b4fcce175d9d", "grade": false, "grade_id": "cell-95680906d451aa5b", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Sur le même modèle, écrivez une fonction `aire` qui renvoie l'aire d'un cercle dont on donne le rayon. Testez-la.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: aad58a88d710e430e63bd4fb49525c44
  grade: true
  grade_id: cell-a8996942ad9ba66b
  locked: false
  points: 2
  schema_version: 3
  solution: true
  task: false
---
double aire(double r) {
    double pi = 3.1415;
    return r*pi*r;
}
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e321117b3abb0a9b8f4ed3d374008477
  grade: false
  grade_id: cell-067f95bd179cf29d
  locked: false
  schema_version: 3
  solution: true
---
aire(10)
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a9a5b76cb5bbf9f304e75ef37671bb78
  grade: false
  grade_id: cell-7d7ab6ff354eb484
  locked: false
  schema_version: 3
  solution: true
---
aire(3.14)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 56a402dc34ece0f1df92342aab0ed66b
  grade: true
  grade_id: cell-69ef785287a5d726
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
ASSERT( std::abs(aire( 10) - 314.15) < 0.1 );
ASSERT( std::abs(aire(100) - 31415 ) < 0.1 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "896f14f77bb2f271c8cbc285dd42c630", "grade": false, "grade_id": "cell-72500357fd98d2d3", "locked": true, "schema_version": 3, "solution": false}}

Bravo, vous avez fini l'exercice «Jupyter: affectations, conditionnelles, fonctions» du TP.

Retournez sur l'énoncé du TP pour consulter la suite des instructions.
