#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

  /** renvoie le prix d'un comprimé **/
  float prixComprime() const;

  /** change le prix d'un médicament **/
  void changePrix(float nouvPrix);
};

struct Stock {
  vector<Medicament> table;

  /** ajoute un nouveau medicament au stock
   *  en verifiant s'il n'existe pas
   *  deja **/
  void ajouteMedicament();
  /** retourne la quantité de boites en stock d'un medicament
   *  et -1 s'il n'est pas dans la base de données du stock **/
  int verifieQuantite(string nomMedicament) const;

  /** retourne l'indice si le medicament existe dans la base et -1 sinon **/
  int indiceMedicament(string nomMedicament) const;

  /** retourne le nb de comprimé d'un médicament **/
  int trouveNbComprime(string nomMedicament) const;
};

struct Prescription {
  string nomMed;
  int nbCparJour;
  int nbJours;

  /** enregistre une nouvelle prescription
   *  en verifiant que le medicament est dans le stock*/
  void lirePrescription(const Stock &s);

  /* retourne le nbre de boites necessaires pour couvrir la prescription **/
  int nbBoites(const Stock &s) const;

  /** vérifie le nb de boites présentes dans le stock,
   *  soustraire le nombre besoin pour la prescription
   *  et retourne le prix total de l'achat **/
  float coutTotal(Stock &s);
};

Stock creeUnStockdeTest() {
  Stock s;
  s.table.clear();
  s.table.push_back({"panadol", 20, 4, 3.5f});
  s.table.push_back({"aspirine", 2, 12, 6.f});
  s.table.push_back({"nexium", 0, 10, 12.5f});
  return s;
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

int main(int argc, const char **argv) {

  Stock s = creeUnStockdeTest();
  Prescription p;
  //p.lirePrescription(s);
  return 0;
}
