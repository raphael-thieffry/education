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

# Semaine 2: Premiers éléments de programmation impérative

La semaine dernière, laby nous a amené à la découverte des
premiers éléments de la programmation impérative: programmes, fonctions,
expressions conditionnelles et itératives. Cette semaine, nous allons
commencer à les approfondir, en y ajoutant expressions et variables.

## [Cours](cours.md)

## <a href="TD.pdf">TD</a>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6b66466b7f04d30b80167a5b5f733e1f", "grade": false, "grade_id": "cell-65f24a4fe8c153c1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## TP

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4abbbed7cf819cf0aaa91d723f158f7d", "grade": false, "grade_id": "cell-65f24a4fe8c153c2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Tout exercice non marqué d'un ♣ est à terminer pour la semaine prochaine.**

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cf6b77b4017174a728435aa43cd6b9a8", "grade": false, "grade_id": "cell-bf0808a9dcb0b572", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Notes de cours

1.  Consultez le poly de l'Amphi 1 sur la page web du cours.

2.  Que signifie *syntaxe*? Et *sémantique*? Vérifiez dans le poly.

3.  Quelle est la syntaxe et la sémantique de l'affectation de
    variables? Vérifiez dans le poly.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "24b038c41b24bcf0252c789ee012da18", "grade": false, "grade_id": "cell-bf0808a9dcb0b573", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Téléchargement du sujet de TP

