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

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "7d4574911b525c2cdf71c587fa14ecc4", "grade": false, "grade_id": "cell-8debedfea96381b5", "locked": true, "schema_version": 3, "solution": false}}

# Jeu de Yams

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "df8d5531cd5246a066b98f90fa9697ca", "grade": false, "grade_id": "cell-6c2c32f5e76ffb43", "locked": true, "schema_version": 3, "solution": false}}

## Rappels d'utilisation des tableaux

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6b730e7ce45c7cb70b2fcfd789a1f561", "grade": false, "grade_id": "cell-48383f81da895a3a", "locked": true, "schema_version": 3, "solution": false}}

- **Déclarer** un tableau d'entiers tab : 
```c++
vector<int> tab;
```
- **Allouer** 5 cases au tableau tab : 
```c++
tab = vector<int>(5);
```
- **Initialiser** ses cases :
```c++
tab[0] = 42; tab[1] = 3; ... ; tab[4] = 36;
```

- **Déclarer**, **allouer** et **initialiser** en une seule instruction :
```c++
vector<int> tab = {25,-3,10,7};
```

- Il est également possible de construire un tableau sans lui donner de nom pour le passer à une fonction de la manière suivante :
```c++
maFonction({17,9,-3,42});
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 9d76f14e87b28586e4e151eb009aea7e
  grade: false
  grade_id: cell-214aa5a1f7ccaa00
  locked: true
  schema_version: 3
  solution: false
---
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

typedef vector<int> tableau;

// Initialisation de la fonction rand (pour les nombres aléatoires) :
srand(time(0));
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "62feab34d216744dd4277cfd207d7dcf", "grade": false, "grade_id": "cell-e8fa588409cbc545", "locked": true, "schema_version": 3, "solution": false}}

<span style="color:red">Nous vous conseillons fortement lorsque vous avez besoin de redémarrer le noyau avec **Kernel > Restart** (and clear all si vous voulez faire le ménage) de faire ensuite systématiquement la commande **Cell > Run all above**, car toutes les fonctions définies dans cette feuille seront utilisées à la fin.</span>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a4ef53b3b3803ae8816a9e484478ffd2", "grade": false, "grade_id": "cell-e8fa588409cbc546", "locked": true, "schema_version": 3, "solution": false}}

## Reconnaître les yams

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "09a50eac55004a1d3caa7c64a69e41be", "grade": false, "grade_id": "cell-b61f9d53913e9c53", "locked": true, "schema_version": 3, "solution": false}}

### `pointsFigureYams`
Complétez la documentation de la fonction `pointsFigureYams` puis implémentez-la dans la case suivante. Pour rappel, la fonction `pointsFigureYams` doit vérifier si les cinq valeurs de dés fournies forment un Yams ou non. Si un Yams est trouvé on renvoie le score correspondant (somme des dés + 60) sinon 0.

<span style="color:red">Attention, pour éviter un bug de l'interpréteur C++ cling, ne pas d'utiliser d'apostrophes (') dans vos commentaires / documentations !</span>

```{code-cell}
/** Fonction pointsFigureYams
 * @param des les valeurs prises par chacun des dés (un tableau d'entiers)
 * @return le score correspondant au coup joué dans une variable res (un entier)
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ef4d843348b29ce92dc055893497c537
  grade: false
  grade_id: cell-e5c12aeafec7d057
  locked: false
  schema_version: 3
  solution: true
---
int pointsFigureYams(vector<int> des){
        if(des[0] ==  des[1] and des[2] == des[3]){
            if(des[0] ==  des[2] and des[2] == des[4]){
                if(des[1]<=6 and des[1]>=1){
                    int res = des[0]*5+60;
                    return res;
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b9a2fc6727f7ea068d0519a0169f0200", "grade": false, "grade_id": "cell-d707ce6b51bc390f", "locked": true, "schema_version": 3, "solution": false}}

Complétez les tests de la cellule suivante avec aux moins deux tests puis exécutez les deux cellules pour vérifier que votre fonction `pointsFigureYams` a bien le comportement attendu.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 595f161425c869ff50a6dbf5e138c984
  grade: true
  grade_id: cell-901b2df503fc5c9f
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( pointsFigureYams({1,1,1,1,1}) == 65 );
CHECK( pointsFigureYams({2,1,1,1,1}) ==  0 );
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ef76bee4cd29515999a264eab2d5aa29
  grade: true
  grade_id: cell-901b2df503fc5c9e
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
CHECK( pointsFigureYams({5,5,5,5,5}) == 85 );
CHECK( pointsFigureYams({78,78,78,78,78}) ==  0 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "cea11a7614843d6b03edc5ce801b2895", "grade": false, "grade_id": "cell-a6a573fb11d8cc17", "locked": true, "schema_version": 3, "solution": false}}

## Compilation et tests en dehors de Jupyter

- Ouvrez le fichier `yams.cpp` fourni dans l'archive Semaine6 avec un éditeur de texte tel que jedit ou l'éditeur de texte de JupyterHub.
- Copiez-collez votre fonction `pointsFigureYams` à un endroit adapté.
- **Enregistrez** votre fichier `yams.cpp`
- **Compilez**-le à l'aide de la commande

      g++ --std=c++11 yams.cpp -o yams
    
  Attention, pour qu'il n'y ait pas de message d'erreur il faut être allé dans le bon repertoire avec la commande `cd` (Ex. `cd ~/ProgImperative/Semaine6`).
- **Exécutez** le programme ainsi généré à l'aide de la commande `./yams`. Votre terminal doit afficher 65.

<span style="color:red">Faire sérieusement les questions de compilation pour vous y habituer: tout votre projet de fin de semestre devra être fait sous forme compilée.</span>

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "52e847c2b68315d017747a81d32d6875", "grade": false, "grade_id": "cell-d46bda39ffdb9b6b", "locked": true, "schema_version": 3, "solution": false}}

## Quelques utilitaires

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "662cce25f672800231d0c04702d744d9", "grade": false, "grade_id": "cell-d87cf79a3fac5aff", "locked": true, "schema_version": 3, "solution": false}}

### `aleaint`
La fonction `aleaint(int a, int b)` proposée ci-dessous permet de tirer au hasard un nombre entier compris entre `a` et `b` :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 41a1b9a71ada4f9f411a293d50f3c2bf
  grade: false
  grade_id: cell-ef2774917880c42d
  locked: true
  schema_version: 3
  solution: false
---
/** Fonction aleaInt
 * @param a un entier représentant le minimum du nombre aléatoire généré
 * @param b un entier représentant le maximum du nombre aléatoire généré
 * @return un entier aléatoire n tel que a <= n <= b
 **/
