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

+++ {"slideshow": {"slide_type": "slide"}}

# TP: premiers programmes compilés en C++

## Exercice: «bonjour!»

+++

1.  Ouvrir un éditeur de texte, par exemple `jedit`.

2.  Créer un nouveau fichier texte `bonjour.cpp` dans votre répertoire `ProgImperative/Semaine5`.

3.  Écrire dans le fichier le programme suivant.  
    **Attention**, le
    programme que vous écrivez doit respecter la même mise en page
    (retour à la ligne, espaces, majuscules).

    ```c++
    #include <iostream>
    using namespace std;

    int main() {
        cout << "Bonjour !" << endl;
        return 0;
    }
    ```

    Ne pas oublier d'enregistrer le fichier.

4.  Ouvrir un terminal et utilisez la commande `cd` pour vous rendre dans le
    répertoire `ProgImperative/Semaine5` où est enregistré votre fichier.

5.  Vérifier avec `ls` que votre répertoire contient bien le fichier
    `bonjour.cpp`.

6.  **Compiler le programme `bonjour.cpp`** en tapant la commande
    suivante sur votre terminal:

		g++ bonjour.cpp -o bonjour

    Si tout se passe bien, vous n'avez aucun message d'erreur.

    **Attention**, cette commande ne peut fonctionner que si vous êtes
    dans le bon répertoire!

    Si une erreur s'affiche, la lire et essayer d'identifier le problème
    en trouvant le numéro de ligne: avez-vous bien respecté le nom du
    fichier, les minuscules et majuscules, les retours à la ligne et
    espaces, les points-virgules à la fin des deux lignes
    d'instructions? Après chaque correction, **enregistrer** le fichier
    et relancer la **compilation** en retapant la commande.
    
    **Rappel:**
    on peut parcourir l'historique des commandes tapées dans le terminal
    avec les touches ↑ et ↓ du clavier.

7.  Lancer la commande `ls`; quels fichiers se trouvent maintenant dans
    votre répertoire?

8.  Votre répertoire doit contenir un fichier `bonjour` (sans
    extension). Exécutez-le en tapant

		./bonjour

    Le texte `Bonjour !` doit s'afficher. Bravo, vous avez lancé votre
    premier programme `C++`!

9.  Modifier le fichier `bonjour.cpp` en remplaçant «Bonjour !» par le
    message de votre choix. L'enregistrer puis lancer la commande

		./bonjour

    Que remarquez-vous?

10. Comment faire pour que l'exécution du programme reflète le
    changement effectué dans `bonjour.cpp`? Le faire.

    Lorsqu'on modifie un programme, pour que les changements soit pris
    en compte, il faut re-compiler le programme avant de l'exécuter.

## Exercice: du max au min

1.  Ouvrir avec votre éditeur de texte le fichier [minmax.cpp](minmax.cpp).

2.  Compiler et exécuter ce programme comme précédemment :

        g++ minmax.cpp -o minmax

		./minmax

3.  Modifier le programme pour qu'il affiche le *minimum* des deux
    nombres. Compiler et exécuter à nouveau pour vérifier vos modifications.
