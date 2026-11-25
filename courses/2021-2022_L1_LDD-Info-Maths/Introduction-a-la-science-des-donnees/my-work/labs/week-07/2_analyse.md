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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "27cf221dcecace13185888821c462ee5", "grade": false, "grade_id": "cell-883bbb5e1919ca1e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Analyse complète

Dans cette feuille, nous allons mener une première analyse sur des données, afin d'obtenir une référence.
Nous utiliserons d'abord les données brutes (représentation en pixel), puis nous extraierons automatiquement des attributs par Analyse en Composante Principale.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6749aa57c3717bca9183392e4907828a", "grade": false, "grade_id": "cell-e5b1c2171c7f8c60", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous ferez l'ensemble de cette feuille avec le jeu de données fourni (pommes et bananes).
La semaine prochaine, vous ferez la même chose pour analyser votre propre jeu de données.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5505231ef795dc8e2187a9d01fe6baa9", "grade": false, "grade_id": "cell-e15fdd0116a9b9e2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Import des librairies

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "537b879245dce753278016e0949d52e7", "grade": false, "grade_id": "cell-406ad2a159064cfa", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On commence par importer les librairies dont nous aurons besoin. Comme d'habitude, nous utiliserons un fichier `utilities.py` où nous vous fournissons quelques fonctions et que vous complèterez au fur et à mesure du projet:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b165a7a4283f25e045698d67fac9286c
  grade: false
  grade_id: cell-76e64ee7bcb96bb5
  locked: true
  schema_version: 3
  solution: false
  task: false
---
# Automatically reload code when changes are made
%load_ext autoreload
%autoreload 2
import os
from PIL import Image, ImageDraw, ImageFont
import matplotlib.pyplot as plt
from scipy import signal
import seaborn as sns