int aleaint(int a, int b) {
    return rand() % (b - a + 1) + a;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8ade143345f9f934aee370d5220f8de8", "grade": false, "grade_id": "cell-04090934b5186301", "locked": true, "schema_version": 3, "solution": false}}

### `lanceDes`
Complétez la documentation de la fonction `lanceDes` puis implémentez-la dans la case suivante en utilisant `aleaint`. Pour rappel, la fonction `lanceDes` doit renvoyer un tableau contenant 5 valeurs tirées aléatoirement entre 1 et 6. *(Comme la semaine dernière, pour contourner un bug dans cling on va mettre le type tableau à la place de `vector<int>`.)*

```{code-cell}
/** Fonction lanceDes
 * @return tab un tableau contenant 5 valeurs entieres aleatoires comprises entre 1 et 6 inclus
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 687b5559e35ce9727f4ca7e94517139a
  grade: false
  grade_id: cell-2400cc6d2f03939a
  locked: false
  schema_version: 3
  solution: true
---
tableau lanceDes() {
    vector<int> tab = {};
    for(int i = 1; i<6; i++){
        tab.push_back(aleaint(1,6));
    }
    return tab;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4cc28ddc0004fdd6a5be604f97ea9e67", "grade": false, "grade_id": "cell-174a3e007c306a19", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour tester la fonction `lanceDes`, il faudrait pouvoir voir son résultat, c'est-à-dire afficher le contenu d'un tableau.
Pour afficher le contenu d'une variable, vous avez maintenant l'habitude d'utiliser `cout`,
mais ceci ne fonctionne pas pour les tableaux, comme vous pouvez le voir en exéctuant la cellule ci-dessous.
Après avoir exécuté et constaté le problème,
mettez en commentaire le ligne contenant le `cout` (en mettant // en début de ligne) puis redémarrez le noyau.

```{code-cell}
vector<int> t = {5,-13,0,27};
//cout << t << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a1d7907f3ef594d40041d2046f72beb5", "grade": false, "grade_id": "cell-174a3e007c306a20", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour pouvoir afficher le contenu d'un tableau, on va écrire la fonction `afficheDes`.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1121b6a5dcd2dc71ce8f711fd6ba4872", "grade": false, "grade_id": "cell-eb7b5f0550c1d0c2", "locked": true, "schema_version": 3, "solution": false}}

### `afficheDes`

Complétez la documentation de la fonction `afficheDes` puis implémentez-la dans la cellule suivante.
Pour rappel, cette fonction doit afficher les valeurs des dés qui lui sont donnés en entrée.

```{code-cell}
/** Fonction afficheDes
 * @param un tableau d'entiers
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: cbb7584f4ac44b540c8d33076df1f93e
  grade: true
  grade_id: cell-c71cd541b0d5a957
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
void afficheDes(vector<int> tab){
    for(auto valeur: tab){
        cout <<  valeur << endl;
    }
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b8b8d6b65c5c0577c45d69f793d79e4a", "grade": false, "grade_id": "cell-273053de1f48bf92", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Pour tester votre fonctions `afficheDes`, exécuter la cellule suivante et vérifier l'affichage obtenu.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 39325c93ecb96507a91ade1334085127
  grade: false
  grade_id: cell-0ce10c221f01679f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
afficheDes({4, 21, -1, 2});
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2fde571cfc862c852dadb68e6015db33", "grade": false, "grade_id": "cell-cd2e170bbcd59ae7", "locked": true, "schema_version": 3, "solution": false}}

Testez votre fonction `lanceDes` en exécutant **à plusieurs reprises** la cellule suivante :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b01252dafee2fd73f43ec9db400ff8ca
  grade: false
  grade_id: cell-b0fd0778b45f503e
  locked: true
  schema_version: 3
  solution: false
  task: false
---
afficheDes(lanceDes());
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "72468df95433e6b1c06842a9a0d3bccb", "grade": false, "grade_id": "cell-d32e8ca14d28aec7", "locked": true, "schema_version": 3, "solution": false}}

### compteDes
Après avoir complété sa spécification, implémentez la fonction `compteDes` vue en TD.

```{code-cell}
/** Fonction compteDes
 * @param Tableau d'entiers de 5 elements
 * @return Tableau de la quantité de chaque chiffre dans le tableau d'entrée
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: e03980ec589aa454961eb09fd95abb4f
  grade: false
  grade_id: cell-cb4ed8a6d66b01c6
  locked: false
  schema_version: 3
  solution: true
---
tableau compteDes(vector<int> des) {
    vector<int> res = {0,0,0,0,0,0};
    if(des.size()==5){
        for(int i=0 ;i<des.size();){
            res[des[i]-1]++;
            i++;
        }
    }
    return res;
};
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "28fc0dc7ea3f1759f2cf69ab26bd88c0", "grade": false, "grade_id": "cell-e86e97430fbdc657", "locked": true, "schema_version": 3, "solution": false}}

Vérifiez la correction de votre fonction `compteDes` en exécutant les tests suivants vus en TD :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 640c53349bdcbbf4ca2a5f69b3b51f49
  grade: true
  grade_id: cell-fb46c8bc8918289e
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( compteDes({1,1,1,1,1}) == vector<int>({5, 0, 0, 0, 0, 0}) );
CHECK( compteDes({2,2,2,2,2}) == vector<int>({0, 5, 0, 0, 0, 0}) );
CHECK( compteDes({3,3,3,3,3}) == vector<int>({0, 0, 5, 0, 0, 0}) );
CHECK( compteDes({4,4,4,4,4}) == vector<int>({0, 0, 0, 5, 0, 0}) );
CHECK( compteDes({5,5,5,5,5}) == vector<int>({0, 0, 0, 0, 5, 0}) );
CHECK( compteDes({6,6,6,6,6}) == vector<int>({0, 0, 0, 0, 0, 5}) );
CHECK( compteDes({1,2,3,4,5}) == vector<int>({1, 1, 1, 1, 1, 0}) );
CHECK( compteDes({2,2,6,2,2}) == vector<int>({0, 4, 0, 0, 0, 1}) );
CHECK( compteDes({4,1,4,1,1}) == vector<int>({3, 0, 0, 2, 0, 0}) );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "8e4e7d68cc5b6f10dbce2c983fcfe889", "grade": false, "grade_id": "cell-374ed3ce37f10dd5", "locked": true, "schema_version": 3, "solution": false}}

### chercheDansTableau

Au tour maintenant de `chercheDansTableau` qui étant donné un entier et un tableau cherche si cet entier est présent ou non dans le tableau, renvoie son indice s'il est présent, et -1 sinon.

```{code-cell}
/** Fonction chercheDansTableau
 * @param n un entier
 * @param tab un tableau d'entiers
 * @return l'indice du tableau où n est present dans tab, et -1 sinon
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 1ebaa2665377a4b0cb5eed9d8fa46c52
  grade: false
  grade_id: cell-ba94d696690fcdcd
  locked: false
  schema_version: 3
  solution: true
---
int chercheDansTableau(int n,vector<int> tab){
    for(int i = 0; i<=tab.size()-1;i++){
        if(tab[i]==n){
            return i;
        }
    }
    return -1;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "1fb91ee1ec3fd4a4e7557c5bea33e180", "grade": false, "grade_id": "cell-089973920882695d", "locked": true, "schema_version": 3, "solution": false}}

Complétez les tests de la cellule suivante et exécutez-les pour vérifier la correction de votre fonction `chercheDansTableau`.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 3ab959c112b46e31a3b34fda74b09a72
  grade: true
  grade_id: cell-91db74d6de43eef4
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( chercheDansTableau( 3, {42,5,3,6,7}) ==  2);
CHECK( chercheDansTableau(56, {42,3,5,6,7}) == -1);
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: cf9b0760d7f9bf4f4df2483f17f89b23
  grade: true
  grade_id: cell-91db74d6de43eef5
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
CHECK( chercheDansTableau( 3, {42,5,54,6,3}) ==  4);
CHECK( chercheDansTableau(56, {56,3,5,6,56}) == 0);
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ee0fbec143a93306fd6be9478915c64f", "grade": false, "grade_id": "cell-76cb66dd2a5989a3", "locked": true, "schema_version": 3, "solution": false}}

### Main
Écrivez ci-dessous les instructions pour :
- Tirer 5 dés aléatoirement et stocker le résultat dans la variable tirage.
- Afficher le résultat du tirage.
- Afficher le nombre de points obtenus en cherchant un Yams dans ce tirage.

Testez votre chance en exécutant plusieurs fois la cellule !

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 09888343daad867a8a9619eb5315a864
  grade: false
  grade_id: cell-fc92242a65bb244c
  locked: true
  schema_version: 3
  solution: false
  task: false
---
vector<int> tirage;
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 21dc93eca449542f4c2e27b7239812fc
  grade: false
  grade_id: cell-6d6243145c1a53a7
  locked: false
  schema_version: 3
  solution: true
---
vector<int> lance = lanceDes();
afficheDes(lance);
cout<< "" <<endl;
cout << "tu obtiens "+ to_string(pointsFigureYams(lance)) + " points !" << endl
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "a51b412dee1e43565ad71a5f440d7cfe", "grade": false, "grade_id": "cell-6258bcc27bfdbca7", "locked": true, "schema_version": 3, "solution": false}}

## Compilation et test en dehors de Jupyter

- Ouvrez votre fichier `yams.cpp`.
- Copiez-collez les fonctions `afficheDes`, `lanceDes`, `compteDes` et `chercheDansTableau` à un endroit adapté.
- Remplacez la ligne d'affichage contenue dans la fonction `main` par le code des deux cellules précedentes.
- **Enregistrez** votre fichier `yams.cpp`
- **Compilez**-le à l'aide de la commande **`g++ --std=c++11 yams.cpp -o yams`**
- **Exécutez** le programme ainsi généré : `./yams`. Le résultat est-il bien celui attendu ?

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d049897a78e375589bc53f7740bd1ea5", "grade": false, "grade_id": "cell-2f1b88aea00c9cca", "locked": true, "schema_version": 3, "solution": false}}

 ## Les autres figures

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "71dc0adae397d73c32949227f55b8303", "grade": false, "grade_id": "cell-203be4570bd190bd", "locked": true, "schema_version": 3, "solution": false}}

### `pointsFigureBrelan`
Voici une fonction `pointsFigureBrelan` un peu différente de celle vue en TD :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 75b89f5b40c8a6fe4de1eff16062e8a6
  grade: false
  grade_id: cell-e0e0e9091c124592
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigureBrelan
 * @param des un tableau de 5 entiers (les dés)
 * @return 0 si aucun brelan est trouvé, la somme des dés formant le brelan + 10 sinon
 **/
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2299e522ed06be560660d373d77b37af
  grade: false
  grade_id: cell-c9713a5cdc3e9d24
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int pointsFigureBrelan(vector<int> des) {
    vector<int> compte = compteDes(des);
    
    int valeur = (chercheDansTableau(3, compte) + 1)
               + (chercheDansTableau(4, compte) + 1)
               + (chercheDansTableau(5, compte) + 1);

    if (valeur > 0) 
        return (valeur * 3) + 10;
    else
        return 0;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ff863e0f3f641ba797fd941b96e8c648", "grade": false, "grade_id": "cell-d1fdee8dffebbc7c", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Analysez son fonctionnement puis écrivez quelques tests pour vérifier qu'elle se comporte comme prévu :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: ee1cf41e90116cf2e43fcfc1d693c940
  grade: true
  grade_id: cell-f542f957d93223ad
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
CHECK(pointsFigureBrelan({3,3,3,2,2})==3*3+10)
CHECK(pointsFigureBrelan({3,3,3,3,2})==3*3+10)
CHECK(pointsFigureBrelan({4,4,4,4,4})==4*3+10)
CHECK(pointsFigureBrelan({1,2,3,4,5})==0)
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d9c9b0011919947f4bea27db57095645", "grade": false, "grade_id": "cell-8e9ded0c351723a8", "locked": true, "schema_version": 3, "solution": false, "task": false}}

### `pointsFigureCarre` & `pointsFigureFull`

Sur le même modèle, donnez deux fonctions `pointsFigureCarre` et `pointsFigureFull` répondant aux documentations ci-dessous.
Rappel: Full: 3 dés identiques et 2 dés identiques, Carré: 4 dés identiques.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 4513944e61cff58b4c4c462e3e5ee110
  grade: false
  grade_id: cell-a5b3fd2f1ed74d99
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigureCarre
 * @param des un tableau de 5 entiers (les dés)
 * @return 0 si aucun carre (4 dés identiques) est trouvé, la somme des dés formant le carré + 30 sinon
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 0d0394bbaf99c1dc14d8d95b756f644d
  grade: false
  grade_id: cell-ee9ea92251796b50
  locked: false
  schema_version: 3
  solution: true
---
int pointsFigureCarre(vector<int> des) {
    vector<int> compte = compteDes(des);
    
    int valeur = (chercheDansTableau(4, compte) + 1)
               + (chercheDansTableau(5, compte) + 1);

    if (valeur > 0) 
        return (valeur * 4) + 30;
    else
        return 0;
};
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: c5a5f6417b7ef1525ea34145ddd3cf01
  grade: false
  grade_id: cell-ee350756a6f1c8e6
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigureFull,
 * @param des un tableau de 5 entiers contenant les valeurs des dés
 * @return 0 si pas de full, somme des dés composant le full + 20 si full il y a
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 43110e994c80b61103df65ad9e7fad81
  grade: false
  grade_id: cell-351f844238b00999
  locked: false
  schema_version: 3
  solution: true
---
int pointsFigureFull(vector<int> des) {
    vector<int> compte = compteDes(des);
    int valeur2 = chercheDansTableau(2, compte) + 1;
    int valeur3 = chercheDansTableau(3, compte) + 1;

    if (valeur2 > 0 and valeur3 > 0) 
        return (valeur2 * 2) + (valeur3*3)+20;
    else
        return 0;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "6df57d79b56418c9c8bf49c8c2c44062", "grade": false, "grade_id": "cell-e9ed1239c05d3a53", "locked": true, "schema_version": 3, "solution": false, "task": false}}

Testez-les :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: b95ae127e91ec9c3d5cd62c6e4a5b181
  grade: true
  grade_id: cell-a7740a7033a46a89
  locked: true
  points: 1
  schema_version: 3
  solution: false
  task: false
---
CHECK( pointsFigureFull({4,4,4,1,1}) == 34 );
CHECK( pointsFigureFull({1,1,4,4,5}) ==  0 );

CHECK( pointsFigureCarre({4,4,4,4,1}) == 46 );
CHECK( pointsFigureCarre({4,4,4,2,5}) ==  0 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "dd00c9f46921341084384141979ffff3", "grade": false, "grade_id": "cell-2775b19eb90e3da1", "locked": true, "schema_version": 3, "solution": false}}

