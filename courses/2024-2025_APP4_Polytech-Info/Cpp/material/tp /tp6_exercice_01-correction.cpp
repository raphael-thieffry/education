/*
  Exercice 1 - Templatification

  Q1 - Implémentez une structure table qui contient une quantité statique de
  double sous la forme d'un double[10]. Cette structure doit se comporter en
  tout point comme un tableau de 10 double. Les opérations à fourni sont :

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

struct table_1_t {
  double data[10];

  // table_1_t(double a) {
  //   data[0] = 0;
  // }

  int size() { return 10; }

  double *begin() { return &data[0]; }
  double *end() { return &data[10]; }

  // double &operator[](const std::size_t i) { return data[i]; }
  double &operator[](const std::size_t i) const { return (double&) data[i]; }
};

template <typename T> struct table_2_t {
  T data[10];

  int size() { return 10; }

  T *begin() { return &data[0]; }
  T *end() { return &data[10]; }

  T &operator[](const std::size_t i) { return data[i]; }
};

template <class T, int N> struct table_3_t {
  T data[N];

  int size() { return N; }

  T *begin() { return &data[0]; }
  T *end() { return &data[N]; }

  T &operator[](const std::size_t i) { return data[i]; }
};

template <class T> struct table_3_t<T, 0> {
  int size() { return 0; }

  // Solution 1 nullptr
  // T * begin(){return nullptr;}
  // T * end(){return nullptr;}
  // T& operator[] (const std::size_t i){return reinterpret_cast<T*>(this);}

  // Solution 2 Good solution
  T *begin() { return reinterpret_cast<T *>(this); }
  T *end() { return reinterpret_cast<T *>(this); }
  T &operator[](const std::size_t i) { return reinterpret_cast<T *>(this); }

  // Solution 3 : bad solution ! Similar to std::array<T, N=0>
  // T data[1];  // avoid sizeof(table_3_t<T, 0>) == 0
  // T * begin(){return &data[0];}
  // T * end(){return &data[0];}
  // T& operator[] (const std::size_t i){return data[i];}
};

template <typename T> void print_table(T tab) {
  std::cout << "[ ";
  for (auto e : tab) {
    std::cout << e << ", ";
  }
  std::cout << " ]( size = " << tab.size() << " )\n";
}

struct empty {};

int main(int, char **) {

  table_1_t tab1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_table(tab1);

  table_2_t<int> tab2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  print_table(tab2);

  table_3_t<int, 5> tab3{1, 2, 3, 4, 5};
  print_table(tab3);

  std::cout << sizeof(table_3_t<int, 0>) << std::endl;
  std::cout << sizeof(empty) << std::endl;

  // table_3_t<table_3_t<double, 3>, 2> tabtab;
  // table_3_t<table_3_t<double, 3>, 0> tabzero;
}
