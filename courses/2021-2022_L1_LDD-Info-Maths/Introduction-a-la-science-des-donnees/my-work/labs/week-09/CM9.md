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
  overlay: "<div style='position: absolute; top: 0; left: 0'>Introduction \xE0 la\
    \ Science des Donn\xE9es, L1 Math-Info, Facult\xE9 des Sciences d'Orsay</div><div\
    \ style='position: absolute; top: 0; right: 0'><img src='media/logoParisSaclay.png'\
    \ width='150'></div>"
  scroll: true
  slideNumber: true
  start_slideshow_at: selected
  transition: none
  width: 90%
---

+++ {"slideshow": {"slide_type": "slide"}}

<center>

# Cours 9: Impact de la science des données et du numérique sur notre société

</center>

<br>

<center>Fanny Pouyet</center>

<center>L1 Informatique</center>

<center>Janvier - Mai 2022</center>

+++ {"slideshow": {"slide_type": "slide"}}

**Précédemment**

* Inititation à la science des données
* Initiation à l'apprentissage statistique
* Classification d'images

**Cette semaine**

* Science et société: l'impact de la science des données et du numérique sur notre société (sources: shift project, ADEME et gouvernement)

+++ {"slideshow": {"slide_type": "slide"}}

Numérique : réseaux de communications + terminaux + data centers 

**Comment maximiser l'impact positif du numérique et de la science des données en minimisant son impact négatif ?**


**Une question en apparence inutile mais aussi insoluble**

+++ {"slideshow": {"slide_type": "slide"}}

## Contexte : le numérique dans notre société

* Les énergies fossiles représentent 80% de la consommation d'énergie mondiale
* Elles sont responsables d'une grande partie des émissions de gaz à effet de serre.
* Ces émissions impactent notre climat et nos sociétés.
* Le numérique consomme de l'énergie mais permet aussi d'en réduire la consommation en permettant une certaine optimisation

+++ {"slideshow": {"slide_type": "slide"}}

### Impacts positifs


#### Le numérique pour limiter la consommation d'énergie

