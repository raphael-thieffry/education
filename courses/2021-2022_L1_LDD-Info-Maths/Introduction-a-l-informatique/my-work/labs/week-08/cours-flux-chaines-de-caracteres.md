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

# Lecture et écriture dans des chaînes de caractères

Nous avons vu comment lire et écrire facilement des
valeurs de types divers (entiers, flottants) dans un fichier texte.
Sous le capot cela a requis des opérations de natures différentes:
1. interactions avec le système pour lire et écrire du texte
  dans un fichier
2. conversions de valeurs en texte et réciproquement

Ne pourrait-on pas utiliser ce deuxième point pour lire et
écrire des valeurs dans des chaînes de caractères?
Après tout, elles contiennent du texte elles aussi!
Allons-y.

+++

Au préalable, nous aurons besoin de la bibliothèque suivante:

```{code-cell}
#include <sstream>
using namespace std;
```

## Lecture depuis une chaîne de caractères

+++

### Exemple

+++

La chaîne de caractère suivante contient -- sous forme de texte -- plusieurs nombres:

```{code-cell}
string s = "1 2 4 8 16";
```

On souhaiterait extraire ces nombres en les convertissant en entiers.
Pour cela on créé un *flux* de type `istringstream` (nous verrons
dans la feuille suivante ce qu'est un flux et la signification du
nom `istringstream`):

```{code-cell}
istringstream flux = istringstream(s)
```

Maintenant il est possible de lire le premier nombre, en procédant
comme s'il était dans un fichier:

```{code-cell}
int i;
```

```{code-cell}
flux >> i;
i
```

Lorsque l'on effectue de nouvelles lectures, les nombres suivants sont lus un à un:

```{code-cell}
flux >> i;
i
```

```{code-cell}
flux >> i;
i
```

```{code-cell}
flux >> i;
i
```

L'exemple suivant illustre que l'on peut lire successivement des valeurs de types mixtes,
et que l'on peut chaîner ces lectures:

```{code-cell}
string s = "truc 33 bidule 2.5 reste"
```

```{code-cell}
istringstream flux = istringstream(s);
```

```{code-cell}
string a, b;
int i;
float f;
```

```{code-cell}
flux >> a >> i >> b >> f;
```

```{code-cell}
a
```

```{code-cell}
b
```

```{code-cell}
i
```

```{code-cell}
f
```

### Syntaxe et sémantique

**Syntaxe:**

```c++
          istringstream flux = istringstream(s);
          flux >> variable1;
          flux >> variable2;
          ...
```

+++

**Sémantique**:

Affecte aux variables `variable1`, `variable2`, ... les valeurs lues successivement depuis la chaîne de caractères `s`, en tenant compte de leurs types respectifs.

+++

## Écriture dans une chaîne de caractères
Réciproquement, on peut souhaiter écrire le contenu de
variables non pas directement à l'écran ou dans un fichier
mais dans une chaîne de caractères. Le principe sera 
le même que pour une lecture.

+++

### Exemple

+++

On commence par définir un flux de type `ostringstream` (là encore, nous verrons dans la feuille suivante la signification du nom de ce type):

```{code-cell}
ostringstream flux;
```

Nous pouvons maintenant écrire dans ce flux:

```{code-cell}
flux << 3.53 << " coucou " << 1 << endl;
flux << 42 << endl;
```

et enfin extraire la chaîne de caractère produite:

```{code-cell}
string s = flux.str();
s
```

### Syntaxe et sémantique

**Syntaxe:**

```c++
          ostringstream flux;
          flux << variable1;
          flux << variable2;
          string s = flux.str()
```

+++

**Sémantique**:

Construit une chaîne de caractères `s` en écrivant successivement le contenu des variables `variable1`, `variable2`, ... en tenant compte de leurs types respectifs.

+++

## Application typique: séparation calcul et entrées sorties

Ce que nous venons de voir sera très utile pour séparer
proprement ce qui relève du **calcul** et ce qui relève des **entrées-sorties**.
Supposons par exemple que nous souhaitions afficher
joliment une entrée d'un annuaire:

```{code-cell}
using namespace std;
#include <iostream>
#include <sstream>
```

```{code-cell}
void afficheEntreeAnnuaire(string nom, string prenom, string tel) {
    cout << "Nom: " << nom 
         << ", Prénom: " << prenom
         << ", Téléphone: " << tel;
}
```

```{code-cell}
afficheEntreeAnnuaire("Lovelace", "Ada", "07 23 23 23 23")
```

- Comment réutiliser cette fonction pour écrire le texte non pas à l'écran mais dans un fichier?
- Comment tester cette fonction?

+++

Cela est rendu difficile par le mélange de deux actions
de natures différentes dans une seule fonction:
1. Construire le texte représentant l'entrée dans l'annuaire.
2. Afficher ce texte à l'écran.

+++

Il faut donc **séparer** ces deux actions. L'écriture dans une chaîne
va nous aider à le faire.

+++

La fonction suivante se concentre sur la construction du texte représentant
l'entrée dans l'annuaire:

```{code-cell}
string formateEntreeAnnuaire(string nom, string prenom, string tel) {
    ostringstream flux;
    flux << "Nom: " << nom 
         << ", Prénom: " << prenom
         << ", Téléphone: " << tel;
    return flux.str();
}
```

Le texte produit est **renvoyé** par la fonction au lieu d'être **affiché**.
Nous pouvons donc maintenant:

- l'affecter à une variable:

```{code-cell}
string s = formateEntreeAnnuaire("Lovelace", "Ada", "07 23 23 23 23")
```

- l'afficher:

```{code-cell}
cout << s << endl;
```

- calculer avec:

```{code-cell}
"- " + s
```

- ou nous en servir pour toute autre opération, comme l'écrire dans un fichier.

+++

De plus, nous pouvons maintenant aisément tester notre fonction:

```{code-cell}
CHECK( formateEntreeAnnuaire("Lovelace", "Ada", "07 23 23 23 23")
       == "Nom: Lovelace, Prénom: Ada, Téléphone: 07 23 23 23 23" );
```

## Résumé
Dans cette feuille, nous avons vu comment **lire et écrire** des données
de types divers **dans des chaînes de caractères**. Nous l'avons
appliqué pour mieux séparer **fonctions qui calculent** et **fonctions
d'entrées-sorties**. Enfin nous avons noté que
l'on utilise la même syntaxe que pour lire et écrire dans un fichier
ou pour interagir avec l'utilisateur. Cela est rendu possible par le concept
de flux qui est le sujet de la [feuille suivante](cours-flux.md).