### `pointsFigure`
Nous vous donnons la fonction `pointsFigure` vue en TD qui a pour but de chercher la figure choisie par l'utilisateur (via une chaîne de caractères) et de retourner le nombre de points ainsi obtenu.

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6d045daa864ad61ccecfa5da2c44ce69
  grade: false
  grade_id: cell-452384d8a308fc1f
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigure,
 * @param des un tableau de 5 entiers contenant les valeurs des dés
 * @param figure une chaine de caractères contenant le nom de la figure a chercher
 * @return 0 si figure introuvable ou inconnue, le score correspondant sinon
 **/
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: d7ddfdf7a1a7dcba30dc325408e17103
  grade: false
  grade_id: cell-328296671f32464d
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int pointsFigure(vector<int> des, string figure) {
    if        ( figure == "brelan" ) {
      return pointsFigureBrelan(des);
    } else if ( figure == "full"   ) {
        return pointsFigureFull(des);
    } else if ( figure == "carre"  ) {
        return pointsFigureCarre(des);
    } else if ( figure == "yams"   ) {
        return pointsFigureYams(des);
    } 
    return 0;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "9364536bfbd33f70249ff9c1eda15b43", "grade": false, "grade_id": "cell-9957e2bdc6fd8707", "locked": true, "schema_version": 3, "solution": false}}

