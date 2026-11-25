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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e9e7d326eb2d9a98a536a424058cf933", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}}

# Semaine 6

+++

## Consignes

Avant mardi 14 mars 22h:
- [ ] Relire les diapos du cours 6.
- [ ] Finir le TP et le déposer sur GitLab (5 points)
<!--- Répondre au [Quizz](https://ecampus.paris-saclay.fr/mod/quiz/view.php?id=487889) sur eCampus (5 points).!-->

## Support de cours

- [Diapos](CM6.md)

+++

## TP

### Objectif

L'objectif de cette semaine est de rajouter à votre escarcelle
quelques outils de manipulation d'images en vue du deuxième projet:
ainsi, vous pourrez y traiter des jeux d'images plus complexes. Nous
verrons par exemple, lorsque l'image n'est pas bien cadrée, comment en
extraire la portion pertinente. Nous verrons aussi comment réaliser
des diaporamas simples avec Jupyter, en vue de votre soutenance de
projet.

N'oubliez pas d'appliquer toutes les [bonnes
pratiques](http://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Students/Semaine1/index.html#bonnes-pratiques)!

### Consignes

- [x] Téléchargez le sujet de TP `Semaine6` (rappel des
     [instructions](http://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Devoirs/Semaine1/index.html#telechar
- [x] Ouvrez la feuille [index](index.md) pour retrouver ces consignes.
- [ ] Ouvrez la feuille [diaporamas](1_diaporamas.md) et suivez les instructions.
- [ ] Ouvrez la feuille [arcimboldo](2_arcimboldo.md) et suivez les instructions.

Au fur et à mesure, vous mettrez à jour votre rapport ci-dessous. Bon TP!

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d8afefb67984b373277863a0c620d91f", "grade": false, "grade_id": "cell-229300fb372ae6d5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Rapport

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "db44c1d27234caea97047c1b1a2e4900", "grade": false, "grade_id": "cell-ceddc6281cff411f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Au fur et à mesure du TP, vous cocherez ci-dessus les actions que vous
aurez effectuées; pour cela, double-cliquez sur la cellule pour
l'éditer, et remplacez `- [ ]` par `- [x]`. Vous prendrez aussi des
notes ci-dessous. Enfin, vous consulterez la section « Revue de code »
ci-dessous pour vérifier la qualité de votre code.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "80ac285c7a3c8fe6409864582068f417", "grade": false, "grade_id": "cell-4911a792a82448dF", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### En quelques mots, qu'avez-vous appris?

#### Quelles difficultés avez vous éventuellement rencontrées?

#### Qu'avez vous aimé ou moins aimé dans ce TP?

#### Notes libres

+++

#### En quelques mots, qu'avez-vous appris?
Sur la feuille "diapo", j'ai appris une maniere plus efficace de faire des supports pour mes presentations

#### Quelles difficultés avez vous éventuellement rencontrées?

#### Qu'avez vous aimé ou moins aimé dans ce TP?

#### Notes libres

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3cdeab84509ec542214d2b5022e65b4d", "grade": false, "grade_id": "cell-4911a792a82448dG", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### Revue du code

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f5be6a8e0307679bd09f7e9a8661ccb2", "grade": false, "grade_id": "cell-4911a792a82448dH", "locked": true, "schema_version": 3, "solution": false, "task": false}}

##### Affichage du code des principales fonctions

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0b7f382020931cebd9159552dab83cff
  grade: false
  grade_id: cell-006fb180e6a86e73
  locked: true
  schema_version: 3
  solution: false
  task: false
---
from intro_science_donnees import show_source
from utilities import *
show_source(yellowness_filter)
show_source(color_correlation_filter)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1c0f01ca7b436223b24fc71e1f74ba08", "grade": false, "grade_id": "cell-d21a1d7d40d56302", "locked": true, "schema_version": 3, "solution": false, "task": false}}

##### Conventions de codage

L'outil `flake8` permet de vérifier que votre code respecte les
conventions de codage usuelles de Python, telles que définies
notamment par le document [PEP
8](https://www.python.org/dev/peps/pep-0008/). Si la cellule suivante
affiche des avertissements, suivez les indications affichées pour
peaufiner votre code.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: af09a7ad3797f2e5dc5ec66e98ee34e2
  grade: true
  grade_id: cell-ce5cf24a9e83ff0e
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
from intro_science_donnees import code_checker
code_checker("flake8 utilities.py")
```

```{code-cell} ipython3

```
