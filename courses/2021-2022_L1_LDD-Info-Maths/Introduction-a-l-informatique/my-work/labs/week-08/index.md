---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: Python 3
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f4ac758f1970322678fbcf9b9a32a127", "grade": false, "grade_id": "cell-415f04d27b610548", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Semaine 8: fichiers

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fa8df6c7071eb4d211a7ed4738ef86bc", "grade": false, "grade_id": "cell-6d952c4decd8c705", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous trouverez ici le matériel pédagogique pour la Semaine 8
qui porte sur les fichiers et flux de données.

<!--
Vous pouver le télécharger et travailler dessus selon la
[procédure usuelle](http://nicolas.thiery.name/Enseignement/Info111/devoirs.html).
Cette deuxième solution est plus riche, puisque vous pouvez essayer et
expérimenter avec les exemples et faire les exercices proposés.

Vous pouvez aussi consulter l'[ancien poly de cours](http://nicolas.thiery.name/Enseignement/Info111/Cours/Cours-7-Fichiers.pdf) qui vous a été distribué en papier.

+++ {"nbgrader": {"grade": false, "grade_id": "cell-cfd11ec03d13c3cc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Planning

En amphi virtuel lundi matin, nous ferons une séance de questions-réponses sur le [projet](http://nicolas.thiery.name/Enseignement/Info111/projet.html), le [cours](#Cours) et, si le temps le permets, les exercices de TD et de TP ([salles virtuelles](https://ecampus.paris-saclay.fr/course/view.php?id=24335#section-5), [Foire-Aux-Questions](https://hackmd.io/_EOMSwynS1uJ9k_w7XXWWQ)). 

En TD, nous continuerons les exercices de la feuille de TD.

En TP, nous continuerons les exercices de TP ci-dessous.

+++ {"nbgrader": {"grade": false, "grade_id": "cell-d6922b9cbb899cac", "locked": true, "schema_version": 3, "solution": false, "task": false}}


## Consignes

- Avant le TD: avoir lu le <a href="TD.pdf">sujet de TD</a> et commencé les exercices
- Avant le TP: avoir lu le sujet de TP<br>
  LDD IM et MNSI: avoir fait les exercices de TD

Plus vous faites d'exercices en amont des TDs et TPs, plus vous êtes efficaces:
cela vous permet en effet de bénéficier de l'aide de vos enseignants lorsque
vous en avez le plus besoin.
!-->

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "280c27b66de2bf065f13dc7f2d5c846a", "grade": false, "grade_id": "cell-bf8b493b391072c0", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## <a name=Cours>Cours</a>
- Projet: lire les [informations](http://nicolas.thiery.name/Enseignement/Info111/projet.html) 
- Cours: [Fichiers](cours-fichiers.md)
- Cours: [État d'un fichier](cours-etat-fichier.md)
- Cours: [Lecture au clavier](cours-lecture-clavier.md)
- Cours: [Lecture et écriture dans des chaînes de caractères](cours-flux-chaines-de-caracteres.md)
- Cours: [Flux de données](cours-flux.md  )

Vous pouvez aussi consulter l'[ancien poly de cours](http://nicolas.thiery.name/Enseignement/Info111/Cours/Cours-7-Fichiers.pdf) qui vous a été distribué en papier.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9be176b01e21e0bafc153e49490f4067", "grade": false, "grade_id": "cell-4f505b81ce738fdd", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## <a href="TD.pdf">TD</a>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a19c3f9a54cc2b0f7cb7ec988963186c", "grade": false, "grade_id": "cell-666b2425eb568c70", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## TP

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "de47f5571f3aab37cd99da716421a3c7", "grade": false, "grade_id": "cell-537f2c0199cca471", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Préalable:**
- Téléchargez le sujet de TP selon la
  [procédure usuelle](http://nicolas.thiery.name/Enseignement/Info111/devoirs.html).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a2cbbab119b17a80184a13012a40c628", "grade": false, "grade_id": "cell-ebc1119e2f2dc021", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: écrire dans un fichier - 20 minutes

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3e0ecf10918889771403ec4618ea680f", "grade": false, "grade_id": "cell-93bf4727bcc65ffb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1.  Consulter le fichier `fichier-ecriture.cpp`.

2.  Ouvrir ce fichier avec un éditeur de texte (par exemple `jedit` ou
    l'éditeur de texte intégré à Jupyter) et essayer de deviner ce que fait ce programme.

3.  Exécuter ce programme.  
    **Rappel:** pour exécuter un programme, il faut d’abord avoir
    compilé le fichier `.cpp` avec la commande `info-111 g++` puis
    lancer l’exécutable créé par la compilation, comme cela a été vu
    dans les TP précédents.

4.  Trouver le fichier `.txt` qui a été créé à l’exécution et l’ouvrir
    avec un éditeur de texte. Que contient-il?

5.  Copier le contenu de `fichier-ecriture.cpp` dans
    `fichier-ecriture-v2.cpp`, et adaptez le pour qu’à l’exécution il
    écrive un fichier nommé `essai.txt` contenant le texte «17 fois 23
    vaut» suivi de la valeur de ce nombre (valeur que le programme calcule par lui-même).

6.  Exécuter ce programme puis ouvrir le fichier `essai.txt` afin de
    vérifier son contenu.

7.  Lire et essayer à nouveau les exemples du cours
    «[lecture depuis le clavier](cours-lecture-clavier)».

8.  En vous en inspirant, complétez le programme `cin.cpp` pour que,
    à l’exécution, il demande à l’utilisateur
    d’entrer deux entiers, puis qu’il écrive un fichier nommé
    `multiplication.txt` contenant un texte similaire au fichier
    `essai.txt` de la question précédente, avec 17 et 23 remplacés
    respectivement par les deux entiers choisis par l’utilisateur.
    
    **Note**: Pour
    faire des affichages à l’écran et pour faire saisir des données
    depuis le clavier, il faut inclure la bibliothèque `iostream` en
    écrivant `#include <iostream>`. Pour lire et écrire dans un fichier
    de texte, il faut inclure la bibliothèque `fstream` en écrivant
    `#include <fstream>`

9.  Exécuter le programme puis ouvrir le fichier `multiplication.txt`
    pour vérifier son contenu.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3bd86b0d2da05b0e21878a4027905258", "grade": false, "grade_id": "cell-c7611331555e6e1b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exercice: petit damier - 20 minutes

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "04b532ae189f747c38896cd5c579705f", "grade": false, "grade_id": "cell-cc294ab2a446be5d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1.  Le fichier `smiley.pbm` contient l’image en noir et blanc du TD.
    Ouvrir ce fichier d’abord avec un éditeur de texte, puis avec un
    logiciel de vision d’images:
    
    -   Sous Windows, vous pouvez utiliser l’application `irfanview`.
    -   Sous Linux, vous pouvez utiliser l’application `xviewer`:
        utilisez «Control +» et «Control -» pour zoomer /
        dezoomer. Vous remarquerez que l’image est lissée / floutée. Allez
        dans le menu «Edit -> Preferences» et décochez «Smooth images when
        zoomed in» pour mieux voir les pixels.
    -   Sur JupyterHub, c'est un peu plus compliqué: dans un terminal,
        convertissez votre image en png avec:
        
            convert smiley.pbm smiley.png
            
        puis ouvrez l'image avec le navigateur de fichiers de Jupyter.

2.  Utiliser un éditeur de texte pour écrire à la main un *fichier*
    `damier.pbm` contenant une image au format PBM ([*Portable Bit Map*](http://fr.wikipedia.org/wiki/Portable_bitmap)) de taille 10x10
    représentant un damier:  

    <img src="images/damier_svg.png" width="5cm" alt="un damier">

3.  Visualiser le résultat avec un logiciel de vision d’images.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9473dc15dadb6da9dbbef807825fb397", "grade": false, "grade_id": "cell-deff170ed3020a3f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: grand damier

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "61b7b035b5709e337b816bff2d646168", "grade": false, "grade_id": "cell-599b9f9ba5a149e1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Compléter le **programme C++** <a href="damier.cpp">damier.cpp</a> qui lorsqu’on l’exécute,
écrit un fichier image `damier-automatique.pbm` comme le précédent, mais
cette fois pour un damier 100x100.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "56d4952f8a8db927f05a9389af12cc11", "grade": false, "grade_id": "cell-f5c707e1923022b4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Indication:** Vous pouvez vous inspirer de `fichier-ecriture.cpp`.
Commencer par un programme pour un damier 10x10 avant de passer à
100x100. *Si le fichier produit ne donne pas l’image attendue, ouvrez-le
avec un éditeur de texte pour mieux comprendre ce qu’il se passe et
aider au débogage. Vous pouvez aussi, si cela vous aide, faire dans un
premier temps des affichages à l’écran avec `cout`, puis écrire dans le
fichier dans un 2ème temps.*

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ef80e3ea433d122bed6c6feb1d0db3e7", "grade": false, "grade_id": "cell-390075c481532385", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: dégradé de gris

Pour créer une image avec des nuances de gris, il faut enregistrer un
fichier de texte au format PGM ([Portable Gray Map](http://fr.wikipedia.org/wiki/Portable_graymap)). Ce fichier doit
contenir des nombres entre 0 et une valeur maximale (au choix) qui
représenteront les différentes nuances de gris.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e375333482304a493af57426659060cd", "grade": false, "grade_id": "cell-e9dc4f9dddf26cf6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1.  Écrire à la main, dans un éditeur de texte, un fichier de texte
    représentant une image de 10 pixels par 10 pixels, contenant
    différentes nuances de gris de votre choix. Ouvrir ce fichier de
    texte avec un logiciel de visualisation d’images pour voir le
    résultat.

2.  Implanter un programme `degrade.cpp` qui écrit un fichier contenant une image
    `degrade.pgm` de taille 255 par 255, avec un dégradé de gris comme celui-ci:

    <img src="images/degrade.png" width="5cm" alt="un dégradé de gris">

3.  Répéter, avec une image de taille 100x100 puis 1000x1000.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "53ceb5c00ee23d9823672a2bc447bbbe", "grade": false, "grade_id": "cell-c12503d517b73b5c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: inversion d’image

Implanter un programme `videoInverse.cpp` qui lit un fichier contenant une image au format
PGM (par exemple le fichier `image.pgm` fourni), et écrit un fichier
contenant la même image en vidéo inverse (clair remplacé par sombre et
réciproquement).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a6d4092f0df8a112caa6cf96101f643c", "grade": false, "grade_id": "cell-df827550236b9f1f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Indication:** Implanter une fonction

        /** Image en vidéo inverse
         * @param image1: le nom du fichier contenant l'image à lire
         * @param image2: le nom du fichier pour l'image à écrire
         **/
        void videoInverse(string image1, string image2);

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f2b719ef1515ccb417393ff5b767f529", "grade": false, "grade_id": "cell-0629f6ca7111d945", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice ♣: Dégradé circulaire de rouge

1.  Implanter un programme `degrade-circulaire.cpp` qui écrit un fichier contenant une image
    `degrade-circulaire.ppm` au format PPM de taille 255 par 255, avec
    un dégradé circulaire de rouge:  

    <img src="images/degrade-circulaire.png" width="5cm" alt="un dégradé circulaire">

2.  Répéter, avec une image de taille 100x100 puis 1000x1000.
