#ifndef PRES_HPP
#define PRES_HPP
#include "medicament.hpp"
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
#endif