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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "18c7334b328263f50028a0ed2c57f0b7", "grade": false, "grade_id": "cell-86380fd084769e80", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Jeux de données disponibles pour le projet 1

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "223d805a84ad990418805d7560debe26", "grade": false, "grade_id": "cell-c2fd6036df8ecb11", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans cette feuille, vous allez parcourir les jeux de données
disponibles et choisir celui que vous étudierez en Semaine 4
et 5 pour le mini projet.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6b6e1663d39b90bc4820816527aa31d0
  grade: false
  grade_id: cell-638b8591a86d2f35
  locked: true
  schema_version: 3
  solution: false
  task: false
---
%load_ext autoreload
%autoreload 2
from utilities import *
from intro_science_donnees import data
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d05ae432ec7d927e7bb629830f56a341
  grade: false
  grade_id: cell-603f0e005a71785c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
! ls {data.dir}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bbff11ed347d80e42d362ba51096a613", "grade": false, "grade_id": "cell-65a29118d123c634", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Poules et canards

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1fbba1528e04cb1bf06a608ca603264a
  grade: false
  grade_id: cell-4bd1153d315503ef
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'Farm')
images = load_images(dataset_dir, "*.jpeg")
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "745c260321fc496c732f9834592822a7", "grade": false, "grade_id": "cell-8ae6e1c8034faf85", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Paumes et dos de mains

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c6216c71d2e8e5eae2de7046ca6eb35f
  grade: false
  grade_id: cell-aa92e20b30d4829d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'Hands')
images = load_images(dataset_dir, "*.jpeg")
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "31c432ddf0ce961a49f3c429c35dbcc4", "grade": false, "grade_id": "cell-c5c09b1ebff30a8a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Mélanomes malins et bénins

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0f083652560320abb45863b812f40f68
  grade: false
  grade_id: cell-f08cb6f6ff9303a8
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'Melanoma')
images = load_images(dataset_dir, "*.jpg")
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "73d1d29e516e4547a8779f1d3549e8ed", "grade": false, "grade_id": "cell-933228e1040c967b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Smileys gais et tristes

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c995abf2fa9813c40b6387cde9bfc7c5
  grade: false
  grade_id: cell-3c651c729aa65f4f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'Smiley')
images = load_images(dataset_dir, "*.png")
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "39c82fc3b220ba08914f93ad282b9878", "grade": false, "grade_id": "cell-15a0b989b1cd4c5b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Zéros et uns manuscrits

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c807ec2807eef81b367168f8a0537387
  grade: false
  grade_id: cell-0e86999691136d40
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'ZeroOne')
images = load_images(dataset_dir, "*.png")
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "daf4a5c24b94d86a068163a71b966a5e", "grade": false, "grade_id": "cell-78ed854e0e4200ba", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Choix du jeu de données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f729f32800d4456283fd558a3f31823a", "grade": false, "grade_id": "cell-78ed854e0e4200bb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice :** Choisissez l'un des jeux de données ci-dessus pour
votre projet. Chargez les images correspondantes dans `images` et
affichez les:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 14efe85c75106a33e063cbd6fadeef4f
  grade: false
  grade_id: cell-e732417891788d51
  locked: false
  schema_version: 3
  solution: true
  task: false
---
dataset_dir = os.path.join(data.dir, 'Smiley')
images = load_images(dataset_dir, "*.png")
image_grid(images, titles=images.index)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 393908f8f06c63d2a3ae481447e7f0da
  grade: true
  grade_id: cell-2389de956025bb38
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
assert isinstance(images, pd.Series)
assert len(images) == 20
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0f753034fd6593bdc86dac221ffc2007", "grade": false, "grade_id": "cell-af6191373559b6be", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Bravo, vous avez terminé la dernière feuille du TP.

Mettez à jour votre rapport et déposez votre travail.
