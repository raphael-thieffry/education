#include <array>
#include <iostream>
#include <vector>

/**
Exercice 5 - Structures de contrôle et vecteurs

  Pour chaque fonction, utilisez les éléments de l'interface des conteneurs
adéquats et les structures de contrôle adéquates pour répondre à la
problématique des fonctions.

  Pensez à tester les éventuels corner cases.
**/

std::array<int, 4> revert(std::array<int, 4> const &tab) {
  // Renvoyer un array contenant les valeurs de tab rangées dans l'ordre inverse
  std::array<int, 4> reversed;
  for (int i = 0; i < 4; i++)
    reversed[i] = tab[3 - i];
  return reversed;
}

std::vector<int> find_all(std::array<int, 4> const &tab, int value) {
  // Renvoyer un tableau contenant tous les index où la valeur de tab vaut value
  std::vector<int> indices;
  for (int i = 0; i < 4; i++) {
    if (tab[i] == value)
      indices.push_back(i);
  }
  return indices;
}

bool in_vec(std::vector<int> const &vec, int value) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] == value)
      return true;
  }
  return false;
}

std::vector<int> uniques(std::array<int, 4> const &tab) {
  // Renvoyer un conteneur contenant la liste des valeurs uniques stockées dans
  // tab Ex:
  //  tab = [ 1 2 5 4 4 1 2 3 6 2 1 5 8 ]
  // renvoit
  //  [ 1 2 5 4 3 6 8 ]
  std::vector<int> res;
  for (auto &t : tab) {
    if (!in_vec(res, t))
      res.push_back(t);
  }
  return res;
}

int unique_sum(std::array<int, 4> const &tab) {
  std::vector<int> unique = uniques(tab);
  int sum = 0;
  for (auto val : unique)
    sum += val;
  return sum;
}

void disp_vector(std::vector<int> vec) {
  for (auto element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::array<int, 4> tab = {1, 2, 2, 3};

  // on peut passer ce tableau en argument d'une fonction comme ceci :
  std::array<int, 4> reverse = revert(tab);
  for (auto e : reverse)
    std::cout << e << " ";
  std::cout << std::endl;

  std::vector<int> twos = find_all(tab, 2);
  disp_vector(twos);

  std::vector<int> unique = uniques(tab);
  disp_vector(unique);

  int sum = unique_sum(tab);
  std::cout << sum << std::cout;
  return 0;
}