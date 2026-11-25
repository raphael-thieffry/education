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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a425fe04adf9e251722a74b927586337", "grade": false, "grade_id": "cell-3876f910a24fe8a7", "locked": true, "schema_version": 3, "solution": false}}

# Analyse de données sur les pays européens

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "800f6f6b25298206e9de2de40b31fc81", "grade": false, "grade_id": "cell-8647bce9e2a5d173", "locked": true, "schema_version": 3, "solution": false}}

Nous allons chercher s'il existe des différences d'espérance de vie
entre les pays européens. Si oui, existe-t-il certaines explications,
sociétales, à ces différences ?

Pour mener cette analyse, nous nous baserons sur des données sur
certains pays de l'Union Européenne, agrégées à partir de données
issues d'un [TP de l'Université
Lyon1](https://pbil.univ-lyon1.fr/R/donnees/santeUE.txt) et des
[données européennes](https://data.europa.eu/en).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "114b2eb7aac993047184dea6844c2335", "grade": false, "grade_id": "cell-8647bce9e2a5d174", "locked": true, "schema_version": 3, "solution": false}}

## Import des bibliothèques

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 929004e81ec702f7ffc1b8bb323e860f
  grade: false
  grade_id: cell-106177762ff8d9b4
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import numpy as np                # Tableaux numériques
import pandas as pd               # Tables de données
import seaborn as sns; sns.set()  # Visualization
import matplotlib.pyplot as plt   # Visualization
# Configuration intégration dans Jupyter
%matplotlib inline
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1558ff93a6764daef77d161320626946", "grade": false, "grade_id": "cell-d7d7ff6550223d3e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Première étape: description de la table de données

Les données sur les pays européens sont fournies dans le fichier CSV
`UE_health.csv` que nous chargeons maintenant dans la table `europe`,
en précisant que l'index est donné par la colonne `pays`.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d76334db7d35f2c89a1fe991c936d6c5
  grade: false
  grade_id: cell-106177762ff8d9b5
  locked: true
  schema_version: 3
  solution: false
  task: false
---
europe = pd.read_csv("UE_health.csv", index_col="pays")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ba57b1caf06f946bc27f06328e493b01", "grade": false, "grade_id": "cell-c2f39100084a043a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les colonnes de cette table contiennent les informations suivantes :

- `depSante_hab` : dépense pour la santé par habitant par an en 2016
  par habitant
- `esp_vie_f` (respectivement `_h`) : esperance de vie des femmes
  (resp. homme) à la naissance en 2008
- `vaccin_DTP` = % de la population vaccinée pour la diphtérie,
  coqueluche et tétanos
- `vaccin_rougeole` = % population vaccinee pour la rougeole
- `medecins` : nombre de médecins exerçant leur profession et qui
  fournissent directement des soins aux patients pour 100,000
  habitants
- `depSprive` (respectivement public) : dépense dans le secteur public
  (resp. privé) en 2012 pour la santé en standard de pouvoir d'achat
  par habitant
- `entree_UE` : année d'entrée dans l'UE
- `prop_scolarise` = proportion des enfants entre trois ans et l’âge
  de début de l’enseignement primaire obligatoire.
- `esp_vie_bonne_sante` : espérance de vie en bonne sante en 2019
- `deces_SIDA` : nombre de deces dus au SIDA en 2018 (homme+femme)
- `brasserie` : nombre de brasseries par millions d'habitants 2018
- `pates` : Consommation de pâtes en kilogrammes par habitant en 2013
- `dep_ALD` : dépense pour les soins de longue durée par habitant par
  an en 2016. Les soins de longue durée consistent en une gamme de
  services médicaux et de soins personnels qui sont consommés dans le
  but principal de soulager la douleur et la souffrance et de réduire
  ou de gérer la détérioration de l'état de santé chez les patients
  avec un degré de dépendance à long terme en standard de pouvoir
  dachat par habitant.
- `nobels` : nombre de prix nobels par pays de naissance (toutes
  catégories) en 2020

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "777aa98ef12b3dbf6b61cce2e0d748cb", "grade": false, "grade_id": "cell-d7d7ff6550223d3f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice** : 

Décrivez ci-dessous cette table par un texte de quelques lignes. Pour
vous guider, répondez entre autres aux questions suivantes:

- Quelle est la taille de la table ? 
- Quels sont les pays décrits ? Y a-t-il des pays de l'UE manquants ?
- Quelles sont les colonnes numériques ? Et les autres ? 
- Y a-t-il des données manquantes ?

Pour trouver les informations, vous pouvez utiliser des commandes
Python dans les cellules plus bas.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7a8c38756d442ae33e1ac2054383ecbc", "grade": true, "grade_id": "cell-34677ecc229d3f8c", "locked": false, "points": 5, "schema_version": 3, "solution": true, "task": false}}

- Taille table : 26 entrées
- Il manque la croatie et malte, et le royaume uni est pris en compte
- 5 colonnes d'entiers et 12 colonnes de flottants
- On voit que le nombre de donnees non nulles est variable selon la collone, donc on en déduis que il y a des NaN

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ca49d9802401cd73660a49383e62edbe
  grade: false
  grade_id: cell-a7eef074d0ac872f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe.shape
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1508983a96d27322761d893bc5a6a204
  grade: false
  grade_id: cell-a7eef074d0ac872g
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe.describe()
```

```{code-cell} ipython3
europe
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "13f6643fff01c32f5aa3172fe5d654d9", "grade": false, "grade_id": "cell-eb2909432b6312ab", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Deuxième étape : description de l'objectif

Nous allons chercher à apporter des questions à la question
scientifique suivante: existe-t-il, d'un pays à l'autre, des
**déterminants de santé**?

Un déterminant de santé est un « facteur définissables qui influence
l’état de santé, ou qui y est associé » (Agence de la santé publique
du Canada, 2007) ?

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "82a7331a87d22d113679c30ed9a6abaa", "grade": false, "grade_id": "cell-eb2909432b6312ac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Quelles données de la table proposez-vous d'utiliser, et comment, pour
déterminer l'espérance de vie des individus d'un pays ?

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fe161c2b75d7a8e660cf1613bab4ade0", "grade": true, "grade_id": "cell-eb2909432b6312ad", "locked": false, "points": 2, "schema_version": 3, "solution": true, "task": false}}

- esp_vie_f /_h -> on peut faire des moyennes et comparer en fonction des sexes
- esp_vie_bonne_sante

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "be33bd36656bfb4d6a097492170e934f", "grade": false, "grade_id": "cell-1ad9ea64fc9cfd94", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Troisième étape: observation de la table

On va commencer par observer nos données.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d50d3bb605e8c0d251226f777e187627", "grade": false, "grade_id": "cell-1ad9ea64fc9cfd95", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice**:

L'objectif est de donner des éléments de réponses aux questions
descriptives suivantes:
- Comment varie l'espérance de vie ? 
- Quel sexe vit le plus longtemps en moyenne ?

Pour cela:

1. Commencez par créer une nouvelle colonne appelée `esp_vie` dans la
   table `europe` calculée en faisant la moyenne de l'espérance de vie
   des femmes et des hommes; pour simplifier, on pourra supposer qu'il
   y a autant de femmes que d'hommes dans la population.
   
   **Indications:** extrayez la colonne `esp_vie_f` et la colonne
   `esp_vie_h` de `europe`, faites en la somme, divisez par $2$ et
   affectez le résultat à la colonne `esp_vie` de `europe` (qui sera
   créée au vol).

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 7d5660f366c9b8219cff9c3651ba1ec5
  grade: false
  grade_id: cell-c77afb97346f035c
  locked: false
  schema_version: 3
  solution: true
  task: false
---
esp_vie_f = europe['esp_vie_f']
esp_vie_h = europe['esp_vie_h']
europe['esp_vie'] = (esp_vie_f+esp_vie_h)/2
europe
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "03a2b43f7a33eac98398f15c8deb3c0a", "grade": false, "grade_id": "cell-38444ee6819ac8ee", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2. Représentez sous forme d'histogramme la distribution de l'espérance
   de vie pour chaque sexe et pour la moyenne des deux. Pour cela vous
   pouvez utiliser la méthode `hist` de `DataFrame`:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: c0867c1dbc2be3ce5690edb21e733cdf
  grade: false
  grade_id: cell-e2de167f5acee5cf
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe.hist("esp_vie_f")
europe.hist("esp_vie_h")
europe.hist("esp_vie")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d6b8bb745cc0b6f67de012529f0bf284", "grade": false, "grade_id": "cell-e5e58156623c4b53", "locked": true, "schema_version": 3, "solution": false, "task": false}}

3.  ♣ (à faire plus tard, lorsque vous aurez fini le reste du TP)
    Raffinez la figure pour que les trois histogrammes soient
    superposés, avec des couleurs pour les distinguer, des labels en
    Français, une légende.
	
	**Indication:** voir `plt.hist`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 4fcb2f228b75e8e0c40c77819c7c672c
  grade: false
  grade_id: cell-c77afb97346f035d
  locked: false
  schema_version: 3
  solution: true
  task: false
---
plt.hist(europe["esp_vie_f"], label="femmes")
plt.hist(europe["esp_vie_h"], label="hommes")
plt.hist(europe["esp_vie"], label="moyenne")
plt.xlabel("Age")
plt.ylabel("Nombre de pays ayant cette esperence de vie")
plt.legend()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5b812e586f57dbbd1dc5bfbb5112e549", "grade": false, "grade_id": "cell-9bc6bfaf45849782", "locked": true, "schema_version": 3, "solution": false, "task": false}}

4.  Calculez la différence d'espérance de vie entre hommes et femmes

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 74f979433d441532a898eb4382d68279
  grade: false
  grade_id: cell-a7db56ceea1030cb
  locked: false
  schema_version: 3
  solution: true
  task: false
---
esp_vie_f-esp_vie_h
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f7b5ebd1ce277b91353991ef01514598", "grade": false, "grade_id": "cell-a261adb91e1a00bc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

5. Décrivez les résultats observés

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "064c2d10a26eba270ca0025e7753710c", "grade": true, "grade_id": "cell-744e94c8f8292a84", "locked": false, "points": 3, "schema_version": 3, "solution": true, "task": false}}