1.  Ouvrez un terminal (vous pouvez consulter l'exercice 2 du TP 1).

3.  Exécutez la commande `info-111` et observez le résultat.

4.  Vous venez de lire la documentation de la commande `info-111`.
    Téléchargez le sujet de TP «Semaine2» en suivant les instructions
    données à ce sujet par cette documentation.
    Remarque: Si vous n'avez pas fait le TP1, vous aurez besoin d'activer
    votre compte gitlab (voir TP1).

6.  Consultez la liste des fichiers de votre nouveau répertoire
    `~/ProgImperative/Semaine2/` à l'aide de la commande `ls` (cf. l'UE
    Introduction à l'Informatique pour ceux qui la suivent):

	    ls ~/ProgImperative/Semaine2/

<!--
5.  Observez ce qui est affiché; notez que `info-111` a fait appel à la
    commande `git clone ...`.
!-->

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3a1b91457cb934e749be7e46479507ea", "grade": false, "grade_id": "cell-bf0808a9dcb0b574", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Jupyter: affectations, conditionnelles, fonctions

1.  Démarrez Jupyter:

    -   **En salle de TP:** vous n'avez pas besoin de vous connecter au
        serveur JupyterHub. Si vous ne vous souvenez plus de la commande
        exacte, tapez `info-111` dans un terminal.

    -   **Sur JupyterHub:** Jupyter est déjà lancé!

2.  Naviguez jusqu'à votre répertoire `Semaine2`.

3.  Sélectionnez la feuille de travail
    `feuille1-valeurs-types-variables.md`. Suivez les instructions
    qu'elle contient. Rappel: ne fermez pas le terminal où vous avez le
    cas échéant lancé Jupyter.

4.  De même avec `feuille2-conditions-fonctions.md`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6bbbfc04daa6d873eaa6a0716bf63085", "grade": false, "grade_id": "cell-bf0808a9dcb0b575", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Dépôt de votre travail

1.  Exécutez la commande `info-111` dans un terminal disponible :
    si votre terminal est occupé par Jupyter, ouvrir un autre terminal.

2.  Suivez les instructions indiquées pour déposer votre travail, en
    veillant à bien préciser votre groupe.

3.  N'oubliez pas de déposer à nouveau votre travail en fin de séance,
    afin que tout soit bien sauvegardé.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3af56b6397fc09f8a7a55aeef9a031ec", "grade": false, "grade_id": "cell-bf0808a9dcb0b576", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Service JupyterHub

Rappel: l'université a déployé un service `JupyterHub` (expérimental)
vous permettant de travailler en dehors des séances avec simplement une
connexion internet et un navigateur web (firefox, chrome, safari, ...).

**Cet exercice n'est à faire que si vous n'avez pas encore utilisé ce
service ou si vous avez rencontré des difficultés.**

1.  Suivez les instructions du TP 1 pour vous connecter au service
    JupyterHub; téléchargez-y vos TP 1 et 2 et consultez les; demandez
    de l'aide au besoin à votre enseignant.

2.  Fermez votre serveur avec `Control Panel -> Stop My Server`, puis
    fermez la page.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5aeb9878fc63e048714c4470c77faffa", "grade": false, "grade_id": "cell-bf0808a9dcb0b577", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: Retour sur le TD

1.  Ouvrez (avec Jupyter) la feuille `feuille-3-td-exercice-3` et implantez en `C++`
    les algorithmes de l'exercice 3 du TD.
    Pensez à faire des tests pour vérifier vos réponses.

2.  De même pour l'exercice 4 dans la feuille `feuille-4-td-exercice-4`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "92f57cb58e6a7ba992993aaceb617d2e", "grade": false, "grade_id": "cell-bf0808a9dcb0b578", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: **Pour la semaine prochaine**

1.  Vérifiez que vous pouvez vous connecter au serveur `JupyterHub`
    depuis chez vous et que vous pouvez y exécuter vos fiches Jupyter
    (voir exercice «Service JupyterHub» ci dessus).

2.  Terminez les fiches Jupyter de ce TP, soit en salle informatique de
    l'université, soit depuis chez vous en utilisant le serveur
    `JupyterHub`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5c3b0a749defe51aed246ab39def2f75", "grade": false, "grade_id": "cell-bf0808a9dcb0b57a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

:::{note}

Vous pouvez aborder les exercices ♣ suivants dans l'ordre que vous
souhaitez.

Pour les réaliser, vous créerez au fur et à mesure de nouvelles
feuilles de travail. Pour cela, depuis le navigateur de fichiers de
`Jupyter`, choisissez `New -> C++` ou `New -> Python 3`. Puis dans la
barre d'en-tête, vous cliquerez sur `Untitled` pour donner un nom
informatif à la feuille.

:::

:::{hint}

Pour que la soumission tienne compte de vos nouveaux fichiers, vous
devez au préalable les déclarer au système de gestion de version
sous-jacent `git`. Par exemple, pour déclarer un nouveau fichier
`mon_fichier.ipynb` que vous avez créé dans votre répertoire
`Semaine2`, vous ferez:

        cd ~/ProgImperative/Semaine2
        git add mon_fichier.ipynb

Il sera alors inclus dans toutes les soumissions ultérieures.
:::


### Exercice ♣: Euler forever!

Vous trouverez sur le site du projet Euler <https://projecteuler.net>
une série de problèmes mathématiques qui nécessitent chacun une
combinaison de réflexion sur feuille et de programmation (voir
<http://submoon.freeshell.org/fr/sphinx/euler.html> pour avoir les
énoncés en français).

Essayez de résoudre les problèmes 1, 2, 5 et tous ceux qui vous
plairont!

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "764307b9d6d8bc4209e145befa9beb0a", "grade": false, "grade_id": "cell-bf0808a9dcb0b579", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice ♣: Python

Dans le cours «Introduction à la programmation», vous (re)découvrirez
le langage de programmation Python. Pour prendre un peu d'avance,
refaites le TP en utilisant cette fois `Python`.

Vous pouvez consulter la feuille «Résumé de la syntaxe de base
Python», fournie dans la <a href="TD.pdf">feuille de TD</a> en parallèle à celle
pour C++.

<!--
Vous trouverez un cours complet sur `Python` à cette adresse:

<http://fr.openclassrooms.com/informatique/cours/apprenez-a-programmer-en-python>

Il est intéressant de le lire et de comparer avec ce que vous apprenez
en C++ ce semestre.
!-->