from intro_science_donnees import *
from utilities import *
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ca3bf4d60a26fe036451447bb88e1bac", "grade": false, "grade_id": "cell-6ec03d05a4e1c693", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Chargement des images
On travaille sur le jeu de données des pommes et des bananes (un jeu de données plus grands qu'au début du cours!)

```{code-cell} ipython3
from intro_science_donnees import data
dataset_dir = os.path.join(data.dir, 'ApplesAndBananas')

images = load_images(dataset_dir, "*.png")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "69e44ab8a645a045cb001209ba76c706", "grade": false, "grade_id": "cell-efcac6252de311fd", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons aborder des jeux de données **beaucoup plus grands** que les précédents, en nombre et en résolution des images; il faut donc être **un peu prudent** et parfois **patient**. Cela prendrai par exemple du temps pour lire et afficher toutes les images dans la feuille Jupyter. Aussi, dans les exemples suivants, nous n'affichons que les premières et dernières images:

```{code-cell} ipython3
head = images.head()
image_grid(head, titles=head.index)
```

```{code-cell} ipython3
tail = images.tail()
image_grid(tail, titles=tail.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9643a689ccd5f38a852e160d86352c7a", "grade": false, "grade_id": "cell-e723e3fb5001bd97", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 2: Redimensionner et recadrer

Il est généralement nécessaire de redimensionner et/ou de recadrer les images. Dans les cours précédents, nous avons utilisé des images recadrées pour se simplifier la tâche. Si l'objet d'intérêt est petit au milieu de l'image, il est préférable d'éliminer une partie de l'arrière-plan pour faciliter la suite de l'analyse. De même, si l'image a une résolution élevée, on peut la réduire pour accélérer les calculs sans pour autant détériorer les performances. Dans l'ensemble, les images ne doivent pas dépasser 100x100 pixels.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cf60f69e8009eefd97ecbec2962c1d2d", "grade": false, "grade_id": "cell-1f5b70462bf6e53f", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans les cellules suivantes, on recadre et redimensionne les images en 32x32 pixels. Aucun effort particulier n'est fait pour centrer l'image sur le fruit. Vous pourrez faire mieux les semaines suivantes, dans la fiche `pretraitement.md`!

```{code-cell} ipython3
images_cropped = images.apply(crop_image)
```

```{code-cell} ipython3
image_grid(images_cropped.head())
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "984afa40181ef0d4858f73045bb9fda6", "grade": false, "grade_id": "cell-1848d8ac9dce2aa3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 3: Représentation en pixels

Dans les cours précédents, nous avons extrait des attributs avec des fonctions ad-hoc, comme la rougeur (*redness*) ou l'élongation. Les attributs ad-hoc sont pratiques pour faciliter la visualisation des données. On peut cependant obtenir d'assez bons résultats en partant directement des données brutes -- ici les valeurs des pixels de nos images recadrées -- et en extrayant automatiquement des attributs par [décomposition en valeurs singulières](https://fr.wikipedia.org/wiki/D%C3%A9composition_en_valeurs_singuli%C3%A8res), à la base de la technique de [PCA](https://fr.wikipedia.org/wiki/Analyse_en_composantes_principales). Cette analyse, présentée ci-dessous est simple à mettre en œuvre et peut donner une première base de résultats.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4d5a61b5b28c1261801404596672298b", "grade": false, "grade_id": "cell-6c8ca7bdc9253abf", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Vous trouverez dans `utilities.py` une fonction appelée `image_to_series` qui transforme une image en une série unidimensionnelle contenant les valeurs de tous les pixels de l'image. En appliquant cette fonction à toutes les images, on obtient un tableau de données où chaque ligne correspond à une image:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a612f0aa6892caed701c54e5dd4daeda
  grade: false
  grade_id: cell-f376c04452c0a2c4
  locked: true
  schema_version: 3
  solution: false
  task: false
---
show_source(image_to_series)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f3ad69fd3e0f42fcb610ebaff9cd418d
  grade: false
  grade_id: cell-e726f7c95a38b80b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df = images_cropped.apply(image_to_series)
df
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "de756b9c5df67fab6e3962df4c1e6272", "grade": true, "grade_id": "cell-edf8fc36ed15faf7", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

**Exercice:**  Pouvez-vous expliquer le nombre de colonnes que nous obtenons?

32\*32\*3 <=> nombre de pixel sur chaque channel RGB

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "afbcb18ccb9e375ba5dcfb40309e9ccf", "grade": false, "grade_id": "cell-bac63aa1dc5a364a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous rajoutons à notre tableau de données une colonne contenant l'étiquette (vérité terrain, *ground truth*) de chaque image; dans le jeu de données fournies, ce sera 1 pour une pomme et -1 pour une banane:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 45dcbbd75dc72916ab9d2c5a71cb4e37
  grade: false
  grade_id: cell-ef9776de8892681b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df['étiquette'] = df.index.map(lambda name: 1 if name[0] == 'a' else -1)
df
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a0f0a7d04559dde1ab89a5ba75c9e671", "grade": false, "grade_id": "cell-b521e08d53e6f7e5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Afficher les statistiques descriptives de Pandas sur votre base de données. Peut-on interpréter ces statistiques?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: d9aecf0f1e72279e18e23c52f68f08c4
  grade: false
  grade_id: cell-265099e5a3fefb08
  locked: false
  schema_version: 3
  solution: true
  task: false
---
df.describe()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0b04fc60580d53165e039ab88751a746", "grade": false, "grade_id": "cell-a69bb602ef2221a4", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Sauvegarde intermédiaire

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fcfa65f265bc5005f0f6dfbd091e52c8", "grade": false, "grade_id": "cell-8cb1846130b9cfe2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous allons sauvegarder ces données brutes dans un fichier:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 75453876738eaeed631d6014965c9b42
  grade: false
  grade_id: cell-2359fca3d8d7ac9b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df.to_csv('crop_data.csv')
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f26d5132ee9b3cc7006b4ca2aed4afa7", "grade": false, "grade_id": "cell-c8e307c24e9822df", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Cela vous permettra par la suite de reprendre la feuille à partir d'ici, sans avoir à reexécuter tous les traitements depuis le début:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4eaef49f3c7ef47b7321ba7ea4753ffe
  grade: false
  grade_id: cell-59f5ff38837b92ad
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df = pd.read_csv('crop_data.csv', index_col=0)
df
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "92e6c6cf013c29b97cb427135913d970", "grade": false, "grade_id": "cell-4576e2c2723b724d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Visualisation des données brutes par carte thermique

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b14bcb37e6178a9bbaaefa566c7cfcda", "grade": false, "grade_id": "cell-2a67648ea9c07906", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les données de la représentation en pixels sont volumineuses; par principe il faut tout de même essayer de les visualiser. On peut pour cela utiliser une carte thermique avec `Seaborn`.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f3c870bca4130ab9236929eb09f24dab
  grade: false
  grade_id: cell-057378ec5d717db0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
plt.figure(figsize=(20,20))
sns.heatmap(df, cmap="YlGnBu");
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fa589541231d2025d3ae8432741a38cf", "grade": false, "grade_id": "cell-261308b1d940c89a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Comme vous le constatez, les données ne sont pas aléatoires: il y a des corrélations entre les lignes. Cela reste cependant difficilement exploitable visuellement.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a914a6742b240e5d82ab7f40058ee5a2", "grade": false, "grade_id": "cell-c103279002f68467", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Étape 4: Performance de référence (BAseline)

À présent, nous allons appliquer la méthode des plus proches voisins sur la représentation en pixels pour avoir une performance de référence.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "97af9d4d2da20419f99d5139ec36d0af", "grade": false, "grade_id": "cell-c67679043304e3f1", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On déclare le classifieur par plus proche voisin (KNN), depuis la librairie `scikit-learn`.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1c40a2534a64d7032b31b7f3934a34d3
  grade: false
  grade_id: cell-4794ca5ee133a97b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import balanced_accuracy_score as sklearn_metric
sklearn_model = KNeighborsClassifier(n_neighbors=3)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "af4dc89a4dbd6c71e7e2333acd9846ae", "grade": false, "grade_id": "cell-f5d1905f8f1e86bf", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Comme les séances précédentes, on calcule la performance et les barres d'erreurs du classifieur par validation croisée (*cross validate*), en divisant de multiples fois nos données en ensemble d'entraînement et en ensemble de test.

La fonction `df_cross_validate` fournie automatise tout le processus. Consultez son code pour retrouver les étapes:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 18a09476bc1299fb57649633a2d04405
  grade: false
  grade_id: cell-1b3c24803336e33f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
show_source(df_cross_validate)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 156a4a7721cdf2f999902e582da677dc
  grade: false
  grade_id: cell-10d1cd02c980dc5b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
p_tr, s_tr, p_te, s_te = df_cross_validate(df, sklearn_model, sklearn_metric, verbose=True)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5c90541ab9816ee07ae0a1624cc79e47", "grade": false, "grade_id": "cell-7a16870bc8b1d91d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On a obtenu cette performance en comparants nos images pixel à pixel (distance euclidienne), sans aucun attributs.

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a211a7ef8290a24c18f439adf985494f", "grade": true, "grade_id": "cell-2b68d19d35bceb2f", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

**Exercice:** Est-ce que ce score vous semble étonnant?

La performance n'est pas si mauvaise !

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2ccd5d21c4e16e3002e18b313f690135", "grade": false, "grade_id": "cell-a93e6286afe7c468", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Réduction de la dimension par analyse en composants principales

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "57df53409fac75c52e93f15c4527d999", "grade": false, "grade_id": "cell-720d9a35a3d6ce4d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Si vous reprenez cette feuille à partir d'ici, vous pouvez charger les données pour éviter d'avoir à tout reexécuter:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 53781ef78f556cb1954a615aaffcc6fa
  grade: false
  grade_id: cell-c140b4ab67bf1e1d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df = pd.read_csv('crop_data.csv', index_col=0)
df
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "43b38822793414749decf234ffa0a212", "grade": false, "grade_id": "cell-79e2147e6deb20b3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Comme noté lorsque nous avons visualisé les données brutes, la représentation en pixels contient beaucoup trop d'information pour être directement exploitable: chaque ligne est un vecteur de grandes dimensions ($32 \times 32$). Il faut donc **réduire la dimension** en synthétisant l'information contenue dans chaque ligne en un petit nombre d'attributs. C'est ce que nous avions fait avec des attributs ad-hoc. Nous allons cette fois utiliser la technique d'[Analyse en Composantes Principales](https://fr.wikipedia.org/wiki/Analyse_en_composantes_principales) (*PCA*: Principal Component Analysis). Elle utilise un algorithme de décomposition de matrices en valeur singulière (SVD) pour déterminer les «directions principales» des données, c'est-à-dire là où elles ont la plus grande variance. Nous l'avions déjà utilisé lors du TP 2 pour calculer l'élongation d'une forme.

Dans ce qui suit, vous pourrez vous aider des tutoriels que vous pouvez trouver sur internet (par exemple [ici](https://machinelearningmastery.com/singular-value-decomposition-for-machine-learning) ou [là](https://cmdlinetips.com/2019/05/singular-value-decomposition-svd-in-python)), et de la documentation de `pandas` et/ou de `numpy`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2eaf1d2637f104771d2d1b5c5c44223d", "grade": false, "grade_id": "cell-b6ce9c809eb0bf2e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Construisez un tableau `df_scaled` contenant les colonnes de `df` après normalisation. Vérifiez que la normalisation a fonctionné en appelant `df.describe()` avant et après la normalisation.

**Indications:**
- La dernière colonne de `df` contient les étiquettes; il faut donc l'ignorer. Pour celà, vous pouvez utiliser la méthode `drop`.
- Certaines colonnes pourraient être constantes, donc d'écart type nul. Dans ce cas, pour éviter une division par zéro, vous pouvez systématiquement ajouter la valeur `sys.float_info.epsilon` qui, comme son nom le suggère, est une toute petite valeur non nulle.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: fd9bc5b4a4cf00a8f605fbe64e4904e3
  grade: false
  grade_id: cell-162a0c66c26f9c65
  locked: false
  schema_version: 3
  solution: true
  task: false
---
import sys
df_scaled = (df-df.mean())/np.std(df)
df_scaled.drop(df.columns[[-1]], axis=1, inplace=True)
df_scaled+=sys.float_info.epsilon
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 78f49e7fa408ac7a917a5d1cdd7c6b11
  grade: false
  grade_id: cell-de918321d3654071
  locked: true
  schema_version: 3
  solution: false
  task: false
---
df_scaled.describe()
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8eb3ed2753741ba8abf9bc6dcfc84556
  grade: true
  grade_id: cell-cdafbcb6707e7900
  locked: true
  points: 2
  schema_version: 3
  solution: false
  task: false
---
assert df_scaled.shape[1] == 32 * 32 * 3
assert (abs(df_scaled.mean()) < 0.01).all()
assert (abs(df_scaled.std()-1) < 0.01).all()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0a6b64d4257ea4f599197539d2cc9cf7", "grade": false, "grade_id": "cell-6dc407ec0a37f340", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice**: Effectuez une décomposition en valeurs singulières de `df_scaled`. Stockez les matrices résultantes dans les variables `u`, `s` et `v`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3ffb25347e2480b75dd733d4fda00719
  grade: false
  grade_id: cell-2dff66e19143b1d5
  locked: false
  schema_version: 3
  solution: true
  task: false
---
from scipy.linalg import svd
U, S, V = svd(df_scaled)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4df100241993a5b195afded7e5d79bb2
  grade: false
  grade_id: cell-186b32b88482f0ea
  locked: true
  schema_version: 3
  solution: false
  task: false
---
U.shape
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a8e9e8df52ec06fc531cf518b8871424
  grade: false
  grade_id: cell-f8c27d5c1249dc17
  locked: true
  schema_version: 3
  solution: false
  task: false
---
S.shape
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 8940f7ea210030caf7c6ea764bca1fc1
  grade: false
  grade_id: cell-9d219cdb7c3dd40c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
V.shape
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "da8956fc7512b3449328f5dd451b9e90", "grade": false, "grade_id": "cell-3f02c719b0a1dc65", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour les curieux souhaitant en savoir plus sur la signification de ces matrices u, s, v, nous renvoyons à cet [article](https://fr.wikipedia.org/wiki/D%C3%A9composition_en_valeurs_singuli%C3%A8res). Pour aujourd'hui, il suffira de savoir ce qui suit:

- `U` est une matrice carrée dont les colonnes sont les attributs extraits automatiquement; chacun est une combinaison linéaire de colonnes de `df_scaled`. Il y en a toujours un grand nombre, mais ils sont triés par ordre d'intérêt: les premiers contiennent le plus d'information (axes de plus grande variance).

- `S` est un vecteur contenant *les valeurs singulières* correspondant aux attributs. Les carrés de celles-ci sont les *valeurs propres*; elles donnent l'importance de chaque attribut pour expliquer la variance des données.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9043e57550214c0d8fcaf9d73b757f53", "grade": false, "grade_id": "cell-4cebd4f2ce937828", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Un [scree plot](https://en.wikipedia.org/wiki/Scree_plot#:~:text=In%20multivariate%20statistics%2C%20a%20scree,principal%20component%20analysis%20(PCA)) affiche toujours les valeurs propres dans une courbe descendante, en classant les valeurs propres de la plus grande à la plus petite. Cette courbe aide à sélectionner le nombre de vecteurs propres qui expliquent la majorité de la variance des données.

**Exercice:** Afficher le scree plot des valeurs propres

**Indications:**
- Les valeurs singulières sont déjà triées de la plus grande à la plus petite
- N'utiliser que les 50 premières valeurs
- Renormaliser les valeurs propres par leur somme pour obtenir un pourcentage

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 929babf1b55d716f785832f2a77f02b3
  grade: false
  grade_id: cell-2b0bffda2b44a8c0
  locked: false
  schema_version: 3
  solution: true
  task: false
---
percent = S[:50]**2/(S[:50]**2).sum()
x = np.arange(50)
y = percent[:50]
print(y.shape)
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.plot(x,y)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a409520f95c97345ba68b243b176b794", "grade": false, "grade_id": "cell-4a804da27ed72447", "locked": true, "schema_version": 3, "solution": false, "task": false}}

D'après le scree plot obtenu, on voit que les premiers attributs contiennent la majorité de l'information. Nous prendrons prendront les cinq premières.

**Exercice:** Créer un nouveau tableau de données `svd_df` avec les six premières colonnes de `U` et l'étiquette du fruit dans la dernière colonne.

**Indication:** Extraire les cinq premières colonnes de `U`, les passer comme argument à pd.DataFrame en spécifiant l'index de `df` comme index. Puis insérer la colonne `étiquette` de `df`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ebe12448393b884ae5138fa3eaf76f89
  grade: false
  grade_id: cell-3fd6e3f44337f707
  locked: false
  schema_version: 3
  solution: true
  task: false
---
svd_df = pd.DataFrame(U[0:6])
svd_df = svd_df.transpose()
svd_df.set_index(df.index, inplace=True)
svd_df.insert(6, 'étiquette', df['étiquette'])
svd_df
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "44fbe1776aa0a1871973fb2f9aaad08e", "grade": false, "grade_id": "cell-c3d368d566dc7676", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Afficher des diagrammes de dispersion par paires des attributs obtenus. Observez-vous que certaines caractéristiques ou paires de caractéristiques séparent bien les données?

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 40449b8368e08eea0f85b5b3127ad102
  grade: false
  grade_id: cell-faeb04dc1e0af87f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
g = sns.pairplot(svd_df, hue="étiquette", markers=["o", "s"], diag_kind="hist")
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "db94700acf265b25929ef1a8624aa3e4", "grade": false, "grade_id": "cell-31bc05cee7d026d8", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice:** Calculer les performances obtenues avec la méthode des trois plus proches voisins en utilisant les cinq premiers attributs. Comparez les performances à celles obtenues avec la représentation des pixels directement.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ef1158ffe5a966a47ad5a7a5ace37901
  grade: false
  grade_id: cell-99d52b0de49e5f4f
  locked: false
  schema_version: 3
  solution: true
  task: false
---
p_tr, s_tr, p_te, s_te = df_cross_validate(svd_df, KNeighborsClassifier(n_neighbors=3), sklearn_metric, verbose=True)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3594470adc568dbe8a123b6f48657476", "grade": false, "grade_id": "cell-36f11e07b9930a24", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Pour aller plus loin $\clubsuit$:** Tracer le score de performance (accuracy) sur l'ensemble de test en fonction du nombre d'attributs de la PCA prise en compte par le classifieur (de 1 à 10 par exemple).

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: cd2d984619f1e103e3ad1cc1dc8b4bfc
  grade: false
  grade_id: cell-d41b42634ff70965
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# VOTRE CODE ICI
raise NotImplementedError()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "efd4135fc63340dd8e0d3d88f89f9741", "grade": false, "grade_id": "cell-c5a8e3d90bb35375", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Conclusion

Terminez toujours par une conclusion. Qu'avez-vous appris ? Qu'est-ce qui pourrait être amélioré ?

Cette première feuille vous fait passer par le formatage de base des données et un flux de travail d'analyse de données de base. Les feuilles des semaines suivantes aborderont d'autres aspects de l'analyse (biais, pré-traîtement, classifieur).

**Bonne pratique:** Terminez toujours votre travail par "Kernel > Restart & Run all" pour vérifier que toutes vos cellules fonctionnent dans leur ordre d'exécution.
