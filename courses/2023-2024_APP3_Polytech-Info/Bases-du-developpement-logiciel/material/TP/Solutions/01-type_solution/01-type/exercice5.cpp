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
  std::array<int, 4> res;
  std::size_t size = tab.size();
  for (std::size_t i = 0; i < size; i++){
    res[i] = tab[size-i-1];
  }
  return res;
}

std::vector<std::size_t> find_all(std::array<int, 4> const &tab, int value) {
  // Renvoyer un tableau contenant tous les index où la valeur de tab vaut value
  std::vector<std::size_t> res;
  for (std::size_t i = 0; i < tab.size(); i++){
    int v = tab[i];
    if (v == value){
      res.push_back(i);
    }
  }
  return res;
}

std::vector<int> uniques(std::array<int, 4> const &tab) {
  // Renvoyer un conteneur contenant la liste des valeurs uniques stockées dans
  // tab Ex:
  //  tab = [ 1 2 5 4 4 1 2 3 6 2 1 5 8 ]
  // renvoit
  //  [ 1 2 5 4 3 6 8 ]
  std::vector<int> res;
  bool unique;
  for (std::size_t i = 0; i < tab.size(); i++){
    unique = true;
    int v = tab[i];
    for (std::size_t j=0; j < res.size(); j++){
      if (v == res[j]){
        unique = false;
        break;
      }
    }
    // N'ajoute le nombre à res que s'il n'y est pas déjà présent
    if (unique){
      res.push_back(v);
    }
  }
  return res;
}

int unique_sum(std::array<int, 4> const &tab) {
  // Renvoyer la somme des valeurs uniques de tab
  int sum = 0;
  for (auto v : tab) {
    sum += v;
  }
  return sum;
}

void print(std::array<int, 4> const &tab){
  for (std::size_t i = 0; i < tab.size(); i++){
    std::cout << tab[i] << ' ';
  }
  std::cout << std::endl;
}

// il faut surcharger la fonction print avec d'autres arguments pour que ça
// fonctionne bien :
void print(std::vector<int> const &tab){
  for (std::size_t i = 0; i < tab.size(); i++){
    std::cout << tab[i] << ' ';
  }
  std::cout << std::endl;
}

void print(std::vector<std::size_t> const &tab){
  for (std::size_t i = 0; i < tab.size(); i++){
    std::cout << tab[i] << ' ';
  }
  std::cout << std::endl;
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
