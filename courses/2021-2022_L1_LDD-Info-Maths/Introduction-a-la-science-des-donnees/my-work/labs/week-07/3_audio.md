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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ab400094f064d6c48790925e644bac57", "grade": false, "grade_id": "cell-19c6eb4994e2384a", "locked": true, "schema_version": 3, "solution": false}}

# Manipuler du son (♣)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7fcb89f06b13d051d60600abd6211070", "grade": false, "grade_id": "cell-19c6eb4994e2384c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans cette feuille, vous allez apprendre à effectuer quelques
manipulations et traitements simples sur du son. Elle s'adresse aux
étudiants désirant s'éloigner des images et de traîter d'autres types
de données. Les étapes de traîtement VI-ME-RÉ-BAR restent les mêmes
mais l'import et l'extraction des attributs peut changer
significativement. Si vous avez déjà des difficultés sur ce cours, il
serait préférable de rester avec des données d'images.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0eacb5e1b22b88691e58e6d91707aed4
  grade: false
  grade_id: cell-38a01921463de697
  locked: true
  schema_version: 3
  solution: false
---
import glob
import io
import os
from scipy.io import wavfile
import numpy as np
import IPython
import matplotlib.pyplot as plt
import pandas as pd
from PIL import Image, ImageTk

%load_ext autoreload
%autoreload 2

from intro_science_donnees import data, image_grid
from utilities import *
```

À titre d'illustration, nous allons étudier un jeu de données
contenant des enregistrements de sons de battements de coeur normaux
ou anormaux, que nous essaierons de classifier:

```{code-cell} ipython3
dataset_dir = os.path.join(data.dir, "BattementsCoeur/")
!ls {dataset_dir}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5744554e900fdb7cf546ba7c9a016ce8", "grade": false, "grade_id": "cell-19c6eb4994e2384b", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Utilisons la bibliothèque `scipy.io` pour lire un fichier audio, que
nous affectons à une variable `son` pour pouvoir la manipuler par la
suite:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d413903940837b623f2c73bbbdd542a1
  grade: false
  grade_id: cell-b5659c2e482c3848
  locked: true
  schema_version: 3
  solution: false
---
file = os.path.join(dataset_dir, "normal_1.wav")
rate, audio = wavfile.read(file)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "92690f0b1b9afa7c559be3c6fb3caafe", "grade": false, "grade_id": "cell-e75aecf3bd8946db", "locked": true, "schema_version": 3, "solution": false}}

Un son se présente comme un tableau de valeurs entières correspondant
à l'onde de pression acoustique enregistrée par un microphone. Lors du
passage en données numériques, ce signal (originellement continu) est
échantillonné c'est à dire découpées en une série de valeurs prélevés
à interval régulier. Ce sont ces valeurs discrétisés que l'on peut
stocker dans un ordinateur.

La fréquence d'échantillonnage nous donne le nombre d'échantillons par
seconde. Générallement, la musique est échantillonnée à 44100 Hz pour
couvrir toute la gamme de fréquence de l'audition humaine. Ici, on est
à 2000 Hz donc toutes les hautes fréquences (les aigües) sont filtrés.

Attention, les sons peuvent être stéréos ou mono. Un son stéréo a été
enregistré par deux microphones pour restituer l'audition humaine
(deux oreilles). Par conséquent, un son stéréo contient deux suites
temporelles de nombres pour chaque canal d'enregistrement.

**Exercice :** Quel est la fréquence d'échantillonnage du son de coeur
importé? Votre son est-il enregistré en stéréo ou mono?

**Indication :** Consulter la documentation de `wavfile.read`

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e518236a192f2649d03bc773c44b03ad
  grade: false
  grade_id: cell-5f412c59d2396365
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# VOTRE CODE ICI
raise NotImplementedError()
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ec75d2c80a3ddf1e7d5746f602f15d16", "grade": true, "grade_id": "cell-5cd3b0905ad4b8c7", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

VOTRE RÉPONSE ICI

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d94cd992afa04e18229bf6ad6eb2c57d", "grade": false, "grade_id": "cell-4a283ea51e247b4a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On peut écouter un fichier audio dans un feuille Jupyter avec la
commande suivante. Attention, cela peut ne pas marcher avec le
navigateur Chrome mais devrait fonctionner avec Firefox.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 209d146f3876af52769cf049bbc807f5
  grade: false
  grade_id: cell-3d78468c1e0f92ec
  locked: true
  schema_version: 3
  solution: false
  task: false