## Compilation et test en dehors de Jupyter

- Ouvrez votre fichier `yams.cpp`.
- Copiez-collez les fonctions `pointsFigureCarre` et `pointsFigureFull` à un endroit adapté.
- *Décommentez* les fonctions `pointsFigureBrelan` et `pointsFigure`.
- **Enregistrez** votre fichier `yams.cpp`
- **Vérifiez qu'il compile toujours** à l'aide de la commande `g++ --std=c++11 yams.cpp -o yams`
- *Exécuter le programme tel quel ne changera rien à l'exécution précédente car nous n'avons pas modifié la fonction **main**, c'est ce que nous allons faire dans la partie suivante.*

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "70da04c656a9d18181ebbfa35315c3f6", "grade": false, "grade_id": "cell-217bb315221f2bcb", "locked": true, "schema_version": 3, "solution": false}}

## Boucle de jeu : la fonction main

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ff23de4518147baf92dec688214613f7", "grade": false, "grade_id": "cell-d0fe9b8212280dc6", "locked": true, "schema_version": 3, "solution": false}}

La boucle de jeu, infinie, se décompose de la façon suivante :
> ### Avant la boucle :
> - Déclaration des variables permettant de stocker la valeur des **dés**, le **score** et la **reponse** écrite du joueur.
>
> ### Pendant la boucle :
> - On lance les dés et on stocke le résultat dans la variable appropriée.
> - On affiche le résultat du lancé à l'utilisateur et on demande quelle figure il choisit.
> - On boucle tant que l'utilisateur donne une réponse qui n'est ni une figure (**brelan**, **full**, **carre**, **yams**) ni **exit**.
> - Si l'utilisateur a répondu **exit** on sort de la boucle principale avec l'instruction **return 0;**
> - Sinon, c'est que l'utilisateur a donné le nom d'une figure, on appelle donc **pointsFigure** de façon à récupérer le nombre de points correspondant à cette figure et à ce lancer de dés. On ajoute ces points au score du joueur, et on affiche le résultat au joueur.

