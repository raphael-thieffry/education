---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "16f013151c494680062de336d1402311", "grade": false, "grade_id": "cell-340372ef6a82d730", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#  Analyses de données en Jupyter

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f27cc12d4fea454e66c24fd5a74a4a6f", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}}

Une *analyse de données* répond aux questions suivantes: 

- quelles sont les données, 
- quelle est la question (notre objectif),
- comment faire pour y répondre (outils statistiques), 
- quels sont les résultats (nos observations) et 
- quelles sont les conclusions (notre interprétation).

Une analyse de données prend la forme d'un document narratif
expliquant les objectifs, hypothèses et étapes de l'analyse: il
typiquement écrit en anglais pour qu'il puisse être partagé avec le
plus grand nombre.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2a1e4cabf662f8a4582a370c8c4d6b0e", "grade": false, "grade_id": "cell-49874ed5d0338eec", "locked": true, "schema_version": 3, "solution": false}}

##  Pourquoi utiliser Jupyter ?

Depuis quelques années, les feuilles de travail (notebook) Jupyter
sont un des moyens prisés pour rédiger de telles analyses de données
et mener les calculs sous-jacents. Il s'agit en effet de documents
permettant d'entremêler narration (textes, formules), visualisation,
interaction, calcul et programmation.

Le document que vous êtes en train de lire est une feuille Jupyter. On
peut y mettre des calculs comme ci-dessous. Pour exécuter le calcul,
cliquez dans la *cellule* ci-dessous et tapez Shift-Enter:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d4fc1b7754a0b4f373967b4653c39d7b
  grade: false
  grade_id: cell-02a086c93b3ab3f2
  locked: true
  schema_version: 3
  solution: false
---
1 + 1
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5e0f525b775b366eaa8ec2d2d2c0e088", "grade": false, "grade_id": "cell-aa712b4c2a825a98", "locked": true, "schema_version": 3, "solution": false}}

Utilisez maintenant la cellule ci-dessous pour calculer 1+2; puis
réutilisez la même cellule pour calculer 3*4:

```{code-cell} ipython3
3*4
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e487e1abff5bf0d0561ccedb03e27ba7", "grade": false, "grade_id": "cell-20435b0654662bc4", "locked": true, "schema_version": 3, "solution": false}}

Vous rencontrerez aussi des cellules à compléter comme la suivante
dans lesquelles vous remplacerez les deux lignes "Your code here" et
"raise ..." par le calcul à faire; calculez cinq fois sept:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f999a880330228a49171a5d4b2d091d5
  grade: true
  grade_id: cell-d8b61dce71965f3e
  locked: false
  points: 0
  schema_version: 3
  solution: true
  task: false
---
5*7
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4dd7f38e9e07db3238ee8359404fb85d", "grade": true, "grade_id": "cell-b35d0d71e7e10dd3", "locked": false, "points": 1, "schema_version": 3, "solution": true}}

Vous pouvez aussi éditer les cellules contenant du texte comme
celle-ci. Allez-y: double-cliquez dans la cellule et mettez votre nom là:

Raphaël Thieffry

Puis Shift-Enter.

Notez que certaines cellules de ce document sont en
lecture-seule. Vous ne pouvez pas les modifier.  En revanche, vous
pouvez toujours insérer de nouvelles cellules libres (Menu
`Insérer` > `Insérer une cellule après`).

+++

On peut ausi mettre des formules mathématiques dans une cellule:
$$\frac 1 {1-\frac 1z} = \sum_{i=0}^\infty \frac 1 {z^i}$$

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d882399f245564f25d087c3cf1987329", "grade": false, "grade_id": "cell-2a163d135d604d5c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Correction semi-automatique avec nbgrader

Lors d'un TP noté, une grande partie de la correction est automatique
à l'aide de l'outil `nbgrader` et s'appuie sur des tests similaires à
ceux du premier semestre. La correction automatique se fait par
*intégration continue* sur GitLab au moment du dépôt (`submit`) et
peut prendre quelques minutes. Vous pouvez ensuite télécharger le
résultat (`fetch_feedback`) pour le consulter.

Le reste de la correction est manuelle: vos enseignants regarderont
vos réponses, vos interprétations des résultats et attribueront des
points à chacune d'entre elles.

La première séance est une séance d'entraînement; les notes,
indicatives, vous permettent de prendre en main le mécanisme. Si vous
soumettez votre travail (même incomplet), vous aurez les cinq points
du TP.

+++

Voici un exemple : Dans la cellule suivante, calculez la
somme de `3` et de `4`, et stockez le résultat dans la variable `s`:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e2020cf0917b932a39130f6249b5c287
  grade: false
  grade_id: cell-d8b61dce71965f3g
  locked: false
  schema_version: 3
  solution: true
  task: false
---
s = 3+4
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2eab32b747769948bb289586d6939b48", "grade": false, "grade_id": "cell-074eb18a150a2c8e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La commande suivante est un test qui vérifie votre réponse; vous
reconnaîtrez le `assert`  que nous utilisions en python et
en C++  au premier semestre:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6ad2856d7da3b56ed5f56a3152f45af2
  grade: true
  grade_id: cell-d8b61dce71965f3h
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert s == 7
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8797087212fec52982ff59b67a2fb0fc", "grade": false, "grade_id": "cell-4c9512739b1f0f29", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Consultez les [instructions](index.md) pour:
1. Valider votre feuille de travail `1_jupyter.md`
2. Déposer votre travail sur GitLab
3. Télécharger et consulter le résultat de la correction automatique

<div class="alert alert-info">

- Pour ce premier TP, les scores sont indicatifs. Il suffit que vous
  déposiez le TP en temps et en heure sur GitLab pour obtenir *tous* les points.
- Les feuilles peuvent contenir des tests cachés (qui influencent le
  score).
- Les scores indiqués ne tiennent compte que de la correction
  automatique. Une autre partie du score sera attribuée par vos
  enseignants (en cours de mise en place; nous verrons si nous
  arrivons à le faire pour ce premier TP).

</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ed3f22ec4b34a2b6eddefacaeb0d8336", "grade": false, "grade_id": "cell-8226871d2f13ccb8", "locked": true, "schema_version": 3, "solution": false}}

## Au boulot!

Maintenant que vous avez appris les rudiments de Jupyter et de
l'environnement de travail :

 - organisation d'une feuille de TP,
 - soumission et correction de TP,
 - création de cellules,
 
 il est temps de faire le rappel sur python et les compréhensions! Passez à la feuille suivante [Python: fonctions et compréhensions](2_python.md)
