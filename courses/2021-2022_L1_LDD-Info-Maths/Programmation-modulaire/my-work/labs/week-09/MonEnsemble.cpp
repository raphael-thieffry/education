#include <stdexcept>
/* Implantation à coup de tableau des ensembles */

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

#include "Ensemble.hpp"

Ensemble::Ensemble() {
  for(int i = 0; i < MaxTaille;i++){
    t_[i] = false;
  }
}

Ensemble::Ensemble(vector<Objet> v) {
  for(int i = 0; i < MaxTaille;i++){
    t_[i] = false;
  }
  for(auto val : v){
    if(val>=0 and val<MaxTaille){
      t_[val] = true;
    }else{
      throw std::invalid_argument("élément superieur à maxTaille");
    }
  }
}

void Ensemble::ajoute(Objet o) {
  t_[int(o)] = true;
}

bool Ensemble::retire(Objet o) {
  bool ishere = t_[int(o)];
  t_[int(o)] = false;
  return ishere;
}

Objet Ensemble::element() const {
  for(int i = 0; i < MaxTaille;i++){
    if(t_[i]){
      return i;
    }
  }
  return -1;
}

bool Ensemble::estVide() const {
  for(int i = 0; i < MaxTaille;i++){
    if(t_[i] == true){
      return false;
    }
  }
  return true;
}

bool Ensemble::contient(Objet o) const {
  return t_[int(o)];
}