On voit que la difference d'esperence de vie en fonction du sexe est signficative en europe : en moyenne, une femme vit 4 ans de plus qu'un homme en suede, et jusqu'a 11,75 ans de plus en Lituanie

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "53fa639ae340d00d1fbc9428a6c4441b", "grade": false, "grade_id": "cell-85e26887a30112ac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons continuer à observer les données.

**Exercice** 

1.  Appliquez la méthode `corr()` de la bibliothèque `Pandas` à la
    table `europe`.

```{code-cell} ipython3
---
code_folding: []
deletable: false
nbgrader:
  cell_type: code
  checksum: 5a09476d767f2b3b5cbf39f920ceb6ee
  grade: false
  grade_id: cell-4b826c34cfe02997
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe.corr()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "43f1d32472dd8e8e96c07275f267d321", "grade": false, "grade_id": "cell-7305fec1819c9690", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2.  Pour mieux visualiser les corrélations, affichez celles-ci sous
    forme de carte de chaleur, comme vu au [CM2](CM2.md):

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 14a02e852eac4c10081f32682f4ddb3a
  grade: false
  grade_id: cell-72f9cbb50a3e1a9c
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe.corr().style.background_gradient(cmap='coolwarm', axis=None)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "510214d331ddb8dd5b52c720a1c91873", "grade": true, "grade_id": "cell-85e26887a30112ad", "locked": false, "points": 6, "schema_version": 3, "solution": true, "task": false}}

3.  Quelles sont les variables les plus corrélées à l'**espérance de
    vie**? Décrivez vos observations. Attention on ne demande pas
    d'interprétation à ce stade.

(positivement ou negativement)
L'esperence de vie des hommes, des femmes et en bonne santé, mais c'etait previsible. Cependant il y a aussi les dépenses de santées par habitant, les depenses de santé dans le public, la date d'entrée dans l'ue, le vaccin contre la rougeole, les déces du sida et enfin les depenses pour des soins de longue durée.

On peut citer la consomation de pates et la propotion de prix nobels dans la population, qui sont modérement corellés


4.   Quelles sont les informations qui ne corrèlent pas ou peu (< 0.3
     en valeur absolue) avec l'espérance de vie des européen.nes ?


Les brasseries, les depenses dans le secteur privé, la proportion de medecins dans la population, le vaccin DTP

5.  Quelle(s) variable(s) corrèle(nt) fortement de façon négative avec
    l'espérance de vie?

Le vaccin de la rougeole, l'entrée dans l'ue et les dèces du sida

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3bb4f126e387cca05d5363aa1bf1b516", "grade": false, "grade_id": "cell-59b086b9a7351acb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Première interprétation

Que pouvez vous dire de ces observations? Y a-t-il des choses
étonnantes ou non attendues? Y a-t-il des choses attendues?

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "98dc4a79fa29c938eea96969a3975e23", "grade": true, "grade_id": "cell-6cc172376a6a1121", "locked": false, "points": 2, "schema_version": 3, "solution": true, "task": false}}

Les variables liées à la santée étaient previsible, cependant la correlation negative rougeole/esperence de vie est surprenante. Meme si la correlation est faible, le fait que la correlation medecin/esperence de vie soit negative est aussi surprenante. Aussi le fait que l'esperence de vie en bonne santé ne soit pas aussi correlée que je le pensais à l'esperence de vie m'a surpris. Meme chose pour l'UE, où la correlation ne me semblait pas pouvoir etre si forte. Enfin pour les collones "hors sujet", c'etait évident

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7ac51cba6cff9da5daaa30554854c7bb", "grade": false, "grade_id": "cell-193e638c102d8d62", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Correlation n'est pas causalité

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "48dd3847d911e3628422dba6b683f573", "grade": false, "grade_id": "cell-193e638c102d8d63", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** 

La corrélation entre la date d'entrée dans l'UE et l'espérance de vie
moyenne est de -0.68 (exactement: -0.677157). Proposez deux hypothèses
pour expliquer cette corrélation.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5084e69ff126aee8221a2ebc42de6f6e", "grade": true, "grade_id": "cell-5adf965bf26113e8", "locked": false, "points": 2, "schema_version": 3, "solution": true, "task": false}}

On pourrait penser que l'UE augmente l'esperence de vie, mais il est important de souligner que les 1ers pays à être rentré dans l'ue (et l'avoir créé) sont les pays les plus riches de l'europe. A contrario, les derniers arrivés sont les pays pauvres des balkans.
Une autre hypothese que la richesse pourrait être trouvée dans le fait que les balkans ont été touchés par les guerres ces dernières années, diminuant l'esperence de vie et faisant augmenter la correlation entrée UE/esperence de vie

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9f254a9dc940551c01a5d58f4a7515ec", "grade": false, "grade_id": "cell-fefe4d124f205c7d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Préparation des données

#### Données manquantes

**Exercice:**

Complétez les valeurs manquantes de la table par la moyenne des
colonnes correspondantes. Pour cela vous utiliserez la méthode
`fillna` vue au [CM2](CM2.md). Stockez le résultat dans la variable
`europe_filled`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 9634c92676f63422d55aa61e6d6f0588
  grade: false
  grade_id: cell-0c29581ba1da5a27
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe_filled = europe.fillna(europe.mean())
europe_filled
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 65e84cb61aab0ac1b34e2df8b7271c13
  grade: true
  grade_id: cell-6dd011ea651d81f1
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert isinstance(europe_filled, pd.DataFrame)
assert europe_filled.shape == europe.shape
assert (europe_filled.index == europe.index).all()
assert (abs(europe_filled.mean()-europe.mean()) < 0.001).all()
assert not (europe_filled.isna()).any(axis=None)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "668dd3fe1e1436b05269c5e81463933c", "grade": false, "grade_id": "cell-1d3c139fc0e06e8e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### Standarisation de la table

Les résultats des calculs peuvent être fortement influencés, si ce
n'est distordus, par l'ordre de grandeur des données, par exemple
selon les unités utilisées pour les exprimer. Pour éviter cela, il est
souvent souhaitable d'utiliser des tables de données
**standardisées**, c'est-à-dire dans lesquelles chaque colonne est de
moyenne $0$ et d'écart type $1$. Sauf cas particulier (colonne
constante), toute table peut être standardisée: il suffit, colonne par
colonne, de soustraire la moyenne puis de diviser par l'écart type.
Nous reverrons cela en détails lors du CM3.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "95b9cac6fd706617cd9a40d278bf8344", "grade": false, "grade_id": "cell-1d3c139fc0e06e8f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** 

Standardisez la table `europe_filled` et stockez le résultat dans
`europe_std`. Puis utilisez `describe` pour vérifier que la table
obtenue est bien standardisée.

Pour rappel, la moyenne se calcule par colonne avec la méthode `mean`
et l'écart-type avec la méthode `std`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1c089d446cb529ddb34448a9a5f82535
  grade: false
  grade_id: cell-578d7438d95a7255
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe_std = (europe_filled-europe_filled.mean())/europe_filled.std()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 457d68a13ce70c66448b26ae1aa242e5
  grade: true
  grade_id: cell-6930becb4cbbf2ea
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert isinstance(europe_std, pd.DataFrame)
assert europe_std.shape == europe.shape
assert (europe_std.index == europe.index).all()
assert (abs(europe_std.mean()) < 0.001).all()
assert (abs(europe_std.std()-1) < 0.001).all()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d6f6ade0adfea09332ba5df9ea314dbe", "grade": false, "grade_id": "cell-7305fec1819c9691", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:**

Affichez la matrice de corrélation sous forme de carte de chaleur:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 67ab01a2522352a7a9c90b4e1abfc8ff
  grade: false
  grade_id: cell-6c3d6f8b82e8b0ac
  locked: false
  schema_version: 3
  solution: true
  task: false
---
europe_std.corr().style.background_gradient(cmap='coolwarm', axis=None)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "34439c289557a7149cc93b2d7213b436", "grade": false, "grade_id": "cell-d6cef0a31ccd3266", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Régressions linéaires

On peut représenter des regressions linéaires entre l'espérance de vie
et n'importe quelle autre donnée. Prenons l'exemple de la dépense
publique de santé qui a la plus forte corrélation. On représente
l'espérance de vie (variable aléatoire) en fonction de la dépense
publique de santé (variable explicative): chaque point correspond à un
pays. La droite bleue correspond au modèle linéaire du type: esp_vie =
a * dep_Spublic + b avec (a,b) les paramètres ajustés:

```{code-cell} ipython3
sns.regplot(x="dep_Spublic", y="esp_vie", data=europe_std)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ea96351a928556f30053071c3e805cba", "grade": false, "grade_id": "cell-5a37f3af26472421", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Représenter les régressions linéaires pour les six
variables données dans le vecteur 'determinants'. Pour cela remplissez
le code ci-dessous en utilisant une boucle `for` et, comme ci-dessus,
la fonction `regplot` du package `seaborn`. Quels déterminants
semblent prédictifs de l'espérance de vie? Est-ce les mêmes qu'avec le
calcul de la corrélation ?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 223dbb68694305d998156dd23cd1ba77
  grade: false
  grade_id: cell-d53234dfccf90ba6
  locked: false
  schema_version: 3
  solution: true
  task: false
