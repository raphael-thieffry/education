#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

namespace std {
ostream &operator<<(ostream &out, const vector<int> &v) {
  out << "{";
  if (v.size() != 0) out << v[0];
  for (int i = 1; i < int(v.size()); i++)
    out << ", " << v[i];
  out << "}";
  return out;
}

ostream &operator<<(ostream &out, const array<vector<int>, 3> &a) {
  out << "{" << a[0] << ", " << a[1] << ", " << a[2] << "}";
  return out;
}
};  // namespace std

struct Hanoi {
  // Attributs
  int nb_disques, nb_mvmts;

  // Constructeur

  // Méthodes
  array<vector<int>, 3> piquets_statut() const;
};

ostream &operator<<(ostream &out, const Hanoi &h);

array<vector<int>, 3> Hanoi::piquets_statut() const {
  throw runtime_error("code non implanté en ligne 40");
}

ostream &operator<<(ostream &out, const Hanoi &h) {
  // Correction
  array<vector<int>, 3> st = h.piquets_statut();
  out << endl;
  for (int i = h.nb_disques; i >= 0; i--) {
    out << " ";
    for (int p = 0; p < 3; p++) {
      int taille_disque =
        i < int(st[p].size()) ? st[p][st[p].size() - i - 1] + 1 : 0;
      out << string(h.nb_disques - taille_disque, ' ')
          << string(taille_disque, '=') << "|" << string(taille_disque, '=')
          << string(h.nb_disques - taille_disque, ' ') << "  ";
    }
    out << endl;
  }
  out << string(6 * (h.nb_disques + 1) + 3, '#') << endl << endl;
  out << "Nombre de mouvements : " << h.nb_mvmts << endl;
  return out;
}

int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;

  return 0;
}
