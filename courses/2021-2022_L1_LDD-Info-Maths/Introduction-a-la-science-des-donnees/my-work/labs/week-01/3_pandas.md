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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b8afb2d8f085e451cdc0940907cd57fa", "grade": false, "grade_id": "cell-d7d1bb6ef72c7615", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Tableaux de données avec Pandas

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/fe/Ailurus_fulgens_RoterPanda_LesserPanda.jpg/394px-Ailurus_fulgens_RoterPanda_LesserPanda.jpg" width="10%"> 
<!-- Photo Par User:Brunswyk — User:Brunswyk, gescannt Januar 2006, CC BY-SA 3.0, https://commons.wikimedia.org/w/index.php?curid=502603 !-->

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "825d89160e5f096da03628a187dc0c24", "grade": false, "grade_id": "cell-289da30635e3d347", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Manipulation de données

Nous allons apprendre à manipuler des données, c'est-à-dire une table avec en colonne des *attributs* et en ligne des *instances* en python.

### Bibliothèque Pandas

[Pandas](https://fr.wikipedia.org/wiki/Pandas) est une bibliothèque python qui permet de:
 
- manipuler des tableaux de données et, 
- faire des analyses statistiques 

comme on pourrait le faire avec un tableur (excel par exemple), mais **programmatiquement**, donc permettant
l'**automatisation**. 

Les tables sont des `DataFrame`: des tableaux à deux (ou plus)
dimensions, avec des labels/headers sur les lignes et les colonnes. Les données ne sont pas forcément **homogènes**: d'une colonne à l'autre, le type
des données peut changer (chaines de caractères, flottants, entiers, etc.) et, certaines
données peuvent être manquantes.

Les `Series`sont des tables à une seule dimension (des vecteurs), 
typiquement obtenues en extrayant une colonne d'un
`DataFrame`.

Dans ce cours, par **tableau**, on entendra un tableau à
deux dimensions de type `DataFrame`, tandis que par **série** on entendra
un tableau à une dimension de type `Series`.

On retrouve ces concepts de `DataFrame` et de `Series` dans les
autres bibliothèques ou systèmes d'analyse de données comme 
[`R`](https://fr.wikipedia.org/wiki/R_(langage)).

De plus, Pandas permet de traiter des données massives réparties sur de très nombreux
ordinateurs en s'appuyant sur des
bibliothèques de parallélisme comme [dask](https://dask.org/)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "91d22a1ad5ee5adc052250d7654054b2", "grade": false, "grade_id": "cell-ac223d59da82346e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Séries de données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f0fca51a53d1406c4c82c840ea5b9c82", "grade": false, "grade_id": "cell-cf5fea782b2f1061", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous devons commencer par importer la bibliothèque `pandas`; il est
traditionnel de définir un raccourci `pd`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4fa5688b4d70facd9bfc7484f3027635
  grade: false
  grade_id: cell-0aed4078f12f53e2
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import pandas as pd
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a6c72a2a44003ed081175b7c30917c9b", "grade": false, "grade_id": "cell-5c46d16ca76f2abb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Construisons une **série** de températures:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6ec4ce8a43314ed6a199350d92cd6ddc
  grade: false
  grade_id: cell-5c9928da632f2ecf
  locked: true
  schema_version: 3
  solution: false
  task: false
---
temperatures = pd.Series([8.3, 10.5, 4.4, 2.9, 5.7, 11.1], name="Température")
temperatures
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "88655d9f7380d0eee333a83bd429d615", "grade": false, "grade_id": "cell-99e3bf349cd460ac", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous noterez que la série est considérée comme une colonne et que les
indices de ses lignes sont affichés. Par défaut, ce sont les entiers
$0,1,\ldots$, mais d'autres indices sont possibles.  Comme pour les
tableaux C++ ou les listes Python, on utiliser la notation 't[i]' pour
extraire la ligne d'indice `i`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a64805c2c4659fccde0fc82a897d8401
  grade: false
  grade_id: cell-7f7949d55483e2ad
  locked: true
  schema_version: 3
  solution: false
  task: false
---
temperatures[3]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "391f1f0439f8ee2717a1d1f8257ad5d5", "grade": false, "grade_id": "cell-9b7eea649e096fa2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La taille de la série s'obtient de manière traditionnelle avec Python
avec la fonction `len`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4062361aca0fae935f3b46fd4bc44448
  grade: false
  grade_id: cell-16635abf042d87f0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
len(temperatures)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c8f8fd9247e44731ca2dee185c2afe4e", "grade": false, "grade_id": "cell-f4286aea6656bcc1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Calculons la moyenne des températures à l'aide de la **méthode**
`mean`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: bdd09cbb92c4386c6a3d6913221c451c
  grade: false
  grade_id: cell-3fa0b1f69a7b0ac8
  locked: true
  schema_version: 3
  solution: false
  task: false
---
temperatures.mean()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3e06944ecfcc455bbae80203da5f9272", "grade": false, "grade_id": "cell-b03d67a06ff3d2cb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Calculez la température maximale à l'aide de la méthode `max`:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: d14c964c50db0296e621d40262c4d4be
  grade: false
  grade_id: cell-f580f5d91a5080a9
  locked: false
  schema_version: 3
  solution: true
  task: false
---
temperatures.max()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0decc0aca849ccd3016f50905e2d4216", "grade": false, "grade_id": "cell-48500c8de7e0e649", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Calculez la température minimale:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f9a38b250c6ff05098cf34b553c01a11
  grade: false
  grade_id: cell-e70535825c143f1a
  locked: false
  schema_version: 3
  solution: true
  task: false
---
temperatures.min()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "32e5e2fa3776b67de7e86530e50f4517", "grade": false, "grade_id": "cell-30d458b1ed341ac9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Quelle est la gamme de données (le range en anglais) de température ?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 94990ad6dc4085a95b3abe268a964356
  grade: false
  grade_id: cell-08c3492e9e62cb75
  locked: false
  schema_version: 3
  solution: true
  task: false
---
temperatures.max()-temperatures.min()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "156597f75df855bab812afd2f64173f2", "grade": false, "grade_id": "cell-a47c8a9795a18646", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Tableaux de données (`DataFrame`)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a3b1be5f355d675ad4fc4bc725f65e93", "grade": false, "grade_id": "cell-cf5fea782b2f1060", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons maintenant construire un tableau contenant les données
d'acidité de l'eau de plusieurs puits.  Il aura deux colonnes: l'une
pour le nom des puits et l'autre pour la valeur du pH (l'acidité).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ba1ea83244862eabe667fc6298e11a74", "grade": false, "grade_id": "cell-37e90fd82938bf28", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous pouvons maintenant construire le tableau à partir de
la liste des noms des puits et la liste des pH des puits:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: be578df8f49f3cb186f2c73e1b887eda
  grade: false
  grade_id: cell-9f2120cfaa448833
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df = pd.DataFrame({
    "Noms" : ['P1', 'P2', 'P3', 'P4', 'P5', 'P6', 'P7', 'P8', 'P9', 'P10'],
    "pH"   : [ 7.0,  6.5,  6.8,  7.1,  8.0,  7.0,  7.1,  6.8,  7.1,  7.1 ]
})
df
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fc1ff123d1773e893ae052c5e529c5e6", "grade": false, "grade_id": "cell-cb461898259486c4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Vous remarquerez que:
- Il est traditionnel de nommer `df` (pour `DataFrame`) la variable
  contenant le tableau.  Mais il est souhaitable d'utiliser un
  meilleur nom chaque fois que naturel!
- La première colonne du tableau donne l'index des lignes. Par défaut,
  il s'agit de leur numéro, commençant à 0, en plus des colonnes "Noms" et "pH".
    
</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d4eab186da75e139255bb9bda5cd4f5b", "grade": false, "grade_id": "cell-973935ade9e7364c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Ce tableau à deux dimensions est vu comme une **collection de
colonnes**. De ce fait, `df[label]` extrait la colonne d'étiquette
`label`, sous la forme d'une **série**:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1f7489618c9f3f2cf0f630ea6151f29a
  grade: false
  grade_id: cell-c68a8e41497ee00c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['Noms']
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "743ffdd4b881fef0af5bc6051b392a40", "grade": false, "grade_id": "cell-d4f69ab34062c6a4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous pouvez ensuite accéder à chacune des valeurs du tableau en en
précisant le label de sa colonne puis l'indice de sa ligne. Voici le
nom dans la deuxième ligne (indice 1):

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f6e52923595b0228e063d31a79f5b871
  grade: false
  grade_id: cell-56c510059d2d37c1
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['Noms'][1]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6906aa6b30f936c2b0dddc76bb026731", "grade": false, "grade_id": "cell-fb0245e634928e3d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Et la valeur du pH dans la quatrième ligne (indice 3):

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1913c41de65dc8997bb48927bc84a937
  grade: false
  grade_id: cell-d8d88f42ea8aaa7c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['pH'][3]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2ef31f40d70868cc76bb12f579a1a8ca", "grade": false, "grade_id": "cell-b8534b479a0883db", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Là encore, vous remarquerez que l'accès est de la forme
`df[colonne][ligne]` alors qu'avec un tableau C++ l'accès serait de la
forme `t[ligne][colonne]`.

</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "64a518bb0b00a69b984907ffd3708155", "grade": false, "grade_id": "cell-013512c4828a5a6e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Métadonnées et statistiques

Nous utilisons maintenant `Pandas` pour extraire quelques métadonnées
et statistiques de nos données.

D'abord la taille du tableau:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a701528adb1cdfb9d23a0795d8d08f5e
  grade: false
  grade_id: cell-53766d85f4b078b5
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.shape
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0d98a17a1c39ddfb09b0028cebabda6f", "grade": false, "grade_id": "cell-b472052099a850e3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Le titre des colonnes:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0bbeef906e2aa02943d1c69e699b448d
  grade: false
  grade_id: cell-c024a3ba83138705
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.columns
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a24cb63e87391e9a012a9a3c93017cec", "grade": false, "grade_id": "cell-81da9f8beb703725", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Le nombre de lignes:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 53575c0255df980113ee02db252f25a1
  grade: false
  grade_id: cell-69e90ca896d314b6
  locked: true
  schema_version: 3
  solution: false
  task: false
---
len(df)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "13826110b4de62749933121ad80b5177", "grade": false, "grade_id": "cell-2fec6b9f7d3ccce8", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Des informations générales:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: decf10e892af3cb293ed0c9b687a64de
  grade: false
  grade_id: cell-1bbf290e1e138bb1
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.info()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "862d13a2c9820c0b0e99a473c36f76dc", "grade": false, "grade_id": "cell-940fd7c4e1dc4073", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La moyenne de chaque colonne pour laquelle cela fait du sens, c'est-à-dire seulement les colonnes contenant des valeurs numériques (ici que le pH):

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3dcfc5fd8d90e6f59e2c79fb0a1f6210
  grade: false
  grade_id: cell-2189135b63cdbae0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.mean(numeric_only = True)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "142c4edeafd34c658966fa3e55e6e079", "grade": false, "grade_id": "cell-98ca5599b03957da", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les écarts-types:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5634cf9d1dba622fecff263fa2591405
  grade: false
  grade_id: cell-466b4e74c7803a60
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.std(numeric_only = True)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f6b2bba62766332d1946bd1cbb669b72", "grade": false, "grade_id": "cell-b61e7d26e49daf10", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La mediane:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 646d80be97309da838bd906bbf230786
  grade: false
  grade_id: cell-b5e3254270f45f7b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.median(numeric_only = True)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7d93c98417a6f3bc781e38bfe6613b63", "grade": false, "grade_id": "cell-03bf669102f061d7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Le quantile 25%:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 74bd182157f7c9b0852d98ad0a9bcb1e
  grade: false
  grade_id: cell-16b89f8187062051
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.quantile(.25)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e7fa82c94d1b685c530e5558cac7b27b", "grade": false, "grade_id": "cell-717e5040fc5be129", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les valeurs min et max:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 02b9a6a9e09b68622096640a4ee33cfc
  grade: false
  grade_id: cell-cd68bd71f0f20ce3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.min()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 08bb84a5c811788f04494827d672d361
  grade: false
  grade_id: cell-cb187482aba2976d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.max()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "426f7e9d8f2617ed1b7dc2999a44a283", "grade": false, "grade_id": "cell-ab7a7f59e0e6e6a8", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Un résumé des statistiques principales:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c03e9bb1859ee80279e707f4770ed14c
  grade: false
  grade_id: cell-b6e27f8742461a16
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4e1368d963a26e2950a697c8c6c1337d", "grade": false, "grade_id": "cell-f2cc9cc176b9f7cb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

L'indice du pH max:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 03de83778af1c652fe631dbaf233d989
  grade: false
  grade_id: cell-f9811ccba3d667f9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['pH'].idxmax()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9efec57c8f4f3f3f68d171d0e3894545", "grade": false, "grade_id": "cell-9c63ed9ae777e46b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Un histogramme des pH:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 07fb5679120d4195da586f9e371effe2
  grade: false
  grade_id: cell-3f1e665bab3d82ee
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['pH'].hist(bins=20);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "12f749ab8e957afd9c7483b398da75b9", "grade": false, "grade_id": "cell-298f65fcc72140cb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Avec pyplot, il est possible de peaufiner le résultat en ajoutant des labels aux axes, etc:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b10943b013eef8dd323715c785b1be2b
  grade: false
  grade_id: cell-5fb270c5dd2151fd
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import matplotlib.pyplot as plt

df['pH'].plot(kind='hist')
plt.grid()
plt.ylabel('Counts')
plt.xlabel('pH');
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "101ee0103cbbecdfa8ceb498a420d8b5", "grade": false, "grade_id": "cell-262050f23d6072a4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Opérations de bases de données

Pandas permet de faire des opérations de bases de données (pour ceux qui
ont fait le projet Données Libres, souvenez-vous de «*select*», «*group by*»,
«*join*», etc.). Nous ne montrons ici que la sélection de lignes; vous jouerez
avec «*group by*» plus loin.

Transformons le tableau pour que l'une des colonnes
serve d'indices; ici nous nous servirons des noms:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 35a55e45ca906166fa55fe9d700f8fe9
  grade: false
  grade_id: cell-335e4c45fc766025
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df1 = df.set_index('Noms')
df1
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "20683ab4cd42e9100455d0e95eeb1dc6", "grade": false, "grade_id": "cell-bb5461f3d3ea3a36", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Il est maintenant possible d'accéder à une valeur de pH en utilisant
directement le nom comme index de ligne:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b16505516a025f267fb637cc4324dc2c
  grade: false
  grade_id: cell-3f3f94fbe3452c6e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df1['pH']['P1']
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9b892f138b30ee36e0773e92b30e0c54", "grade": false, "grade_id": "cell-e19de85935fd9b7b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Sélectionnons maintenant toutes les lignes de pH $7.1$:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ad7e196a66f1920f8e8f7f566ed6e894
  grade: false
  grade_id: cell-2a9db86282914390
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df1[df1['pH'] == 7.1]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0120f4a8f8dfde15678547bbdad65550", "grade": false, "grade_id": "cell-ffbae1669741130e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Comment cela fonctionne-t'il?

Notons `pH` la colonne de même label:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2ab741ef94c2ef0d37ad9e8fa65b3d40
  grade: false
  grade_id: cell-7667ef7acb0dac30
  locked: true
  schema_version: 3
  solution: false
  task: false
---
pH = df1['pH']
pH
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3a40b25426be2bc97feb03d1c5e1bb88", "grade": false, "grade_id": "cell-67e284df8a9fb822", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Comme avec `NumPy`, toutes les opérations sont **vectorisées** sur
tous les éléments du tableau ou de la séries. Ainsi, si l'on écrit
`pH + 1` (ce qui n'a pas de sens mathématique, les
objets étant de type très différents: `pH` est une série tandis que
`1` est un nombre), cela ajoute 1 à toutes les valeurs de la série:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6e5ca0e0be6c995da47f676ffeb5c03a
  grade: false
  grade_id: cell-f128e25349f7c6fe
  locked: true
  schema_version: 3
  solution: false
  task: false
---
pH + 1
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d998f397f4bd5e80f81746aff4689a44", "grade": false, "grade_id": "cell-5bc61a01ff98891d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

De manière similaire, si l'on écrit `pH == 7.1`, cela renvoie une
série de booléens, chacun indiquant si la valeur correspondante est
égale ou non à $7.1$:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0c765a9d17195fc7774e991447e04594
  grade: false
  grade_id: cell-c2b441d487361b19
  locked: true
  schema_version: 3
  solution: false
  task: false
---
pH == 7.1
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1aa7fc465fbcec3cf451821268db185e", "grade": false, "grade_id": "cell-43e5fd190ea6ab51", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Enfin, si l'on indexe un tableau par une série de booléen, cela
extrait les lignes pour lesquelles la série contient `True`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5bf55f20ad6a2eedaa3c1da0a90674e8
  grade: false
  grade_id: cell-d88ca9d84539658d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df1[pH == 7.1]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "22c588c7cc8a62eccdff9a310c8bd05b", "grade": false, "grade_id": "cell-4340811f1f92f40d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exercice: les notes

Vos notes d'Info 111 (anonymes!) sont dans le fichier CSV <a
href="notes_info_111.csv">notes_info_111.csv</a>. Consultez le contenu
de ce fichier: vous noterez que les valeurs sont séparées par des
virgules ',' (CSV: Comma Separated Value).

Voici comment charger ce fichier comme tableau `Pandas`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2d96ce80e36fc8decca17b09b4baea9e
  grade: false
  grade_id: cell-262586f75c92af2d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df = pd.read_csv("notes_info_111.csv", sep=",")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bd6b5b83034518807c71304a83cefeb5", "grade": false, "grade_id": "cell-5ff64a3d432eab08", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Affichez en les statistiques simples:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 29b1aa53afef8d5b460cba17d899424b
  grade: false
  grade_id: cell-54e7f4d5dc6fd16f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
df.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "093f007240d5dfccf47d508337726760", "grade": false, "grade_id": "cell-05ef5bba7ee4074b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Avec `qgrid`, vous pouvez explorer interactivement le tableau, et même
changer ses valeurs; faites quelques essais:
- de filtrage (icône <i class='fa fa-filter'></i>);
- de tri (cliquer sur le titre de la colonne par rapport à laquelle trier);
- d'édition (non, non cela ne changera pas vos notes d'Info 111 😀 ).

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0ee460538ca2ac64d89032611fa885db
  grade: false
  grade_id: cell-79a27f30dea3d0da
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import qgrid
qgrid.show_grid(df)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3c159ba741d7c1a0960a8912d4b209d6", "grade": false, "grade_id": "cell-ec49397df0d83061", "locked": true, "schema_version": 3, "solution": false, "task": false}}

</div>

## Exercice: Les prénoms

 
Dans cet exercice il s'agit d'analyser une base de données qui porte
sur les prénoms donnés à Paris entre 2004 et 2018 (souvenirs du S1?).
Ces données sont librement accessibles également sur le site
[opendata](https://opendata.paris.fr/explore/dataset/liste_des_prenoms)
de la ville de Paris. La commande shell suivante va les télécharger dans
le fichier `liste_des_prenoms.csv` s'il n'est pas déjà présent.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8b0173a47678c2f6760d8a5053e5ec84
  grade: false
  grade_id: cell-3140b1ab59a10a89
  locked: true
  schema_version: 3
  solution: false
  task: false
---
!if [ ! -f liste_des_prenoms.csv ]; then  \
    curl https://opendata.paris.fr/explore/dataset/liste_des_prenoms/download/\?format\=csv\&timezone\=Europe/Berlin\&lang\=fr\&use_labels_for_header\=true\&csv_separator\=%3B -o liste_des_prenoms.csv; \
fi
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ca5526d3b26007297a4e133f6fafd256", "grade": false, "grade_id": "cell-905982d5e4442afc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

1. Ouvrez le fichier pour consulter son contenu.

1. En vous inspirant de l'exemple ci-dessus, importez le fichier
   `liste_des_prenoms.csv` dans un tableau `prenoms`. Attention: le
   fichier utilise des ';' comme séparateurs et non des ','.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 387cc85e6f5af1c628477867a9485601
  grade: false
  grade_id: cell-2e96fb2ad3e81e19
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms = pd.read_csv("liste_des_prenoms.csv", sep=";")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9d1f7f4281a507cec0da68347234a143", "grade": false, "grade_id": "cell-289a73016c79919b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Si le test ci-dessous ne passe pas, vérifiez que vous avez bien
appelé votre tableau `prenoms`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 17a6b85e3266bbea5aa275b2b0cb8ccf
  grade: true
  grade_id: cell-67bd204a8c5ac7c3
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert isinstance(prenoms, pd.DataFrame)
assert list(prenoms.columns) == ['Nombre prénoms déclarés', 'Sexe', 'Annee', 'Prenoms','Nombre total cumule par annee']
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "45bd8290cbea8f80f3d4354b97c21c6e", "grade": false, "grade_id": "cell-289a73016c79919c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

2. Affichez les dix premières lignes du fichier.  
   **Indication:** utiliser la méthode `head`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 80f8d7fed27f4e714efbae201f0b2338
  grade: false
  grade_id: cell-28188cf6e0799b09
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms.head(10)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8d6789dbeab0c3d7b54eb7b31beb8116", "grade": false, "grade_id": "cell-a926269564abbaf2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

3. Affichez les lignes correspondant à votre prénom:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ad81bd7a451ff6aba7a692ef3ba3b3e0
  grade: false
  grade_id: cell-f185b6e7fa7ef2ce
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms[(prenoms['Prenoms'] == 'Raphael')+ (prenoms['Prenoms'] == 'Raphaël')]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "79b6ebd023fdc5535a714f1a4dfd7240", "grade": false, "grade_id": "cell-cb6b0c5d80aa1386", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Faites de même interactivement avec `qgrid`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e95e1e318a9fc404c6b7d743f6bc9a26
  grade: false
  grade_id: cell-9952e98662206372
  locked: true
  schema_version: 3
  solution: false
  task: false
---
qgrid.show_grid(prenoms)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "699c27844aa1b2e3050e082dcd061b0d", "grade": false, "grade_id": "cell-a3d7955629d5b2e5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

4. Extraire dans une variable `prenoms_femmes` les prénoms de
   femmes (avec répétitions), sous la forme d'une série.  
   **Indication:** retrouvez dans les exemples ci-dessus comment
   sélectionner des lignes et comment extraire une colonne.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 4ef75d3731abf2bcc8aa32a0a3655327
  grade: false
  grade_id: cell-4be7cb049409b338
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms_femmes=prenoms['Prenoms'][prenoms['Sexe'] == 'F']
prenoms_femmes
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "44ee52d91e1781984544b29c04959928", "grade": false, "grade_id": "cell-180965b7bdf5978e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Combien y en a-t'il?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 9a271108b206d25c1c7b21a7168d591e
  grade: false
  grade_id: cell-9b5843d34bb6a6f0
  locked: false
  schema_version: 3
  solution: true
  task: false
---
len(prenoms_femmes)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 596b38cfdca5d1f5433fd44cdf88213b
  grade: true
  grade_id: cell-6f036c8cc1d8e0e3
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
# Vérifie que prenoms_femmes est bien une série
assert isinstance(prenoms_femmes, pd.Series)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d4c08cf4be8734bae472a70edc212686
  grade: true
  grade_id: cell-6f036c8cc1d8e0e4
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
# Vérifie le premier prénom alphabetiquement
assert prenoms_femmes.min() == 'Aaliyah'
# Vérifie le nombre de prénoms après suppression des répétitions
assert len(set(prenoms_femmes)) == 1410
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "93319d58920d12c4cf290a6005a735fa", "grade": false, "grade_id": "cell-6240b3e60e97a698", "locked": true, "schema_version": 3, "solution": false, "task": false}}