---
determinants=['esp_vie_bonne_sante', 'entree_UE','brasseries', 'dep_Spublic','dep_Sprive','medecins']

# Ici, écrivez une boucle for pour repésenter graphiquement la régression linéaire 
# pour chaque déterminant dans l'objet plot.
plt.figure(figsize=(10,10))
for v in determinants:
    plot = sns.regplot(x=v, y="esp_vie", data=europe_std)
    # plt.plot(reg.x, reg.y, 'o-', color='lightgrey', label='No mask')
    plot.set_xlim(-2,2.5)
    plot.set_xlabel(v)
    plot.set_ylabel("Espérance de vie")
    plot.legend(labels=determinants, bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "24a1a999ab712e8b2e92e6d4fa5ad774", "grade": false, "grade_id": "cell-30a2ce5f1e7c564b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Commentez et interprétez cette figure.

+++

Les pentes negatives indiquent une correlation negative. La zone autour de la pente indique l'ecart type (J'ai été forcé de modifier un peu le code etant donné que je n'ai pu comprendre exactement ce qu'on attendait de moi pour cette question)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7bd9702c7257dc73fb7b2e361d367334", "grade": false, "grade_id": "cell-4b1fe4e8ee6971ac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Quatrième étape: la modélisation

Comme vu [en cours CM2](CM2.md), on peut combiner les déterminants et
construire un modèle linéaire généralisé (GLM). Par exemple, sachant
que l'espérance de vie dépend de la dépense en santé par habitant, on
peut construire un modèle simple qui ne dépend que de ce déterminant:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d38c2f99423e0bd7722a3ba72506162f
  grade: false
  grade_id: cell-5ea04eead96598d0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import statsmodels.formula.api as smf
