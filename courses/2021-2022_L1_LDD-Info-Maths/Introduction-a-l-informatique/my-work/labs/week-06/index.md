---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "36973f7f5dc90f248eab5d7efe0027ac", "grade": false, "grade_id": "cell-405b64781fe13bde", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Semaine 6: Modèle de mémoire, collections, consolidation

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e2dbbc0eea5346755c03794af63e93e5", "grade": false, "grade_id": "cell-249063faf999e9b3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les semaines précédentes nous avons successivement empilé de nombreux
éléments de la programmation impérative: variables,
conditionnelles, boucles, fonctions, tableaux. Cette
semaine est consacrée à la consolidation de ces éléments,
en vue du partiel début novembre.

En cours, nous commencerons par un exemple jouet de **piratage par
débordement**. Cela motivera l'introduction d'un **modèle de mémoire**
raffiné (**pile** + **tas**) pour mieux comprendre l'allocation des
tableaux. Nous généraliserons ensuite les tableaux avec la notion de
collections et introduirons la boucle **for each**.

En TD et TP, nous combinerons tout ce que nous avons vu jusqu'ici pour
implanter le **jeu de Yams**.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8622671ea569503773fe84e1de25d096", "grade": false, "grade_id": "cell-b74ea1a2236a0f8c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## [Cours](cours.md)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c687c1874282b78bc008facab55ab325", "grade": false, "grade_id": "cell-b74ea1a2236a0f8d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## <a href="TD.pdf">TD</a>: Premiers pas vers le jeu de Yam's

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c1364e564beb16751fce76e036707359", "grade": false, "grade_id": "cell-2cb5de2667417f2e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## TP: Implantation du jeu de Yam's

**Préalable:**
Téléchargez le sujet de TP selon la
  [procédure usuelle](http://nicolas.thiery.name/Enseignement/Info111/devoirs.html).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "54d52a917d6d2a441e77f904d91a4b32", "grade": false, "grade_id": "cell-47ce0b02cfcdb434", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Yam's simplifié

Nous allons travailler en parallèle dans une feuille de travail Jupyter
`yams.md` et dans
un fichier source `yams.cpp` afin, à la fin du TP, d'obtenir un
exécutable autonome permettant de jouer une partie de Yam's simplifiée.

Après avoir lancé Jupyter, ouvrez la feuille `yams.md`. Lorsqu'il vous est demandé de compiler du
code à la main la première fois, **ouvrez un nouveau terminal pour cela**, faites
attention à ne pas quitter Jupyter!

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e0fdffb4092cadcfa27a8512697b3601", "grade": false, "grade_id": "cell-47ce0b02cfcdb435", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Interlude: boucles imbriquées

Ouvrir la feuille `laby-imbriquee.md` et suivre ses instructions.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1f7b0cba552d076d09bd4df334635a2b", "grade": false, "grade_id": "cell-1272d7485b5484ce", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice ♣:** Yam's complet

Le programme que vous obtenez à la fin de l'exercice 1 est encore loin
de représenter le jeu de Yams réel.

Dans cet exercice nous vous proposons plusieurs extensions (dont
certaines déjà évoquées dans le sujet de TD) qui vous permettront
de vous en approcher.

Vous pouvez utiliser Jupyter pour prototyper vos fonctions, mais vous
devez au final implémenter ces extensions dans votre programme compilé
(fichier [yams.cpp](yams.cpp)).

-   Dans le vrai jeu de Yam's, le joueur peut relancer jusqu'à trois
    fois un ou plusieurs dés avant de choisir une figure.

    1.  Ajouter une fonction
        `vector<int> relance(int nde, vector<int> des)` qui "relance" le
        dé choisi en premier argument et le remplace donc par un nouveau
        nombre aléatoire entre 1 et 6.

    2.  Dans la boucle de jeu, ajouter les instructions nécessaires pour
        que le joueur puisse choisir jusqu'à trois dés à relancer et les
        relancer.

-   La partie de Yams se termine lorsqu'un joueur a marqué des points
    pour toutes les figures possibles.

    1.  Ajouter dans le `main` un tableau de score contenant une case
        pour chaque figure.

    2.  Lorsque le joueur choisit une figure, les points qu'il gagne
        doivent être stockés dans la partie correspondante du tableau.
        Une fois une case du tableau remplie, elle ne peut plus être
        modifiée.

    3.  La partie se termine lorsque toutes les cases du tableau sont
        remplies. Le score du joueur correspond à la somme des cases du
        tableau.

-   C'est un peu triste de jouer tout seul! Modifiez la boucle
    principale pour alterner les tours entre 2 joueurs dont les scores
    seront stockés dans deux tableaux de score distincts. La partie
    s'arrête lorsqu'un joueur a fini de remplir son tableau de score. On
    compare alors le score de chaque joueur pour désigner le gagnant.

-   Si vous êtes très motivés vous pouvez transformer une dernière fois
    votre programme afin de rendre possible des parties entre un nombre
    quelconque de joueurs. Pour cela vous aurez besoin d'utiliser un
    tableau de tableaux de scores. Ce tableau contiendra un tableau de
    score pour chaque joueur présent dans la partie.
