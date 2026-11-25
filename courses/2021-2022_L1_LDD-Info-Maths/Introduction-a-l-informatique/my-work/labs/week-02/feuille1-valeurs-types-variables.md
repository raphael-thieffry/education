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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0bc8f5b451833f0c8f12a57730708157", "grade": false, "grade_id": "cell-b78562ee2ff6d72c", "locked": true, "schema_version": 3, "solution": false}}

# TP 2, Feuille 1 : valeurs, types et variables

## Introduction à Jupyter et premiers calculs

Lors de ces premières semaines de cours, nous allons travailler dans l'application web *Jupyter* qui permet d'exécuter du code `C++` interactivement, un peu comme une super calculatrice. Plus tard, nous verrons comment créer un programme `C++` indépendant en dehors de *Jupyter*.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1329d3804d96ba3e74c93ba23ed0bb01", "grade": false, "grade_id": "cell-33660fa4ef5903e4", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

- Cliquez sur la cellule suivante puis exécutez la en appuyant sur les touches `Maj+Entr` .

```{code-cell}
1 + 924
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2ae3ce1d83a565f46da2b561cc55d30d", "grade": false, "grade_id": "cell-291a3535b726abef", "locked": true, "schema_version": 3, "solution": false}}

La première ligne donne le résultat du calcul. La deuxième ligne indique que ce résultat est de type *entier* (`int`).

Techniquement parlant, le navigateur web a envoyé le contenu `1+1` de la cellule à un *noyau* (kernel en anglais) qui l'a *compilé* et *exécuté*, avant de renvoyer le résultat à afficher. Le noyau que nous utilisons (`C++11`) permet de travailler en `C++`. Il existe des noyaux pour beaucoup d'autres langages de programmation.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6d43cb2b8f7e89bf236ccae8b5c6a9dd", "grade": false, "grade_id": "cell-c7495bbedb1de8c7", "locked": true, "schema_version": 3, "solution": false}}

- Modifiez l'expression dans la cellule précédente et exécutez la de nouveau.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "268fb44487d223bfae33e1dbcf7e0b29", "grade": false, "grade_id": "cell-12b1679926b1768d", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

* Utilisez la cellule suivante pour calculer la surface d'un rectangle de largeur 25 et de longueur 37.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 5a844ab147a2f6ba85923671f196e85d
  grade: false
  grade_id: cell-b645bc465bd310ae
  locked: false
  schema_version: 3
  solution: true
ordo_failure: "R\xE9ponse incorrecte; essayes encore!"
ordo_solution:
  text/plain: '925

    type: int'
ordo_success: "Bonne r\xE9ponse!"
---
25*37
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c8af574d3e59a483fb32168752794312", "grade": false, "grade_id": "cell-30c68bc6103bcacf", "locked": true, "schema_version": 3, "solution": false}}

* Regardez le type du résultat. Quels autres types de variables avez-vous vus en cours ?
* Refaites le calcul précédent de sorte que son type soit `double`:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a0b1e710683aafa0ee948c25879f1696
  grade: false
  grade_id: cell-7db7adf07618a111
  locked: false
  schema_version: 3
  solution: true
ordo_failure: "R\xE9ponse incorrecte; essayes encore!"
ordo_solution:
  text/plain: '925

    type: double'
ordo_success: "Bonne r\xE9ponse!"
---
double resultat = 25*37;
resultat
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "98fc56b8a08c3997f1c1b2b5286c5a8f", "grade": false, "grade_id": "cell-7c72028bf998c9e5", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Les lignes suivantes vous présentent des exemples de calculs. Exécutez-les en observant bien la valeur du résultat et son type.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 593fcfb7063e8d55389842ed36c10a03
  grade: false
  grade_id: cell-678ae0462813d831
  locked: true
  schema_version: 3
  solution: false
  task: false
---
3*(1+3) + (1+4)*(2+4)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9f3cc6c0e458e40336da192b6f55aa16
  grade: false
  grade_id: cell-8c8f01689a82794b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
42 / 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: babcd64046ca10ca7696da6a16825c30
  grade: false
  grade_id: cell-9678ffe15c270b81
  locked: true
  schema_version: 3
  solution: false
  task: false
---
42 / 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a1b61504a42f653f72eeb746b99dd23f
  grade: false
  grade_id: cell-15172444994cbdff
  locked: true
  schema_version: 3
  solution: false
  task: false
---
42. / 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7f94e7cc2a78f5f84d00835ab6e3c7fc
  grade: false
  grade_id: cell-7009aedea5b1e925
  locked: true
  schema_version: 3
  solution: false
  task: false
---
42 % 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 73faf81ec97e7a196d35eb58d0016ed1
  grade: false
  grade_id: cell-7c66e2817d57b95c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 + 1.
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: eb7d7730da271c2d1e497aa89c9ad470
  grade: false
  grade_id: cell-33bc66dde9266641
  locked: true
  schema_version: 3
  solution: false
  task: false
---
42 == 6*7
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 88c54f98c8270c287d5ff9cf434e1f2a
  grade: false
  grade_id: cell-3163364eab44d8d7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
41 == 2*21
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "60ba4d2ff75acaa820d33009b21b7679", "grade": false, "grade_id": "cell-cf97d7e3ffc985a0", "locked": true, "schema_version": 3, "solution": false}}

Remarque: dans les deux cellules précédentes, nous avons utilisé un **double égal** `==` qui sert à **tester** une égalité. Nous reverrons bientôt la signification du **simple égal** `=`.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: dbabeaac7e3f9d86ef9a32e951cd5df1
  grade: false
  grade_id: cell-d4b738450011dd37
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 < 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0a8e6b094ad756a7c0ffa364fcc7ee15
  grade: false
  grade_id: cell-3e5e3a25f145a973
  locked: true
  schema_version: 3
  solution: false
  task: false
---
2 > 3
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: cb08d8a9c4574e2b2adad48f3464fad8
  grade: false
  grade_id: cell-606159825dc54bf9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 < 2 and 2 > 3
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 697a998ec2daa1290313a8fc7797575d
  grade: false
  grade_id: cell-783a55b0abd2377f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 < 2 or 2 > 3
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f23b75ba212d267c483f435b6c03e00a", "grade": false, "grade_id": "cell-05caf97c8306b9b4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Note: pour éviter de fausses manœuvres, nous configurons de nombreuses
cellules, telles celles ci-dessus, pour qu'elles soient non modifiables.
Pour faire vos propres expérimentations ou pour prendre des notes personnelles,
vous pouvez à tout moment insérer de nouvelles cellules. Insérez maintenant
une cellule ci-dessous en utilisant le Menu `Insérer`. Ensuite, utilisez
le menu `Cellule` -> `Type de cellule` pour en faire une cellule de texte
(`Markdown`). Notez les raccourcis claviers dans les menus.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b5cb9ead75f6ec588e99ab1c29144611", "grade": false, "grade_id": "cell-884721498ad284a1", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Pour chacune des expressions suivantes, déterminez **de tête** le type et le résultat, et donnez votre réponse à l'endroit indiqué sous la forme `type`, `résultat`; puis vérifiez en exécutant la cellule.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "acc1ab54dc1bb46edba6eace7c302d8f", "grade": true, "grade_id": "cell-a8d152d15809265f", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

 ---
 * Type : int
 * Résultat : 11

VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a72897335f295c7d452b11e914f2fc49
  grade: false
  grade_id: cell-0f3ff9e9e4c33f41
  locked: true
  schema_version: 3
  solution: false
---
3 * 2 + 5
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cac25377cf4f4f98abca71d47a3056a5", "grade": true, "grade_id": "cell-b866905e681f44cb", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

 ---
 * Type : int
 * Résultat : 12
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 962d88d6809f73496c72662e2f1a341d
  grade: false
  grade_id: cell-127febc577edfc08
  locked: true
  schema_version: 3
  solution: false
---
25 / 2
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "29b0780506487bdcf9193e50b85bcd21", "grade": true, "grade_id": "cell-899fabbcd7ecd371", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : double
 * Résultat : 7.0000
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: dfc73c6565beb9718da57a04d56a539a
  grade: false
  grade_id: cell-286c54ae7e34701d
  locked: true
  schema_version: 3
  solution: false
---
3.5*2
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ced4a55522cc6ebe19e5dcf558ca7a3e", "grade": true, "grade_id": "cell-fe0c64ef514d2b0f", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type: double
 * Résultat : 4.66667
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 20a02b357e2b564128c22de02d6bafff
  grade: false
  grade_id: cell-b52c330c011b1b89
  locked: true
  schema_version: 3
  solution: false
  task: false
---
14. / 3
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "71a31a0e0c76f23428f6d87b7610ded2", "grade": true, "grade_id": "cell-b1b2d0d4b7baa06e", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat : true
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5d1d2f1a6a8c2051575b59fe5305d7ab
  grade: false
  grade_id: cell-67ced375854c7fb3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
3*7 == 21
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "96df40422a798cfc424d6a15527c1ba5", "grade": true, "grade_id": "cell-59ff90739ae5b7b2", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat :true
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1ed41b3835b89e6fcbc70955741fe280
  grade: false
  grade_id: cell-959d3023456a140e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
(3*7 == 21) and (4.2 > 5.3 or 4*4 == 8*2)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "afac64ca0e2acf1e56d5b291f09ff4cc", "grade": true, "grade_id": "cell-2bf659cbac5d597a", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat : false
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: abfc8ff20663be8e6949ec8c6c06ce55
  grade: false
  grade_id: cell-f47f3ad36d564ee3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
true and false
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d9be423dac4dd246285b49910fe60594", "grade": true, "grade_id": "cell-e5856c338c095691", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat : true
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 84b49eb8f761d684f8e79173e910b814
  grade: false
  grade_id: cell-e0555c4a9b71b38e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
true or false
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "aac9c3f7f84e71c950e6db6025a11e0c", "grade": true, "grade_id": "cell-89f6e927581416a9", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat : true
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ab4121e4a092cce93227b3fe2b6c7ca1
  grade: false
  grade_id: cell-b578732ac62c6681
  locked: true
  schema_version: 3
  solution: false
  task: false
---
(false and false) or true
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "429efe616c3e6d6d5615d5311f6581df", "grade": true, "grade_id": "cell-447af0863372964d", "locked": false, "points": 2, "schema_version": 3, "solution": true}}

---
 * Type : bool
 * Résultat :false
 
 VOTRE RÉPONSE ICI

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: cb2b8d971ecd3f9ac908ced0e3a2f28b
  grade: false
  grade_id: cell-64d5df8a0de7fed9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
false and (false or true)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cc2d4827a669ef403b1d41fdbd1eadc1", "grade": false, "grade_id": "cell-d0fd0aed7c0e6f00", "locked": true, "schema_version": 3, "solution": false}}

## Variables

Jusqu'à présent, nous avons effectué des calculs et observé le résultat. Pour écrire des programmes, nous aurons besoin de **stocker le résultat dans une variable**. Exécutez la cellule suivante.

```{code-cell}
int a = 3;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e5d0e2ae950f827fda2558c3524fdafe", "grade": false, "grade_id": "cell-77b23801c7675aeb", "locked": true, "schema_version": 3, "solution": false}}

