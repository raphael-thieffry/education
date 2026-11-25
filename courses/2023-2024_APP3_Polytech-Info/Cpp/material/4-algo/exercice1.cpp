/*
  Exercice 1 - Algos, prise en main

        Q1 - A l'aide de l'agorithme std::for_each de la biblio standard,
  écrivez une fonction d'affichage de tous les éléments du tableau.

        Q2 - A l'aide de l'agorithme std::transform de la biblio standard,
  modifiez le tableau en remplaçant chaque élément par son carré.

        Q3 - A l'aide de l'agorithme std::min_element et std::max_element,
  écrivez deux fonctions qui renvoient respectivement l'élément le plus proche
  et le plus éloigné d'un élément passé en paramètre.

        Q4 - Enfin, à l'aide de l'agorithme std::accumulate de la biblio
  standard, écrivez une fonction qui renvoie la moyenne de tous les éléments du
  tableau.

        Q5 - A l'aide de l'agorithme std::find_if, écrivez une fonction un
  itérateur sur le premier élément supérieur à la moyenne.

*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

/* Q1 */
void affichage(std::vector<int> &tab) { /* TODO */
}

/* Q2 */
void au_Carre(std::vector<int> &tab) { /* TODO */
}

/* Q3 */
auto plus_proche(std::vector<int> &tab, int origine) { /* TODO */
}

auto plus_eloigne(std::vector<int> &tab, int origine) { /* TODO */
}

/* Q4 */
auto moyenne(std::vector<int> &tab) { /* TODO */
}

/* Q5 */
auto premier_Plus_grand_Moyenne(std::vector<int> &tab, int moyenne) {
  /* TODO */
}

int main(int, char **) {
  std::vector<int> tab = {7, 15, 4, 12, 19, 8, 3, 5, 1, 24};
  affichage(tab);
  au_Carre(tab);
  affichage(tab);
  int origine = 290;
  std::cout << "Le plus eloigne de " << origine << " : "
            << plus_eloigne(tab, origine) << std::endl;
  std::cout << "Le plus proche de " << origine << " : "
            << plus_proche(tab, origine) << std::endl;
  auto moy = moyenne(tab);
  std::cout << "Moyenne du tableau : " << moy << std::endl;
  std::cout << "Plus proche de la moyenne du tableau : "
            << premier_Plus_grand_Moyenne(tab, moy) << std::endl;
}