import statsmodels.api as sm
frm = "esp_vie ~ depSante_hab "
model = smf.glm(formula = frm, data = europe_filled)
result = model.fit()
result.summary()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f78734323f72774ab2182e7f18ff07f1
  grade: false
  grade_id: cell-99cf38941a80bd86
  locked: true
  schema_version: 3
  solution: false
  task: false
---
result.pvalues
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7d7e7623295a3ef294565ce1ba18e0ab", "grade": false, "grade_id": "cell-429fc2516bb30344", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La p-value est inférieure à $0.05$ : on peut rejeter l'hypothèse nulle
et conclure que la dépense en santé par habitant permet d'estimer
l'espérance de vie moyenne. Le modèle est du type: esp_vie = 0.0014 *
depSante_hab + 73.8531.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2f77486fe710cbd05df29ef89fe2d8a8", "grade": false, "grade_id": "cell-429fc2516bb30345", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les modèles linéaires généralisés peuvent etre utilisés dans le cas où :
- Il n'y a pas de données extrêmes qui fausseraient le modèle: les
  résultats du GLM sont fortement influencées par une ou plusieurs
  valeurs beaucoup plus grandes que les autres dans les variables
  explicatives.
- Les variables explicatives sont indépendantes : quand $X_i$ augmente
  $Y$ peut etre modifié mais les autres variables explicatives restent
  inchangées. Ceci est impossible quand les variables sont corrélées
  entre elles.