Dans le Jupyter Notebook on ne peut pas utiliser "cin" pour demander quelque chose à l'utilisateur, on **simulera donc les boucles par une exécution multiple des cellules concernées**. Votre objectif est de **compléter le corps de la boucle ci-dessous**, puis de **tester le jeu en exécutant les cellules dans l'ordre approprié**.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "4a435128be2e862adabd1f2cf1efaebf", "grade": false, "grade_id": "cell-0007a11a16dc6c1d", "locked": true, "schema_version": 3, "solution": false}}

### /\* AVANT LA BOUCLE PRINCIPALE \*/

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: bededf09f5d5bfc5190ef1af0e24b434
  grade: false
  grade_id: cell-1b909b89c99451ac
  locked: true
  schema_version: 3
  solution: false
  task: false
---
int pts, score = 0;
string reponse = "";
vector<int> des;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d6b122036928e70881250eddaec95b49", "grade": false, "grade_id": "cell-97cf55fa5ff66cda", "locked": true, "schema_version": 3, "solution": false}}

### /\* BOUCLE PRINCIPALE \*/
On lance les dés et on stocke le résultat dans la variable appropriée :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 2bac1ea4f46f806e6f8132369a42528d
  grade: true
  grade_id: cell-92a727dd6952ff6f
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
// VOTRE CODE ICI
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "b45b02d921c2fbe0416be63869de529c", "grade": false, "grade_id": "cell-53956a4ccaa8c96b", "locked": true, "schema_version": 3, "solution": false}}

