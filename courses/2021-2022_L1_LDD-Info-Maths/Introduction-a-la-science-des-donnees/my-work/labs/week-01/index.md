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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4d504868e6de86a07cde9b9d2fcb4b27", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}}

# Semaine 1: introduction

## Cours

- [Présentation de l'UE](CM1_1_presentation_UE.md)
- [Introduction](CM1_2_introduction.md)
- [Conclusions](CM1_3_conclusions.md)

## Consignes

Avant le TP:
- Relisez le cours

Pendant le TP puis chez vous:
- Faites les feuilles de travail de TP ci-dessous;
- Déposez régulièrement le TP sur GitLab (submit),

Avant lundi 31 janvier 22h00:
- Déposez votre TP sur GitLab, même incorrect ou incomplet (5 points/100).

<!--
- Suivre ce [tutoriel sur les compréhensions et les itérateurs](https://doc.sagemath.org/html/en/thematic_tutorials/tutorial-comprehensions.html#tutorial-comprehensions)
!-->

## TP

### Objectifs

L'objectif de ce premier TP est de vous familiariser avec les outils
que nous utiliserons pendant tous le semestre :

- forge GitLab,
- environnement Jupyter, 
- programmation simple avec Python, 
- statistiques et
- analyse de données

En fin de TP, vous mènerez une première *étude statistique* pour
tester une hypothèse sur la composition des jurys d'assise dans le
contexte de la lutte pour les droits civiques aux États Unis.


### Exercices avancés 

Les exercices (et projets) sont organisés en deux couches: tout
d'abord des exercices pour mettre en œuvre les compétences
fondamentales et les maîtriser à l'issue de l'UE; et d'autre part des
exercices marqués d'un ♣ pour aller plus loin. Avec les premiers
exercices, vous pourrez avoir 18. Et si vous avez 18 ou plus, vous
avez suffisamment de compétences pour faire les exercices avancés :)

### Environnement de travail

L'organisation des TPs est très similaire à celle des autres cours
d'informatique comme «programmation impérative» ou «programmation
modulaire».

En salle de TP, ouvrez Jupyter en tapant dans un terminal (vous
travaillerez en local; cela permet de ne pas surcharger le service
JupyterHub):

    intro-science-donnees jupyter notebook

Sinon, à la maison (ou en salle de TP), connectez-vous au
service [JupyterHub@ParisSaclay](https://jupyterhub.ijclab.in2p3.fr/),
ou sur le serveur de secours (lien à venir), ou bien sur votre propre
machine si vous avez [installé les logiciels adéquats](https://nicolas.thiery.name/Enseignement/IntroScienceDonnees/ComputerLab/README.html)


#### Téléchargement, dépôt et correction des TPs

<div class="alert alert-info">

Dans ce cours, nous utiliserons le même outil que d'habitude (`travo`)
pour la gestion des devoirs avec GitLab, en passant par le script
`intro-science-donnees` mentionné ci-dessus; `travo` utilisera
également GitLab pour faire de la correction automatique.

</div>

Une fois Jupyter activé, téléchargez le sujet de TP en tapant la
commande suivante dans un terminal:

	intro-science-donnees fetch Semaine1

En salle de TP, il se peut que la commande ne soit pas encore
installée sur votre machine. Dans ce cas, utiliser à la place:

	~nthiery/intro-science-donnees fetch Semaine1

Ouvrez le navigateur de fichiers de `Jupyter`. 

Ouvrez la feuille de travail `~/IntroSciencesDonnees/Semaine1/index.md`
pour retrouver ces consignes et suivez les instructions à partir de là.

Une fois une feuille de travail terminée (par l'exemple
`1_jupyter.md`), tapez dans un terminal la commande suivante (elle
exécute une copie de la feuille de travail dans l'ordre en vérifiant
tous les tests automatiques):

	intro-science-donnees validate 1_jupyter.md

Pour déposer votre travail sur GitLab, tapez dans un terminal (si vous
êtes dans le groupe MI3 et soumettez la Semaine1):

	intro-science-donnees submit Semaine1 MI3

Pour lancer la correction automatique sur GitLab et télécharger le
résultat:

	intro-science-donnees fetch_feedback Semaine1

Vous pouvez alors ouvrir avec votre navigateur le fichier
`scores.html` du sous-répertoire `feedback/` nouvellement créé, et
consulter les feuilles de travail corrigées.

#### Bonnes pratiques

Comme pour les autres cours d'informatique, vous allez travailler
alternativement dans plusieurs environnements (salle de TP,
JupyterHub, ...). Pour éviter de vous mélanger les pinceaux avec
plusieurs versions du même devoir, nous vous rappelons les bonnes
pratiques:

- En début de séance: mettez systématiquement à jour votre devoir avec
  fetch.
- En cours de séance: déposez de temps en temps votre devoir avec
  submit pour le sauvegarder.
- En fin de séance: déposez systématiquement votre devoir avec submit.

**Vous taperez les commandes précédentes à chaque TP pour le commencer, le soumettre et obtenir une correction! Si ce n'est pas clair, demandez des explications.**

### Feuilles de travail

Dans ce cours, nous utiliserons Jupyter comme environnement de travail
et Python comme langage d'interaction, de calcul et de programmation. La plupart
d'entre vous ont suivi les cours «Info 111: Programmation Impérative»
et «Introduction à l'Informatique» au premier semestre et êtes déjà
familiers avec Jupyter et Python; les deux premières feuilles sont
donc des rappels et vous permettent de vous refamiliariser avec la
**correction automatique** et les **compréhensions**.

- [Prise en main de Jupyter et correction automatique](1_jupyter.md)

- [Python: fonctions et compréhensions](2_python.md)

- [Prise en main des tableaux de données (Pandas)](3_pandas.md)

- [Une première étude statistique](4_etude_statistique.md)