- Lorsqu'on a trop de variables explicatives par rapport aux données
  même si elles n'ont aucun pouvoir explicatif, le modèle peut
  toujours parfaitement expliquer les données (chaque variable
  explique une donnée, indépendemment les une des autres). Le problème
  c'est que le modèle n'est pas généralisable à un autre jeu de
  données.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7acbb551ede4d6cbe5a9138f8febb106", "grade": true, "grade_id": "cell-429fc2516bb30346", "locked": false, "points": 6, "schema_version": 3, "solution": true, "task": false}}

**Exercice $\clubsuit$:** 

Proposez un modèle explicatif avec un GLM avec la dépense en santé par
habitant et la dépense dans le secteur public. Décrivez brièvement les
résultats (on ne vous demande pas de les interpréter). Est-ce qu'on a
le droit de faire un modèle GLM avec ces deux paramètres ? Pourquoi ?

**Consigne:** Vous utiliserez les cellules ci-dessous pour faire les
calculs dont vous aurez besoin (en supprimant celles que vous
n'utiliserez pas) et répondrez aux questions ici:

Lorsque la depense publique augmente, la depense de santé par habitant augmente également (coefficient positif). La P-value est inferieure à 0.05 ce qui veut dire que cette augmentation n'est pas due au hasard dans notre jeu de donnees. Puisque ici la seule variable explicative impliquée se trouve être la depense de santé par habitant, les variables sont évidement independantes. Il n'y a pas non plus de données extremes. On peut donc utiliser le model glm

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ba688b9a97f540890a8a352e071826e7
  grade: false
  grade_id: cell-1db4578e47bf6caf
  locked: false
  schema_version: 3
  solution: true
  task: false
---
frm = "dep_Spublic ~ depSante_hab"
model = smf.glm(formula = frm, data = europe_filled)
result = model.fit()
result.summary()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1e6232cdff1ac5e90e592b2751d0f285
  grade: false
  grade_id: cell-1db4578e47bf6cag
  locked: false
  schema_version: 3
  solution: true
  task: false
---
result.pvalues
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "84a24fa65902b2fba1f5fff886d31a73", "grade": false, "grade_id": "cell-f2330dcf5f3ebc8c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Nouveau jeu de données : les fleurs d'iris

Le jeu de données suivant a été collecté par Fisher en 1936 et
comprend des échantillons de trois espèces d'iris (*Iris setosa, Iris
virginica* et *Iris versicolor*). Pour chaque échantillon, vous avez
accès à : la longueur (*length*) et la largeur (*width*) des sépales
(*sepal*) et des pétales (*petal*), en centimètres.