Une fois que la variable `a` a été déclarée et qu'on lui a assigné une valeur, on peut afficher ou réutiliser cette valeur:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fee5830b8aede03bdf41f0db12f9fc19
  grade: false
  grade_id: cell-cb019a2142f5c180
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0a7b5f91e93c4c924efdde3a9c0ea28e
  grade: false
  grade_id: cell-001bb0d2577daa8b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a + 1
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 614b58ab1299f4d79e8ddcd5ad514017
  grade: false
  grade_id: cell-8830572316055e34
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a + a + a
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a1b5c819a57670f7c20ef7cc3272fe1f", "grade": false, "grade_id": "cell-69cecfe5105b306d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On peut aussi modifier la valeur de `a`:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fdff95e0a32bac31d137441fae8be11d
  grade: false
  grade_id: cell-feb1fac9b27cedcf
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a = 5;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d74c1bb7fc965c0b5c1c8009638608f3
  grade: false
  grade_id: cell-17a1af4fbfa578ce
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5a93e22553675b75564e9e456d740448
  grade: false
  grade_id: cell-66c91df51588842e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a = a + 1;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 215bcd1733f78d667ea804052a5fce82
  grade: false
  grade_id: cell-f93c662745eac3cc
  locked: true
  schema_version: 3
  solution: false
  task: false
