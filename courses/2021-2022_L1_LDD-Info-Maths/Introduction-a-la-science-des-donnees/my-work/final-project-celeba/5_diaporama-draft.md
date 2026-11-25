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
  backimage: fond.png
  centered: false
  controls: false
  enable_chalkboard: true
  height: 100%
  margin: 0
  maxScale: 1
  minScale: 1
  scroll: true
  slideNumber: true
  start_slideshow_at: selected
  transition: none
  width: 90%
---

+++ {"slideshow": {"slide_type": "slide"}}

# Titre

- Binôme: Raphaël Thieffry, Jeremy Wendels
- Adresses mails: raphael.thieffry@universite-paris-saclay.fr - jeremy.wendels@universite-paris-saclay.fr
- [Dépôt GitLab](https://gitlab.dsi.universite-paris-saclay.fr/raphael.thieffry/L1InfoInitiationScienceDonnees-Semaine8)

```{code-cell} ipython3
import os, re
from glob import glob as ls
from PIL import Image, ImageDraw
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

+++ {"slideshow": {"slide_type": "slide"}}

## Jeu de données

+++

Pour ce projet, nous avions initialement pensé à differencier les photos des dessins : malheureusement il s'est vite avéré que ce que nous avions appris cette année ne nous permettait pas d'y répondre

+++

Nous avons donc simplement pris le projet smiley et nous avons voulu l'amener une étape au dessus : la reconnaissance d'un sourire sur un visage humain.
  
Simplement les circonstances et les difficultés nous aurons amené à transformer la partie "apprentissange supervisé à la detection de sourire" en lutte pour extraire l'avant plan de l'image.
  
Nous verrons ensuite comment nous avons essayé de surmonter ces difficultés à l'aide d'un outil survolé rapidement en cours recement, et d'un jeu de données (un peu) plus grand !

```{code-cell} ipython3
dataset_dir = 'data/512x512/'
images = load_images(dataset_dir, "*.jpg")
image_grid(images.head(10), titles=images.index)
```

+++ {"slideshow": {"slide_type": "slide"}}

## Prétraitement

+++

La difficulté commence ici : nous avons en effet selectionné des images ayant un arriere plan parfois marqué, et malgré toute l'ingéniosité du monde, il parait impossible avec des heuristiques d'extraire convernablement les sujets pour les avoir sur fond blanc. Voici ce que nous avons fait pour cela:

+++

D'abord nous avons extrait l'avant plan, avec un seuil établi de maniere automatique :

```{code-cell} ipython3
show_source(calc_seuil)
```

```{code-cell} ipython3
img_foreground = np.array([invert(foreground_filter(img, calc_seuil(img))) for img in images])
image_grid(img_foreground[:10])
```

Le calcul du seuil est un peu arbitraire, mais fonctionne correctement  
Nous pouvons maintenent estimer où se trouve la personne par un calcul de barycentre. Pour La presentation nous utiliserons une fonction appelée "place_barycentre"

```{code-cell} ipython3
show_source(place_barycentre)
show_source(barycentre)
show_source(place_point)
```

```{code-cell} ipython3
image_grid([place_barycentre(img_foreground[i]) for i in range(len(img_foreground))][:10])
```

Nous avons à partir du barycentre mis toutes les images sous le meme format carré :

```{code-cell} ipython3
show_source(crop_around_barycentre)
```

```{code-cell} ipython3
images_cropped = pd.Series([crop_around_barycentre(img_foreground[i], images[i]) for i in range(len(images))])
images_cropped.index = images.index
```

Et reduit leur definition :

```{code-cell} ipython3
images_resize = pd.Series([img.resize((64, 64)) for img in images_cropped])
images_resize.index = images.index
```

```{code-cell} ipython3
image_grid(images_resize.head(10))
```

Bien sûr nous les avons sauvegardées après ça

+++ {"slideshow": {"slide_type": "slide"}}

## Visualisation des données

+++

Nous pouvons bien entendu afficher nos images recardées sous format carré, mais elles restent malheureuement inexploitables tant que nous n'avons pas supprimé l'arriere plan, c'est pourquoi nous ne pourrons pas faire les analyses de correlations, le choix du meilleur classificateur etc... Dans la mesure où nous n'avons malheureusement pas pu extraire d'attribut pertinent. L'idée d'origine etait d'extraire la bouche du visage, mais pour cela il nous fallait une image du seul visage.
Nous vous presenterons ici les methodes que nous avons éssayées pour avoir cette extraction, mais cela ne nous a pas mené bien loin

+++

Le foreground des images carrées :

```{code-cell} ipython3
foreground = pd.Series([invert(foreground_filter(img, calc_seuil(img))) for img in images_resize])
```

Nous avons essayé BEAUCOUP de methodes, nous vous montrons celle qui a le mieux marché

```{code-cell} ipython3
contour = np.array([contours(img) for img in images_resize])
image_grid(contour[:10])
```

```{code-cell} ipython3
show_source(superieur_couleur)
```

```{code-cell} ipython3
point_valides = np.array([(superieur_couleur(img) * np.array(foreground[i])[:-1,:-1]) for i, img in enumerate(contour)])
```

L'étape ci dessus permet d'enlever les artefacts hors du personnage

```{code-cell} ipython3
image_grid(point_valides[:10])
```

L'idée consiste dès lors à relier le barycentre (certain d'etre sur la personne) avec tous les autres pixels de point_valides grace à des lignes blanches. Ainsi les personnes sur les images seront remplis, et comme il reste tres peu d'artefacts cela ne "devrait pas" avoir d'incidence.

```{code-cell} ipython3
show_source(to_lines)
show_source(pt_isole)
```

```{code-cell} ipython3
image_grid([place_barycentre(to_lines(i), width= 2) for i in point_valides][:10])
```

Une fois cette étape atteinte, nous somme dans une impasse. Trop d'images ne subissent pas le traitement attendu, et nous ne pourrons finalement pas detecter si la personne souris, ou non

+++ {"slideshow": {"slide_type": "slide"}}

## Classificateurs favoris

+++

Puisque nous n'avons pas vraiment d'attributs, et puisque la nuance entre chaque classe d'image est minime au sein de l'amas des pixels constituant l'image (la PCA devient clairment inutile une fois ce constat établi), notre derniere maniere de reussir ce projet était donc de nous lancer dans du deeplearning.
  
Il aurait été interessant de faire comme Thimoté et Moncef mais la 1ere partie du projet et notre tentative de faire avec des atributs artisanaux nous a privé d'un temps devenu précieux.

+++

### Tensorflow et le jeu de donnée celeb_a

+++

Tout d'abord, nous avons récupéré les lignes de code du cours, et nous avons essayé de l'appliquer à notre jeu de donné. Le seul soucis est que nous n'avons pas assez d'images : 60 images ne sont pas suffisantes pour entrainer le model.
  
Intervient le jeu de donnee celeb_a. Il s'agit d'un jeu de donnée de 1.3go contenant 200 000 images, avec en plus un fichier csv contenant des étiquettes pour chaque images, dont une appelée "smiling".

En visualisant le jeu de donnée et en affichant la classe "smiling" juste en dessous cette étiquette est convainquante :

```{code-cell} ipython3
dataset_dir = 'data/img_align_celeba/img_align_celeba'
images = load_images(dataset_dir, "000???.jpg")
```

```{code-cell} ipython3
attributes = pd.read_csv('data/list_attr_celeba.csv', index_col=0)
```

```{code-cell} ipython3
smiling = [f"Smiling : {attributes['Smiling'][img]}" for img in images.index]
```

```{code-cell} ipython3
smiling = [f"Smiling : {attributes['Smiling'][img]}" for img in images.index]
image_grid(images.head(100), titles=smiling[:100])
```

On peut donc afficher les images avec leur classe sans soucis

```{code-cell} ipython3
import tensorflow as tf
tf.config.run_functions_eagerly(True)

mobilenet = tf.keras.applications.MobileNet(include_top=False, weights='imagenet', input_shape = (178,218,3))
for layer in mobilenet.layers:
    layer.trainable=False
mobilenet.summary()
```

On suit les mêmes etapes que pendant le dernier TP

```{code-cell} ipython3
from tensorflow import keras
from keras.models import Model
from keras.layers import Dense,GlobalAveragePooling2D

myneuralnet = keras.Sequential(
    [
        mobilenet,
        GlobalAveragePooling2D(),
        Dense(64, activation="relu", name="layer1"),
        Dense(64, activation="relu", name="layer2"),
        Dense(2, activation="softmax",name="layer3"),
    ]
)
myneuralnet.build((None,178,218,3))
myneuralnet.summary()
```

Il aura egalment fallu convertir les images en suite de chiffres à une seule dimension dans un fichier csv (cette étape fait planter jupyter)

```{code-cell} ipython3
'''df_clean = images.apply(image_to_series)
df_clean["class"] = attributes['Smiling']
df_clean.to_csv('clean_data.csv')'''
df_clean = pd.read_csv('clean_data.csv', index_col=0)  # chargement du fichier dans le notebook
df_clean
```

Et puis, nous passerons les details, mais nous avons entrainé notre model sur les 999 permieres images (avec un temps de calcul de pres de 2h, en local évidemment pour ne pas faire planter jupyter). Vous comprendrez que nous ne le referons pas immediatement  
Nous avons simplement, là encore, réutilisé le code du TP

```{code-cell} ipython3
X = np.array(df_clean.drop(['class'], axis=1)).reshape((999, 178, 218, 3))
y = np.array(df_clean["class"])
classes = np.unique(y)
class_to_class_number = { cls: number for number, cls in enumerate(classes) }
y_onehot = np.zeros((len(y), len(np.unique(y))))
for i, label in enumerate(y):
    y_onehot[i, class_to_class_number[label]] = 1
opt = keras.optimizers.Adam(learning_rate=0.01)
myneuralnet.compile(loss='categorical_crossentropy', metrics=["accuracy"], optimizer=opt)
test = np.array(y == 1, dtype = int)
X_train = np.concatenate((X[:165], X[333:333+ 79]), axis = 0)
y_train = np.concatenate((y_onehot[:165], y_onehot[333:333+ 79]), axis = 0)

X_test = np.concatenate((X[165:333], X[333+ 79:]), axis = 0)
y_test = np.concatenate((y_onehot[165:333], y_onehot[333+ 79:]), axis = 0)
```

```{code-cell} ipython3
from sklearn.model_selection import StratifiedKFold
import pdb
stop = pdb.set_trace
def create_model():
    myneuralnet = keras.Sequential(
    [
        mobilenet,
        GlobalAveragePooling2D(),
        Dense(64, activation="relu", name=f"layer1"),
        Dense(64, activation="relu", name=f"layer2"),
        Dense(2, activation="softmax",name=f"layer5"),
    ])
    myneuralnet.build((None,64,64,3))
    opt = keras.optimizers.Adtest = np.array(y == 1, dtype = int)
    myneuralnet.compile(loss='categorical_crossentropy', metrics=["accuracy"], optimizer=opt)
    return myneuralnet

def train_evaluate(model, x_train, y_train, x_test, y_test):
    history = model.fit(x_train, y_train, epochs = 10, shuffle = True, batch_size=20)
    return model.evaluate(x_test, y_test)
```

```{code-cell} ipython3
'''kFold = StratifiedKFold(n_splits=10)
scores = np.zeros(10)
idx = 0
for train, test in kFold.split(X, y):
    model = create_model()
    scores[idx] = train_evaluate(model, X[train], y_onehot[train], X[test], y_onehot[test])[1]
    idx += 1
print(scores)
print(scores.mean())'''
```

Il est difficile pour nous de justifier chaque choix fait lors de cette étape, dans la mesure où ce cours ne s'est pas vraiment étendu sur le sujet. Par ailleurs nous nous somme lancé un peu tard dans la decouverte de cet outil

```{code-cell} ipython3
model = create_model()
```

```{code-cell} ipython3
model.load_weights("save")
```

On remarque en utilisant le model sur l'ensemble d'images utilisées pendant l'entrainement que la deuxieme composante de la valeur de retour correspond au degré de "sourire" de l'image : plus cette deuxieme composante est proche de 1, plus la personne a de chance de sourire.

```{code-cell} ipython3
predict = model.predict(X)
for i in range(len(y)): 
    print(y[i], end=' : ')
    print(predict[i][1])
```

+++ {"slideshow": {"slide_type": "slide"}}

## Résultats

### Observations

+++

Par simple curiosité, et puisque nous avions pres de 200 000 images à notre disposition, nous avons essayé de tester notre model sur des images ayant servi à l'entrainement (que ce soit dans l'ensemble de test ou non), et puis d'autres images completement inconnues.  
Le code suivant prend ~1min à s'executer :

```{code-cell} ipython3
error = 0
depart = 1
arrivee = 51
for i in range(depart,arrivee):
    strimage = f"{i:06d}.jpg"
    test = load_images(dataset_dir, strimage)
    serietest = np.array(test.apply(image_to_series)).reshape((1, 178, 218, 3))
    error += round(model.predict(serietest)[0][1])*2-1 != attributes["Smiling"][strimage]

print("###################", error/(arrivee-depart-1))
```

```{code-cell} ipython3
error = 0
depart = 1000
arrivee = 1050
for i in range(depart,arrivee):
    strimage = f"{i:06d}.jpg"
    test = load_images(dataset_dir, strimage)
    serietest = np.array(test.apply(image_to_series)).reshape((1, 178, 218, 3))
    error += round(model.predict(serietest)[0][1])*2-1 != attributes["Smiling"][strimage]

print("###################", error/(arrivee-depart-1))
```

L'échantillion de 50 images est petit pour faciliter les calculs lors de la presentation, mais nous avons essayé sur 1000 images et le constat est le même : pres de 25% d'erreurs de prediction sur des images totalement inconnues

+++

### Interprétations

+++

Ces erreurs peuvent s'expliquer peut etre par de l'overfitting (notre méconnaissance de l'outil utilisé peut en etre la cause)ou de mauvais hyperparametres (la encore par notre maitrise imparfaite de tensorflow).  

On peut aussi envisager le fait que la source de cet écart important soit le nombre d'images utilisées : 999 reste peu pour quelque chose d'aussi complexe que notre projet.

+++ {"slideshow": {"slide_type": "slide"}}

## Discussion

+++

Avant tout il parait clair que les difficultés ont été nombreuses : le projet a pris un trajectoire completment differente de ce qui était prévu, alors que la soutenance allait bientot arriver. Par ailleurs, dans cette deuxieme partie, il est clair que travailler sur jupyter est quelque chose de completement contreproductif. Les biais du jeu de donnée semblent evidents (il s'agit de visages de celebrités, pas de personnes du quotidien), et le fort taux d'erreur sur des images inconnues nous confortent dans l'idée que ce model n'est pas vraiment utilisable en pratique. Enfin, dans ce projet nous avons pu voir les limites des attributs utilisant des heuristiques.

+++

## Conclusion
