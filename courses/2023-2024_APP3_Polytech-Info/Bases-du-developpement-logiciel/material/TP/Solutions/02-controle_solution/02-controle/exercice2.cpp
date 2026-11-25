/*
  Exercice 2 - Morpion

  Nous allons écrire un jeu simpliste de morpion. Le morpion est un jeu à deux
  joueurs qui consiste, à tour de rôle, de poser une croix (X) ou un rond (O)
  dans une grille 3x3. Un joueur gagne s'il aligne 3 symboles identiques en
  ligne, colonne ou diagonale.

  Q1 - Définissez un type 'grille' à base de std::array pour représenter la
  grille de jeu

  Q2 - Créez une valeur booléenne 'fin' valant false. Utilisez-la dans une
  boucle while dont la condition d'arrêt est le fait que cette variable vaille
  true. Vérifiez que le programme ne s'arrête pas.

  Q3 - Créez à l'endroit adéquat une variable 'symbole' de type char. Cette
  variable vaut 'X' au démarrage. Faites en sorte que, à chaque tour de boucle
  while, sa valeur alterne entre 'X' et 'O'.

  Q4 - Modifiez la boucle afin d'afficher un texte invitant le symbole courant à
  entrer sa position de jeu. Lisez ensuite une paire d'entiers entre 0 et 2.
  Cette paire d'entiers représente la coordonnée (x,y) dans la grille où le
  symbole courant doit être placé.

  Q5 - Construisez à l'endroit adéquat une variable de type 'grille' et mettez à
  jour sa valeur et affichez la à chaque itération.

  Q6 - Implémentez une série de tests qui vérifie après chaque coup si le joueur
  courant a gagné. Si c'est le cas, annoncez sa victoire et mettez la variable
  fin à true pour arrêter le jeu.

  QBONUS - Ajoutez tous les tests nécessaires à la capture des erreurs dues à
  l'entrée des positions des joueurs : case hors grille, case déjà utilisée, etc
  ...
*/

#include <array>
#include <iostream>

int main(int, char **) {

  // Q1 - Définissez un type 'grille' à base de std::array pour représenter la
  // grille de jeu
  using grille = std::array<std::array<char, 3>, 3>;

  // Q2 - Créez une valeur booléenne 'fin' valant false. Utilisez-la dans une
  // boucle while dont la condition d'arrêt est le fait que cette variable vaille
  // true. Vérifiez que le programme ne s'arrête pas.
  bool fin = false;
  // while (!fin) {
  // }

  // Q3 - Créez à l'endroit adéquat une variable 'symbole' de type char. Cette
  // variable vaut 'X' au démarrage. Faites en sorte que, à chaque tour de boucle
  // while, sa valeur alterne entre 'X' et 'O'.
  char symbole = 'X';
  // int tcount = 10; // afficher 10 fois le symbole
  // while ( tcount-- > 0) {
  //   if (symbole == 'X')
  //     symbole = 'O';
  //   else
  //     symbole = 'X';
  //   std::cout << symbole << " ";
  // }
  // std::cout << std::endl;
  // return 0; 
  
  // Q4 - Modifiez la boucle afin d'afficher un texte invitant le symbole courant à
  // entrer sa position de jeu. Lisez ensuite une paire d'entiers entre 0 et 2.
  // Cette paire d'entiers représente la coordonnée (x,y) dans la grille où le
  // symbole courant doit être placé.
  // int tcount = 2;
  // while ( tcount-- > 0) {
  //   if (symbole == 'X')
  //     symbole = 'O';
  //   else
  //     symbole = 'X';
  //   int x, y;
  //   std::cout << "Position de jeu pour " << symbole << " :\n";
  //   std::cin >> x >> y;
  //   std::cout << symbole << " joue à " << x << ", " << y;
  //   std::cout << std::endl;
  // }
  // return 0;

  // Q5 - Construisez à l'endroit adéquat une variable de type 'grille' et mettez à
  // jour sa valeur et affichez la à chaque itération.
  grille plateau;
  for (auto& col : plateau) {
    col.fill('-');
  }

  // Q2 - Lecture de la position
  while (!fin) {

    // Q4 - lecture (x,y);
    int x, y;
    std::cout << "Position de jeu pour " << symbole << " :\n";
    std::cin >> x >> y;

    // Q5
    plateau[x][y] = symbole;

    for (int yy = 0; yy < 3; ++yy) {
      for (int xx = 0; xx < 3; ++xx) {
        std::cout << plateau[xx][yy] << " ";
      }
      std::cout << "\n";
    }

    // Q6 Victoire ?
    // le long d'une colonne (à x fixé)
    for (int xx = 0; xx < 3; ++xx) {
      if (!fin) {
        fin = (plateau[xx][0] == symbole) && (plateau[xx][1] == symbole) &&
              (plateau[xx][2] == symbole);
      }
    }
    
    // le long d'une ligne (à y fixé)
    for (int yy = 0; yy < 3; ++yy) {
      if (!fin) {
        fin = (plateau[0][yy] == symbole) && (plateau[1][yy] == symbole) &&
              (plateau[2][yy] == symbole);
      }
    }

    // En diagonale
    if (!fin) {
      fin = ((plateau[0][0] == symbole) && (plateau[1][1] == symbole) &&
             (plateau[2][2] == symbole)) ||
            ((plateau[0][2] == symbole) && (plateau[1][1] == symbole) &&
             (plateau[2][0] == symbole));
    }

    if (fin)
      std::cout << symbole << " remporte la manche.\n";

    // Q3
    if (symbole == 'X')
      symbole = 'O';
    else
      symbole = 'X';
  }

  return 0;
}