On affiche le résultat du lancé au joueur et on affiche un texte demandant quelle figure il choisit :

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 30e283794c07fea4f789b293ad519aa2
  grade: true
  grade_id: cell-096cc4b7f9dd204b
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
// VOTRE CODE ICI
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "32ea5694bdd0bd4acdaf7991164dab85", "grade": false, "grade_id": "cell-534727077c44c82b", "locked": true, "schema_version": 3, "solution": false}}

On boucle tant que la réponse de l'utilisateur n'est pas brelan, carre, full ou yams ni exit. Ici, on considère que le joueur modifie directement la cellule suivante pour indiquer son choix (mais dans le programme compilé on récupèrera le choix avec cin) :

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: f761cbe3e51d035b2afc7bba6a7e909b
  grade: false
  grade_id: cell-9c34399406e3c9fb
  locked: true
  schema_version: 3
  solution: false
  task: false
---
reponse = "brelan";
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "57e7e796e480cf8fd24a026a6608356d", "grade": false, "grade_id": "cell-00f3946a079599bf", "locked": true, "schema_version": 3, "solution": false}}

Si l'utilisateur a répondu **exit** on affiche "Fin du programme" dans Jupyter (mais dans le programme compilé il faudra penser à sortir de la boucle principale avec l'instruction **return 0;**).

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 6b7fdc18f3fb721290641c2542ec588a
  grade: false
  grade_id: cell-1e5d72c36917c373
  locked: true
  schema_version: 3
  solution: false
  task: false
