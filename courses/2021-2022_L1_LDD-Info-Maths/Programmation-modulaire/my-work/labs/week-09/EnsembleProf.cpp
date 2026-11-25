/* Implantation à coup de tableau des ensembles */

#include <cassert>
#include <iostream>

using namespace std;

#include "Ensemble.hpp"

// BEGIN: constructeurs
Ensemble::Ensemble() : set_{} {}

Ensemble::Ensemble(vector<Objet> v): set_{} {
  for (int i : v) set_.insert(i);
}
// END: constructeurs

// BEGIN: ajoute
void Ensemble::ajoute(Objet o) {
  set_.insert(o);
}
// END: ajoute

// BEGIN: retire
bool Ensemble::retire(Objet o) {
  // Cherche un n dans le sac
  if (set_.find(o) == set_.end()) {
    return false;
  }
  set_.erase(o);
  return true;
}
// END: retire

// BEGIN: element
Objet Ensemble::element() const {
  return *set_.begin();
}
// END: element

// BEGIN: estVide
bool Ensemble::estVide() const {
  return set_.empty();
}
// END: estVide

// BEGIN: contient
bool Ensemble::contient(Objet o) const {
  if (set_.find(o) == set_.end()) {
    return false;
  }
  return true;
}
// END: contient
