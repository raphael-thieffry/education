---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++11
  language: C++11
  name: xcpp11
---

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "60a941245f19bdde4e2e56f401446497", "grade": false, "grade_id": "cell-3cbc94081bd728ce", "locked": true, "schema_version": 3, "solution": false}}

# Exercices supplémentaires: tableaux, chaînes de caractères, `switch`

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 196643acace6c1aaf7d475b4b7f32a45
  grade: false
  grade_id: cell-ce888f6efcf83b87
  locked: true
  schema_version: 3
  solution: false
---
#include <vector>
using namespace std;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1b2a72be0bbab36bdfd99a55460dbe55", "grade": false, "grade_id": "cell-19ad87e1d8a9a99f", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (tableaux)

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "992f5ea5ba3e7ed465927752f9c11268", "grade": false, "grade_id": "cell-058102d9d95e90a6", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- ♣ Implanter une fonction `plus_proche` qui prend en arguments un tableau de réels et un réel, puis renvoie l'élement du tableau le plus proche de ce réel. S'il y en a plusieurs, n'importe lequel convient. Commencer par en écrire la documentation.

```{code-cell}
/*double abs(double a) {
    if (a > 0) {
        return a;
    } else {
        return -a;
    }
}*/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 835e824224368dac4d4d11467428d99c
  grade: true
  grade_id: cell-27f7673b67041a81
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
/** trouve l'element le plus proche du reel en parametre à l'interieur d'un tableau
 *  @param t un tableau de réels
 *  @param r un réel
 *  @return l'element le plus proche du reel r
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 42790ead7d290a5ed2ff562e39acc19f
  grade: false
  grade_id: cell-e5ca6d001b080384
  locked: false
  schema_version: 3
  solution: true
  task: false
---
double plus_proche(vector<double> t, double r){
    double mindif = abs(t[0]-r);
    double plusProche;
    for(int i=0; i<t.size();i++){
        if(abs(t[i]-r) < mindif){
            mindif = abs(t[i]-r);
            plusProche = t[i];
        }
    }
    return plusProche;
}
plus_proche( {42., -4.2, 4.2}, 0.)
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f7aef7ca6bcc1229af144600a00745d7
  grade: true
  grade_id: cell-34d0d4cb0f65e1ab
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
slideshow:
  slide_type: subslide
---
CHECK( plus_proche( {0., 100., 200., 300.}, 245.) == 200. );
CHECK( plus_proche( {42., -4.2, 4.2}, 0.) == -4.2 or plus_proche( {42., -4.2, 4.2}, 0.) == 4.2);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "fd7b7de641ae513790f00346f2c5a091", "grade": false, "grade_id": "cell-d70f04be873364d3", "locked": true, "schema_version": 3, "solution": false, "task": false}}

- ♣ Implanter une fonction `est_dense` qui prend en arguments un tableau de réels et une valeur d'espacement réelle, et renvoie vrai si le tableau est dense et faux sinon. Un tableau est dense si deux valeurs consécutives du tableau n'ont jamais une différence supérieure à la valeur d'espacement.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: b5f72918c4ba9ee9d02f83f23ed6d238
  grade: false
  grade_id: cell-596e4232a582ada2
  locked: false
  schema_version: 3
  solution: true
  task: false
---
/** Tester si un tableau est dense
 *  @param t un tableau de réels
 *  @param espacement un réel
 *  @return vrai deux valeurs consécutives de t ont une différence d au plus espacement
 **/
bool est_dense(vector<double> t, double espacement) {
    double maxdif = abs(t[0]-t[1]);
    for(int i=0; i<t.size();i++){
        if(abs(t[i]-t[i+1]) > maxdif){
            maxdif = abs(t[i]-t[i+1]);
        }
    }
    if(maxdif<=espacement){
        return true;
    }else{
        return false;
    }
}
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: e7f77fd23a71fc7a47bc5ce0e47eb2e5
  grade: true
  grade_id: cell-cb4acc7da37cb36d
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( not est_dense( {100., 200., 300.}, 10. ));
CHECK(     est_dense( {0.7, 1.5, 2.4, 3.2}, 1. ));
CHECK( not est_dense( {0.7, 1.5, 2.1, 3.2}, 1. ));
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "c2e62430ca041312541e0ef8fd97ab0e", "grade": false, "grade_id": "cell-66b633c1602039e5", "locked": true, "schema_version": 3, "solution": false}}

## Exercice (Code Morse ♣)

- Voici une fonction qui traduit une lettre en code Morse. Elle contient une instruction `switch` que nous n'avons pas encore vue. À quoi ressemblerait la fonction avec des `if` à la place?

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3ca49740a5d4f5564cb6ce05fba185bb
  grade: false
  grade_id: cell-f07298860784b45c
  locked: true
  schema_version: 3
  solution: false
---
/** Traduction d une lettre en Morse
 *  @param a un caractère
 *  @return une chaîne de caractère représentant le code Morse du caractère
 **/
string morseCaractere(char a) {
    switch(a) {
    case 'A':
        return ".-";
    case 'B':
        return "-...";
    case 'C':
        return "-.-.";
    case 'D':
        return "-..";
    case 'E':
        return ".";
    case 'F':
        return "..-.";
    case 'G':
        return "--.";
    case 'H':
        return "....";
    case 'I':
        return "..";
    case 'J':
        return ".---";
    case 'K':
        return "-.-";
    case 'L':
        return ".-..";
    case 'M':
        return "--";
    case 'N':
        return "-.";
    case 'O':
        return "---";
    case 'P':
        return ".--.";
    case 'Q':
        return "--.-";
    case 'R':
        return ".-.";
    case 'S':
        return "...";
    case 'T':
        return "-";
    case 'U':
        return "..-";
    case 'V':
        return "...-";
    case 'W':
        return ".--";
    case 'X':
        return "-..-";
    case 'Y':
        return "-.--";
    case 'Z':
        return "--..";
    default:
        return "???";
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6d0c7ae033fa7e98f98f97d5e2c2e9cb", "grade": false, "grade_id": "cell-24dc4e8cc41056bd", "locked": true, "schema_version": 3, "solution": false}}

- Implanter une fonction `morseString` qui prend en entrée une chaîne de caractères de longueur arbitraire et qui la traduit entièrement en code Morse. <br>
  **Indication:** les chaînes de caractères (`string`) se comportent essentiellement comme des tableaux de caractères (`char`).

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 72ef67cbec2745e302ed96d621384478
  grade: false
  grade_id: cell-edcc8a9c8d2d2b2c
  locked: false
  schema_version: 3
  solution: true
---
/** Traduction d un texte en Morse
 *  @param chaine une chaîne de caractères
 *  @return une chaîne de caractère contenant la traduction en Morse de la chaîne de caractère
 **/
string morseString(string texte) {
    // VOTRE CODE ICI
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6e2a19ab7a97266d475c32112fbf7d42", "grade": false, "grade_id": "cell-47d8a29517433827", "locked": true, "schema_version": 3, "solution": false}}

- Compléter les tests ci-dessous et vérifier que la fonction les passe:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 5086f0b8adc2cbbd3abdf5fa16554f7a
  grade: true
  grade_id: cell-ba2015b421b4196e
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( morseString("HELLO") == "......-...-..---" );
CHECK( morseString("GOOD LUCK") == "--.-------..???.-....--.-.-.-" );
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e379e2d12d3bcd144600d3f68cf1f851
  grade: true
  grade_id: cell-e7a9db8ea360121c
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
// VOTRE CODE ICI
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "47760b408f85e2952ce096e8dc07e796", "grade": false, "grade_id": "cell-951b06851913ec61", "locked": true, "schema_version": 3, "solution": false}}

## Bilan

Si vous êtes arrivés jusqu'ici, bravo ! Vous pouvez reprendre le TP, en Python cette fois-ci :)
