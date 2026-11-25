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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6bc9d6338be13612ac267f51a9a55bfb", "grade": false, "grade_id": "cell-1bfd4fe0c7b1174a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

# Traitement des erreurs et exceptions

Occasionnellement, un programme, ou plus généralement une fonction,
peut rencontrer une situation *exceptionnelle*: c'est-à-dire une
situation qui n'est pas prévue dans les entrées normales. Que faire
dans ce cas? Continuer comme si de rien était pourrait amener toutes
sortes de catastrophes. Renvoyer une valeur arbitraire risquerait
de passer inaperçu par l'utilisateur du programme ou de la fonction.

On souhaite donc arrêter l'exécution de la fonction, en **signalant**
qu'une situation exceptionnelle s'est produite.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0997036774eb3b57298689587c7c4946", "grade": false, "grade_id": "cell-54ac108eb66bf5f3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Exemple: gestion d’entrées invalides

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "73e7dc3ce0f3093f69ed22a3834c28d7", "grade": false, "grade_id": "cell-2a42eeb3d13ce52c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Nous avons vu précédemment la fonction factorielle récursive:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3f4bc4030002f09d5a5163b636fb8e79
  grade: false
  grade_id: cell-f2845efb4e8c1193
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int factorielle(int n) {
    if ( n == 0 ) return 1;
    return n * factorielle(n-1);
}
```

```{code-cell}
factorielle(4)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7de2a4c3ed4f43c7fb49f99ec907cafb", "grade": false, "grade_id": "cell-533b786ae648ea71", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Que se passerait-il si on calculait `factorielle(-1)`?
Cela appellerait `factorielle(-2)` qui à son tour appellerait
`factorielle(-3)`, et ainsi de suite. Jusqu'à ce que le programme
plante. Allez-y, essayez pour voir ci-dessus. Et tenez vous prêt
à redémarer le noyau!

L'entrée `-1` n'est pas prévue par la fonction. C'est une situation
**exceptionnelle** que l'on souhaiterait **signaler** immédiatement et de
façon plus informative que par un simple plantage.

