/*
  Exercice 1 - Templatification

  Q1 - Implémentez une structure table qui contient une quantité statique de
  double sous la forme d'un double[10]. Cette structure doit se comporter en
  tout point comme un tableau de 10 double. Les opérations à fournri sont :

    - un moyen de construire un table à partir de 10 double
    - une fonction membre size() qui renvoit la taille de l'objet (à savoir 10)
    - les surcharges adéquates de operator[] pour accéder aux éléments ainsi
  stockés
    - des fonctions membres begin() et end() renvoyant un pointeur vers le debtu
  et la fin des données

  Q2 - Utilisez les templates pour transformer table en template de structure
  permettant de choisir le type des données stockées dans table.

  Q3 - Utilisez les templates pour transformer table en template de structure
  permettant de choisir le type des données stockées dans table ET leur quantité

  Q4 - Discuter le cas table<double,0>; Doit on le gérer de manière spéciale ?
*/

#include <iostream>

template <typename T, int N>
struct table {
  T data[N];

  table() = default;

  T &operator[](int i) { return data[i]; }
  T const &operator[](int i) const { return data[i]; }

  int size() const { return N; }

  T *begin() { return data; }
  T *end() { return data + N; }
};

int main(int, char **) {

  table<double, 0> t;
  for (int i = 0; i < t.size(); ++i) {
    t[i] = i;
  }

  for (auto &v : t) {
    std::cout << v << std::endl;
  }


  table<char, 20> t2;
  for (int i = 0; i < t2.size(); ++i) {
    t2[i] = i + 'a';
  }
  
  for (auto &v : t2) {
    std::cout << v << std::endl;
  }

}
