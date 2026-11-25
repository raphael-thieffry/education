#include <stdexcept>
/* Implantation à coup de tableau des ensembles */

#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#include "Ensemble.hpp"

Ensemble::Ensemble() {
  t_ = {};
}

Ensemble::Ensemble(vector<Objet> v) {
    for(auto ev : v){
     bool seen = false;
     for(auto et : t_){
         if(ev == et){
             seen = true;
         }
     }
     if(not seen) t_.push_back(ev);
    }
    std::sort(t_.begin(), t_.end()); 
}

void Ensemble::ajoute(Objet o) {
    if(t_.size() == 0 or t_[t_.size()-1] < o){ t_.push_back(o); return; };
    for(int unsigned i = 0; i < t_.size();i++){
        if(t_[i] == o) return;
        if(t_[i] > o){
            t_.insert (t_.begin()+i, o);
            return;
        }
    }
        
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

bool Ensemble::contient(Objet o) const{
    return contient(o, 0, t_.size());
}

bool Ensemble::contient(Objet o, int beg, int end) const {
    if(end-beg == 1){
        if(t_[beg] == o) return true;
        return false;
    }
    int middle = beg + (end-beg)/2;
    if(t_[middle] > o){
        return contient(o, beg, middle);
    }else{
        return contient(o, middle, end);
    }
}
