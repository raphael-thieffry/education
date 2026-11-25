#ifndef MED_HPP
#define MED_HPP
int lireValeurBornee(string texteAEcrire, int min, int max);

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
#endif