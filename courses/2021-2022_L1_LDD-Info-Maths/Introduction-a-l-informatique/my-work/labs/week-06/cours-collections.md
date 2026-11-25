---
jupytext:
  notebook_metadata_filter: rise
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++14
  language: C++14
  name: xcpp14
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
  scroll: true
  slideNumber: true
  start_slideshow_at: selected
  transition: none
  width: 90%
---

+++ {"slideshow": {"slide_type": "slide"}}

# Collections et boucle for each

+++ {"slideshow": {"slide_type": "subslide"}}

## Quelques exemples de collections

+++ {"slideshow": {"slide_type": "fragment"}}

### Rappel: tableaux (`vector`)

+++ {"slideshow": {"slide_type": "fragment"}}

Nous avons vu qu'un tableau (`vector` en C++) regroupe
plusieurs valeurs dans un ordre donné,
en tenant compte des répétitions:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
#include<vector>
using namespace std;
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
vector<int> v = { 3, 2, 5, 2 };
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
v
```

+++ {"slideshow": {"slide_type": "fragment"}}

Cela donne un sens au i-ème élément d'un tableau:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
v[3]
```

+++ {"slideshow": {"slide_type": "fragment"}}

Un tableau est un exemple de **valeur composite homogène**,
ou **collection** qui regroupe plusieurs valeurs
d'un même type. 

Il existe d'autres types de collections. Voyons quelques exemples.

+++ {"slideshow": {"slide_type": "subslide"}}

### Ensembles (`set`)

+++ {"slideshow": {"slide_type": "fragment"}}

Lorsque l'on souhaite ne tenir compte ni de l'ordre, ni des
répétitions -- comme dans un ensemble mathématique -- on peut
utiliser un `set`:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
#include <set>
using namespace std;
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
set<int> s = { 3, 2, 5, 2};
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
s
```

+++ {"slideshow": {"slide_type": "fragment"}}

Du coup, accéder au i-ème élément n'a pas de sens:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
s[1]
```

+++ {"slideshow": {"slide_type": "subslide"}}

### Multi-ensembles (`multiset`)

+++ {"slideshow": {"slide_type": "fragment"}}

Si l'on ne souhaite pas tenir compte de l'ordre mais tout de même
des répétitions, on peut utiliser un multi-ensemble (`multiset`):

```{code-cell}
---
slideshow:
  slide_type: fragment
---
multiset<int> m = { 3, 2, 5, 2 };
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
m
```

+++ {"slideshow": {"slide_type": "subslide"}}

## Boucle foreach

+++ {"slideshow": {"slide_type": "fragment"}}

Une opération omniprésente sur une collection est de parcourir
toutes ses valeurs: jusqu'ici on l'a fait à l'aide d'un index:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
#include<vector>
#include<iostream>
using namespace std;
vector<int> v = { 3, 2, 5, 2 };
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
for ( int i=0; i < v.size(); i++ )
    cout << v[i] << endl;
```

+++ {"slideshow": {"slide_type": "fragment"}}

C'est un peu lourd, et sujet à erreurs. Surtout, cela ne se généralisera pas aux ensembles! (pourquoi?).

+++ {"slideshow": {"slide_type": "fragment"}}

À la place nous allons litérallement écrire «pour toute `valeur` dans `v` faire ...»:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
for ( auto valeur: v )
    cout << valeur << endl;
```

+++ {"slideshow": {"slide_type": "fragment"}}

C'est l'équivalent du `for valeur in v:` de Python.
Et cela fonctionnera tout aussi bien pour toute autre collection:

```{code-cell}
#include<set>
set<int> s = { 3, 2, 5, 2 };
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
for ( auto valeur: s )
    cout << valeur << endl;
```

```{code-cell}
multiset<int> m = { 3, 2, 5, 2 };
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
for ( auto valeur: m )
    cout << valeur << endl;
```

+++ {"slideshow": {"slide_type": "subslide"}}

### Digression: à propos de `auto` ♣

Vous vous demandez peut-être quelle est la
signification de `auto`?

On est en train de déclarer une nouvelle variable.
Il faut donc préciser son type. On pourrait très
bien mettre `int` ci-dessus puisque l'on manipule
des collections d'entiers:

```{code-cell}
---
slideshow:
  slide_type: fragment
---
for ( int valeur: v )
    cout << valeur << endl;
```

+++ {"slideshow": {"slide_type": "fragment"}}

`auto` est un type spécial qui indique à C++ de
sélectionner automatiquement le type adéquat en
fonction du contexte ce qui est facile ici.

```{code-cell}
---
slideshow:
  slide_type: fragment
---
auto i = 1;
i
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
auto pi = 3.14;
pi
```
