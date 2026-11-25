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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b0a4740255b8d8b7a6f692e2e0ff4f49", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}}

# Semaine 4

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "786bab265d79ba4842e83768ab3087c6", "grade": false, "grade_id": "cell-4911a792a82448d8", "locked": true, "schema_version": 3, "solution": false}}

## Consignes

Avant le lundi 21 février 22h00:
- [ ] Relire les [diapos du cours 4](CM4.md)
- [ ] Rendu d'étape du TP (voir ci-dessous)

+++

## Cours

- [ ] [CM4: Construction et sélection d'attributs](CM4.md)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7551814a42ecca38806aa36e67133d76", "grade": false, "grade_id": "cell-4911a792a82448d9", "locked": true, "schema_version": 3, "solution": false}}

## TP: VI-ME-RÉ-BAR sur vos propres données

### Objectif

La semaine dernière, vous vous êtes familiarisé avec le schéma
VI-ME-RÉ-BAR -- [VI]sualisation, [ME]sure, [RÉ]férence (*baseline*),
[BAR]res d'erreur -- en reproduisant une analyse de données
préexistante dont l'objet était de classifier automatiquement des
images de pommes et bananes. Maintenant, c'est à vous de jouer! Vous
allez effectuer en binôme votre propre analyse de données.

La semaine dernière, vous avez choisi l'un des [jeux de données
fournis](../Semaine3/3_jeux_de_donnees.md) consistant chacun
de vingt images réparties en deux classes: poules et canards,
mélanomes cancéreux et bénins, émoticons tristes et gais, paumes et
dos de la main, ou chiffres manuscrits zéro et un.

Saurez-vous apprendre à l'ordinateur à distinguer automatiquement, par
exemple, un mélanome cancéreux d'un mélanome bénin, uniquement à
partir de sa photographie? Nous avons veillé à ce que votre défi ne
soit ni trop simple, ni trop compliqué.

Ce travail sera l'objet du premier projet qui va se
dérouler sur les deux semaines qui viennent:

