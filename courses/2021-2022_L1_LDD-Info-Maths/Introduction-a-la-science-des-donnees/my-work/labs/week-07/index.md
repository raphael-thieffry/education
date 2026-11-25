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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1b85a5f281e2ddc3b2e9d65806cb9230", "grade": false, "grade_id": "cell-ebb8f94141812ddb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Semaine 7

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5bacf7fbc084700b8b209e994454ab6d", "grade": false, "grade_id": "cell-987eb3c03a1417f4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Objectifs

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "48f92d8a1abf93e2dee632c9a9ecbe27", "grade": false, "grade_id": "cell-d94d0b397fc433ff", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous êtes désormais familiers avec le schéma VI-ME-RÉ-BAR --
[VI]sualisation, [ME]sure, [RÉ]férence (baseline), [BAR]res d'erreur,
et vous avez appris à classifier des jeux de données simples:

- Collecter et traiter des images (recentrage automatique, seuillage
  etc.).
- Extraire des attributs sur les couleurs (ad-hoc), la forme (ad-hoc
  ou matched filters) ou les pixels (PCA).
- Entraîner un classificateur (oneR, k-NN, arbre de décision, perceptron
  ou autres) sur vos données d'entraînement.
- Calculer un score de performance du classificateur sur vos données
  de test.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9cb9021531b977b2619745096271847b", "grade": false, "grade_id": "cell-3c07cc11be90a0d2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

À l'occasion du second mini-projet, vous allez appliquer ces
connaissances et votre savoir faire à vos propres données, en
développant de nouveaux aspects de l'analyse (biais sur les
méta-données) ou en allant plus loin des les concepts déjà introduits
(PCA, nouveaux classificateurs).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "52b6fa9944f0284718257bae7bd4ae2a", "grade": false, "grade_id": "cell-c8b352e502568e10", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Ce travail va se dérouler sur les trois dernières séances:

Semaine 7 : 14 - 18 mars (dépôt le 21 mars à 22h, 5 points)
- Analyse de biais
- Manipulation de son (♣).
- Choix du jeu de données; il consistera typiquement d'images ou
  photographies que vous aurez prises vous-même ou que vous aurez
  collectées sur internet. Si vous êtes intéressés vous pouvez faire
  une analyse sur d'autres données que les images!

Semaine 8 : 28 - 31 mars (dépôt le 4 avril à 22h)
- Validation du jeu de données auprès de vos chargées et chargés de TP
  et import de celui-ci dans votre dépôt de la semaine 8. Préparation
  de votre jeu de données, prétraitement et analyse.

Semaine 9 : 4 - 8 avril (dépôt le 11 avril à 22h)
- Fin du projet, retour sur les classificateurs.

Semaine 11 : Soutenances de projet
- Selon les groupes de TD: le 20 ou le 21 avril. Voir le
  [planning](https://ecampus.paris-saclay.fr/course/view.php?id=57746#section-1) sur eCampus.

Le travail se fera en binôme, le même que pour le premier mini-projet
sauf demande motivée auprès de vos chargées et chargés de TP.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "31a2e4d3450ec0b2b18d68c2cf4e4762", "grade": false, "grade_id": "cell-37c9a8d98b17a12c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Support de cours

- [Diapos](CM7.md)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d28db13b3adc7b26c27a843cf178b338", "grade": false, "grade_id": "cell-862f8113cb548aa9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## TP

+++

- [ ] Téléchargez le sujet de TP `Semaine7` (rappel des
     [instructions](http://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Devoirs/Semaine1/index.html#telechargement-et-depot-des-tps)).
- [ ] Ouvrez la feuille [index](index.md) pour retrouver ces consignes.
- [ ] Ouvrez la feuille sur le [biais dans les données](1_biais.md) et
     suivez les instructions.
- [ ] Ouvrez la feuille [analyse](2_analyse.md) et suivez les
     instructions pour lancer l'analyse sur le jeu de données fourni.
- [ ] Ouvrez la feuille sur la manipulation de [données
     audio](3_audio.md) et suivez les instructions.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b2df12ecdebcbd335c9ed14088f4bcd9", "grade": false, "grade_id": "cell-31de674cb5a74482", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Préparation de vos images pour la semaine prochaine

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c160c6b9d5ffb8e589e814d8036eecc5", "grade": false, "grade_id": "cell-4a02dd473501da58", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La semaine prochaine (après les examens mi-semestre), vous
travaillerez sur vos images. Commencez des à présent à les collecter.

**Conseil important :** Choisissez des images qui sont toutes dans la
même orientation (carrée, portrait ou paysage) car avoir un mélange
rend la préparation des données plus complexe.

+++

Voilà comment les préparer :
- [ ] Déposez votre propre jeu de données dans un sous-dossier `data`
    dans `IntroSciencesDonnees`. Sur JupyterHub, vous pouvez utiliser
    le bouton `Téléverser` en haut à droite.
- [ ] Suivez les mêmes conventions de nommage que lors du premier projet:
    - `a01.jpg`, `a02.jpg`, ... pour les images de la première classe;
    - `b01.jpg`, `b02.jpg`, ... pour les images de la deuxième classe.



- [ ] Vérifiez la taille individuelle des images:

        cd ~/IntroScienceDonnees/data
		ls -lh

    Si elle dépasse 50~ko par image, réduisez la résolution pour
    limiter les temps de calcul et la taille de votre dépôt avant de
    démarrer le projet 2. Pour cela, utilisez la commande ci-dessous,
    disponible sur JupyterHub et en salles de TP :

        cd ~/IntroScienceDonnees/data
        mogrify -geometry 256x256 *.jpg 
       
    Vous pourrez ensuite les redimensionner et les recadrer en Python,
    comme vu la semaine dernière.