5. Procéder de même pour les prénoms d'hommes:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 8f947cea7ea0a20dc3aabcff257fe9a0
  grade: false
  grade_id: cell-dc545198068cf41e
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms_hommes=prenoms['Prenoms'][prenoms['Sexe'] == 'M']
prenoms_hommes
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 35ffb5355b37ff98720eaa93d3379bfe
  grade: false
  grade_id: cell-690ab8393a87e5c7
  locked: false
  schema_version: 3
  solution: true
  task: false
---
len(prenoms_hommes)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "49353f594432705e88a776efab4c3b24", "grade": false, "grade_id": "cell-b1f9b68e24279320", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Une petite vérification:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b3d81854d1ace197a5db3414a6eb4479
  grade: true
  grade_id: cell-efac9b8b791a78ce
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
assert len(prenoms_hommes) + len(prenoms_femmes) == len(prenoms)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7c64bf12178e2c65e84c87b12ba7bfaa", "grade": false, "grade_id": "cell-d1f89b8f8a18e6ba", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice**
*Objectif*: savoir rechercher dans la documentation pandas: https://pandas.pydata.org/docs/user_guide/.

Transformez les Prenoms en majuscule dans la table `prenoms`. Affectez le résultat à la variable `prenoms_maj`

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e2482558042eac3cb8c7b0e7a7b95bfc
  grade: false
  grade_id: cell-18c6986ae5a2f1e4
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenoms_maj = prenoms.copy()
prenoms_maj['Prenoms'] = prenoms_maj['Prenoms'].str.upper()
prenoms_maj
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ec676d6e160aee6455dcbd82be97f0af", "grade": false, "grade_id": "cell-2e4703603e531e08", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice $\clubsuit$**

