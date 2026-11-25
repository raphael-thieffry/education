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
  header: <div><img src='media/logoParisSaclay.png' width='150' align=right></div>
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

<center>

# Cours: Initiation à la Science des Données
## VI-ME-RÉ-BAR

</center>

<center>Fanny Pouyet</center>

<center>L1 Informatique</center>

<center>Janvier - Mai 2022</center>

+++ {"slideshow": {"slide_type": "slide"}}

**Précédemment**

* Définition et objectifs de la science des données
* Découverte des bibliothèques `Pandas`, `Matplotlib`, `Seaborn` et
  `Statsmodels`
* Observation des données

**Cette semaine**

* Chaîne de traitement en analyse des données
* Un peu d'interprétation des résultats

Remerciements: Isabelle Guyon

+++ {"slideshow": {"slide_type": "slide"}}

## Chaine de traitement en analyse des données

* **EXPLORATION**

    1. Observer les données : Combien d'instances a-t-on ? (CM2)
    2. Identifier la question posée. (CM2)
    3. Comprendre ce qu'est un attribut (feature) voire en calculer d'autres (CM3) pour répondre à la question.
    

* ***VI*sualisation** , ***ME*sures**, ***RÉ*férences** et ***BAR*res d'erreurs**  

VI-ME-RÉ-BAR (CM3)

+++ {"slideshow": {"slide_type": "slide"}}

* **OBSERVATION** 

La conclusion se fait en 2 temps: l'observation de nos résultats 

* **INTERPRÉTATIONS**

Et leur interprétation. Qu'est ce qu'on peut raconter ?

+++ {"slideshow": {"slide_type": "slide"}}

## Problématique

Nous allons aborder un problème de classification automatique d'images de
fruits par apprentissage statistique (*machine learning*). A part
l'intérêt pédagogique, quelle peut être l'utilité d'étudier un tel
problème ?

https://youtu.be/h0-NS3z-EXo

<center><img src="media/fruits.jpeg" width="600"> 
https://observatoire-des-aliments.fr/wp-content/uploads/2015/09/fruit8.jpg</center>

+++ {"slideshow": {"slide_type": "slide"}}

## Connaissez-vous ce qu'est l'apprentissage statistique? l'apprentissage profond? l'AI ?

* Vous en avez déjà entendu parler ? Êtes vous capable de le définir ?
* Voulez vous en faire ? Si oui, l'utiliser ou le développer ?
* Connaissez-vous des entreprises qui en font ? Des exemples
  d'application ?

+++ {"slideshow": {"slide_type": "slide"}}

<center><img src="media/alphafold.png" width="400"> 
La dernière révolution en AI : https://www.youtube.com/watch?v=B9PL__gVxLI&ab_channel=YannicKilcher </center>

+++ {"slideshow": {"slide_type": "slide"}}

### Définition de l'apprentissage statistique

L'apprentissage statistique (*Machine Learning*), combinant
statistiques et informatique, est au coeur de la science des données
et de l’intelligence artificielle. L'objectif est d'obtenir une
fonction prédictive à partir d'un jeu de données; ici: la
classification d'images de fruits.

### Applications diverses 

* moteurs de recherche
* banque
* médecine
* énergie

+++ {"slideshow": {"slide_type": "slide"}}

### Overview - Marcelle

*Marcelle* est une boîte à outil qui permet de concevoir des
applications interactives d'apprentissage statistique dans le
navigateur. Elle permet de programmer le flux de données (*pipeline*)
depuis, vers les modèles) et d'interagir sur les composants du flux
avec des outils interactifs (visualisations, choix des paramètres
etc.).  Les applications ainsi réalisés peuvent être utilisés dans des
contextes variés:
* **Pédagogie**: démonstrations et utilisation de l'apprentissage
  machine sans programmation.
* **Recherche**: Conception et évaluation de nouvelles interactions
  avec les algorithmes de ML
* **Collaboration** entre différents domaines. Par exemple, un médecin
  peut s'occuper de vérifier les données tandis qu'un chercheur en
  apprentissage statistique conçoit le modèle. Ils peuvent collaborer
  via Marcelle.

