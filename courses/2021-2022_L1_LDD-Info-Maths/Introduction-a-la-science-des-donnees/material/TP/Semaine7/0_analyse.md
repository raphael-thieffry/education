---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "56952047c4310bf0c313ca44bb5af720", "grade": false, "grade_id": "cell-883bbb5e1919ca1e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Analyse de données

:::{admonition} Consignes
:class: dropdown

Vous documenterez votre analyse de données dans cette feuille. Nous
vous fournissons seulement l'ossature. À vous de piocher dans les
feuilles et TPs précédents les éléments que vous souhaiterez
réutiliser et adapter pour composer votre propre analyse!

:::

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "07b6f7ec89dbe99e092902adb7ff9cc8", "grade": false, "grade_id": "cell-e15fdd0116a9b9e2", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Import des bibliothèques

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "96489bd4f670f5daa152f95fa18ce301", "grade": false, "grade_id": "cell-406ad2a159064cfa", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On commence par importer les bibliothèques dont nous aurons besoin.

:::{admonition} Consignes
:class: dropdown

Inspirez vous des précédentes feuilles. N'oubliez pas d'importer
`utilities` et `intro_science_donnees`.

:::

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 8e6a7da13b6e1d41caa1c33a8c0104e5
  grade: false
  grade_id: cell-76e64ee7bcb96bb5
  locked: false
  schema_version: 3
  solution: true
  task: false
---
from intro_science_donnees import *
## les utilitaires
%load_ext autoreload
%autoreload 2
from utilities import *
# Graphs and visualization library
import seaborn as sns; sns.set()      
# Configuration intégration dans Jupyter
%matplotlib inline
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e319f7fbbc65f7368fd94b546edb9e34", "grade": false, "grade_id": "cell-6ec03d05a4e1c693", "locked": true, "schema_version": 3, "solution": false, "task": false}, "user_expressions": []}

## Chargement des images

:::{admonition} Consignes
:class: dropdown

- Chargez vos images recentrées et réduites.
- Affichez les.

:::

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: a842cb19c2f315d9a183cf8a17bd295f
  grade: false
  grade_id: cell-211e275ccc954714
  locked: false
  schema_version: 3
  solution: true
  task: false
---
dataset_dir = os.path.join('data')
images_a = load_images(dataset_dir, f"a*.JPG")
images_b = load_images(dataset_dir, f"b*.JPG")
images = pd.concat([images_a, images_b])
image_grid(images, titles=images.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0e4e77fedcf1d467c6139e4c44ff1e5e", "grade": false, "grade_id": "cell-e723e3fb5001bd97", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Prétraitement : extraction des attributs

:::{admonition} Consignes
:class: dropdown

- Choisissez entre des attributs ad-hoc ou obtenus via une ACP depuis
  les données brutes (représentation en pixel).
- N'oubliez pas de normaliser votre table une fois les traitements
  effectués.
  
:::

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0b04fc60580d53165e039ab88751a746", "grade": false, "grade_id": "cell-a69bb602ef2221a4", "locked": true, "schema_version": 3, "solution": false, "task": false}, "user_expressions": []}

## Sauvegarde intermédiaire

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "35a89b8dc927e0dd763e9cdf592c4bdf", "grade": false, "grade_id": "cell-8cb1846130b9cfe2", "locked": true, "schema_version": 3, "solution": false, "task": false}, "user_expressions": []}

:::{admonition} Consignes
:class: dropdown

Une fois que vous êtes satisfaits des attributs obtenus, faites en une
sauvegarde intermédiaire.

:::

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b11c92757f734a72bf65f47b9513ca5f", "grade": false, "grade_id": "cell-4576e2c2723b724d", "locked": true, "schema_version": 3, "solution": false, "task": false}, "user_expressions": []}

## Visualisation des données

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ba2beca9ed69fdecbf145787bb70f7af", "grade": false, "grade_id": "cell-2a67648ea9c07906", "locked": true, "schema_version": 3, "solution": false, "task": false}}

:::{admonition} Consignes
:class: dropdown

Visualisez les attributs et leur corrélation. Mettez en œuvre les
formes que vous jugerez les plus pertinentes (carte thermique, ...).

:::

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fed3b57a555c863751f511011266a6de", "grade": false, "grade_id": "cell-c103279002f68467", "locked": true, "schema_version": 3, "solution": false, "task": false}, "user_expressions": []}

## Performance 

:::{admonition} Consignes
:class: dropdown

- Choisissez un ou plusieurs classificateurs et calculez leur
  performances.
- Comparez les performances selon les attributs utilisés (ad-hoc,
  ...).
- Si vous le souhaitez, vous pouvez aussi:
    - comparer un ou plusieurs classificateurs
	- comparer les performances selon le nombre de colonnes (pixels ou
      attributs) considérées.

:::

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ae7f04d9aea4689c8f25f33fd8cddf30", "grade": true, "grade_id": "cell-c5a8e3d90bb35375", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

VOTRE RÉPONSE ICI
