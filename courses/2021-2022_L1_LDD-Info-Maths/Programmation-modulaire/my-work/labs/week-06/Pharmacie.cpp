#include <stdexcept>
#include <exception>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int lireValeurBornee(string texteAEcrire, int min, int max) {
  int val;
  do {
    cout << texteAEcrire;
    cin >> val;
  } while (val < min or val > max);
  return val;
}


struct Medicament {
  string nom;
  int nbBoites;
  int nbParBoite;
  float prixBoite;

  float prixComprime() const;
  void changePrix(float nouvPrix);
};
float Medicament::prixComprime() const{
  return prixBoite/nbParBoite;
}
void Medicament::changePrix(float nouvPrix){ 
  prixBoite = nouvPrix;
}

struct Stock {
  vector<Medicament> table;

  int indiceMedicament(string nomMedicament) const;
  void ajouteMedicament();
};
int Stock::indiceMedicament(string nomMedicament) const{
    for(size_t i = 0; i<table.size(); i++){
    if(table[i].nom == nomMedicament){
      return i;
    }
  }
  return -1;
}
void Stock::ajouteMedicament(){ 
  string nom;
  int nbb,nbpb;
  float prix;
  cout<<"nom (string)";
  cin>> nom;
  cout<<"nb de boites (int)";
  cin>> nbb;
  cout<<"nb par boites (int)";
  cin>> nbpb;
  cout<<"prix (float)";
  cin>> prix;
  Medicament med = {nom, nbb,nbpb, prix};
  if(indiceMedicament(nom)<0){
    table.push_back(med);
  }
}

struct Prescription {
  string nomMed;
  int nbCparJour;
  int nbJours;

  void lirePrescription(const Stock &s);
  int nbBoites(const Stock &s) const;
  float coutTotal(Stock &s) const;
};
void Prescription::lirePrescription(const Stock &s){
  string nom;
  int nbcj,duree;
  do {
    cout << "nom (string)";
    cin >> nom;
  } while (!(s.indiceMedicament(nom)<0));
  nbcj = lireValeurBornee("nb comp par jour :",0,6);
  duree = lireValeurBornee("nb de jours :",0,31);
  nomMed = nom;
  nbCparJour = nbcj;
  nbJours = duree;
}
int Prescription::nbBoites(const Stock &s) const{
  int medI = s.indiceMedicament(nomMed);
  Medicament med = s.table[medI];
  //si le reste est non nul, je rajoute une boite
  return nbCparJour*nbJours/med.nbParBoite+(nbCparJour*nbJours%med.nbParBoite!=0);
}
float Prescription::coutTotal(Stock &s) const{ 
  int medI = s.indiceMedicament(nomMed);
  Medicament med = s.table[medI];
  s.table[medI].nbBoites -= 1;
  return nbBoites(s)*med.prixBoite;
}


Stock creeUnStockdeTest() {
  Stock s;
  s.table.clear();
  s.table.push_back({"panadol", 20, 4, 3.5f});
  s.table.push_back({"aspirine", 2, 12, 6.f});
  s.table.push_back({"nexium", 0, 10, 12.5f});
  return s;
}
TEST_CASE("cherche un medoc") {
  Stock a;
  a = creeUnStockdeTest();
  Prescription pres1 = {"nexium", 6, 3};
  Prescription pres2 = {"nexium", 6, 4};
  CHECK(pres1.nbBoites(a) == 2);
  CHECK(pres2.nbBoites(a) == 3);
}
TEST_CASE("cb de boites pour telle ou telle prescription") {
  Stock a;
  a = creeUnStockdeTest();
  CHECK(a.indiceMedicament("panadol") == 0);
  CHECK(a.indiceMedicament("aspirine") == 1);
  CHECK(a.indiceMedicament("nexium") == 2);
  CHECK(a.indiceMedicament("sdfgrefghrbeuivbr") == -1);
}
TEST_CASE("test prix comprime") {
  Stock s = creeUnStockdeTest();
  CHECK(s.table[0].prixComprime() == 0.875f);
  CHECK(s.table[1].prixComprime() == 0.5f);
  CHECK(s.table[2].prixComprime() == 1.25f);
}




int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit())
    return test_result;

  return 0;
}
