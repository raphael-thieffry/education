---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

+++ {"slideshow": {"slide_type": "slide"}}

# Exemple jouet de piratage par débordement

+++ {"slideshow": {"slide_type": "notes"}}

Le programme suivant implante un écran de connexion simple
qui demande à l'utilisateur d'entrer un mot de passe et le
compare avec le contenu de la variable `motDePasseSecret`,
et répète tant que le bon mot de passe n'a pas été fourni.

**Détail technique**: il se trouve que, pour minimaliser
l'exemple, nous avons recours à des tableaux `C` de caractères
plutôt que des `string` pour stocker le mot de passe et le
mot de passe secret. D'où le `char motDePasseSecret[]`. Vous
en saurez plus au deuxième semestre, mais vous pouvez ignorer
la distinction pour le moment.

**Instructions:**
1.  Essayez le programme suivant en saisissant successivement
    les mots de passe «coucou» et «s3*iA3».
2.  Essayez le programme suivant en saisissant successivement
    les mots de passe «ouvre!», «Sesame,ouvre!», et «ouvre!».

```{code-cell}
---
slideshow:
  slide_type: fragment
---
#include <iostream>
using namespace std;
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
char motDePasse      [] = "XXXXXX";
char motDePasseSecret[] = "s3*iA3";
```

```{code-cell}
---
slideshow:
  slide_type: fragment
---
do {
    cout << "Entrez le mot de passe: " << endl;
    cin >> motDePasse;
} while ( string(motDePasse) != string(motDePasseSecret) );

cout << "Connexion réussie. Bienvenue chef!" << endl;
```

+++ {"slideshow": {"slide_type": "slide"}}

## Explications

<div class="alert alert-primary">

Bien sûr, «Sésame» n'est pas une incantation magique. Il y a une
explication derrière ce piratage réussi. Pour la comprendre, il vous
faudra d'abord avoir lu le début du cours
[Modèle de mémoire et tableaux](cours-memoire-tableaux.md).

</div>

+++ {"slideshow": {"slide_type": "fragment"}}

Les deux tableaux sont de longueurs fixes, et le début du tableau
`motDePasseSecret` se trouve être 7 cases après le début du tableau
`motDePasse`. On peut retrouver cette information par le calcul
suivant dit d'*arithmétique de pointeurs* (vous verrez plus tard
pourquoi):

```{code-cell}
---
slideshow:
  slide_type: fragment
---
motDePasseSecret - motDePasse
```

+++ {"slideshow": {"slide_type": "fragment"}}

De ce fait, lorsque l'attaquant saisi «Sesame,ouvre!» cela déborde de
`motDePasse`: le caractère «,» est écrit juste après `motDePasse`, et
«ouvre!» est écrit dans `motDePasseSecret`.  Cette dernière variable
est donc *corrompue*: l'attaquant a pu y mettre le mot de passe de son
choix à la place de celui d'origine.

```{code-cell}
---
slideshow:
  slide_type: fragment
---
motDePasseSecret
```

+++ {"slideshow": {"slide_type": "fragment"}}

Du coup, à la tentative de connexion suivante, le mot de passe
«ouvre!» est accepté.
