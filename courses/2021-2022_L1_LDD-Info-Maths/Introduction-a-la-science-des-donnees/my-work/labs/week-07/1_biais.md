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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "680b70ea84a4041c79780ea53b5abe2a", "grade": false, "grade_id": "cell-cbf46e872f135da1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Les biais dans les données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "766826515de0a5629c0e4adccada9e0f", "grade": false, "grade_id": "cell-17f5a484646f4ce2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans cette fiche, vous allez essayer de trouver des biais dans le jeu
de données sur les pommes et les bananes proposé dans la fiche
précédente. Pour cela, nous allons analyser les
[métadonnées](https://fr.wikipedia.org/wiki/M%C3%A9tadonn%C3%A9e). On
les appelle métadonnées car ce sont des données à propos d'autres
données. Dans notre cas, elles contiennent des informations sur la
manière dont les images ont été collectés: quand, où, dans quelles
conditions d'éclairages, etc.

La question qui se pose est: peut-on prédire les classes "pomme" ou
"banane" sur la seule base de ces métadonnées? Si oui, cela mettrait
en exergue un biais, ou un [facteur de
confusion](https://en.wikipedia.org/wiki/Confounding), dans la manière
dont les données ont été collectées.

Pour votre projet, nous vous encourageaons à:
- Collecter des métadonnées. Pour les images prises avec un téléphone
  ou appareil photo, elles sont automatiquement enregistrées dans le
  fichier de l'image lui même.
- Utiliser cette feuille sur vos propres données pour identifier les
  facteurs de biais potentiels dans la manière dont ont été collectés
  les données.

Les stratégies pour détecter et corriger les biais comprennent la
*stratification des données* et l'*inclusion des méta-données* dans
l'ensemble des variables prédictives. Consultez le [cours](CM7.md)
pour plus de détails.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9fc39a1146f75d01b615fb7484b732cb
  grade: false
  grade_id: cell-d6806c408e81245d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import os, re
from glob import glob as ls
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
%matplotlib inline
import pandas as pd
import seaborn as sns; sns.set()
import qgrid
from PIL import Image
%load_ext autoreload
%autoreload 2
import warnings
warnings.filterwarnings("ignore")
from sys import path
from intro_science_donnees import *
from intro_science_donnees import data

from utilities import *
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b14eafff121e9491909ad74790ac1f66", "grade": false, "grade_id": "cell-2a93df23f66ce17a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 1: Charger les méta-données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c62fe02d1ccf6c0f63909e2dc860b6d0", "grade": false, "grade_id": "cell-dd9a44f8e7714d7a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les métadonnées ont été extraites des images et collectées dans un
table stocké dans un fichier CSV (*Comma Separated Value*) qui peut
être chargé comme une table Pandas (*DataFrame*):

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b991ef4f208cc10fa5d9e6d576b7a333
  grade: false
  grade_id: cell-7ba8acf4ad70adf3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
dataset_dir = os.path.join(data.dir, 'ApplesAndBananas')
metadata = pd.read_csv(os.path.join(dataset_dir, 'metadata.csv'))
qgrid.show_grid(metadata)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2d2a59e5f1b297814aaade683dda60eb", "grade": false, "grade_id": "cell-34d81c466ee72a78", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les métadonnées que nous avons comprennent des informations sur notre
ensemble de photos telles que la date et l'heure de la prise de vue,
les coordonnées GPS, la vitesse de l'obturateur, le temps de
numérisation, le temps d'exposition ou bien la valeur de
luminosité. Elles sont complétées par une étiquette (*label*)
spécifiant le type de fruit(s) présent sur la photos.

En classe, nous avons analysé uniquement les images ne contenant qu'un
seul fruit (une seule pomme ou une seule banane). Ici, les images
peuvent contenir plusieurs fruits, voire aucun. Leur nombre est
indiqué dans la colonne `Count`.

**Exercice**: Sélectionner deux ensembles de données stockés dans les
variable `apple_subset` et `banana_subset` contenant uniquement des
pommes respectivement des bananes n'apparaissant qu'une seule fois sur
l'image.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7f88305519c7446bb5865cd332e55e65", "grade": false, "grade_id": "cell-71238e31523da62b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Rappel: la variable `metadata` est du type
`pandas.DataFrame`. Rappelez-vous qu'on peut appliquer des filtres sur
ses valeurs en utilisant des tableaux de booléens (indifféremment de
type `list`, `numpy.array` ou `pandas.Series`). Par exemple,
`metadata["Color"] == "COLOR-NA"` renverra une série de type
`pandas.Series` de booléens avec des `True` quand la condition est
vérifiée (c'est-à-dire que les fruits photographiés n'ont pas de
couleur identifiée) ou `False` sinon. Ensuite,
`metadata[metadata["Color"] == "COLOR-NA"]` renverra une table ne
contenant que les lignes dont la couleur du fruit n'est pas
identifié. Pour faire le lien avec le cours de **Programmation
Modulaire**, vous pouvez voir cela comme une surcharge de l'opérateur
`==` par la classe `pandas.DataFrame`.

</div>

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: c3cac608672e38f4e4a8b590bb00061f
  grade: false
  grade_id: cell-48c0fefe9a8a5665
  locked: false
  schema_version: 3
  solution: true
  task: false
---
apple_subset = metadata[metadata['Fruit'] == "APPLE"][metadata['Count'] == "1-ONE"]
banana_subset = metadata[metadata['Fruit'] == "BANANA"][metadata['Count'] == "1-ONE"]
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "445ad1295e115096bc44db5235935b02", "grade": false, "grade_id": "cell-b267dc2caa5149c0", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice**: Les classes sont elles équilibrées dans le jeu de donnée
(nombre d'échantillon pour chaque type de fruit)?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ad0cda5c73778b7ccc050d79ec275d93
  grade: false
  grade_id: cell-242b61ec3338bd2f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
apple_subset.shape[0]-banana_subset.shape[0]
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4502674b45084418652e0b4d757bcfce", "grade": true, "grade_id": "cell-120771a4518aef2a", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

Pas vraiment, il y a moitié moins de banane que de pommes (approximativement)

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: adb77776aab2cf0922ed9c1c454c98c7
  grade: false
  grade_id: cell-0c71d0d5595391eb
  locked: true
  schema_version: 3
  solution: false
  task: false
---
apple_subset
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5a2e532dc2ee29ff28c3a6400fb550cd", "grade": false, "grade_id": "cell-4e443d88ac18301b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons nous limiter au sous-ensemble de données où il n'y a qu'un
seul fruit par image. On peut alors
supprimer la colonne ``Count`` puisqu'on ne s'intéresse plus qu'à des
images ne contenant qu'un seul fruit à la fois.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ba04f4a697ff59b2e9ccc89f72fc559c
  grade: false
  grade_id: cell-66445e967825c078
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata = pd.concat([apple_subset, banana_subset])
metadata = metadata.drop(columns=['Count'])
metadata.shape
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5cc38df74aa31d7aae1fcc20b0714c56", "grade": false, "grade_id": "cell-17184c560ee1095b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La méthode `describe` de Pandas vous permet de visualiser les
statistiques sur des variables **numériques** uniquement. Cependant
notre jeu de données contient de nombreuses variables
**catégorielles** (encodées sous forme de chaînes de
caractères). L'une des premières chose à faire sera donc de convertir
les variables catégorielles en variables numériques.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a35cf03f6c4c9bc08b537b7b0b41a1ac
  grade: false
  grade_id: cell-50ff2ea5ceb3f24f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "51e235f97ba99c6d9736f7a9395a735c", "grade": false, "grade_id": "cell-4cef598d5e34bc40", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 2: Prétraitement des métadonnées

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "54339deea6e7261093ce46a73f34763a", "grade": false, "grade_id": "cell-aa4cd2bc9dbf7267", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Gestion des valeurs manquantes

Souvent les jeux de données comportent des valeurs manquantes,
encodées comme `NaN` (Not a Number). Le nôtre ne fait pas exception.
C'est un problème pour certains algorithmes d'apprentissage
automatique ou de méthodes statistiques, aussi faut-il gérer ces
valeurs manquantes.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c958665b50c21ea6d33caa1af44c292e", "grade": false, "grade_id": "cell-b1e9bda1d199a785", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Rappel : en Semaine 2 (jeu de données du Titanic et des pays
européens), nous avions vu et discuté les stratégies suivantes :
-   Si très peu d'échantillons sont concernés par rapport à la taille
    de l'ensemble du jeu de donnée, vous pouvez simplement les
    supprimer complètement.
-   Sinon, vous pouvez aussi remplacer les valeurs manquantes par une
    valeur fixe (moyenne, médiane, valeur la plus fréquente
    etc.). Votre choix devra être justifié.

Utiliser une valeur fixe peut mener à des échantillons
incohérents. Par exemple, si vous avez des données physiologiques
d'individus, remplacer les valeurs manquantes de tailles par la
moyenne de toutes les tailles peut mener à des incohérences: un enfant
de quelques mois pourrait se retrouver avec une taille de plus d'un
mètre cinquante. Dans ce cas, il est possible d'utiliser un
classificateur tel qu'un arbre de décision ou un kNN pour déduire la
valeur approprié en fonction du reste des données (les autres
colonnes). Nous n'utiliserons pas cette approche dans ce TP.

</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b627166f97775eb2ef6408fb84786619", "grade": false, "grade_id": "cell-ad71940a62fabbe7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Lister ci-dessous les lignes comportant des valeurs manquantes:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6fe0b17cd2767c4886f9ac7f17b3481f
  grade: false
  grade_id: cell-dd8f936622ea0c91
  locked: true
  schema_version: 3
  solution: false
  task: false
---
na_val = check_na(metadata)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c40e4aca674bf0fd4beb2b9a1df50443", "grade": false, "grade_id": "cell-5ff2300723b6d9f5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice**: Traitez les données manquantes en supprimant les
échantillons concernés. Justifier pourquoi ce choix de traitement est
raisonnable.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 0a1c3a7e499d0bd618658248b58dfdcd
  grade: false
  grade_id: cell-b3fd782e99a3b868
  locked: false
  schema_version: 3
  solution: true
  task: false
---
metadata.dropna(axis=0, inplace=True)
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "457795e81377921890bf9c24109d5be6", "grade": true, "grade_id": "cell-0d9d8be3a42735d2", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

On voit que il n'y a qu'une seule ligne contenant des NaN, cela n'impacte donc pas notre jeu de données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f8e7b1fd3577f60b71a76e4eef319b2c", "grade": false, "grade_id": "cell-024c2b1e05c58f69", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Conversion des variables catégorielles en variables numériques

L'une de vos tâches consistera d'abord à convertir les variables
**catégorielles** en variables **numériques**.

**Exercice**: en utilisant la méthode `unique` d'une série
`pandas.Series`, afficher le nom et le nombre de valeurs uniques de
chaque colonne de `metadata`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 64eafe1396257c3d5844812a485f360e
  grade: false
  grade_id: cell-07ed5ed51deb175a
  locked: false
  schema_version: 3
  solution: true
  task: false
---
for col in metadata:
    print(metadata[col].unique())
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8bb9bd0173406c849f3779872c14cb42", "grade": false, "grade_id": "cell-93776b525bca9fb9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On peut également afficher les types de chaque attributs dans notre
jeu de données.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 7e4b1b923eb793ceeb6e091ce5c93ca8
  grade: false
  grade_id: cell-f77d36994e7fadde
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata.convert_dtypes().dtypes
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1ded4373e7e537972c839d6ae4dd232a", "grade": false, "grade_id": "cell-836c64f8ced6beb6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

`Subset`, `Fruit` et `Color` sont de véritables variables
catégorielles; les autres sont des variables qui peuvent être
naturellement transformées en variables numériques.

Dans la section suivante, nous vous montrons un certain nombre
d'astuces pour traiter ces dernières.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5ed6316ead32f21b07a8ac8c5a9e8f5d", "grade": false, "grade_id": "cell-e67772dc99259e63", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Conversion en valeurs numériques

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0b45c9a192a31fc5f8a79c153eb9b488", "grade": false, "grade_id": "cell-67da460cec92cfdc", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### File

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "58e6876d5ebe6c473edf75244303b96c", "grade": false, "grade_id": "cell-b4e30af7bff6c48e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Le nom des fichiers encode le numéro des images. Il est donc aisé de
transformer la variable `file` en variable numérique en extrayant et
convertissant ce numéro:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9417fff522e60b8f3c8c853d92257995
  grade: false
  grade_id: cell-a65c1bb721bc6c34
  locked: true
  schema_version: 3
  solution: false
  task: false
---
def get_file_num(s):
    start = s.find("_")+1
    end = s.find(".png")
    return int(s[start:end])

metadata['File'] = metadata['File'].apply(get_file_num)

metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4876e3b37f2a440c7bd0e447a3f29822", "grade": false, "grade_id": "cell-8d9cb56a97fa12d4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### DateTime

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6f7c650d25c0cc6a001ff1af464de772", "grade": false, "grade_id": "cell-852a4283d85c0dfd", "locked": true, "schema_version": 3, "solution": false, "task": false}}

De même, la date peut-être encodé comme une valeur numérique; par
convention, une telle date est représentée en interne par le nombre de
secondes depuis le 1er janvier 1970. On peut la convertir de la
manière suivante:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: fc412646cabdb686f99ec79ec4e05a32
  grade: false
  grade_id: cell-44d325e68cef0923
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata['DateTime'] = pd.to_datetime(metadata['DateTime']).apply(lambda x: x.value)
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8d86947136dc4b212e11a289a50fa266", "grade": false, "grade_id": "cell-88ee5fb119c7424f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Complément: Ci-dessus, nous avons utilisé une fonction ***anonyme***
`lambda x: x.value`: c'est une fonction d’une seule ligne déclarée
sans nom. Elle peut avoir un avoir un nombre quelconque d’arguments
(ici `x`), mais ne peut avoir qu’une seule expression (ici:
`x.value`). C'est un outil pratique lorsque l'on un besoin ponctuel
d'une petite fonction triviale. Le nom `lambda` vient de la théorie du
$\lambda$-calcul qui est un des fondements de la programmation
fonctionnelle et de la théorie de la calculabilité.

</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c63e2bb3428500d21bfa46a8f8327f30", "grade": false, "grade_id": "cell-9aea97f2f13bb48c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### GPSAltitude, GPSLatitude and GPSLongitude

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4e8c175c8fb20eafa911ba07f465bd4f", "grade": false, "grade_id": "cell-7c9a1b5422f3cd54", "locked": true, "schema_version": 3, "solution": false, "task": false}}

GPSAltitude est déjà numérique. Pour GPSLatitude et GPSLongitude, nous
avons utilisons des routines provenant de 
[ce forum](https://stackoverflow.com/questions/21298772/how-to-convert-latitude-longitude-to-decimal-in-python)
et de
[celui-ci](https://stackoverflow.com/questions/1059559/split-strings-into-words-with-multiple-word-boundary-delimiters).
qui convertissent les angles exprimés en degrés entiers et secondes
d'arc en degrés décimaux:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c664d8fd33649d9afed77b24f708237a
  grade: false
  grade_id: cell-54f958ee90a97ce9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
def convert(tude):
    multiplier = 1 if tude[-1] in ['N', 'E'] else -1
    return multiplier * sum(float(x) / 60 ** n for n, x in enumerate(tude[:-1].replace(';','.').split('.')))

metadata['GPSLatitude'] = metadata['GPSLatitude'].apply(convert)
metadata['GPSLongitude'] = metadata['GPSLongitude'].apply(convert)
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b37e100c980d20d0817bce9c36b26632", "grade": false, "grade_id": "cell-35b066ef4099b589", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### GPSImgDirection and GPSDestBearing

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f7867ce88d8869a1a73388fa6774b415", "grade": false, "grade_id": "cell-5c6c7254c5a7a5bb", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous modifions les valeurs de PSImgDirection et GPSDestBearing en nous
appuyons sur les explications de
[ce forum de discussion](https://gis.stackexchange.com/questions/356582/how-to-interpret-gpsdestbearing-and-gpsimgdirection) :

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0324d3823e5ec49f25ae8a9e86fdfc93
  grade: false
  grade_id: cell-d566e2c71f842c4c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
import math
def convert(dir):
    f, s = dir.split('/')
    return 180*(float(f)/float(s))/math.pi
    
metadata['GPSImgDirection'] = metadata['GPSImgDirection'].apply(convert)
#metadata['GPSDestBearing'] = metadata['GPSDestBearing'].apply(convert)
metadata.head()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e765b36b8363fac6db0c3722d3c09e27
  grade: false
  grade_id: cell-d1668d83d331c8a0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata['GPSDestBearing'] = metadata['GPSDestBearing'].apply(convert)
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "aa599dd66fc169dc95eb45105dc1dfd6", "grade": false, "grade_id": "cell-eb037455c07c702c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### ShutterSpeedValue

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5ede3345066aec3ce056e3d77b42c66f", "grade": false, "grade_id": "cell-c35ec26fc393597a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

De même, nous convertisons les valeurs de ShutterSpeedValue, selon
[ce forum](https://photo.stackexchange.com/questions/108817/shutter-speed-from-the-exif-shutterspeedvalue).
Cela correpond à la vitesse de fermeture de l'obturateur dans un
appareil photo.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 75619d05ab61f446bcfd0c580108da6a
  grade: false
  grade_id: cell-a1e469fed6329127
  locked: true
  schema_version: 3
  solution: false
  task: false
---
def convert(spval):
    f, s = spval.split('/')
    return 2**(-float(f)/float(s))

metadata['ShutterSpeedValue'] = metadata['ShutterSpeedValue'].apply(convert)
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ed31b9a61035d25004cd4be58c1d4188", "grade": false, "grade_id": "cell-7d1e10d408119668", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### SubsecTimeDigitized, ExposureTime and BrightnessValue

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f4e01c14277961928d5c7da7c2993a11", "grade": false, "grade_id": "cell-963bf3fdea246bd9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

SubsecTimeDigitized est déjà numérique: elle mesure le temps de
numérisation de l'image prise.

Pour ExposureTime et BrightnessValue (temps d'exposition et
luminosité), sont données par des nombres rationnels que nous
convertissons en nombres flottants:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d18bf8772ba1c3b8f30ae106e8f73690
  grade: false
  grade_id: cell-89f56fd720120469
  locked: true
  schema_version: 3
  solution: false
  task: false
---
def convert(rat):
    f, s = rat.split('/')
    return float(f)/float(s)

metadata['ExposureTime'] = metadata['ExposureTime'].apply(convert)
metadata['BrightnessValue'] = metadata['BrightnessValue'].apply(convert)

metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "77660e2a28b89343fd185166e0f3bb67", "grade": false, "grade_id": "cell-3784fa16055b9e9b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Conversion des valeurs catégorielle en numérique

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "00cf9b70ce7109f639bed0a3112b3782", "grade": false, "grade_id": "cell-6e625c246a6b1f4a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

#### Fruit

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 76b6a3451311a6c10dcbb794a01f063d
  grade: false
  grade_id: cell-eb3910db685762ee
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata['Fruit'].unique()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "16aa38a7e9fe5eaa0fc2d1f78c081b5d", "grade": false, "grade_id": "cell-3aa3c29415e08106", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nos catégories (ou classes) que l'on souhaite prédire ne sont qu'au
nombre de deux.

**Exercice**: En utilisant une liste par compréhension et le
dictionnaire ci-dessous, remplacer l'attribut `Fruit` (chaînes de
caractères) par des valeur binaire entières (-1 ou 1 selon la
catégorie).

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 8f62030d722711a39d6bf9038c52e369
  grade: false
  grade_id: cell-76b9c3ab77877813
  locked: false
  schema_version: 3
  solution: true
  task: false
---
labels = metadata['Fruit']
association = {'APPLE':1, 'BANANA':-1}
metadata['Fruit'] = (metadata['Fruit'] == 'APPLE')*2-1
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ed5e1c82c0c7c9084cb1522922bac370", "grade": false, "grade_id": "cell-0757f02f54ad8e0d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Rappel: En Python, un dictionnaire (de type `dict`) est composé de
clés et de valeurs. Ici les clés sont 'APPLE' et 'BANANA' tandis que
les valeurs associées aux clés sont `1` et `-1`. On peut accéder à la
valeur d'une clé de la manière suivante `association['APPLE']`.
</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6e4502e7803db69b06e2df64a30349cd", "grade": false, "grade_id": "cell-ebde1f2d94f673c4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

<div class="alert alert-info">

Rappel: Une liste par compréhension s'écrit comme:

    `[f(<valeur>) for <valeur> in <itérateur> if <expression booléenne>]`. 

Avec `f` une fonction quelconque, `<valeur>` la valeur extraite d'un
`<itérateur>` (liste, série pandas ou autre). Le résultat de
l'expression `f(<valeur>)` est stockée dans la liste seulement si
l'`<expression booléenne>` est vraie.

</div>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "897b31232fb13ae75196f1b4b0b2d971", "grade": false, "grade_id": "cell-2961aefe4ecfa968", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Subset et Color

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d429d068540a564308b9aab65c1cf83e", "grade": false, "grade_id": "cell-01f7bc4d9c390a8c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour les deux autres, examinons leurs histogrammes:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4b0dc91fa3ae07f8bae62dd1319074a6
  grade: false
  grade_id: cell-ff0366e33a6f55f9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata['Subset'].hist();
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2a1e1c8bb13030a622afb228a1238b5b", "grade": false, "grade_id": "cell-debd5c119e4573d9", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Il semble qu'il y ait trois types de pommes et deux types de bananes.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: ce184685f83fa4fe72573338a2f5e8a8
  grade: false
  grade_id: cell-7aed5b14d60d047e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata['Color'].hist()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0191146751a2cd45cc2e36eea58014eb", "grade": false, "grade_id": "cell-7a519c954d83eed6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

De même, il y a trois couleurs de fruits et une catégorie de couleur
non identifiée.

On peut utiliser la fonction `pandas.get_dummies` qui va
automatiquement convertir tous les attributs multi-classe en plusieurs
attributs binaires. Par exemple, on a deux attributs contenant
respectivement 5 et 4 catégories. En appliquant cette fonction, on
obtient 4+5=9 attributs binaires (contenant des 0 ou des 1).

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b34562fe68033afb356b38c88b885ce6
  grade: false
  grade_id: cell-4080a1659e93c9f0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata = pd.get_dummies(metadata)
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6e50f033e0db308185d1b61315b8c81b", "grade": false, "grade_id": "cell-d977108762e74c40", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour plus de clarté, mettons la colonne "Fruit" en dernier car il
s'agit de notre valeur cible.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8a151454ade6c67e820f665ae19375dd
  grade: false
  grade_id: cell-9de60843b73e20a1
  locked: true
  schema_version: 3
  solution: false
  task: false
---
cols = metadata.columns.tolist()
cols.remove("Fruit")
cols.append("Fruit")
metadata=metadata[cols]
metadata.head()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "53324ff93844f6d16bd811a940e01c49", "grade": false, "grade_id": "cell-ff64d84e3d00f5ce", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Nous avons terminé le pré-traitement des méta-données!** La
description statistique de nos données peut enfin être appliquée.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f478453da58d1ba309ac8a9ad21fe8d3
  grade: false
  grade_id: cell-3239e4bab494d137
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ab4d8a895e1028a176e97578bba800dc", "grade": false, "grade_id": "cell-359e4250a351d64b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 3 : Visualisation des données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "056fd8606158aafdbbda0cb3d01c07fe", "grade": false, "grade_id": "cell-cbd0734e5f9242e4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On s'intéresse à présent à la visualisation de nos données.


**Exercice :**
- Visualiser la table `metadata` à l'aide d'une carte de chaleur:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 393052aa1fad898716d69da43013a3b9
  grade: false
  grade_id: cell-f4fa463455bf4d67
  locked: false
  schema_version: 3
  solution: true
  task: false
---
metadata.style.background_gradient(cmap='coolwarm')
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "52552c4d3e8b4ea274bc225ebb684da5", "grade": false, "grade_id": "cell-91b47429f518074e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Pour une visualisation plus compacte, utilisez la fonction `sns.heatmap` de la bibliothèque Seaborn.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: fa62f99ccf7babc68721a9308ed8f498
  grade: false
  grade_id: cell-c745e118046bc5d5
  locked: false
  schema_version: 3
  solution: true
  task: false
---
sns.heatmap(metadata)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1e69fcf45f354dbf3154a90ba467e9fe", "grade": false, "grade_id": "cell-c05bf73799ef514b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Vous avez dû être décus par le résultat; c'est que `headmap` fait l'hypothèse que la table est normalisée! Normalisez la table et stockez le résultat dans `metadata_scaled` (comme d'habitude, à l'exception des colonnes de fruits). Cela nous resservira par la suite.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 31fcfcd23fe06c6c318a4d5556d37272
  grade: false
  grade_id: cell-e0d99b337f503674
  locked: false
  schema_version: 3
  solution: true
  task: false
---
metadata_scaled = (metadata-metadata.mean())/np.std(metadata)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2629d8365f75053d318e3e9e0c52c106
  grade: false
  grade_id: cell-44e586750e9ec064
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata_scaled.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e17a3784779847229085628c286ec7cd", "grade": false, "grade_id": "cell-4f2d090a12ed6837", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- Essayez à nouveau la fonction `sns.heatmap`:

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a97cf63f1437401ba998327c21b9729f
  grade: false
  grade_id: cell-30e82ecbbb19a15f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
sns.heatmap(metadata_scaled)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "15580493985f582d12462088eeadde36", "grade": false, "grade_id": "cell-792e83f0bbe3e93e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- À présent, visualisezla carte thermique de la matrice de corrélation de vos données.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 65577d8445d94fddf4a3fcb18830eacc
  grade: false
  grade_id: cell-693c7d788101da48
  locked: false
  schema_version: 3
  solution: true
  task: false
---
metadata.corr().style.background_gradient(cmap='coolwarm')
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "31e992b91211283851d8b087cfe83481", "grade": false, "grade_id": "cell-4871f67079ac971e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Certains attributs des métadonnées sont très fortement (voir parfaitement) corrélés ou anti-corrélés. Identifier les attributs corrélés (sans considérer l'attribut `Fruit` pour le moment) et expliquer brièvement les raisons de leurs corrélations.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bf9892fa5e095f186a1acdc6bdb4c6cf", "grade": true, "grade_id": "cell-eaed3e295e0327dd", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

La date et le nom de fichiers sont très corrélés

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6e44bf3c1945562b9127cd07fb61df10", "grade": false, "grade_id": "cell-4373ab91507e0847", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La fonction ci-dessous affiche une carte thermique ***clusterisée***.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4c887315167f83489b088650015ac2d1
  grade: false
  grade_id: cell-ec3360061ce92917
  locked: true
  schema_version: 3
  solution: false
  task: false
---
sns.clustermap(metadata.corr(), cmap="coolwarm");
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2c0a88f9b3077f2ad2d553d01cacb437", "grade": false, "grade_id": "cell-a1c1ad52661dd2d3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Pouvez-vous expliquer la signification de ce graphique?

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0650633dc173f22a6ea2440cf3587898", "grade": true, "grade_id": "cell-8691a43384423c24", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

Il semble que les variables reliées entre elles par des trait soit corrélée d'une certaine façon

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1d51991e5c1cabc3de43e8e1e9bd4d84", "grade": false, "grade_id": "cell-ed1ca3c32db1249a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

La valeur absolue de la matrice de corrélation est également informative.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6ba73483b75441bd7a76358579a23459
  grade: false
  grade_id: cell-31aff59ac6239886
  locked: true
  schema_version: 3
  solution: false
  task: false
---
sns.clustermap(np.abs(metadata.corr()), cmap="coolwarm");
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "54e8cfd0d3220a4f252412f604d628c1", "grade": false, "grade_id": "cell-4a42d4773c17d200", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Interprétation

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f6ab7cc30207fabf9ae4953e1352706d", "grade": false, "grade_id": "cell-d995a8b88e913bc0", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Notre rôle à présent est d'interpréter les différentes corrélations entre les attributs listés ci-dessous. Ces corrélations sont-elles toutes légitimes? Lesquelles sont des biais?

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8773d760affefb46c41964476f1699c1
  grade: false
  grade_id: cell-16e9451390a182f0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
cols
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "15e3eb0dd30c1291d288992a5ef10e56", "grade": false, "grade_id": "cell-c8be5b13e6b9b7d7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Rapporter ci-dessous vos observations et interprétations des corrélations:

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "865d85ad83e19433f744f0968699795a", "grade": true, "grade_id": "cell-df0c55c90d6cc13c", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

Comme dit plus haut il me semble, le nom de fichier est très corrélé à la date : cela peut sexpliquer simplement, par exemple le personne qui prend des photos tel ou tel jour a un appareil qui stock les noms differement. Cependant cela ne pose pas probleme car il ne permet pas à lui seul d'identifier les fruits.

Cependant, le fait qu'il y ait une correlation, meme legere entre le nom de fichier et le fruit pour illustrer un biais important : differentes personnes ont donc pris les photos, mais pas autant de bananes que de pommes, il s'agit dun biais

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bca62c36f5e03b7298af008511a6d4fe", "grade": false, "grade_id": "cell-82971df17c17b52d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Diagramme de dispersion

Pour obtenir des résultats intéressants avec des diagrammes de dispersion, nous devons simplifier la matrice de métadonnées.

**Exercice**:
* Garder Num et supprimer DateTime (qui en principe devrait apporter la même information, mais semble bidon).
* Garder les coordonnées GPS.
* Ne garder que GPSImgDirection et supprimer le redondant GPSDestBearing.
* Conserver uniquement BrightnessValue et supprimer les redondants ShutterSpeedValue et ExposureTime.
* Conservez SubsecTimeDigitized/.
* Ne conservez que Fruit comme étiquette et supprimez les autres variables catégorielles.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: b3b11a86d93aba14b471f68d2cbfa8eb
  grade: false
  grade_id: cell-96624b47fe0b3a2d
  locked: false
  schema_version: 3
  solution: true
  task: false
---
metadata_subset = metadata[['Num', 'GPSAltitude', 'GPSLatitude', 'GPSLongitude',
                            'GPSImgDirection', 'BrightnessValue', 'SubsecTimeDigitized', 'Fruit']]
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1ffbb50100e663a771c59212c30338b1
  grade: false
  grade_id: cell-40284995c378d46d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
metadata_subset.head()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0dcb535bb32a8d1a497f3eb15c8c5121
  grade: false
  grade_id: cell-d37ba58e028aeed3
  locked: true
  schema_version: 3
  solution: false
  task: false
---
sns.pairplot(metadata_subset, hue="Fruit", diag_kind="hist", palette='Set2')
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d3b148cae7702f9121ccb03e615721a8", "grade": false, "grade_id": "cell-5f84c56043289545", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Des tendances intéressantes peuvent être observées : bien que certaines variables ne soient pas très corrélées, il existe des dépendances notables. Par exemple 
* Seules les pommes sont trouvées à basse altitude : cela peut être un biais.
* Les bananes ont une valeur de luminosité plus élevée que les pommes.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "eb2d8cc551cdf0b8f0124ca4077b0d9b", "grade": false, "grade_id": "cell-690447fa3b6b03be", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 4: Prédire les catégories

Nous essayons maintenant de prédire la valeur cible (pomme ou banane) à partir des métadonnées en utilisant le classificateur à 3 plus proches voisins.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3c38778d36d921614ecd3fdaf0c79658
  grade: false
  grade_id: cell-a3a77dcccac922c8
  locked: true
  schema_version: 3
  solution: false
  task: false
---
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import balanced_accuracy_score as sklearn_metric
sklearn_model = KNeighborsClassifier(n_neighbors=3)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e8447b40b45c8b65bd9907a616629818
  grade: false
  grade_id: cell-7215903a2603f96a
  locked: true
  schema_version: 3
  solution: false
  task: false
---
p_tr, s_tr, p_te, s_te = df_cross_validate(metadata_subset, sklearn_model, sklearn_metric, n=10, verbose=False)
metric_name = sklearn_metric.__name__.upper()
print("AVERAGE TRAINING {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_tr, s_tr))
print("AVERAGE TEST {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_te, s_te))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "744d0cbf7501701adaf76a667abd28e1", "grade": false, "grade_id": "cell-77a5ea8f5b76f4d3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

De façon surprenante, nous prédisons la séparation avec une précision de 82 % sur les données de test. Quelles variables de métadonnées révèlent un biais? Lesquelles devraient être utilisées pour "ajuster" les résultats?

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8f9bb954697fdf3faba7c1c28714bd05", "grade": true, "grade_id": "cell-1474e837efd3e174", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

Num comme ça a été précisé plus tot, et la brightness, qui pourrait etre ajustée au meme niveau que pour les pommes

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e2286196218b930c49cd810005db09b5", "grade": false, "grade_id": "cell-16c43adde3a2a1e0", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Il serait erroné d'utiliser la variable "Num" pour prédire la cible, car la plupart des images de pommes ont été collectées avant les bananes, donc inclure Num est une forme de "fuite de données". Num ne semble pas être en corrélation avec d'autres variables, il est donc correct de la supprimer.
Gardons toutes les autres.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 25fce9e71e2e200272a8faa017af54c3
  grade: false
  grade_id: cell-5b8b02da5c0a3ac1
  locked: true
  schema_version: 3
  solution: false
  task: false
---
new_subset = metadata_subset.drop(columns=['Num'])
p_tr, s_tr, p_te, s_te = df_cross_validate(new_subset, sklearn_model, sklearn_metric, n=10, verbose=False)
metric_name = sklearn_metric.__name__.upper()
print("AVERAGE TRAINING {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_tr, s_tr))
print("AVERAGE TEST {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_te, s_te))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f74966ea09a3f7e495f435d256e9f7b8", "grade": false, "grade_id": "cell-e352593dac7eb000", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Lorsque nous abandonnons "Num", nous ne pouvons pas vraiment faire de prédictions utiles, donc l'ensemble de données n'est pas trop biaisé. Néanmoins, on observe que 'GPSAltitude' et 'BrightnessValue' semblent être très prédictifs, étudions-les :

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 538ccdc9229d0ddaeb417b9d90ab68c6
  grade: false
  grade_id: cell-11ca5c19c66c1321
  locked: true
  schema_version: 3
  solution: false
  task: false
---
new_subset = metadata_subset[['GPSAltitude', 'BrightnessValue', 'Fruit']]
p_tr, s_tr, p_te, s_te = df_cross_validate(new_subset, sklearn_model, sklearn_metric, n=10, verbose=False)
metric_name = sklearn_metric.__name__.upper()
print("AVERAGE TRAINING {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_tr, s_tr))
print("AVERAGE TEST {0:s} +- STD: {1:.2f} +- {2:.2f}".format(metric_name, p_te, s_te))
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "630813d53e4c63bb722041d86238487b", "grade": false, "grade_id": "cell-f7356111f44fbcb6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

En effet, ils sont assez prédictifs. Nous devons approfondir nos recherches. Peut-être que l'altitude est révélatrice d'un arrière-plan différent ? Peut-être que les bananes ont été photographiées un jour plus ensoleillé ?

+++

## Conclusion

Prenez ici quelques notes sur ce que vous avez appris dans cette feuille, puis
passez à la feuille sur le [l'analyse](2_analyse.md).

**Bonne pratique:** Terminez toujours votre travail sur une feuille par "Kernel > Restart & Run all" pour vérifier que toutes vos cellules fonctionnent dans leur ordre d'exécution.
