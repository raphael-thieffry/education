#include <array>
#include <iostream>
#include <vector>

/**
  Pour chaque fonction, utilisez les éléments de l'interface des conteneurs
adéquats et les structures de contrôles adéquates pour répondre à la
problématique des fonctions.

  Pensez à tester les éventuels corner cases.
**/

std::array<int, 4> revert(std::array<int, 4> const &tab) {
  // Renvoyer un array contenant les valeurs de tab rangées dans l'ordre inverse
}

/* ??? */ find_all(std::array<int, 4> const &tab, int value) {
  // Renvoyer un tableau contenant tous les index où la valeur de tab vaut value
}

/* ??? */ uniques(std::array<int, 4> const &tab) {
  // Renvoyer un conteneur contenant la liste des valeurs uniques stockées dans
  // tab Ex:
  //  tab = [ 1 2 5 4 4 1 2 3 6 2 1 5 8 ]
  // renvoit
  //  [ 1 2 5 4 3 6 8 ]
}

/* ??? */ unique_sum(std::array<int, 4> const &tab) {
  // Renvoyer la somme des valeurs uniques de tab
}

void print(std::array<int, 4> const &tab){
  std::cout << "Contenu du tableau : " << std::endl;
  // afficher le contenu complet du tableau
}

// il faut surcharger la fonction print avec d'autres arguments pour que ça
// fonctionne bien :
void print(std::vector<int> const &tab){
  std::cout << "Contenu du tableau : " << std::endl;
}
void print(std::vector<std::size_t> const &tab){
  std::cout << "Contenu du tableau : " << std::endl;
}


int main(){
  std::array<int, 4> foo = {1, 2, 2, 3};
  // on peut passer ce tableau en argument d'une fonction comme ceci :
  print(foo);
  print(revert(foo));
  print(find_all(foo, 2));
  print(uniques(foo));
  std::cout << unique_sum(foo) << std::endl;
  return 0;
}