Ce jeu de données est fourni avec la bibliothèque `seaborn` et vous
pouvez le charger avec:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: babffbf6151bc8665adadb7237948b31
  grade: false
  grade_id: cell-dbe1aad4d899aeae
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import seaborn
iris = seaborn.load_dataset("iris").set_index("species")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8ed0b81f10fea95cdfdff58f37ef99a4", "grade": false, "grade_id": "cell-aee6b63970210f97", "locked": true, "schema_version": 3, "solution": false, "task": false}}

L'appel à `set_index` transforme la colonne `species` en index; cela a
notamment comme avantage que toutes les colonnes de la table obtenue
sont numériques.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7130bd950da8bfe81376e3d944af164a", "grade": true, "grade_id": "cell-f5a9de1250ea8efh", "locked": false, "points": 6, "schema_version": 3, "solution": true, "task": false}}

**Exercice $\clubsuit$:** 

Menez sur ce jeu de données une analyse similaire à celles que nous
avons mené depuis le début du TP.

**Consigne:** Vous répondrez aux questions ici, en utilisant les
cellules ci-dessous pour faire les calculs dont vous aurez besoin
(et en supprimant celles que vous n'utiliserez pas):

1.  Décrivez les données. En particulier répondez au minimum aux
    questions suivantes: Quelle est la taille du jeu de données? Y
    a-t-il des données manquantes ?

    Il y a 150 entrées dans le tableau et 4 collonnes. Le "info()" nous apprend qu'il n'y a aucune donnée manquante

2.  Calculez les corrélations deux à deux et représentez les valeurs à
    l'aide d'un carte de chaleur. Que pouvez vous en dire ?

    la taille (longueur/largeur) des pétales est corrélée à la longueur des sépales. De la meme maniere la largeur des sépales est correlée (negtivement cette fois ci) avec la largeur et la longueur des pétales

3.  Représentez les variations de données à l'aide de pair plots vus
    en cours. Selon vous, existe-t-il une ou plusieurs de ces quatre
    caractéristiques qui permet de différencier les espèces ?

    **Indication:** nous avons vu en cours l'utilisation de l'argument
    `hue` pour classer les échantillons en fonction du contenu d'une
    colonne. Ici, on veut classer en fonction de l'espèce. Pour cela,
    vous utiliserez `reset_index` pour refaire de l'index une colonne
    à part entière `species`.

    La longueur des pétales permet d'identifier tres distinctement l'espece setosa, de meme que la largeur des pétales (en moyenne la largeur des petales est plus grande sur l'espece virginica que sur l'espece versicolor)

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 5840f8adc5cd41bc20b5eda456e54746
  grade: false
  grade_id: cell-34a65b06ccee9ec7
  locked: false
  schema_version: 3
  solution: true
  task: false
---
iris.info()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 40393d3f36d1729f66deb52b2f577e49
  grade: false
  grade_id: cell-e50af8129d0f7da4
  locked: false
  schema_version: 3
  solution: true
  task: false
---
iris.corr().style.background_gradient(cmap='coolwarm')
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f180997795d86f7e8801d82cfeae482b
  grade: false
  grade_id: cell-13103286418476c5
  locked: false
  schema_version: 3
  solution: true
  task: false
---
sns.pairplot(iris.reset_index(), hue="species")
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 24dbddc0123453ce2972c2a04bac39f5
  grade: false
  grade_id: cell-02c3ae8a3075a53f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# YOUR CODE HERE
raise NotImplementedError()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 7cd16387cb70e6c5646a263929681b24
  grade: false
  grade_id: cell-e57843f15ef4f82a
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# YOUR CODE HERE
raise NotImplementedError()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 751e52f9c46977efca1cce3ab9db26f6
  grade: false
  grade_id: cell-e57843f15ef4f82b
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# YOUR CODE HERE
raise NotImplementedError()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "90144d15cc6a515583b8e201a2831d40", "grade": false, "grade_id": "cell-60c511633f2899a1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Conclusion

<div class="alert alert-info">

Nous avons fini cette première partie de ce cours consacré aux
analyses de données, avec un accent mis sur la [VI]sualisation des
données. La semaine prochaine et jusqu'à fin du cours nous nous
concentrerons sur la classification d'image par apprentissage
statistiques, avec le schema d'analyse complet: VI-ME-BA-BAR.

</div>

<div class="alert alert-success">

Bravo, vous avez fini le TP. 

Déposez votre travail (avec `submit`) et téléchargez votre score (avec
`fetch_feedback`). Vous pourrez utiliser à nouveau `fetch_feedback`
pour télécharger votre score et les commentaires après correction par
votre enseignant.

</div>
