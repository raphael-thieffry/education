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

# État d'un fichier (ou d'un flux)
Jusqu'ici nous avions principalement fait du calcul.
Dans ces derniers, les situations exceptionnelles
sont relativement rares: divisions par zéro,
préconditions, ...

Avec les manipulations de fichiers, nos
programmes commencent à interagir avec leur
environnement extérieur, environnement que nous ne
contrôlons pas forcément. Il va falloir faire face à
des situations exceptionnelles ou entâchées d'inconnues:

- le fichier existe-t-il?
- quelle longueur fait-il?
- est-il écrit correctement?
- y a-t-il suffisament de place sur mon disque?

De ce fait, les opérations peuvent échouer. 

Dans cette feuille, nous allons voir comment détecter
ces échecs pour pouvoir ensuite les gérer. Cela utilisera
la notion d'**état d'un fichier**.

+++

## Exemple: afficher un annuaire contenu dans un fichier

+++

Revenons à notre annuaire; celui-ci est stocké dans un fichier
[annuaire.txt](annuaire.txt) dont voici le contenu:

```{code-cell}
!cat annuaire.txt
```

Pour l'afficher, nous pouvons mettre en pratique ce que nous venons
de voir:

```{code-cell}
#include <iostream>
#include <fstream>
using namespace std;
```

```{code-cell}
ifstream annuaire;
annuaire.open("annuaire.txt");
```

```{code-cell}
string nom;
string tel;
```

```{code-cell}
for ( int i=0; i < 4 ; i++ ) {
    annuaire >> nom;
    annuaire >> tel;
    cout << nom << ": " << tel << endl;
}
```

```{code-cell}
annuaire.close();
```

Mais il y a une **inconnue** sur le fichier: combien contient-il d'entrées?

Notre programme tel quel ne fonctionnera que si le fichier contient
exactement quatre entrées.

+++

Au lieu de lire un nombre fixé d'entrées, nous voudrions lire les
entrées une à une tant que la lecture se passe bien.

+++

### État d’un fichier

Une variable de type fichier peut être dans un **bon état**:

-   «jusqu’ici tout va bien»

ou un **mauvais état**:

-   Fichier non trouvé à l’ouverture, problème de permissions
-   Lecture ou écriture incorrecte
-   Fin du fichier atteinte
-   Plus de place disque

**Syntaxe:**

        if ( fichier ) { ...
        if ( fichier >> i ) { ...

**Sémantique:**

-   Le fichier est-il en bon état?
-   la lecture s’est elle bien passée?

Remarque: si un fichier n'est pas en bon état, il est bien
entendu possible de demander plus d'informations au système
pour en déterminer la cause. Pour ce semestre, le test de bon
état sera suffisant pour nos besoins.

+++

### Exemple: Afficher un annuaire contenu dans un fichier

+++

Voici notre programme d'affichage d'annuaire réécrit pour
lire dans le fichier tant que le fichier est en bon état.
C'est-à-dire tant que la lecture de l'entrée se passe bien.

```{code-cell}
#include <iostream>
#include <fstream>
using namespace std;
```

```{code-cell}
ifstream annuaire;
annuaire.open("annuaire.txt");
```

```{code-cell}
string nom;
string tel;
```

```{code-cell}
while ( annuaire >> nom  and  annuaire >> tel ) {
    cout << nom << ": " << tel << endl;
}
```

```{code-cell}
annuaire.close();
```

### Bonne pratique: vérifier l’état d’un fichier

+++

L'autre inconnue est: le fichier existe-t-il? Une bonne pratique est
de toujours vérifier l'état d'un fichier après toute opération
pouvant échouer, et notamment l'ouverture:

```{code-cell}
#include <iostream>
#include <fstream>
using namespace std;
```

```{code-cell}
ifstream fichier;
```

```{code-cell}
fichier.open("annuaire.txt"); // Un fichier existant
```

```{code-cell}
if ( not fichier ) {
    cout << "Erreur à l'ouverture" << endl;
}
```

```{code-cell}
fichier.close();
```

```{code-cell}
fichier.open("oups.txt");    // Un fichier non existant
```

```{code-cell}
if ( not fichier ) {
    cout << "Erreur à l'ouverture" << endl;
}
```

Pour mieux signaler cette situation exceptionnelle, il est recommandé d'utiliser les **exceptions**,
que nous avons introduites lors du [cours précédent](../Semaine7/cours-exceptions.md):

```{code-cell}
#include <stdexcept>
```

```{code-cell}
if ( not fichier ) {
    throw runtime_error("Erreur à l'ouverture du fichier");
}
```

## Résumé
Lorsque l'on manipule des fichiers, les opérations sont
succeptibles d'échouer. Dans cette feuille, nous avons vu que la notion
d'**état de fichier** permet de détecter de tels échecs
pour les traiter. Il est fortement recommandé de
**systématiquement vérifier l'état du fichier après toute
opération pouvant échouer**, et tout particulièrement
après l'ouverture d'un fichier, et de **signaler un tel
échec au moyen d'une exception**.

La notion d'état d'un fichier peut aussi être mise à profit
avec l'idiome usuel «lire dans un fichier tant que la lecture se passe bien».