---
IPython.display.Audio(file)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "13a3efe90ad5288668801398f4a98fe7", "grade": false, "grade_id": "cell-450a9499627740e6", "locked": true, "schema_version": 3, "solution": false}}

**Exercice :** Afficher l'onde de pression en fonction du **temps**
(forme d'onde) avec la fonction `plot` de la librairie `matplotlib`.

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: bfa9d9684531bfd11c5f52856c608d2e
  grade: false
  grade_id: cell-1b1461380b6fef35
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# VOTRE CODE ICI
raise NotImplementedError()
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "760e0ea7100ef1d699c15587a566bfda", "grade": true, "grade_id": "cell-5e5e2ae30d666c70", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

**Exercice :** Combien de secondes dure le fichier?

VOTRE RÉPONSE ICI

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3775156a9d9eaa9c6f26e12cd32ef22b", "grade": false, "grade_id": "cell-67d310808fac6650", "locked": true, "schema_version": 3, "solution": false}}

Nous allons maintenant ouvrir un ensemble de sons et stocker leurs
valeurs dans une table :

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 0591dd4e4263702807ca56712faf4fea
  grade: false
  grade_id: cell-46598b84e0c79fc6
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# VOTRE CODE ICI
raise NotImplementedError()
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "be613eaa8faa2cbcec269e87a2a66027", "grade": false, "grade_id": "cell-5aa2ff2d91d5b0b3", "locked": true, "schema_version": 3, "solution": false}}

## Domaine temporel ou fréquentiel

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3315ea65de4d0fc0a133f113f82d4c97", "grade": false, "grade_id": "cell-5aa2ff2d91d5b0b4", "locked": true, "schema_version": 3, "solution": false}}

Pour travailler avec des sons, il nous faut calculer des descripteurs.

On peut interpréter un son à la fois dans le domaine fréquentiel ou
temporel:

- Le domaine temporel s'intéresse à la forme de l'onde tel que nous
  l'avons affichée plus haut.
