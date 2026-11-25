#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

namespace std {
ostream& operator<<(ostream& out, const vector<int>& v) {
  out << "{";
  if (v.size() != 0) out << v[0];
  for (int i=1; i < int(v.size()); i++)
    out << ", " << v[i];
  out << "}";
  return out;
}

ostream& operator<<(ostream& out, const array<vector<int>, 3>& a) {
  out << "{" << a[0] << ", " << a[1] << ", " << a[2] << "}";
  return out;
}
};

struct Hanoi {
  // Attributs
  int nb_disques, nb_mvmts;
  vector<int> positions = {};
  vector<int> goal = {};
    
  // Constructeur
  Hanoi(int nb);
  // Méthodes
  array<vector<int>, 3> piquets_statut() const;
  void reinitialise();
  void bouge_disque(int deb, int fin);
  bool gagne() const;
};
void Hanoi::reinitialise(){
    (*this) = Hanoi(nb_disques);
}
Hanoi::Hanoi(int nb){
    nb_disques = nb;
    for(int i = 0; i<nb;i++){
        positions.push_back(0);
        goal.push_back(2);
    }
    nb_mvmts = 0;
}
bool Hanoi::gagne() const{
    return positions == goal;
}
void Hanoi::bouge_disque(int deb, int fin){
    if(deb > 2 or fin >2){
        throw invalid_argument("il n'y a que 3 piquets, choisir 0,1 ou 2 seulement");
    }
    //on suppose que le disque 0 est le plus petit, etc....
    int dsize = piquets_statut()[deb][0];
    if(piquets_statut()[fin].size() == 0){
        positions[dsize] = fin;
    }else{
        int asize = piquets_statut()[fin][0];
        if(dsize>asize){
            throw invalid_argument("le disque de depart est plus gros que celui du piquet d'arrivée !");
        }
        positions[dsize] = fin;
    }
    nb_mvmts++;
}
ostream &operator<<(ostream &out, const Hanoi& h);

array<vector<int>, 3> Hanoi::piquets_statut() const {
  array<vector<int>, 3> piquet = {{ {}, {}, {} }};
  for(unsigned int i = 0; i<positions.size();i++){
      piquet[positions[i]].push_back(i); 
  }
  for(auto &v : piquet){
      if(v.size() != 0){
          sort(v.begin(), v.end());
      }
  }
  return piquet;
}

ostream &operator<<(ostream &out, const Hanoi& h) {
  array<vector<int>, 3> st = h.piquets_statut();
  out << endl;
  for (int i = h.nb_disques; i >= 0; i--) {
    out << " ";
    for (int p = 0; p < 3; p++) {
      int taille_disque = i < int(st[p].size()) ?
                              st[p][st[p].size() - i - 1] + 1 : 0;
      out << string(h.nb_disques - taille_disque, ' ')
          << string(taille_disque, '=') << "|"
          << string(taille_disque, '=')
          << string(h.nb_disques - taille_disque, ' ') << "  ";
    }
    out << endl;
  }
  out << string(6*(h.nb_disques + 1)+3, '#') << endl << endl;
  out << "Nombre de mouvements : " << h.nb_mvmts << endl;
  return out;
}

TEST_CASE("piquet_statut, bouge_disques"){
    Hanoi h = Hanoi(5);
    cout<<h.piquets_statut()<<endl;
    CHECK(h.piquets_statut() == array<vector<int>,3>({{ {0,1,2,3,4}, {}, {} }}));
    h.bouge_disque(0,2);
    CHECK(h.piquets_statut() ==  array<vector<int>,3>({{ {1,2,3,4}, {}, {0} }}));
    CHECK_THROWS_AS(h.bouge_disque(0,2), invalid_argument);
    h.reinitialise();
    CHECK(h.piquets_statut() ==  array<vector<int>,3>({{ {0,1,2,3,4}, {}, {} }}));
}

int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  int a;
  cout<<"nb disques"<<endl;
    cin>>a;
  Hanoi h = Hanoi(a);
  do{
      int dep;
      int arr;
      cout<<h<<endl;
      cout<<"dep ? : "<<endl;
      cin>>dep;
      cout<<"arr ? : "<<endl;
      cin>>arr;
      h.bouge_disque(dep,arr);
  }while(not(h.gagne()));
    cout<<"gagné en "<<h.nb_mvmts<<" mouvements"<<endl;
  return 0;
}
