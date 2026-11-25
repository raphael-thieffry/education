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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "708c86b619ca7b7c225a887d40fcf65c", "grade": false, "grade_id": "cell-4911a792a82448d7", "locked": true, "schema_version": 3, "solution": false}}

# Semaine 2: premières analyses de données

## Cours

- Cours: [analyses de données](CM2.md)

## TP: votre première analyse de donnée

### Objectif

Dans ce TP, vous allez réaliser votre première **analyse de données**,
pour répondre à diverses questions en vous appuyant sur de la
**visualisation de données** et des **tests statistiques simples**, à
l'aide des bibliothèques `Pandas`, `Numpy`, `Matplotlib` et `Seaborn`.

Suivant les bonnes pratiques pour la **Science Ouverte** et la
**Reproductibilité**, cette analyse sera documentée par un **rapport
d'analyse de données exécutable**: un document narratif détaillant
l'analyse, spécifiant pas-à-pas les traitements effectués, accompagné
de tous les artefacts requis pour reproduire les traitements: données,
code, dépendances logicielles. 

Pour cette première analyse, nous vous fournissons la trame du rapport
dans la feuille Jupyter [analyse_de_donnees](1_analyse_de_donnees.md);
votre travail est de lire cette feuille en détail, en complétant au
fur et à mesure les éléments manquants pour pouvoir l'exécuter de bout
en bout et en interpréter les résultats.

### Consignes

1.  Relisez les
    [instructions](https://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Devoirs/Semaine1/index.html#telechargement-depot-et-correction-des-tps)
    pour le téléchargement et le dépôt des TPs, ainsi que les 
	[bonnes pratiques](http://nicolas.thiery.name/Enseignement/IntroScienceDonnees/Devoirs/Semaine1/index.html#bonnes-pratiques).
2.  Téléchargez le sujet de TP `Semaine2`.
3.  Ouvrez la feuille [index.md](index.md) pour retrouver ces consignes.
4.  Ouvrez la feuille
    [1_analyse_de_donnees.md](1_analyse_de_donnees.md) et suivez les
    instructions.  
	Bon TP!

**Avant mardi 8 février à 20h**:

- Relire les diapos du cours 2.
- Finir le TP et le déposer sur GitLab; il sera corrigé en partie
  automatiquement et en partie par vos enseignants (10 points)