---
a
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5f423707ad31a5fbdf64c0186e3d178f", "grade": false, "grade_id": "cell-67887572028175dc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Que se passe-t-il si l'on exécute à nouveau la dernière cellule? Si on exécute alternativement les deux dernières cellules?

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a80ab6c338f8ee24f98ca54fc08d9e15", "grade": false, "grade_id": "cell-11418469192f043e", "locked": true, "schema_version": 3, "solution": false}}

## Quelques remarques sur Jupyter
L'ordre dans lequel vous exécutez les cellules est important, la variable contient la **dernière valeur que vous lui avez attribuée**. L'ordre d'exécution des cellules est indiqué entre crochets dans la marge de gauche.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4d5c4823c359ed7dd77e0cdd027931a3", "grade": false, "grade_id": "cell-11418469192f043f", "locked": true, "schema_version": 3, "solution": false}}

Vous aurez noté que certaines cellules finissaient par «;», d'autres non. Exécutez les cellules suivantes et observez le résultat:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: dd0aa0094b5e584ca8a31ef372270dfc
  grade: false
  grade_id: cell-3c981205fdf5c2ad
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 + 1
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8c5186bab6e5dea35f1c042c728da4a7
  grade: false
  grade_id: cell-1ca515e4663fceff
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 + 1;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a8da5cfabb98bfff0cacb60780a1bce9
  grade: false
  grade_id: cell-14ff22d2652ac945
  locked: true
  schema_version: 3
  solution: false
  task: false