---
if (reponse == "exit") cout << "Fin du jeu, votre score final est : " << score << endl;
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "96dcdfebe834fde366419bf715544af3", "grade": false, "grade_id": "cell-880ced3468d45bd1", "locked": true, "schema_version": 3, "solution": false}}

Sinon, c'est que l'utilisateur a donné le nom d'une figure, on appelle alors **pointsFigure** de façon à récupérer le nombre de points correspondant à cette figure et à ce lancer de dés. On ajoute ces points au score du joueur, et on affiche le résultat au joueur.

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 698b9c49ac0a6a289fd822406e1ca7c0
  grade: true
  grade_id: cell-59a128ea054550e1
  locked: false
  points: 1
  schema_version: 3
  solution: true
  task: false
---
// VOTRE CODE ICI
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "68dd9e93da35fd758c123309ac3397ee", "grade": false, "grade_id": "cell-b7f9ac24211d8b2d", "locked": true, "schema_version": 3, "solution": false}}

### /\* FIN DE LA BOUCLE PRINCIPALE \*/

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ca6c626d0db76f6bd3fc55138e8de547", "grade": false, "grade_id": "cell-b9e9ca23583105bc", "locked": true, "schema_version": 3, "solution": false}}

## Compilation et test en dehors de Jupyter
Enfin, en vous basant sur le code de cette partie de la fiche, la fin du TD et le squelette suivant, **complétez la fonction main de votre fichier *yams.cpp* afin de pouvoir jouer au jeu en l'exécutant (après l'avoir compilé) depuis votre terminal**. *(Si jamais vous entrez dans une boucle infinie, vous pouvez stopper votre programme à tout moment en pressant les touches `ctrl+c`)*

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "ad0a36838b0f4bd8ffd4786767675e58", "grade": false, "grade_id": "cell-a70fb12dada72cca", "locked": true, "schema_version": 3, "solution": false, "task": false}}

