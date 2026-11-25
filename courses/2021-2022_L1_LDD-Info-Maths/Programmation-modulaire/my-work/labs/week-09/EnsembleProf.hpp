#include <set>
#include <vector>

using Objet = int;
const int MaxTaille = 100;

class Ensemble {

 public:

  //* Constructeur par défaut
  //* @param[out] e : le ensemble vide
  Ensemble ();

  //* Constructeur a partir d'un vecteur
  //* @param[out] e : le ensemble
  //* @param[in] v : vecteur d'entiers
  Ensemble (vector<Objet> v);

  //* Ajoute un objet à un ensemble
  //* @param[in] o : l'objet à ajouter
  void ajoute(Objet o);

  //* Retire un objet à un ensemble
  //*  @param[in] o : l'objet à retirer
  //*  si n n'est pas dans e, ne fait rien
  //*  @return si on a bien pris l'objet dans le sac
  bool retire(Objet o);

  //* Retourne un objet de l'ensemble
  //*  @return : un objet de e si e n'est pas vide
  //*            le comportement est indéfini si e est vide
  Objet element() const;

  //* Teste si l'ensemble est vide
  //*  @return : un booléen selon le résultat du test
  bool estVide() const;

  //* Teste si un objet est dans l'ensemble
  //* @param[in] o : l'objet avec qu'il faut vérifier
  bool contient(Objet o) const;

 private:

  std::set<Objet> set_;
};