---
1 + 1;
2 + 2
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c435fe263fa1e13af38b6612ff61ee0b", "grade": false, "grade_id": "cell-11418469192f043g", "locked": true, "schema_version": 3, "solution": false}}

En général, toute *instruction* C++ doit se terminer par un «;». Par convention pour C++ dans Jupyter, si la dernière instruction d'une cellule est une *expression* (elle a une valeur), et si l'on omets le «;», alors cette valeur est affichée.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1b10baba9e56f1d65b5987d2fceb2b75", "grade": false, "grade_id": "cell-51cce273e81a7bb6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Retour sur les variables

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "78362ae80e0828ac017122ba921c4698", "grade": false, "grade_id": "cell-36f8f65940be42e9", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Les cellules suivantes définissent deux variables `r` et `pi`. Utilisez ces variables pour calculer l'aire et le périmètre d'un disque de rayon `r` pour les différentes valeurs données (considérer que `pi` contient la valeur exacte du nombre bien connu). Utilisez les cellules vides pour faire vos calculs. N'oubliez pas d'exécuter aussi les cellules qui changent la valeur de `r`.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 21ab90495a9e1454b6f8d02225c1e49b
  grade: false
  grade_id: cell-6d21b67b8f0160bc
  locked: true
  schema_version: 3
  solution: false
