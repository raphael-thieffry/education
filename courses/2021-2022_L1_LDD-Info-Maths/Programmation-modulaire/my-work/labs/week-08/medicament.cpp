#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "medicament.hpp"
int lireValeurBornee(string texteAEcrire, int min, int max) {
  int val;
  do {
    cout << texteAEcrire;
    cin >> val;
  } while (val < min or val > max);
  return val;
}

float Medicament::prixComprime() const { return prixBoite / nbParBoite; }

void Medicament::changePrix(float nouvPrix) { prixBoite = nouvPrix; }

int Stock::indiceMedicament(string nomMedicament) const {

  int nbMeds = table.size();
  for (int i = 0; i < nbMeds; i++) {
    if (nomMedicament == table[i].nom) return i;
  }
  return -1;
}

void Stock::ajouteMedicament() {

  Medicament med;
  do {
    cout << "entrez le nom du medicament" << endl;
    cin >> med.nom;
  } while (indiceMedicament(med.nom));
  med.nbBoites = lireValeurBornee("entrez nombre de boites ", 0, 100);
  med.nbParBoite =
    lireValeurBornee("entrez nombre de comprimés par boite ", 0, 100);
  cout << "entrez le prix " << endl;
  cin >> med.prixBoite;
  table.push_back(med);
}

int Stock::trouveNbComprime(string nomMedicament) const {

  int i = indiceMedicament(nomMedicament);
  if (i == -1) return -1;
  return table[i].nbParBoite;
}

int Stock::verifieQuantite(string nomMedicament) const {

  int i = indiceMedicament(nomMedicament);
  if (i == -1) return -1;
  return table[i].nbBoites;
}