```c++
int main() {
  // Initialisation de la fonction rand (pour les nombres aléatoires) :
  srand(time(0));

  // AVANT LA BOUCLE PRINCIPALE
  // On déclare les variables utilisées par la boucle principale :
  // VOTRE CODE ICI
  
  // BOUCLE PRINCIPALE
  while (true) {
    // On lance les dés et on stocke le résultat dans la variable appropriée :
    // VOTRE CODE ICI
    
    // On affiche le résultat du lancé au joueur et on affiche un texte demandant quelle figure il choisit :
    // VOTRE CODE ICI

    // On boucle tant que la réponse de l'utilisateur n'est pas brelan, carre, full ou yams ni exit : 
    do {
      cin >> reponse;
    } while (reponse != "brelan" and reponse != "full" 
	     and reponse != "carre" and reponse != "yams" and reponse != "exit");

	// Si la réponse est exit on quitte l'application :
    if(reponse == "exit") { 
        return 0; 
    }
    
    // Si l'utilisateur a choisi une figure on calcule le nouveau score et on l'affiche :
    // VOTRE CODE ICI
  }
  // FIN DE LA BOUCLE PRINCIPALE
    
  return 0;
}
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "973fe036153806654b4325b204909a43", "grade": false, "grade_id": "cell-d1ac5129b5c6f068", "locked": true, "schema_version": 3, "solution": false}}

## <span style="font-size: 150%">♣</span> De la suite dans les idées

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "d631fc79ec49e6b13901ba67ca526f34", "grade": false, "grade_id": "cell-0bb931cc66d8c75a", "locked": true, "schema_version": 3, "solution": false}}

Dans le jeux de Yams complet d'autres figures sont reconnues comme la Grande Suite (5 dés qui se suivent comme 2,3,4,5,6) et la Petite Suite (4 dés qui se suivent comme 2,3,4,5). Attention, l'ordre des dés n'a pas d'importance, les dés 2,4,3,1,5 forment donc une grande suite, même s'ils sont dans le désordre !

Donner deux fonctions répondant aux spécifications ci-dessous et vérifier que vos implémentations passent les tests:

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2d016fa05d0056a559936d715ba2bfca
  grade: false
  grade_id: cell-ae6ac015ffb2c632
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigureGrandeSuite
 * @param des un tableau de 5 entiers (les dés)
 * @return 0 si aucune grande suite (5 dés qui se suivent) n est trouvée, 
 *   la somme des dés formant la grande suite  + 50 sinon
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: 3bb6799c6b6c049dd08968a5c49fe105
  grade: false
  grade_id: cell-b61d5e0e0254a652
  locked: false
  schema_version: 3
  solution: true
---
// VOTRE CODE ICI
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 91b96cce09f0848f91b89b6b71bb15a5
  grade: true
  grade_id: cell-7b2e9d66e5e91143
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( pointsFigureGrandeSuite({4,3,2,1,5}) == 15+50 );
CHECK( pointsFigureGrandeSuite({2,3,4,5,6}) == 20+50 );
CHECK( pointsFigureGrandeSuite({2,3,4,5,2}) ==     0 );
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 1ba42e77819a999625bc429d38b08b92
  grade: false
  grade_id: cell-9c53aa2f27303d0b
  locked: true
  schema_version: 3
  solution: false
  task: false
---
/** Fonction pointsFigurePetiteSuite
 * @param des un tableau de 5 entiers (les dés)
 * @return 0 si aucune petite suite (4 dés qui se suivent) n est trouvée, 
 *   la somme des dés formant la petite suite  + 40 sinon
 **/
```

```{code-cell}
---
deletable: false
nbgrader:
  cell_type: code
  checksum: f8381317b15961731d2dd7a2a3524b85
  grade: false
  grade_id: cell-0d76bd6bdf1fba46
  locked: false
  schema_version: 3
  solution: true
---
// VOTRE CODE ICI
```

```{code-cell}
---
deletable: false
editable: false
nbgrader:
  cell_type: code
  checksum: 2bef1e17cc8130509aea8f3f04eb9150
  grade: true
  grade_id: cell-27757a711ef348de
  locked: true
  points: 1
  schema_version: 3
  solution: false
---
CHECK( pointsFigurePetiteSuite({2,3,4,5,2}) == 14+40 );
CHECK( pointsFigurePetiteSuite({3,3,4,5,6}) == 18+40 );
CHECK( pointsFigurePetiteSuite({2,3,4,2,2}) == 0 );
CHECK( pointsFigurePetiteSuite({2,3,2,5,4}) == 14+40 );
CHECK( pointsFigurePetiteSuite({2,6,4,5,3}) == 18+40 );
```

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "32999f188eeb4bd593a241147f4032ad", "grade": false, "grade_id": "cell-11e28f7da9b9115e", "locked": true, "schema_version": 3, "solution": false}}

Modifiez maintenant la boucle de jeu réalisée un peu plus haut afin de prendre en compte ces deux nouvelles figures. Testez-là en executant les cellules dans le bon ordre.

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2d595c615246482b178610ac26ed1503", "grade": false, "grade_id": "cell-40b367fc26d3b2d2", "locked": true, "schema_version": 3, "solution": false}}

## Compilation et test en dehors de Jupyter

- **Ajoutez à votre fichier yams.cpp les fonctions que vous venez de réaliser.** 
- Modifiez la fonction **main** en conséquence. 
- **Compilez** votre programme et **testez-le** en l'exécutant.