---
double pi = 3.1415;
double r;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4b56524e61ead946e966a61bfe137c13
  grade: false
  grade_id: cell-36b8bae3af9f71aa
  locked: true
  schema_version: 3
  solution: false
---
r = 5;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2f07c8d1e1e0042444606a3019c68d34", "grade": false, "grade_id": "cell-ac377dc636c17e35", "locked": true, "schema_version": 3, "solution": false}}

Aire:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 44151c83912672b956f0ba11ebec2f4f
  grade: false
  grade_id: cell-c99afbf62e837109
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '78.5375

    type: double'
---
double aire = pi*r*r;
aire
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fee30a6f5d59e9d17fd1933e53df1100", "grade": false, "grade_id": "cell-ecae8424fb68b04b", "locked": true, "schema_version": 3, "solution": false}}

Périmètre:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e296b1ddeeda0c40fa6559e7d773b09a
  grade: false
  grade_id: cell-d382e01e1d7d9147
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '31.415

    type: double'
---
double peri = 2*pi*r;
peri
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8306dbab487059781a611cb5951e0ca3
  grade: false
  grade_id: cell-9a35ab21a5662c0e
  locked: true
  schema_version: 3
  solution: false
---
r = 2.5;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0b16f0cbe19fb796de65e6d7f64ef5d8", "grade": false, "grade_id": "cell-9bcdb6ed085c381b", "locked": true, "schema_version": 3, "solution": false}}

Aire:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a16a5faa1f789ae282c12008a2cd7afa
  grade: false
  grade_id: cell-6af902a046062f5f
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '19.6344

    type: double'
---
double aire = pi*r*r;
aire
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c3e92ae6923158adc07bc2d680a25590", "grade": false, "grade_id": "cell-801dfeea6ca8176e", "locked": true, "schema_version": 3, "solution": false}}

Périmètre:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 6f9050e3ddc8e8297e25fdc6b219b56d
  grade: false
  grade_id: cell-d525fdb0f7f4a3f6
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '15.7075

    type: double'
---
double peri = 2*pi*r;
peri
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d63d00ab1644881330eece81b82690c7
  grade: false
  grade_id: cell-be5d7b2e92bbc466
  locked: true
  schema_version: 3
  solution: false
---
r = 10;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5ecf916ca2ca2b515154925d8de7ec41", "grade": false, "grade_id": "cell-5c2043feb2b5ee9a", "locked": true, "schema_version": 3, "solution": false}}

Aire:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 426ae5794e3e4383ca663e07d30f7915
  grade: false
  grade_id: cell-3b07ae4aadece3b1
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '314.15

    type: double'
---
double aire = pi*r*r;
aire
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a21bc742d81ff078ce718d264a7941ee", "grade": false, "grade_id": "cell-7a1dfca8d4b36e75", "locked": true, "schema_version": 3, "solution": false}}

Périmètre:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3a354a340c853d64276da2ca648e8cf7
  grade: false
  grade_id: cell-43dcdfdaac13d375
  locked: false
  schema_version: 3
  solution: true
ordo_solution:
  text/plain: '62.83

    type: double'
---
double peri = 2*pi*r;
peri
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "971ae7f1a783bdd700e3b6c79dd8a1e8", "grade": false, "grade_id": "cell-2b028b9f5cbf1a95", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Les cellules suivantes définissent deux variables `b` et `c` :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7f89aca42a78ecf5618433b0949f3234
  grade: false
  grade_id: cell-5f25dd0c5b2575d2
  locked: true
  schema_version: 3
  solution: false
---
int b, c;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 25f4bd23b50ecc22b1f51f4947e60349
  grade: false
  grade_id: cell-c60f20281517629f
  locked: true
  schema_version: 3
  solution: false
---
b = 5;
c = 8;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c39ec28140e40d7e41586526feb2c6aa", "grade": false, "grade_id": "cell-e9b1884cc2aaecf1", "locked": true, "schema_version": 3, "solution": false}}

