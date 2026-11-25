// Correction pour l'exercice de bridge
#include <iostream>
#include <vector>
#include <array>
#include <string>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl

enum class CouleurCarte {pique, coeur, carreau, trefle};

enum class ValeurCarte {
  v2, v3, v4, v5, v6, v7, v8, v9, v10, Valet, Dame, Roi, As};

struct carte {
  CouleurCarte couleur;
  ValeurCarte valeur;
};

using MainJ = array<carte, 13>;

MainJ exemple1 = {{
    {CouleurCarte::pique, ValeurCarte::As},
    {CouleurCarte::pique, ValeurCarte::Roi},
    {CouleurCarte::pique, ValeurCarte::v10},
    {CouleurCarte::pique, ValeurCarte::v2},
    {CouleurCarte::coeur, ValeurCarte::As},
    {CouleurCarte::coeur, ValeurCarte::Dame},
    {CouleurCarte::coeur, ValeurCarte::v10},
    {CouleurCarte::coeur, ValeurCarte::v9},
    {CouleurCarte::coeur, ValeurCarte::v8},
    {CouleurCarte::coeur, ValeurCarte::v7},
    {CouleurCarte::coeur, ValeurCarte::v4},
    {CouleurCarte::trefle, ValeurCarte::Valet},
    {CouleurCarte::trefle, ValeurCarte::v6}
  }};

MainJ exemple2 = {{
    {CouleurCarte::pique, ValeurCarte::v2},
    {CouleurCarte::coeur, ValeurCarte::As},
    {CouleurCarte::coeur, ValeurCarte::v9},
    {CouleurCarte::trefle, ValeurCarte::As},
    {CouleurCarte::trefle, ValeurCarte::Roi},
    {CouleurCarte::trefle, ValeurCarte::Dame},
    {CouleurCarte::trefle, ValeurCarte::Valet},
    {CouleurCarte::trefle, ValeurCarte::v10},
    {CouleurCarte::carreau, ValeurCarte::As},
    {CouleurCarte::carreau, ValeurCarte::v10},
    {CouleurCarte::carreau, ValeurCarte::v9},
    {CouleurCarte::carreau, ValeurCarte::v7},
    {CouleurCarte::carreau, ValeurCarte::v6}
  }};

array<int, 13> ptHCarte { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4 };

// la fonction qui remplace le tableau, avec vc de type valeurCarte
int pointHCarte(ValeurCarte vc){
  int val;
    switch(vc){
      case ValeurCarte::Valet : val=1;break;
      case ValeurCarte::Dame : val=2;break;
      case ValeurCarte::Roi : val=3;break;
      case ValeurCarte::As : val=4;break;
      default : val = 0; break;
    }
  return val;
}

void test_pointHCarte() {
  for(int i = 0; i<13;i++ ){
    ASSERT(ptHCarte[i] == pointHCarte((ValeurCarte)i));
  }

}

int nbreCarteCouleur(MainJ m, CouleurCarte c) {
  int i=0;
  for(auto carte: m){
    if(carte.couleur == c){
      i++;
    }
  }
  return i;
}

void test_nbreCarteCouleur() {
  ASSERT(nbreCarteCouleur(exemple1, CouleurCarte::pique) == 4);
  ASSERT(nbreCarteCouleur(exemple1, CouleurCarte::coeur) == 7);
  ASSERT(nbreCarteCouleur(exemple2, CouleurCarte::coeur) == 2);
  ASSERT(nbreCarteCouleur(exemple2, CouleurCarte::carreau) == 5);
  ASSERT(nbreCarteCouleur(exemple2, CouleurCarte::pique) == 1);
}

int evaluePtD(MainJ m) {
  vector<int> mainCoul = vector<int>(4);
  for(int i = 0;i<4;i++) mainCoul[i] = 0;
  for(auto c : m){
    mainCoul[int(c.couleur)]++;
  }
  int tot = 0;
  for(auto n:mainCoul){
    switch (n)
    {
    case 0:
      tot+=3;
      break;
    case 1:
      tot+=2;
      break;
    case 2:
      tot++;
      break;
    default:
      break;
    }
  }
  return tot;
}

void test_evaluePtD() {
  ASSERT(evaluePtD(exemple1) == 4);
  ASSERT(evaluePtD(exemple2) == 3);
}

int evaluePtH(MainJ m) {
  int tot = 0;
  for(auto c:m){
    tot+=pointHCarte(c.valeur);
  }
  return tot;
}

void test_evaluePtH() {
  ASSERT(evaluePtH(exemple1) == 14);
  ASSERT(evaluePtH(exemple2) == 18);
}

carte makeCarte(){
  int colInt;
  int valInt;
  do{
  cout<<"Choisir une couleur pique-1, coeur-2, carreau-3, trefle-4 : ";
  cin>> colInt;  
  cout<<"Choisir une valeur valet-11, reine-12, roi-13, as-14      : ";
  cin>> valInt;
  }while(not(colInt>0 and colInt<=4) or not(valInt>0 and valInt<=14));
  colInt--;
  valInt--;
  carte c = {CouleurCarte(colInt),ValeurCarte(colInt)};
  return c;
}
bool isInArray(CouleurCarte col, ValeurCarte val,MainJ a,int stopper){
  for(int i = 0; i<stopper; i++){
    if(a[i].couleur == col and a[i].valeur == val) return true;
  }
  return false;
}
MainJ makeMain(){
  MainJ fin;
  carte temp;
  int i;
  for(i = 0; i<13; i++){
    cout<<"carte numero "<<i<<" :"<<endl;
    do{
      temp = makeCarte();
    }while(isInArray(temp.couleur, temp.valeur,fin,i));
    fin[i] = temp;
  }
  return fin;
}
int main() {
  test_nbreCarteCouleur();
  test_evaluePtD();
  test_evaluePtH();
  test_pointHCarte();
  makeMain();
}
