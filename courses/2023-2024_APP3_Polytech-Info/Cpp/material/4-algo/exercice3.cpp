/*
  Exercice 3 - Algo v2.0

  Q1 - Pour les algorthimes suivant de la bibliothèque standard
  - for_each
  - transform
  - accumulate
  - find_if

  Ecrivez un jeu de template de fonction permettant de passer directement des
  conteneurs à ces algorithmes.

  Par ex:

  std::vector<int> a = ... ,b = ...;

  // equivalent a std::transform(a.begin(),a.end(),b.begin(), ... );
  range_transform(a,b, [](int x) { return -x; });

 Q2 - Implémentez un template de structure permettant de transformer
 deux pointeurs décrivant un bloc de mémoire pré-existant en un objet
 ayant une interface similaire à celle de vector en fournissant :
  - begin
  - end
  - operator[]
  - size

  Quelles contraintes devez-vous résoudre pour pouvoir utiliser ce template
  dans votre version des algorithmes?
*/

#include <iostream>

int main(int, char **) {}