Dans les cellules vides ci-dessous, écrivez un programme qui *échange les valeurs* des deux variables, comme dans le TD 1. Votre programme pourra déclarer de nouvelles variables et utiliser des affectations, mais sans écrire les nombres à la main bien sûr, ce serait tricher.

**Indication:**
- Une cellule peut contenir plusieurs instructions (comme ci-dessus) séparées par des points-virgules ";".

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 445568ca8ef283bd08359a90f01ee70b
  grade: false
  grade_id: cell-054289e2e6184e6c
  locked: false
  schema_version: 3
  solution: true
---
int d;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 5ec1990800f1f5382d47bda057d64f64
  grade: false
  grade_id: cell-0c01da91c9e5a5d1
  locked: false
  schema_version: 3
  solution: true
---
d = b;
b = c;
c = d;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a0748f5ce7e06cd19500daa5395bef43
  grade: false
  grade_id: cell-84a2a3a6c8bc8087
  locked: true
  schema_version: 3
  solution: false
ordo_solution:
  text/plain: '8

    type: int'
---
b // doit afficher 8 (ancienne valeur de c)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 417ab1d925007b97a1991322b0608381
  grade: false
  grade_id: cell-033b5743ea66933d
  locked: true
  schema_version: 3
  solution: false
ordo_solution:
  text/plain: '5

    type: int'
---
c // doit afficher 5 (ancienne valeur de b)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5a4b0fe380c84a45c8cb0fd199a72dbb
  grade: true
  grade_id: cell-1bd7d603649344f2
  locked: true
  points: 2
  schema_version: 3
  solution: false
---