- Le domaine fréquentiel cherche à représenter le son en fréquences à
  l'aide d'une [transformation de
  Fourier](https://fr.wikipedia.org/wiki/Transformation_de_Fourier)

Avec une transformation de Fourier on peut représenter le son sous la
forme d'une «image», un spectrogramme. Voyons comment obtenir un
spectrogramme sur la première image de notre jeu de données.

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 0f0bccf9ec632c5f170c699a5ebc4496
  grade: false
  grade_id: cell-8f62152c1e513665
  locked: true
  schema_version: 3
  solution: false
  task: false
---
audio = df.iloc[0]["audio"]
spectrogram =  plt.specgram(audio, Fs=rate)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "e39b476fb5d51baff7df0a4e1b49972c", "grade": false, "grade_id": "cell-6da995203577e3b3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

L'axe des x représente le temps tandis que l'axe des y représente les
fréquences. Les hautes valeurs de y sont les **composantes aigües** du
son tandis que les basses valeurs valeurs de fréquences correspondent
au **composantes graves** du son.  Le son est formée d'une
superposition de fréquences qui peuvent être :

- Localisés sur des lignes horizontales. On parle de sons harmoniques
  ou purs. Ce serait le cas de chants d'oiseaux ou d'une flute par
  exemple. On peut clairement distingué une note jouée.
- Étalé dans la gamme de fréquence, se traduisant par des lignes
  hotizontales. Ce sont des sons bruités, percussifs tels qu'une
  caisse claire de batterie ou une porte qui claque.

**Exercice**: Nos battements de coeurs sont-ils plutôt des sons
harmoniques ou bruités?

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7f65519e6f01d34d329be2221dc3f4f1", "grade": false, "grade_id": "cell-9b8a85ef412d45e5", "locked": true, "schema_version": 3, "solution": false, "task": false}}

On récupère les valeurs du spectrogramme dans un tableau `numpy.array`
comme ceci:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 451d9a21054507b70e46b8b6b1a24556
  grade: false
  grade_id: cell-f1cf391e96f32f52
  locked: true
  schema_version: 3
  solution: false
---
freqs_temps = spectrogram[0] # Le spectrogramme
freqs = spectrogram[1] # L'axe des fréquences
temps = spectrogram[2] # L'axe temporel
fig =  spectrogram[3] # La figure affichée ce-dessus
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "70cd13c9536bbc079b7b627d513d2ead", "grade": false, "grade_id": "cell-bb2a8e7a345544d6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Attributs

Vous pouvez maintenant réfléchir à des attributs dans le domaine
temporel (forme d'onde 1D), tempo-fréquentiel (spectrogramme 2D) ou
purement fréquentiel (moyenne des différentes fréquences dans le temps
1D). Pensez qu'un spectrogramme peut-être vu comme une image sur
laquelle vous maîtriser déjà des traitements et de l'extraction
d'attributs.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "12550fcde4b2f9d615c13fd3d18ef683", "grade": false, "grade_id": "cell-bb2a8e7a345544d7", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Exercice :**

- Quelles est la taille de notre spectrogramme?

- Combien de bandes temporelles possède notre spectrogramme (nombre de
  pas selon l'axe temporel)?

- Combien de bandes fréquentielle possède notre spectrogramme (nombre
  de pas selon l'axe des fréquences)?

```{code-cell} ipython3
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 4afbb7e23090ce2d2adc4046462d99ab
  grade: false
  grade_id: cell-a9ad2735545bebae
  locked: false
  schema_version: 3
  solution: true
  task: false
---
# VOTRE CODE ICI
raise NotImplementedError()
```

+++ {"deletable": false, "nbgrader": {"cell_type": "markdown", "checksum": "f9824fd23d1896392c43fd6c672ab748", "grade": true, "grade_id": "cell-6c3373f2c0a00f5d", "locked": false, "points": 0, "schema_version": 3, "solution": true, "task": false}}

VOTRE RÉPONSE ICI

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0128b4b10bb6f91d2676727c2ae93a2e", "grade": false, "grade_id": "cell-4e8e799f0f70e118", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Voici comment afficher les spectrogrammes de tous nos sons avec
`image_grid`:

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3b847ccc1feefd1da18c4416d1d419fb
  grade: false
  grade_id: cell-6336da8d3c6f9ee0
  locked: true
  schema_version: 3
  solution: false
  task: false
---
def spectrogram_PIL(audio):
    """Renvoie le spectrogramme du son sous forme d'une image PIL"""
    # Compute the spectrogram
    spectrogram = plt.specgram(audio, Fs=rate)[0];
    # Convert into an array of ints between 0 and 255
    spectrogram_uint = (spectrogram * 255 / np.mean(freqs_temps)).astype(np.uint8)
    # Convert into a PIL image
    return Image.fromarray(spectrogram_uint, mode='L')
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b4aca620fd237a9325292e9023254fa6
  grade: false
  grade_id: cell-2b620a642297a871
  locked: true
  schema_version: 3
  solution: false
  task: false
---
# Une table contenant le le spectrogramme de chaque son du jeu de données
spectrograms_PIL = df['audio'].map(spectrogram_PIL)
```

```{code-cell} ipython3
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1c7e76517abc171a8fe5b505ad527048
  grade: false
  grade_id: cell-02a67a82c66f523b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
image_grid(spectrograms_PIL, titles=spectrograms_PIL.index)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "855fcc547fe129ba13a7a32d2e5ce5e9", "grade": false, "grade_id": "cell-d0ca296b14cdaa49", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Dans le domaine fréquentiel, des attributs audio fréquents sont [le
centroïde spectral](https://en.wikipedia.org/wiki/Spectral_centroid)
et [l'étalement de
spectre](https://fr.wikipedia.org/wiki/%C3%89talement_de_spectre).

Vous trouverez des idées d'attributs audio dans [la publication
suivante](https://brungio.github.io/GP_2011_JASA.pdf).

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3230078fe214d24f258aa7db8f737456", "grade": false, "grade_id": "cell-d0fb04b5c7bf1744", "locked": true, "schema_version": 3, "solution": false}}

## Conclusion

Vous avons vu dans cette feuille comment charger un son dans Python et
effectuer quelques manipulations, visualisations et passer dans le
domaine fréquentiel. Cela a été l'occasion de mieux comprendre la
décomposition d'un son en fréquence. Faites part de votre intérêt de
choisir un projet avec du son à votre chargé de TD avant de vous
lancer.