* utilisation plus efficace des ressources
* diminution des pertes (capteurs d'humidité,..)

Repose sur de l'analyse des données !

+++ {"slideshow": {"slide_type": "slide"}}

#### Développement économique et social
* augmentation de la productivité des entreprises, 
* création d'emplois, 
* commerce mondialisé

+++ {"slideshow": {"slide_type": "slide"}}

#### Science ouverte et utilisation critique des données publiques 

<center> <img src=https://www.gouvernement.fr/sites/default/files/styles/plein-cadre/public/action/image/2014/09/v-ouverture-des-donnees.jpg?itok=j2Hvmyqy width=1100> source : https://www.gouvernement.fr/action/l-ouverture-des-donnees-publiques</center>

+++ {"slideshow": {"slide_type": "slide"}}

Prenons l'exemple des données publiques de [data.gouv.fr](data.gouv.fr), site développé depuis une dizaine d'années:

**Ouverture des données**: partage des données dont disposent les institutions (généralement, publiques, depuis la loi Cada 1978). Cela implique:
* la gratuité, 
* des formats facilement traitables,
* et réutilisables.

+++ {"slideshow": {"slide_type": "slide"}}

**3 objectifs** :

1. améliorer le fonctionnement démocratique (transparence, concertation);
 
2. améliorer l'efficacité de l'action publique;
 
3. intégration des données dans de nouveaux services à forte valeur ajoutée économique ou sociale.

+++ {"slideshow": {"slide_type": "slide"}}

**Avantages** :

* simplification des systèmes d'informations par la création de nouvelles bases de données;
* accès facilité par internet aux documents administratifs.
* informations publiques réutilisables à d’autres fins que la mission de service public pour laquelle elles ont été produites ou reçues.

+++ {"slideshow": {"slide_type": "slide"}}

### Impacts négatifs

**Effet direct** Le numérique consomme de l'éléctricité...

+++ {"slideshow": {"slide_type": "slide"}}

**Effets indirects**
* Augmentation de l'utilisation des ressources informatiques par sa facilitation (smartphones vs. Nokia 3310)
* Production de matériel informatique (métaux rares, pollution loin de la France)

<center> <img src=media/incidences_geostrategiques.png width=1000></center>

+++ {"slideshow": {"slide_type": "slide"}}

## Consommation énergétique

* Etude de 2018 (projection à partir de cette date): 4 scénarios
* Consommation électrique en 2017 : 21000 TWh (augmentation d'1,5%/an)
* Observation : la part du numérique (DEC) a augmenté de 70% entre 2013 et 2020 

<center> <img src=media/DEC.png width=1000></center>

+++ {"slideshow": {"slide_type": "slide"}}

## Postes de consommation

<center> <img src=media/poste_consommation.png width=1000></center>

+++ {"slideshow": {"slide_type": "slide"}}

## Nombre de postes numériques par personne

<center> <img src=media/nb_equipement.png width=1100></center>

+++ {"slideshow": {"slide_type": "slide"}}

## Empreinte carbone des calculs numériques

L'ADEME (Agence de l'Environnement et de la Maîtrise de l'Energie, **créée en 1991**) propose des moyens de calculer l'empreinte carbone des parcs numériques dans le secteur privé et public. 

<center> <img src=https://expertises.ademe.fr/sites/default/files/assets/images/loi-agec-perimetre.gif width=1000> source : https://expertises.ademe.fr</center>

+++ {"slideshow": {"slide_type": "slide"}}

* **Empreinte carbone**: équivalent C02 qui prend en compte les différents gaz responsables du changement climatique.


* Prend en compte chaque étape du cycle de vie des équipements en incluant le transport et l'utilisation.
* Bien que le calcul soit critiqué, il donne un *ordre de grandeur* tout à fait pertinent.

+++ {"slideshow": {"slide_type": "slide"}}

### Dans le secteur privé 

**Exemple d'estimation moyenne de l'empreinte carbone de l'accès à internet (au 01/01/2022):**

* Réseaux mobiles : 50 gCO2e/Go
* Réseaux fixes : 3,95 kgCO2e/mois/abonné. 
* L’utilisation des réseaux fixes est à privilégier dès que possible.

+++ {"slideshow": {"slide_type": "slide"}}

### Dans le monde de la recherche
* Estimer la consommation énergétique d'un entrainement d'un réseau de neurones n'est pas chose facile.
* Recherche active récente : exemple de calcul de vos émissions, [ML CO2 Impact](https://mlco2.github.io/impact/#home)

* Les émissions dépendent des **infrastructures** et de votre **code**.

+++ {"slideshow": {"slide_type": "slide"}}

- Une thèse en apprentissage statistique émet plusieurs tonnes de CO2. 
- Prenons l'exemple d'une thèse 2018-2022, qui a émis 2,9 tonnes de CO2 (source : doctorat de Téo Sanchez, non encore publiée)

<center> <img src=media/These_2p9TCO2.png width=700></center>

+++ {"slideshow": {"slide_type": "slide"}}

**Ordre de grandeur et objectif des émissions en France**
<center> <img src=media/ordre_grandeur_CO2.png width=700></center>

+++ {"slideshow": {"slide_type": "slide"}}

## Et pour la suite ? 

**L2 : Introduction à la science des données**
* Cours assuré par Marc Evrard (MCU, LISN)
* Apprentissage supervisé (classification + régression)
* Apprentissage non supervisé
* Evaluations (cross-validation par exemple)
* Analyses statistiques (un peu plus de mathématiques même si ca restera léger)
* TP = utiisation de `sklearn`.

+++ {"slideshow": {"slide_type": "slide"}}

## Conclusions

* Cours d'initiation:
    * Observation n'est pas interprétation (l'observation est toujours possible! normalement elle ne devrait pas poser de problème)
    * identifier la question *précise* à laquelle on souhaite répondre c'est déjà une large partie du travail en science des données
    * Notions d'apprentissage statistiques, classificateurs, langage python
    * Recul sur l'importance du numérique et des données dans notre société

+++ {"slideshow": {"slide_type": "slide"}}

* Vous avez récupéré des images, les avez prétraitées, analysées leur composition et vous avez produit un classificateur en python. Auriez-vous pensé faire ca dès la L1 ? Bravo !
