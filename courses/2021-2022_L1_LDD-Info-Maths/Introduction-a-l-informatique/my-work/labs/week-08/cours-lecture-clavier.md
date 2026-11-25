---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

# Cours: lecture depuis le clavier

Avant de voir comment lire et écrire dans un fichier,
nous avions vu comment afficher; c'est-à-dire écrire
à l'écran au moyen de `cout`. Nous avons occasionnellement
vu comment lire depuis le clavier `cin`. Voici l'occasion
de le formaliser.

## Exemple

```{code-cell}
#include <iostream>
using namespace std;
```

```{code-cell}
string nom;
cout << "Comment t'appelles-tu?" << endl;
cin >> nom;
cout << "Bonjour " << nom << "!" << endl;
```

## Syntaxe et sémantique

**Syntaxe:**

Lecture d’une variable:

          cin >> variable;

**Sémantique:**

-   Lit une valeur du type approprié sur le clavier
-   Affecte cette valeur à la variable
