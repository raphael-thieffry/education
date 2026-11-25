---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++11
  language: C++11
  name: xcpp11
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "724cb18a77983043de51522d70cc425b", "grade": false, "grade_id": "cell-a1cea05ac1387514", "locked": true, "schema_version": 3, "solution": false}}

# TP: Implanter la fonction exponentielle (1/5)

**Imaginez que vous développez la nouvelle librairie de fonctions mathématiques du `C++`.** Au départ, les seules opérations auxquelles vous avez le droit sont les *opérations arithmétiques usuelles* telles que `+` `*` `/` `%`. Notre but aujourd'hui est d'écrire la fonction qui calcule $e^x$.

Pour cela, on utilise la définition de $e^x$ en tant que *série* (somme infinie) :

$$e^x = \sum_{n=0}^{+\infty} \frac{x^n}{n!} = 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} +\cdots+\frac{x^n}{n!}+\cdots$$

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ee04ac4d3303e53ef489eeb19c036279", "grade": false, "grade_id": "cell-670b85df3798f432", "locked": true, "schema_version": 3, "solution": false}}

On remarque que l'on a besoin en particulier de calculer $x^n$ ainsi que $n!$. Ce sera l'objet de la première partie. Dans la partie 2, on calculera une approximation de la fonction exponnentielle en la tronquant à un nombre de terme fixé; par exemple:
$e^x \approx 1+\frac{x^2}{2!}+\frac{x^3}{3!}$

La précision d'une telle approximation dépend beaucoup de la valeur de $x$. Dans la partie 4 on utilisera une méthode *adaptative*: on fixera cette fois la précision relative souhaitée et on calculera autant de termes que nécessaire pour atteindre cette précision. Pour cela on aura préalablement défini -- et implanté ! -- dans la partie 3 ce que l'on entend par précision relative.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "bb95d100cc9ae530047d0368b43871cf", "grade": false, "grade_id": "cell-8ce9f4aa74ff1ade", "locked": true, "schema_version": 3, "solution": false}}

## Partie 1 : Fonctions puissance et factorielle

Le but de cette partie est d'écrire les fonctions `factorielle` et `puissance` (vues en TD) et de vérifier que l'on obtient bien les résultats attendus. Complétez la fonction `factorielle` ci-dessous puis vérifiez les résultats des cellules suivantes:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3dd1504f2a31dae0097e54a53ab00048
  grade: false
  grade_id: cell-26599ba8b0db5d2c
  locked: false
  schema_version: 3
  solution: true
---
/** Factorielle
 * @param n un entier
 * @return la valeur n! en tant que double
**/
double factorielle(int n) {
    int resultat = 1;
    for(int i=1; i<=n; i++){
        resultat = resultat*i;
    }
    return resultat;
}
```

```{code-cell}
factorielle(5)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 77b5b29ad8316807bdc9188ac65ef447
  grade: true
  grade_id: cell-b141e2a8fe5b4d49
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( factorielle(0) == 1   );   // Par convention mathématique
CHECK( factorielle(3) == 6   );
CHECK( factorielle(4) == 24  );
CHECK( factorielle(5) == 120 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "0f492c57be1cb4e5c54cebdd27127699", "grade": false, "grade_id": "cell-4034b50f9054165a", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez l'ordre de grandeur du calcul suivant. Si la valeur est aberrante, vérifiez l'utilisation du type `double` à toutes les étapes du calcul.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5baea162ffe9ed953e12e730886f2cce
  grade: false
  grade_id: cell-248a410c27f82b9c
  locked: true
  schema_version: 3
  solution: false
---
factorielle(100)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "50358d4b7d412ad1219d46febc4fd2a9", "grade": false, "grade_id": "cell-1a440314756d1d38", "locked": true, "schema_version": 3, "solution": false}}

Complétez la fonction `puissance` ci-dessous puis vérifiez les résultats des cellules suivantes:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ffcfd173b84e127cea202faa83372989
  grade: false
  grade_id: cell-98509d177b22e222
  locked: false
  schema_version: 3
  solution: true
---
/** Puissance
 * @param x un nombre de type double
 * @param n un entier
 * @return le nombre x^n de type double
**/
double puissance(double x, int n) {
    double resultat = x;
    if(n!=0){
    for(int i=1; i<n; i++){
            resultat = resultat*x;
        }
    return resultat;
    }else{
        return 1;
    }
}
```

```{code-cell}
puissance(1.5, 3)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5649e332a8cfaca594c48b6062cc74f6
  grade: true
  grade_id: cell-0c4baef17dc81ab9
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( puissance(1,  10) == 1     );
CHECK( puissance(2,   5) == 32    );
CHECK( puissance(1.5, 3) == 3.375 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c32369f1bde59662949abe7ca7285708", "grade": false, "grade_id": "cell-471123af8e648bfb", "locked": true, "schema_version": 3, "solution": false}}

Ajoutez des tests (toujours avec CHECK) pour vérifier les cas limites:
vérifiez (pour une valeur de x de votre choix) que $x^0$ vaut $1$,
que $0^r$ vaut 0 pour $r$ non nul, et que $0^0$ vaut $1$:

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 26f5d0fd04864ff97d1bc9a9a67019d1
  grade: false
  grade_id: cell-a852e5dd3d8aeab1
  locked: false
  schema_version: 3
  solution: true
---
CHECK( puissance(18,  0) == 1     );
CHECK( puissance(0,   27) == 0    );
CHECK( puissance(0, 0) == 1 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "34111634158e4bc529a756cf6c717118", "grade": false, "grade_id": "cell-b9ac4bd82bc4f381", "locked": true, "schema_version": 3, "solution": false}}

## Bilan de la partie 1
Vous avez maintenant les prérequis pour implanter la fonction exponentielle.
Vous pouvez maintenant passer à la [partie 2](02-exponentielle2.md).
