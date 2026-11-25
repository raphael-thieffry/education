---
jupytext:
  notebook_metadata_filter: rise
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
rise:
  auto_select: first
  autolaunch: false
  centered: false
  controls: false
  enable_chalkboard: true
  height: 100%
  margin: 0
  maxScale: 1
  minScale: 1
  scroll: true
  slideNumber: true
  start_slideshow_at: selected
  transition: none
  width: 90%
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ea5cac756cb589df60b23ae76971fabe", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}, "slideshow": {"slide_type": "slide"}}

# Diaporamas interactifs avec Jupyter

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9836b73b664af36dc6e4bee5e286fc34", "grade": false, "grade_id": "cell-8b77acf5d2044f9d", "locked": true, "schema_version": 3, "solution": false, "task": false}, "slideshow": {"slide_type": "fragment"}}

Dans cette feuille de travail, vous allez apprendre à utiliser Jupyter
et son extension [RISE](https://rise.readthedocs.io/) pour produire un
diaporama interactif pour vos présentations orales.

C'est ce que nous utilisons pour les notes de cours et ce que vous
pourrez utiliser pour la soutenance du projet final.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "20c4948c5e22b3a8fb2da440181df6f8", "grade": false, "grade_id": "cell-e55a0f76366ee6ec", "locked": true, "schema_version": 3, "solution": false, "task": false}, "slideshow": {"slide_type": "subslide"}}

## Utiliser un diaporama

Cette feuille de travail est en fait un diaporama!

- Activez le diaporama en cliquant sur le bouton <i class="btn btn-default fa fa-bar-chart my-main-tool-bar"></i> de la barre d'outils.
- Parcourir l'ensemble du diaporama en explorant les fontionalités suivantes:
  - Naviguez avec les touches Page Haut et Page Bas.
  - Consultez la documentation en cliquant sur le bouton <i class="fa fa-question" style="color: #727272;"></i>.
  - Suivez la documentation pour afficher la vue d'ensemble du diaporama (*overview*) puis revenir.
  - Suivez la documentation pour cacher puis afficher à nouveau les boutons.
  - Utilisez `Control +` et `Control -` pour ajuster la taille des fontes.
  - Cliquez sur l'icône <i class="fa fa-pencil-square" style="color: #727272;"></i> pour lancer le tableau noir.
  - Cliquez sur l'icône <i class="fa fa-pencil" style="color: #727272;"></i> pour dessiner sur les diapos.
  - Cliquez sur l'icône <i class="fa fa-times-circle" style="color: #727272;"></i> pour quitter le tableau noir ou les diapos.

- Ouvrez les [notes de cours](CM6.md) et activez le diaporama.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4d0ab253317f7d1c3c2c50e6f38b3f89", "grade": false, "grade_id": "cell-f3f6ad1e405c3005", "locked": true, "schema_version": 3, "solution": false, "task": false}, "slideshow": {"slide_type": "subslide"}}

## Éditer un diaporama
- Quittez le diaporama
- Dans le menu «Affichage» (*View*), selectionnez «Barre d'outil de cellule» (*Cell Toolbar*) puis «Diaporama» (*Diaporama*).  
  Une barre de menu apparaît sur chaque cellule qui permet de définir son rôle:
  - Diapo (*Slide*): commence une nouvelle diapo
  - Sous-Diapo (*Subslide*): commence une nouvelle sous-diapo (l'équivalent d'une sous-section)
  - Extrait (*Fragment*): la cellule se rajoute à la diapo en cours
  - Sauter (*Skip*): la cellule n'apparaît pas dans les diapos
  - Note (*Note*): idem, mais il est possible de faire afficher le contenu sur un deuxième écran
- Utilisez le bac à sable ci-dessous pour explorer les différents rôles et leur effet

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "598435ec5f30e97c39b547a4ec6b6ffe", "grade": false, "grade_id": "cell-cc4538c8e274a947", "locked": true, "schema_version": 3, "solution": false, "task": false}, "slideshow": {"slide_type": "subslide"}}

## ♣ Pour aller plus loin
- Consultez la documentation de [RISE](https://rise.readthedocs.io/).

+++ {"heading_collapsed": true, "slideshow": {"slide_type": "slide"}}

## Bac à sable
La suite de cette feuille contient une succession de cellules sans signification pour vous
servir de bac à sable. Vous pouvez en rajouter de nouvelles à votre convenance. 

Vous ne comprenez pas les textes? Pour savoir pourquoi, consultez
l'article [Lorem Ipsum](https://fr.wikipedia.org/wiki/Lorem_ipsum).

+++

## Bla bla bla
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.

Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.

```{code-cell} ipython3
39 + 1
```

Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.

```{code-cell} ipython3
40 + 1
```

Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4eb92563ec2160428a2cee982dfe3045", "grade": false, "grade_id": "cell-ca0131f59521fce9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## The end of the universe

Vous êtes venus jusqu'ici? Bravo! Affectez 42 à la variable `ultime` pour marquer un point :-)

Ouvrez ensuite la feuille `arcimboldo`, après avoir mis à jour votre rapport.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 218423a852fc9df7481e81ad8c7a498a
  grade: false
  grade_id: cell-0fcaec8b81d7a78b
  locked: false
  schema_version: 3
  solution: true
  task: false
---
ultime = 42
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f6f1ce00c13dab615d2679e1c80a7a61
  grade: true
  grade_id: cell-963f3a9626ae1519
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert ultime == 42
```
