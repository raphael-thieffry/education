#include <stdexcept>
/* Implantation à coup de tableau des ensembles */

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

#include "Ensemble.hpp"

Ensemble::Ensemble() {
  t_ = {};
}

Ensemble::Ensemble(vector<Objet> v) {
 t_ = {};
 for(auto ev : v){
     bool seen = false;
     for(auto et : t_){
         if(ev == et){
             seen = true;
         }
     }
     if(not seen) t_.push_back(ev);
 }
}

void Ensemble::ajoute(Objet o) {
    if(not contient(o)) t_.push_back(o);
}

bool Ensemble::retire(Objet o) {
  bool ishere = false;
  int ind = -1;
  for (int unsigned i = 0; i < t_.size();i++){
      if(t_[i] == o){
          ishere = true;
          ind = i;
          break;
      }
  }
  for (int unsigned i = ind; i < t_.size()-1;i++){
      t_[i] = t_[i+1];
  }
  t_.pop_back();
  return ishere;
}

Objet Ensemble::element() const {
  return t_[0];
}

bool Ensemble::estVide() const {
  return t_.size() == 0;
}

bool Ensemble::contient(Objet o) const {
  for (int unsigned i = 0; i < t_.size();i++){
      if(t_[i] == o){
          return true;
      }
  }
  return false;
}