```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1de275ff7eb694be4c9736afc26a43bc", "grade": false, "grade_id": "cell-34adf2e9f2f58483", "locked": true, "schema_version": 3, "solution": false}}

## Affectations et types

Tout à l'heure, nous avons exploré différents types de valeurs et nous venons de voir comment déclarer une variable pouvant contenir un certain type. Mais que se passe-t-il lorsque l'on assigne une valeur du mauvais type à une variable ?

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e0a3fc3b240c1993f35740a83ad30327", "grade": false, "grade_id": "cell-f81a9bffcf2e6811", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Faites-vous une opinion en observant le résultat des affectations suivantes.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8368cad476d6516dbea29b439b81c08b
  grade: false
  grade_id: cell-c6a5c1361e8a71f0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int v1;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0dac43a47070505a81b9154cf313cb1b
  grade: false
  grade_id: cell-aad302a69e2794c9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v1 = 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 11e278ab0cb8e547ffcaa849dd88faab
  grade: false
  grade_id: cell-81f6d9263306f1fc
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v1 = 2.5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e510bd0d66eaf1fe4ba198ebab324783
  grade: false
  grade_id: cell-99247d901236707c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v1 = false
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ab6718d91052a12b1aec7e3d4c2adab3
  grade: false
  grade_id: cell-aad3ff4ab68c3c99
  locked: true
  schema_version: 3
  solution: false
  task: false
---
double v2;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7ca0ec23af4630a9c8ddfd7f60304eb4
  grade: false
  grade_id: cell-6764f63ae84baff7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v2 = 5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 638f3e82aad7ae20b2a6f19b25de31da
  grade: false
  grade_id: cell-d7b67f8a693dbd5a
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v2 = 5.3
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5b1496172e14d9da1582fc56b64b8792
  grade: false
  grade_id: cell-affbe7ff2805f4e9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v2 = true
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d7ff4725ffeda12fc091687b1625bea5
  grade: false
  grade_id: cell-6df3d448966350a3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
bool v3;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3da733ce5e09d780fcb01919e30576d3
  grade: false
  grade_id: cell-523ce03309e05c43
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v3 = 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: be3033a8b0a25ba327fb284c6837d4fb
  grade: false
  grade_id: cell-737e6ebdf0d644f9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v3 = 0
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 515f178cfc192b1bb48715cf45890c09
  grade: false
  grade_id: cell-06d4a669f9f8d504
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v3 = 1.5
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5ff50d1529ad5c7ee9820be9e29286a9
  grade: false
  grade_id: cell-80c1c116570040af
  locked: true
  schema_version: 3
  solution: false
  task: false
---
v3 = false
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "90a79f756bb222d04e6de588fc94606d", "grade": false, "grade_id": "cell-a5106c0a703afcee", "locked": true, "schema_version": 3, "solution": false}}

Vous remarquez que, lorsque les types sont suffisament proches, les valeurs sont converties automatiquement au moment de l'affectation. Dans les autres cas, l'affectation déclenche une erreur.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a6c219cb06ebb45f0767e0496f6c884f", "grade": false, "grade_id": "cell-4edc9c17698dd130", "locked": true, "schema_version": 3, "solution": false}}

**Exercice**

Pour chaque expression ci-dessous, déclarez une variable **du bon type** et assignez-lui le résultat, puis affichez le contenu de la variable pour le vérifier

**Exemple :**

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 25eafdd02a1ad64b706211bd130d4a8e
  grade: false
  grade_id: cell-015c0695f0c9e26c
  locked: true
  schema_version: 3
  solution: false
---
1 + 2
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ad7a74816b419c51dcd355ece119422d
  grade: false
  grade_id: cell-06a91ae7c8417a4c
  locked: true
  schema_version: 3
  solution: false
---
int i = 1 + 2;
i
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "12d9f7914e6c18f3e53e0ecb7f0ddbcd", "grade": false, "grade_id": "cell-4dbcd55e901230ff", "locked": true, "schema_version": 3, "solution": false}}

A vous de faire comme dans l'exemple avec les expressions ci-dessous:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: adc648f4fcd2a577cc05d0be2ec0bda5
  grade: false
  grade_id: cell-51887552dc9d6af2
  locked: true
  schema_version: 3
  solution: false
---
2.3*9 + 5
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: b4d041b2052985f3637790c5520401b9
  grade: false
  grade_id: cell-cc56a59bc6dcf4c2
  locked: false
  schema_version: 3
  solution: true
---
double j = 2.3*9 + 5;
j
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d46a5e4f1dea31ff2408ae0dff3bd74e
  grade: false
  grade_id: cell-d20289b033bf354b
  locked: true
  schema_version: 3
  solution: false
---
45/2 + 8 + 6
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e6bc8d10f91991232a24cd1dd2f7ff10
  grade: false
  grade_id: cell-7a9392df96472f0b
  locked: false
  schema_version: 3
  solution: true
---
int k = 45/2 + 8 + 6;
k
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 52823a6ea04871547296b080b77843e9
  grade: false
  grade_id: cell-b5d8285e37ecdd1c
  locked: true
  schema_version: 3
  solution: false
---
9 == 3*3
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a4cf14e599f4d71c4dca0bc1ff2c3a77
  grade: false
  grade_id: cell-cb28c000ca6f75bd
  locked: false
  schema_version: 3
  solution: true
---
bool t = (9 == 3*3);
t
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: cf9482805dca18bdaec39c3069fd2028
  grade: false
  grade_id: cell-4269879c75c2237f
  locked: true
  schema_version: 3
  solution: false
---
true and 8 > 10
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 26f43165faa74ca0b85cdf69de7fc4b0
  grade: false
  grade_id: cell-2e94206797747f78
  locked: false
  schema_version: 3
  solution: true
---
bool f = (true and 8 > 10);
f
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "55fe60faab26afe65aa7020e635fec2c", "grade": false, "grade_id": "cell-6e834cd22ecc144b", "locked": true, "schema_version": 3, "solution": false}}

Bravo, vous avez terminé la première feuille de l'exercice 2.

Vous pouvez maintenant passer à la deuxième feuille!