Semaine 4: dépôt lundi 21 février 22h
- Choix définitif du binôme (voir annonce sur e-Campus et [document partagé](https://codimd.math.cnrs.fr/3f98v4-YT4CN2ktM6_g5lw?both))
- Traitement des images numériques pour en extraire des attributs
  (*features*) simples.
- Utilisation d'un premier classificateur donné par vos enseignantes et
  enseignants, afin d'obtenir une performance de [RÉ]férence
  (*baseline*) pour ce jeu de données.
- Évaluation de la performance.

Semaine 5: dépôt mardi 1er mars 22h
- Implémentation d'un classificateur.
- Évaluation de la performance.

Vous déposerez chaque semaine votre travail dans son état
d'avancement. Votre version définitive sera évaluée par vos
enseignants (20% de la note finale).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a38848b52282fec1810b68789dd30709", "grade": false, "grade_id": "cell-4911a792a82448dA", "locked": true, "schema_version": 3, "solution": false}}

### Consignes

Vous documenterez au fur et à mesure votre analyse de données dans le
document exécutable [analyse de données](4_analyse_de_donnees.md), en
suivant la trame fournie. Gardez notamment une trace des
expérimentations intermédiaires («nous avons essayé telle combinaison
d'attributs; voici les résultats et la performance obtenue»). Ce
document devra rester à tout moment synthétique, suivant notamment les
[bonnes pratiques](../Semaine3/1_bonnes_pratiques.md) vues la semaine
dernière:
- Vous mettrez dans le fichier `utilities.py` les utilitaires du TP3
  (`load_images`, ...)  que vous souhaiterez réutiliser, ainsi que vos
  nouvelles fonctions.
- Complétez régulièrement le rapport ci-dessous, notamment pour qu'il
  affiche le code de toutes les fonctions que vous avez
  implantées. Vérifiez à chaque fois le résultat des outils de
  vérifications (`flake8`, ...).
- Lorsque vous aurez besoin de brouillon -- par exemple pour mettre au
  point du code -- créez des petites feuilles Jupyter séparées pour ne
  pas polluer votre document.

La qualité de la rédaction sera l'un des critères d'évaluation du
mini-projet.

+++ {"nbgrader": {"grade": false, "grade_id": "cell-4911a792a82448dB", "locked": false, "schema_version": 3, "solution": false}}

### Au travail!

- [x] Vérifiez votre inscription avec votre binôme pour le projet 1
     dans le [document
     partagé](https://codimd.math.cnrs.fr/3f98v4-YT4CN2ktM6_g5lw?both).
     Inscrivez-vous aussi si vous n'avez pas encore de binôme!
- [x] Téléchargez le sujet de TP `Semaine4` (rappel des
     [instructions](http://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Devoirs/Semaine1/index.html#telechargement-et-depot-des-tps))
- [x] Ouvrez la feuille [index](index.md) pour retrouver ces consignes.
- [ ] Consultez la section « Rapport » en fin de feuille.
- [x] Faites un rappel sur la [manipulation des tableaux](1_tableaux.md).
- [x] Apprenez à traiter des [images](2_images.md)  ...
- [ ] et à [extraire des attributs](3_extraction_d_attributs.md) de
     votre jeu de données
- [ ] Effectuez votre [analyse de donnees](4_analyse_de_donnees.md),
     en suivant les instructions fournies.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3177d01c29a687657f68d8ca1773f841", "grade": false, "grade_id": "cell-4911a792a82448dE", "locked": true, "schema_version": 3, "solution": false}}

### Brouillon de rapport

Cette feuille joue aussi le rôle de brouillon de mini-rapport qui vous
permettra à vous et votre enseignant d'évaluer rapidement votre
avancement sur cette première partie du projet. Cela vous donnera une
base pour le mini-rapport de projet la semaine prochaine.

Au fur et à mesure du TP, vous cocherez ci-dessus les actions que vous
aurez effectuées; pour cela, double-cliquez sur la cellule pour
l'éditer, et remplacez `- [ ]` par `- [x]`. Vous prendrez aussi des
notes ci-dessous. Enfin, vous consulterez la section « Revue de code »
ci-dessous pour vérifier la qualité de votre code.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6563f058f4e26554f094663c22bb3f3c", "grade": true, "grade_id": "cell-4911a792a82448dF", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

Resumons : 
En regardant les images unes par une sur chaque canal, on remarque que le canal bleu semble, de maniere generale, decrire l'arriere plan de maniere bien plus précise que notre fonction foreground_filter appliquée à l'image normale. On va donc utiliser le meme principe mais uniquement sur le canal bleu. On obtient ainsi une image noir et blanc qui decrit le foreground.  
D'autre part le cannal rouge semble être le plus à même de décrire les details du visage ie: ce qui nous interesse le plus.
En s'inspirant de la fonction éllongation, on peut utiliser l'image obtenue et trouver le barycentre du smiley : on supposera qu'il s'agit du milieu du smiley.  
De nautoriété commune, il arrive très rarement que la bouche se trouve au dessus de la moitié du visage. Cette evidence nous permettra d'effectuer l'analyse du smiley uniquement sur la partie inferieure du visage.  
Un petit calcul peut nous permettre d'obtenir le rayon du smiley : on prend la distance entre le barycentre et le 1er element nul de l'image "foreground" lorsqu'on se deplace vers le haut. On fait la meme chose vers le bas et on garde le maximum des deux valeurs : l'interet de cette demarche est qu'un similey ne peut pas sourir la bouche ouverte (= en montrant les dents, source de confusion pour notre filtre foreground) tout en ayant les yeux grand ouverts (ce serait particulierement bizarre). Un smiley triste quand à lui ne sourit pas ce qui ne pose donc pas probleme.  
Enfin, grace à ces informations, on peut créer une surface d'un demi disque comprenant seulement notre bouche: on prend le cercle de rayon rayonSmiley et on ignore les points au dessus du barycentre.  
Il ne reste qu'à isoler le sourire et faire ~~une regression quadratique et retourner le coefficiant dominant a~~ le calcul du minimum afin de voir si il est eloigné où non du barycentre sur l'axe des x.  
Si oui -> triste  
Si non -> content  
  
  
Biais:
Il faut que les smileys soient ronds et avec un arriere plan uni, il faut que les smileys soient jaunes et dans cette methode on suppose que un smiley ne peut sourire les yeux grand ouverts

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "db64aca779ecc9f6030d7442c300f254", "grade": false, "grade_id": "cell-4911a792a82448dG", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### Revue du code

##### Affichage du code des principales fonctions

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6744175f54caf5f72be76a7ffb88cc9d
  grade: false
  grade_id: cell-006fb180e6a86e73
  locked: true
  schema_version: 3
  solution: false
  task: false
---
from utilities import *
# Feuille 2_images.md
show_source(show_color_channels)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "abdfb5a24c36ae9a2cd982e3bcd4dba8", "grade": false, "grade_id": "cell-d21a1d7d40d56302", "locked": true, "schema_version": 3, "solution": false, "task": false}}

##### Conventions de codage

L'outil `flake8` permet de vérifier que votre code respecte les
conventions de codage usuelles de Python, telles que définies
notamment par le document [PEP
8](https://www.python.org/dev/peps/pep-0008/). Si la cellule suivante
affiche des avertissements, suivez les indications données pour
peaufiner votre code.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 698d7f2038bc259e761d6835254b4b13
  grade: true
  grade_id: cell-ce5cf24a9e83ff0e
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
assert run_without_error("flake8 utilities.py")
```

```{code-cell} ipython3

```