<center><img src="media/marcelle.png" width="400"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

### Overview - Chaîne de Traitement

Classification en direct de pommes et de bananes à l'aide d'un exemple
utilisant [Marcelle](https://www.lisn.upsaclay.fr/~tsanchez/ISD_CM3/)

*Crédits: Jules Françoise, Baptiste Caramiaux, Téo Sanchez. Marcelle: Composing Interactive Machine Learning Workflows and Interfaces. Annual ACM Symposium on User Interface Software and Technology (UIST ’21), Oct 2021, Virtual. DOI: 10.1145/3472749.3474734 (opens new window).

*N.B: Marcelle* est développé à Saclay par J. Francoise, B. Caramiaux
et T. Sanchez.  Vous pouvez aller sur le site pour tester les exemple
vous même (ne fonctionne pas sur mobile):
[https://marcelle.dev/](https://marcelle.dev/).

+++ {"slideshow": {"slide_type": "skip"}}

Exemple de questions:
- combien d'instance ?
- pas d'infos d'attributs
- notion de matrice de confusion (*confusion matrix*): combien on a
  juste / combien on a faux?

+++ {"slideshow": {"slide_type": "slide"}}

### Notre jeu de données (CM3 et TP3)

Nous cherchons à classer des pommes et des bananes.

<center><img src="media/apples_bananas.png" width="600"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

**EXPLORATION**

* 10 images de chaque type
* Label / Etiquette : l'étiquetage est le processus d'identification
  des données brutes. Cet étiquetage permet d'estimer l'efficacité de
  classification du modèle prédictif.

Quel était l'étiquette sur le jeu de données du titanic ?

* Question : séparer correctement les pommes des bananes.
* Attributs : les données que nous allons traiter
* Etiquettes : l'appartenance aux classes de nos images

+++ {"slideshow": {"slide_type": "slide"}}

## Comment peut-on manipuler des images en Python ?

Une image est un tableau de pixels

Dans le TP, un pixel de couleur est défini comme la superposition de
quatre couches d'information, RGBA (Red Green Blue Alpha): trois
couleurs + l'opacité (alpha).

<center><img src="media/features_images.svg" width="200"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

<center><img src="media/cartesRGB.svg" width="800"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

<center><img src="media/histograms_colors.svg" width="800"> </center>
On peut aussi visualiser les données comme un histogramme. Comment le lisez vous ?

+++ {"slideshow": {"slide_type": "slide"}}

<center><img src="media/histograms_colors_trueapple.svg" width="800"> </center>
Refaisons l'exercice avec une image d'une vraie pomme.

+++ {"slideshow": {"slide_type": "slide"}}

### Des images aux dataframes

Vous apprendrez à passer d'une image à un tableau dans la feuille
[Manipulation d'images](../Semaine4/2_images.md) du TP4. Le tableau
est en 3D car on a:
- le nombre de pixels en largeur (32 dans notre cas)
- le nombre de pixels en hauteur (32 dans notre cas)
- les quatre couches: R, G, B et A

Quelle bibliothèque (qu'on a déjà mentionnée) va-t-on utiliser lors du
TP3 ? Combien de cases a-t-on par image ?

+++ {"slideshow": {"slide_type": "fragment"}}

Bibliothèque : 
* `Numpy`

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
#Nombre d'infos "raw" par image
32*32*4
```

+++ {"slideshow": {"slide_type": "slide"}}

## Attributs (*features*)

Finalement, ce qui nous intéresse ce ne sont pas les 4096 cases mais
seulement celles associées au fruit et pas au fond (au décor) à partir
desquelles nous pourrons calculer des attributs explicites tels que:

* la couleur;
* la forme du fruit.

Lors du CM4/TP4, nous apprendrons à extraire automatiquement ce genre
d'information de nos images. Pour aujourd'hui, nous supposons
simplement qu'elles sont disponibles.

```{code-cell} ipython3
---
slideshow:
  slide_type: slide
---
import pandas as pd                   

df = pd.read_csv("media/preprocessed_data.csv", index_col=0)
df.head()
```

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
df.shape
```

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
df.describe()
```

+++ {"slideshow": {"slide_type": "slide"}}

### Description de la table de données

* 20 instances
* 3 attributs dont un label (lequel ?):
    * *redness* : couleur, à quel point le fruit est rouge
    * *elongation* : elongation, la ratio entre hauteur et longeur
    * *fruit* : 1 c'est une pomme, -1 c'est une banane

+++ {"slideshow": {"slide_type": "slide"}}

### Observation - Objectif en TP

Faire la description de la table, comme vu la semaine dernière :
* quelle est la rougeur moyenne des pommes et des bananes ?
* quelle est l'élongation moyenne des pommes et des bananes ?
* quelles sont les échelles de valeurs des attributs ? Peut-on les comparer entre elles ?

+++ {"slideshow": {"slide_type": "slide"}}

## Standardisation des données

Géométriquement, standardiser c'est:
* translater la distribution à droite ou à gauche
* étendre ou compresser les données en largeur

<center><img src="media/standarization.png" width="600"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

### Définition et motivation
La standardisation revient à:
1. **centrer** les valeurs d'un attribut autour de sa moyenne. Si la
   valeur est >0 alors elle est plus grande que la moyenne (<0, plus
   petite que la moyenne). **Chaque attribut standardisé aura une
   moyenne de 0.**
2. **réduire** les valeurs d'un attribut. Une valeur absolue de $v=2$
   (par exemple) veut dire qu'on est à 2 écart-types de la
   moyenne. **Chaque attribut standardisé (chaque colonne) aura un
   écart-type de 1.**

*Motivation*: La standardisation permet d'interpréter la valeur d'un
attribut (*i.e.* d'une case) indépendamment de son échelle de valeur
(range).

+++ {"slideshow": {"slide_type": "slide"}}

Mathématiquement cela revient à calculer pour chaque attribut $X$:

$ X_{stz} = (X - \mu)/\sigma$

La **standardisation** permet de mettre en évidence les valeurs
aberrantes (*outliers*) qui auront une valeur largement différente de
0 (loin de la moyenne).

<center><img src="media/standarization.svg" width="800"> </center>

+++ {"slideshow": {"slide_type": "subslide"}}

### Objectifs du TP

* Standardiser les attributs selon la formule présentée (= question
  d'algorithmique en Python). On notera *dfstz* cette
  table. *Remarquez que le label 'fruit' n'a pas à être standardisé;
  c'est un attribut catégoriciel*.

+++ {"slideshow": {"slide_type": "slide"}}

## Étude de nos attributs

En TP vous ferez:
* Calcul des corrélations entre les attributs et le label (= refaire
  comme au TP précédent)
* Représentation et analyse de ces relations à l'aide d'un pairplot
* Observation des résultats
* Interprétation: en quoi les attributs élongation/rougeur permettent
  de différencier les pommes des bananes ?

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
dfstz = (df-df.mean()) / df.std()
#on ne veut pas standardiser le label !
dfstz['fruit'] = df['fruit']
```

+++ {"slideshow": {"slide_type": "slide"}}

## 1. *VI*sualisation

Passons ensuite à l'étape de Visualisation (nouveau). Commençons par
représenter les fruits selon nos 2 attributs:

```{code-cell} ipython3
---
slideshow:
  slide_type: slide
---
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

#Create a label with names instead of -1/1 for the legend
dfstz['Fruits'] = np.where(dfstz['fruit'] == 1, "Pommes", "Bananes")

#Make the plot
sns.scatterplot(data=dfstz, x="redness", y="elongation", hue="Fruits")
```

+++ {"slideshow": {"slide_type": "slide"}}

### Problème de classification

Maintenant que les données ont été observées et préparées, on va
répondre à notre question : peut-on séparer les pommes des bananes ?

Pour cela, on va définir un *modèle* qui selon des *critères*
déterminera la *nature* des fruits:
* le *modèle* permet de faire des prédictions; on veut mesurer ses
  performances
* les *critères* se basent sur les *attributs*
* la *nature* des fruits est encodé par le *label*

+++ {"slideshow": {"slide_type": "slide"}}

#### a. Séparation des attributs et des étiquettes

On va séparer l'information de la table en deux sous-tables:
* $X$ contiendra les attributs pour faire des prédictions
* $Y$ contiendra ce qu'on cherche à prédire: le label

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
X = dfstz[['redness', 'elongation']]
Y = dfstz['fruit']
```

+++ {"slideshow": {"slide_type": "slide"}}

**Notations $X$ et $Y$ :**

Mathématiquement, on cherche une fonction $f$ qui, pour chaque
instance $i$, permet de prédire $Y_i$ en fonction des valeurs $X_i$
des attributs.

On cherche $f$ telle que:
$\forall i, Y_i = f(X_i)$

+++ {"slideshow": {"slide_type": "slide"}}

#### b. Séparation du jeu de données

Afin de mesurer la performance de notre modèle, on le sépare en deux
groupes:
* l'ensemble d'entraînement (*training set*) à partir duquel on
  ajustera (*fit*) les paramètres du modèle

  *Le modèle doit apprendre à partir d'exemples.*

* l'ensemble de test (*test set*) à partir duquel on mesurera la
  performance du modèle.

  *Le modèle est-il capable de classifier de nouveaux fruits, qu'il ne connaissait pas?*
<center><img src="media/test_training_sets.svg" width="600"> </center>

```{code-cell} ipython3
---
slideshow:
  slide_type: slide
---
from sklearn.model_selection import train_test_split

#Separation en training et test set
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.5)

print("Training set:\n",X_train,'\n\n', Y_train)
```

```{code-cell} ipython3
---
slideshow:
  slide_type: slide
---
print("Test set:\n",X_test,'\n\n', Y_test)
```

+++ {"slideshow": {"slide_type": "slide"}}

Représentation des données
<center><img src="media/test_training_scatterplot.svg" width="800"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

## 3. *RE*férence, Modélisation

On peut **enfin** passer à la modélisation. **En fait, la préparation
des données, le calcul des attributs, etc. est ce qui prend le plus de
temps et requiert le plus d'expertise!**

Il existe pléthores de modèles. On va commencer par les $k$ plus
proches voisins mais nous en verrons d'autres au cours de l'UE.

+++ {"slideshow": {"slide_type": "slide"}}

### KNN : $k$-Nearest Neighbors

Le classificateur *$k$-nearest neighbors* est une méthode assez
intuitive, l'objet est définit selon le label majoritaire de ses $k$
voisins. Les résultats changent selon la valeur de $k$ utilisée.

<center><img src="media/knn.svg" width="600"> </center>

Le classificateur KNN est implémenté dans la bibliothèque
`scikit-learn` (notée `sklearn`) dans la classe `KNeighborsClassifier`
de `sklearn.neighbors`. En pratique cela donne:

```{code-cell} ipython3
---
slideshow:
  slide_type: slide
---
from sklearn.neighbors import KNeighborsClassifier

#Posons :
k = 3

# Définissons le modèle KNN avec k=3
my_first_model = KNeighborsClassifier(n_neighbors=k)

# Apprentissage automatique à partir de l'ensemble d'entrainement
my_first_model.fit(X_train, Y_train) 
```

+++ {"slideshow": {"slide_type": "slide"}}

<center><img src="media/knn3_predict.svg" width="800"> </center>

+++ {"slideshow": {"slide_type": "slide"}}

## 4. *ME*sure des performances

L'ensemble de test (*test set*) permet de mesurer les performances an appliquant le modèle ajusté au test. Le modèle détermine si le fruit est une pomme ou pas.

```{code-cell} ipython3
---
slideshow:
  slide_type: fragment
---
Y_test_predicted = my_first_model.predict(X_test)
```

+++ {"slideshow": {"slide_type": "slide"}}

La prédiction correspond-t-elle à la vérité de l'ensemble de *test* ?

Pour mesurer les performances de notre modèle prédictif on peut
compter le nombre d'erreurs:
* **Faux positifs (FP)** : Nombre de bananes (négatif) prises pour des
  pommes (positif) <center><img src="media/falsepositive.svg"
  width="800"> Un exemple de FP du modèle prédictif</center>

+++ {"slideshow": {"slide_type": "slide"}}

* **Faux négatifs (FN)** : Nombre de pommes (positif) prises pour des bananes (négatif)

  <center><img src="media/falsenegative.svg" width="800"> Exemple de FN de notre modèle </center>

+++ {"slideshow": {"slide_type": "slide"}}

|                      | TRUE = Pomme = 1 | FALSE = Banane = -1 |
| -------------------- | ---------------- | ------------------- | 
| PREDICT Pomme = 1    | TP               | FP                  |
| PREDICT Banane = -1  | FN               | TN                  |

Ceci est une **matrice de confusion**.

**TP** = vrai (true) positif; **TN** = vrai (true) négatif

+++ {"slideshow": {"slide_type": "slide"}}

Au total on a $n$ prédictions et $n= TP + TN + FP + FN$

Le **taux d'erreur** $e$ est donc:

$e  = \frac{(FP + FN)}{ n}= \frac{n_{erreurs}}{n_{prédictions}}$

+++ {"slideshow": {"slide_type": "-"}}

En pratique, on va comparer les labels estimés donc *Y_test_predicted*
avec les véritables labels *Y_test*.

```{code-cell} ipython3
e = np.sum((Y_test_predicted != Y_test))  / len(Y_test)
e
```

```{code-cell} ipython3
#Strictement équivalent à
e_v2 = np.mean(Y_test_predicted != Y_test)
e_v2
```

+++ {"slideshow": {"slide_type": "slide"}}

On peut également calculer 

* La **précision de la classification (*accuracy*)**,  a = 1 – e

* Le **Balanced Error Rate, BER** = 0.5 (T1 + T2)
    * avec T1 = Type I error = FP / (TN+FP) 
    * et T2 = Type II error = FN / (TP+FN) 

Le BER est utilisé lorsque le nombre d'échantillons par classe
(pommes/bananes) est déséquilibré car on calcule la moyenne du taux
d'erreur de *chaque* classe. Ce n'est pas le cas ici.

+++ {"slideshow": {"slide_type": "slide"}}

### Objectifs en TP

* Implémenter une fonction `error_rate()` pour automatiser ce calcul
  et l'utiliser.
* Calculer la précision de la classification
* Représenter graphiquement les données et observer les résultats

+++ {"slideshow": {"slide_type": "slide"}}

## 5. *BAR*res d'erreurs et significativité

Enfin, on va évaluer la significativité de nos résultats en calculant
les barres d'erreurs.

L'objectif est de répondre à la question : *A quel point avons-nous
confiance dans notre modèle ?*

C'est seulement **après** cette étape que nous pourrons **interpréter**
les résultats.

Pour ce faire nous cherchons à estimer *la barre d'erreur de notre
taux d'erreur*, notée $\sigma$.

On cherche à déterminer un intervalle de confiance. On peut :

+++ {"slideshow": {"slide_type": "slide"}}

1. Calculer la barre d'erreur **1-$\sigma$** de notre modèle prédictif:

$ \sigma = \sqrt{\bar{e}(1-\bar{e})/n} $, l'écart-type des $e$

En fait, les valeurs de $e$ dépend $n$ des echantillons testés : si
l'on analysait les mêmes données avec le même modèle de nombreuses
fois en ré-échantillonnant les tests, le $e$ varierait. Comment
varierait-il ?

+++ {"slideshow": {"slide_type": "slide"}}

2. Estimer la confiance que l'on a dans le classificateur à partir de
   *réplicats*:

  * répéter $N=100$ ou $1000$ (ou encore plus) fois la séparation
    entre l'ensemble de test et d'entrainement;
  * recalculer la performance du modèle réapprenant.
  
On a donc $N$ taux d'erreurs à partir desquels on peut estimer *la
barre d'erreur de notre taux d'erreur*.

+++ {"slideshow": {"slide_type": "slide"}}

En application du théorème central limite (en mathématiques, voir
[CM4](../Semaine4/CM4.md)), la distribution des $e$ observées par
rééchantillonnage se rapproche d'une courbe gaussiene (loi normale,
courbe en cloche) définies par sa moyenne ($\bar{e}$) et son
écart-type $\sigma$.

On peut calculer le taux d'erreur moyen des réplicats : $\bar{e} =
\frac{\sum_{k=1}^N e_k}{N}$

La **barre d'erreur de la validation croisée (*cross-validation*,
CV)**, $\sigma$ vaut :

$ \sigma^= \sqrt{\frac{ (\sum_{k=1}^N e_k - \bar{e})^2 }{N}}$

La *validation croisée* permet d'estimer la robustesse de la méthode
de classification (ici, le 3-NN) l'écart-type du taux d'erreur du
test. La CV prend en compte la variabilité du training et celle du
test set mais reste un estimateur biaisé du taux d'erreur.

+++ {"slideshow": {"slide_type": "slide"}}

Connaissant la distribution, on peut définir un **intervalle de
confiance** à partir de ces valeurs.

Pour l'interprétation du $\sigma$ cela veut dire que 68% des valeurs
(ici, notre taux d'erreur) seraient compris entre $\bar{e}+\sigma$ et
$\bar{e}-\sigma$. De même, 95% des mesures (valeurs observées)
tomberaient entre $\bar{e}+2\sigma$ et $\bar{e}-2\sigma$.

A noter: plus on veut avoir confiance, plus grand sera l'intervalle de
confiance.

<center><img src="media/tcl.png" width="600">https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_central_limite </center>

+++ {"slideshow": {"slide_type": "slide"}}

### Objectif en TP

* Calculer la barre d'erreur 1-$\sigma$ d'une instance de
  classificateur.
* Implémenter une CV avec 100 réplicats du classificateur
* Interpréter les résultats !

+++ {"slideshow": {"slide_type": "slide"}}

## Conclusions

**Science des données** 
* Chaîne de traitement en analyses des données:
    * on peut synthétiser l'information dans les images en une table
    * préparer les données prend du temps
* L'interprétation des résultats dépend des barres d'erreurs !

**Langage Python 3**
* `sklearn` pour l'apprentissage statistique et les problèmes de classification
* *PIL* pour le traitement d'images (en détail lors du [CM4](../Semaine4.md))

+++ {"slideshow": {"slide_type": "slide"}}

## Perspectives

**CM 4 : Construction & selection d'attributs**
* Retour sur les barres d'erreurs: compréhension, calcul et interprétation
* Extraction d'attributs a partir d'images
* Votre propre jeu de données

**TP 3**
* Observer les attributs
* Calculer un modèle prédictif (prédeterminé: le 1-NN)
* Calculer des barres d'erreur

**Quiz 1**
* Le [premier Quiz](https://ecampus.paris-saclay.fr/mod/quiz/view.php?id=796782)
  (note pour l'UE: 10%) est à faire sur e-campus *avant* le prochain cours ! 
* 2 tentatives, nous garderons la meilleure
* 9 questions
* QCM (plusieurs réponses peuvent être correctes), Vrai/Faux

+++ {"slideshow": {"slide_type": "slide"}}

**TP 4 et 5 : Mini-projet**

Afin de vous préparez sachez que:

* Travail en **binôme**
    * choisissez un binôme dans le même groupe de TP que vous
    * inscrivez-vous [ici](https://codimd.math.cnrs.fr/3f98v4-YT4CN2ktM6_g5lw?both)
* Classification d'**images**
    * Choisissez deux catégories d'images que vous aimeriez classer
      parmi un ensemble fourni en TP3:
        * canards/poulets, zeros/uns, melanomes,  ...
        * il y aura 10 images par classe
