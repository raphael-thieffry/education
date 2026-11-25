#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "prescription.hpp"
void Prescription::lirePrescription(const Stock &s) {

  int indiceMed = 0;
  do {
    cout << "entrez le nom du medicament" << endl;
    cin >> nomMed;
    indiceMed = s.indiceMedicament(nomMed);
  } while (nomMed == "" or indiceMed == -1);
  nbCparJour = lireValeurBornee("Nbre de comprimes par jour ", 1, 6);
  nbJours = lireValeurBornee("Duree du traitement ", 1, 31);
}

int Prescription::nbBoites(const Stock &s) const {

  Medicament med = s.table[s.indiceMedicament(nomMed)];
  int nbC = nbCparJour * nbJours;  // nb de comprimes necessaires
  if (med.nbParBoite >= nbC) return 1;
  int res = nbC / med.nbParBoite;
  if (nbC % med.nbParBoite != 0) res++;
  return res;
}

float Prescription::coutTotal(Stock &s) {

  int nbB = nbBoites(s);
  int indiceMed = s.indiceMedicament(nomMed);
  int nbStock = s.table[indiceMed].nbBoites;

  if (nbStock >= nbB) {
    s.table[indiceMed].nbBoites = nbStock - nbB;
    return nbB * s.table[indiceMed].prixBoite;
  } else {
    cout << "stock insuffisant, il manque " << nbB - nbStock << " boites";
    s.table[indiceMed].nbBoites = 0;
    return nbStock * s.table[indiceMed].prixBoite;
  }
}