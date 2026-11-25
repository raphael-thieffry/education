#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


TEST_SUITE_BEGIN("Nombres Naturels");

// Le chiffre de poids i est en position i
// Le chiffre de poids le plus fort est différent de zéro
struct Naturel {
  vector<int> chiffres;

  // Déclarations Constructeurs
  Naturel(vector<int> v);
  Naturel(int n);
  Naturel();
  // Déclarations Méthodes
  void normalise();
  int nb_chiffres();
  int ieme_chiffre(unsigned int i);
};
// Définitions
Naturel::Naturel(vector<int> v){
    for(unsigned int i = 0; i < v.size(); i++){
      if(v[i]<0 or v[i]>9){
        throw std::invalid_argument("Les entiers doivent etre entre 0 et 9 inclus");
      }
    }
    chiffres = v;
    normalise();
}
Naturel::Naturel(){
  chiffres = {{}};
}
Naturel::Naturel(int n){
  string nS = to_string(n);
  int chiffre = 0;
  if(n<0){
    throw std::invalid_argument("n doit etre >= 0");
  }
  chiffres = vector<int>(nS.size());
  for(int i = nS.size()-1; i>=0; i--){
    chiffre = int(nS[i])-48;
    chiffres[nS.size()-1-i] = chiffre;
  }
  normalise();
}
void Naturel::normalise(){
  for(int i = chiffres.size()-1; i>=0; i--){
    if(chiffres[i]==0){
      chiffres.pop_back();
    }else{
      break;
    }
  }
}
int Naturel::ieme_chiffre(unsigned int i){
  if(i>=chiffres.size()){
    return 0;
  }else{
    return chiffres[i];
  }
}
int Naturel::nb_chiffres(){return chiffres.size();}
ostream& operator<<(ostream& out,Naturel n);
ostream& operator<<(ostream& out,Naturel n){
  for(int i = n.chiffres.size()-1; i>=0; i--){
    out<<n.chiffres[i];
  }
  return out;
}
bool operator==(Naturel a,Naturel b);
bool operator==(Naturel a,Naturel b){
  if(a.nb_chiffres() != b.nb_chiffres()){return false;}
  return a.chiffres == b.chiffres;
}
bool operator!=(Naturel a,Naturel b){
  return not(a==b);
}
TEST_CASE("Constructeur") {
  CHECK(Naturel{{3, 2, 1}}.chiffres == vector<int>{{3, 2, 1}});
  CHECK_THROWS_AS((Naturel{{3, 12, 7}}), invalid_argument);
  CHECK(Naturel{{0 ,0,0,0,0,0, 2, 1,0,0,0,0,0,0,0,0}}.chiffres == vector<int>{{0 ,0,0,0,0,0, 2, 1}});
  CHECK_THROWS_AS((Naturel{{4244242,0}}), invalid_argument);
  CHECK(Naturel{{0,0}}.chiffres == vector<int>{});
}
TEST_CASE("nb_chiffres") {
  CHECK(((Naturel)0).nb_chiffres() == 0);
  CHECK((Naturel{{1,2}}).nb_chiffres() == 2);
}
// Déclaration de naturels exemple (variables globales)
//********************************
//const Naturel N0{}; // A décommenter quand le constructeur par défaut sera fait
const Naturel N1{vector<int>{{1}}};
const Naturel N2{vector<int>{{2}}};
const Naturel N1000{vector<int>{{0, 0, 0, 1}}};
const Naturel a {{0, 0, 8, 0, 5, 6, 5, 2}};
const Naturel b {{0, 0, 8, 2, 5, 6, 5, 2}};


TEST_SUITE_END();


int main(int argc, const char** argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  cout<<Naturel(18)<<endl;
  return 0;
}
