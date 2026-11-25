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

# Fichiers et flux

## Prélude

### Résumé des épisodes précédents …

Pour le moment nous avons vu les concepts suivants:

-   Instructions conditionnelles et itératives
-   Fonctions (avec documentation et tests)
-   Variables, tableaux (2D), collections

Pourquoi aller plus loin?

+++

### Étude de cas: afficher un annuaire

+++

Revenons sur le programme que nous avions écrit pour afficher un annuaire:

```{code-cell}
#include<vector>
#include<iostream>
using namespace std;

vector<string> noms = {
    "Jeanne", 
    "Franck", 
    "Marie", 
    "Joël"
};
vector<string> telephones = {
    "04 23 23 54 56", 
    "03 23 42 34 26", 
    "06 52 95 56 06",
    "07 23 63 92 38"
};

for (int i=0; i < noms.size(); i++) {
    cout << noms[i] << " " << telephones[i] << endl;
}
```

Imaginons maintenant que le carnet de contact sur nos téléphones
adopte la même approche. Les données étant une partie intégrante
du programme, nous devrions chacun avoir un programme différent,
alors que seules les données changent d'une personne à l'autre.

De plus, toute modification dans l'annuaire est volatile:
toute modification qui a pu avoir lieu pendant l'exécution
du programme (par exemple l'ajout d'un contact) est perdue
au moment où celui-ci s'arrête.

Nous avons donc besoin:
- d'une séparation claire entre programme et données;
- d'un stockage persistant des données.

+++

C'est ce que les fichiers vont nous apporter. On voudrait
pour notre annuaire avoir:

+++

-   Un fichier `annuaire.txt`:

    ``` default
    Jean-Claude 0645235432
    Alban       0734534534
    Tibo        +1150343234
    Célestin    0634534534
    ```

-   Un programme

+++

Reste à définir la notion de fichier et à voir comment les manipuler en C++.

+++

## Fichiers

### Qu’est-ce qu’un fichier

Un **fichier informatique** est, au sens commun, une collection
d’informations numériques réunies sous un même **nom**, enregistrées sur
un support de stockage tel qu’un disque dur, un CD-ROM ou une bande
magnétique, et manipulées comme une unité.

Techniquement, un fichier est une **information numérique** constituée
d'une **séquence d’octets**, c'est-à-dire d'une séquence de nombres,
permettant des usages divers.

+++

En bref, c'est comme la mémoire, mais en persistant!

De même que le type d'une variable indique comment l'information
est encodée dans la mémoire, le **format du fichier** indique
comment l’information y est encodée:

+++

Voyons maintenant comment on peut écrire et lire dans un fichier.

+++

### Écriture dans un fichier

+++

L'exemple suivant écrit `Noel 42` dans le fichier `bla.txt`:

```{code-cell}
#include <fstream>
using namespace std;
```

```{code-cell}
ofstream  fichier;                       // Déclaration
```

```{code-cell}
fichier.open("bla.txt");                 // Ouverture
```

```{code-cell}
fichier << "Noel " << 42 << endl;        // Écriture
```

```{code-cell}
fichier.close();                         // Fermeture
```

**À retenir**:

Écrire dans un fichier se fait  en **Quatre étapes**:

1.  Déclaration
2.  Ouverture du fichier
3.  Écriture
4.  Fermeture du fichier

+++

### Lecture depuis un fichier

+++

Nous allons maintenant faire l'opération inverse: lire
les informations stockées dans `bla.txt`:

```{code-cell}
#include <fstream>
using namespace std;
```

```{code-cell}
ifstream fichier;         // Déclaration
```

```{code-cell}
fichier.open("bla.txt");  // Ouverture du fichier
```

```{code-cell}
string s;
fichier >> s;             // Lecture
s
```

```{code-cell}
int i;
fichier >> i;
i
```

```{code-cell}
fichier.close();          // Fermeture du fichier
```

**À retenir**:

De même que l'écriture dans un fichier, la lecture se fait en **quatre étapes**:

1.  Déclaration
2.  Ouverture du fichier
3.  Lecture
4.  Fermeture du fichier