Quel est le prénom le plus déclaré, en cumulé sur toutes les années?
Affectez le à la variable `prenom`.

**Indication:** consulter le premier exemple à la fin de la
documentation de la méthode `groupby` pour calculer les nombres
cumulés par prénom (avec `sum`). Puis utilisez `qgrid` pour visualiser
le résultat et le trier, ou bien utilisez `sort_values`, ou `idx_max`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ca176272545b8dafbd4b82263e8527c0
  grade: false
  grade_id: cell-dd455b550f4a8e23
  locked: false
  schema_version: 3
  solution: true
  task: false
---
prenom = prenoms.groupby(by=['Prenoms']).sum()['Nombre prénoms déclarés'].idxmax()
```

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: bbd824646fd1cb38048588b35ed5cdfb
  grade: false
  grade_id: cell-ce14db82bf40fa73
  locked: false
  schema_version: 3
  solution: true
  task: false
---
qgrid.show_grid(prenoms.groupby(by=['Prenoms']).sum()['Nombre prénoms déclarés'])
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7cc3a9170260596d1b6e83a7d493993d", "grade": false, "grade_id": "cell-c4b5fe76ae7dfdb2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Ce test vérifie que vous avez trouvé la bonne réponse; sans vous la donner;
la magie des fonctions de hachage :-)

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8fc9aa627689cfdf33b29bdc297dc41b
  grade: true
  grade_id: cell-589694408684333e
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
import hashlib
assert hashlib.md5(prenom.encode("utf-8")).hexdigest() == 'b70e2a0d855b4dc7b1ea34a8a9d10305'
```

Validez votre feuille tapant dans le terminal `intro-science-donnees validate 3_pandas.md`.

**Exercice**
Passez à l'[étude statistique](4_etude_statistique.md).

```{code-cell} ipython3

```