Note: il vous faudra probablement redémarer le noyau avant de
redéfinir factorielle comme ci-dessous

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c992370f41ff375f18fea455563761f4
  grade: false
  grade_id: cell-b58dbae0de2d20f7
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <stdexcept>
using namespace std;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9c4c4cd979917145641212c11850ef0d
  grade: false
  grade_id: cell-a51e9e5f2d9ab521
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int factorielle(int n) {
    if ( n  < 0 ) throw invalid_argument("n doit être positif");
    if ( n == 0 ) return 1;
    return n * factorielle(n-1);
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6d03feff4512fe90d111e9bbeb8de3b5
  grade: false
  grade_id: cell-f07aa79d9ed20984
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(4)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f85e6d5d6548ecff051bb8718cef1dae
  grade: false
  grade_id: cell-306f3e20bff2186c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
factorielle(-1)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ed5da5ceea84e6e9ce825437bb974698", "grade": false, "grade_id": "cell-19bd13a2eea1ce1a", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Maintenant, l'utilisateur est satisfait: l'exécution
de `factorielle` s'est immédiatement arrêté, avec un
message d'erreur explicite sur le problème rencontré.

Nous allons maintenant expliquer les différents
éléments utilisés: `throw` (lancer), `invalid_argument` et
la bibliothèque `stdexcept`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a446f4ba9e68577adf2f03de91e0e865", "grade": false, "grade_id": "cell-d5809a45a8512527", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Signaler une exception

**Syntaxe**:

      throw e;

**Sémantique**:

-   Une situation exceptionnelle que je ne sais pas gérer s’est produite
-   Je m’arrête immédiatement et je préviens mon «chef» (l'utilisateur ou la fonction appelante)
-   On dit qu’on **signale une exception**
-   La situation est décrite par l'exception `e`  
    `e` est un objet quelconque; par exemple une **exception standard**
-   Si à son tour mon «chef» ne sait pas gérer, il prévient son «chef»
-   …
-   Si personne ne sait gérer, *le programme s’arrête*

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a4e429a119d121ad0a81733615df225b", "grade": false, "grade_id": "cell-c08780e1e2a49a5e", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Quelques exceptions standard

Les erreurs dans les programmes peuvent être classifiée
en plusieurs types classiques; ci-dessus, il s'agissait
d'un «argument invalide». Dans d'autre cas, cela peut
être un problème d'allocation, une erreur arithmétique,
etc. Cette classification aide le lecteur et l'utilisateur
à mieux analyser les erreurs et, par exemple, décider du
comportement à adopter face à l'une d'elle.

Pour cela, la bibliothèque standard `stdexcept` fournit
plusieurs types d'**exceptions standard** qui forment
une hiérarchie avec, tout en haut, le type le moins
spécifique `exception`; en voici quelques unes:

-   `exception`
-   `runtime_error`
-   `invalid_argument`, `out_of_range`, `length_error`
-   `logic_error`, `bad_alloc`, `system_error`
-   ...

Essayez de deviner le rôle de chacune.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1867bc5059c1bd8298b973e5ba1e1c18", "grade": false, "grade_id": "cell-8e32dd67c8e79ff8", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Gestion d’exception

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "afa9e28e78488b692d8f23278fce1413", "grade": false, "grade_id": "cell-6c2400e8b1f72c65", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exemple 1

Imaginez que vous utilisiez votre traitement de texte, et que
vous lui demandiez d'ouvrir un fichier qui n'existe pas.
Pour la fonction en charge d'ouvrir ce fichier, c'est une
situation exceptionnelle. Pour autant, serait-il acceptable que
le traitement de texte plante avec juste un petit message
«fichier inexistant»?

Non: pour un traitement de texte, ce n'est pas une situation
exceptionnelle. Il sait gérer: prévenir l'utilisateur que
le fichier n'existe pas, puis continuer normalement.

**Une situation peut-être exceptionnelle pour une fonction, sans qu'elle le soit pour pour son «chef»**.

Il nous faut donc un mécanisme par lequel le chef puisse prendre la main et gérer la situation.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "3b9c504b814807c612dbce372ef60b1c", "grade": false, "grade_id": "cell-63a99e6a23d65392", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### Exemple 2

Nous allons considérer un sénario similaire, en plus simple: un programme qui
demande un nombre $n$ à l'utilisateur et affiche la factorielle de ce nombre.
Pour ce programme, ce n'est pas exceptionnel que l'utilisateur fasse des bêtises
en saisissant une valeur invalide. Le programme sait gérer, en affichant un
petit message avant de continuer.

Voilà comment cela s'écrit. Pour que tout soit au même endroit, nous rappelons
d'abord la définition de la fonction factorielle.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 343bcc0439e37089f40288c7827a2353
  grade: false
  grade_id: cell-ce7bab8e19b5c2c9
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <stdexcept>
using namespace std;
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: a86563cd90f9f13922cfacfefeb690ab
  grade: false
  grade_id: cell-77f927ef9fe02810
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int factorielle(int n) {
    if ( n  < 0 ) throw invalid_argument("n doit être positif");
    if ( n == 0 ) return 1;
    return n * factorielle(n-1);
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 879dc044770e4ea8109329e9e4100e51
  grade: false
  grade_id: cell-297c4f2f3e944b2c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
#include <iostream>
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3ab75cd8339f115484eb7b718fae3db9
  grade: false
  grade_id: cell-42039d542c5acba6
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int n;
cout << "Veuillez saisir un nombre entier positif:" << endl;
cin >> n;
try {
    int f = factorielle(n);
    cout << "Factorielle n vaut " << f << endl;
} catch (invalid_argument & e) {
    cout << "Valeur de n invalide: " << n << endl;
}
cout << "Je continue ..." << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0c60f9c1e64811bd4f379d1644adc54f", "grade": false, "grade_id": "cell-7342df335446495d", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Les deux éléments nouveaux sont `try` (essayer) et `catch` (rattraper l'erreur).
En voici la signification.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "5186a03cc09237757f59c2ba6ea2ab6e", "grade": false, "grade_id": "cell-89cd2a160ce25eb3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## ♣ Gestion des exceptions

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "51190f79340e53d9a806e8c1d591bc05", "grade": false, "grade_id": "cell-0d62f19248f5fb87", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Syntaxe:**

``` c++
    try {
        bloc d´instructions;
    } catch (type & e) {
        bloc d´instructions;
    }
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "237eff56a21cb02391b0a34e9c59d654", "grade": false, "grade_id": "cell-ff023926458f8702", "locked": true, "schema_version": 3, "solution": false, "task": false}}

**Sémantique:**

-   Exécute le premier bloc d’instructions
-   Si le bloc signale une exception de type `type`, ce n’est pas grave, je
    sais gérer:
    -   L’exécution du premier bloc d’instruction s’interrompt
    -   Le deuxième bloc d’instruction est exécuté

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b3eaad9fcf74b47762c4a7cb5efa5460", "grade": false, "grade_id": "cell-52f4b3af30627779", "locked": true, "schema_version": 3, "solution": false, "task": false}}

## Résumé

Nous avons vu comment **signaler une situations exceptionnelle**
(communément appellée erreur) lors de l'exécution d'un programme
ou d'une fonction.

Cela se fait avec `throw e` où `e` est une **exception**.
Cette dernière est typiquement construite avec l'un des types d'exceptions
de la bibliothèque standard `stdexcept`.

Les fonctions appelantes peuvent alors **gérer cette exception**,
à l'aide de `try ... catch ...`.
Si aucune d'entre elles ne gère l'exception, alors le programme s'arrête.

Il y aurait bien d'autres choses à dire sur les exceptions, mais cela
sera suffisant pour notre usage ce semestre.
