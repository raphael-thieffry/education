#include <stdexcept>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

enum class Genre { Masc, Fem };

struct Personne {
  string nom;
  Genre genre;
  // indices dans le champ table de l'état civil de son conjoint et de
  // ses parents ou -1 si l'information est inconnue
  int indConjoint, indParent1, indParent2;
  vector<int> enfants;  // indices des enfants (vecteur eventuellement vide)
};

struct EtatCivil {
  string nomEtatCivil;     // Nom de l'état civil. Exemple: "Ville de Paris"
  vector<Personne> table;  // description des personnes de cet état civil
};

/* Ci-dessous toutes les fonctions prennent une reference sur un état civil
 * en premier parametre. Si la fonction n'est pas supposée modifier l'état civil,
 * le parametre a le statut de constante ('const').
 * Sinon, comme on passe une reference sur l'état civil, toute modification par
 * la fonction subsistera quand on quittera la fonction.
 *
 * Une personne d'un état civil est representee par l'indice dans le champ
 * 'table' de cet état civil ou sont stockees les informations la concernant.
 */

/* En-tetes des fonctions qui suivent */
void initialise(EtatCivil &a, string nom);
int cherche(const EtatCivil &a, string nom);
void imprimePersonne(const EtatCivil &a, string nom);
int personne(EtatCivil &a, string sonNom, Genre s);
bool mariage(EtatCivil &a, string lun, string lautre);
bool naissance(EtatCivil &a, string qui, Genre s, string parent1, string parent2);
bool ascendantI(const EtatCivil &a, string qui, string ancetre);
bool ascendantR(const EtatCivil &a, string qui, string ancetre);

// Surcharge de l'operator << pour enum Genre
std::ostream &operator<<(std::ostream &out, Genre g) {
  switch(g) {
    case Genre::Masc : out << "Masculin"; break;
    case Genre::Fem : out << "Feminin"; break;
    default : out << "Feminin";
  }
  return out;
}

// Surcharge de l'operator << pour struct personne
std::ostream &operator<<(std::ostream &out, Personne P) {
  string statut = ((P.indConjoint > 0) ? "marié" : "célibataire");
  string indStatut = ((P.indConjoint > 0) ? to_string(P.indConjoint) : "");
  string p1 = (P.indParent1 > 0) ? to_string(P.indParent1) : "inconnu";
  string p2 = ((P.indParent2 > 0) ? to_string(P.indParent2) : "inconnu" );
  out<<P.nom<<" "<<P.genre<<endl<<statut<< indStatut<< endl << p1 <<p2<< P.enfants.size();
  return out;
}

// Surcharge de l'operateur << pour struct état civil
std::ostream &operator<<(std::ostream &out, EtatCivil a) {
  // Remplacer la ligne suivante par le code adéquat
  throw runtime_error("code non implanté");
}

void initialise(EtatCivil &a, string nom) {
  a.nomEtatCivil = nom;
  a.table = {};
}

TEST_CASE("test initialise") {
  EtatCivil a;
  initialise(a,"nom");
  CHECK(a.table.size() == 0);
  CHECK(a.nomEtatCivil == "nom");
}

EtatCivil creeEtatCivildeTest() {
  EtatCivil a;
  initialise(a, "Etat civil de Test");
  a.table.push_back({"Remy", Genre::Masc, 1, -1, -1, {2, 3}});
  a.table.push_back({"Camille", Genre::Fem, 0, -1, -1, {2, 3}});
  a.table.push_back({"Noemie", Genre::Fem, -1, 0, 1, {}});
  a.table.push_back({"Guillaume", Genre::Masc, -1, 0, 1, {4}});
  a.table.push_back({"Dodi", Genre::Masc, -1, -1, 3, {7}});
  a.table.push_back({"Sylvaine", Genre::Fem, -1, -1, -1, {6}});
  a.table.push_back({"Armand", Genre::Masc, 4, -1, 5, {7}});
  a.table.push_back({"Yuri", Genre::Fem, -1, 4, 6, {}});
  return a;
}

/*
 * Renvoie l'indice dans le tableau qui correspond a la personne ou -1 si
 * aucune personne de ce nom n'a ete enregistree.
 */
int cherche(const EtatCivil &a, string nom) {
  for(int i = 0; i<a.table.size(); i++){
    if(a.table[i].nom == nom){
      return i;
    }
  }
  return -1;
}

TEST_CASE("cherche une personne") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(cherche(a, "Noemie") == 2);
  CHECK(cherche(a, "Remy") == 0);
  CHECK_FALSE(cherche(a, "Guillaume") == 25);
  CHECK(cherche(a, "Yuri") == 7);
  CHECK_FALSE(cherche(a, "Fabrice") == 2);
  CHECK(cherche(a, "Donatien") == -1);
}

/* imprime les infos d'une personne dont on passe le nom en parametre */
void imprimePersonne(const EtatCivil &a, string nom) {
  int ind = cherche(a, nom);
  cout<<a.table[ind];
}



/* enregistre une personne (si possible) et renvoie son indice dans le tableau.
 * Renvoie un nombre negatif en cas d'erreur. Dans la suite" du code on
 * utilise les 3 valeurs suivantes pour les erreurs
 * -1 : pas de personne du nom indique lors d'une recherche
 * -2 : tentative d'ajout d'un homonyme
 * -3 : nom de personne vide
 * Si on n'est pas interesse par le detail d'une erreur, une valeur negative
 * renvoyee a la place d'un indice indique unn cas d'erreur.
 */
int personne(EtatCivil &a, string sonNom, Genre s) {
  if(cherche(a, sonNom)>=0){
    return -2;
  }else if(sonNom.size() == 0){
    return -3;
  }
  a.table.push_back({sonNom, s, -1, -1, -1, {}});
  return a.table.size()-1;
}


TEST_CASE("Ajout d'une personne") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(personne(a, "Noemie", Genre::Fem) == -2);
  CHECK(personne(a, "", Genre::Fem) == -3);
  CHECK(personne(a, "Gustave", Genre::Fem) == 8);
  CHECK_FALSE(personne(a, "Remy", Genre::Masc) >= 0);
  CHECK_FALSE(personne(a, "", Genre::Fem) >= 0);
}


bool mariage(EtatCivil &a, string lun, string lautre) {
  int i1 = cherche(a, lun);
  int i2 = cherche(a, lautre);
  if(not(i1 >= 0 and i2 >= 0))return false;
  Personne p1, p2;
  p1 = a.table[i1];
  p2 = a.table[i2];
  if(p1.indConjoint >=0 or p2.indConjoint >=0)return false;
  a.table[i1].indConjoint = i2;
  a.table[i2].indConjoint = i1;
  return true;
}

TEST_CASE("Mariage de deux personnes") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK_FALSE(mariage(a, "Noemie", "Remy"));
  CHECK(mariage(a, "Noemie", "Guillaume"));
  CHECK_FALSE(mariage(a, "Noemie", "Yuri"));
  CHECK_FALSE(mariage(a, "Daniel", "Remy"));
}

/* Enregistre la naissance (en creant la personne) et renvoie true/false selon
 * qu'elle est validee ou pas.
 * Les parents doivent exister et etre maries (entre eux !)
 * S'il y a une erreur, la nouvelle personne n'est PAS enregistree.
 */
bool naissance(EtatCivil &a, string qui, Genre s, string p1, string p2) {
  int i1,i2;
  Personne p,m,e;
  i1 = cherche(a,p1);
  i2 = cherche(a,p2);
  if(not(i1 >= 0 and i2 >= 0))return false;
  p = a.table[i1];
  m = a.table[i2];
  if(not(p.indConjoint == i2 and m.indConjoint == i1))return false;
  int res = personne(a, qui, s);
  if(not(res > 0))return false;
  a.table[res].indParent1 = i1;
  a.table[res].indParent2 = i2;
  return res >=0;
}

TEST_CASE("Naissance d'un bébé") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(naissance(a, "Ludivine", Genre::Fem, "Camille", "Remy"));
  int iL = cherche(a,"Ludivine");
  Personne lud = a.table[iL];
  CHECK(lud.indParent1 == cherche(a,"Camille"));
  CHECK(lud.indParent2 == cherche(a,"Remy"));
  CHECK_FALSE(naissance(a, "", Genre::Fem, "Camille", "Remy"));
  CHECK_FALSE(naissance(a, "Noemie", Genre::Fem, "Camille", "Remy"));
  CHECK_FALSE(naissance(a, "Ludivine", Genre::Fem, "Noemie", "Remy"));
  CHECK_FALSE(naissance(a, "Ludivine", Genre::Fem, "Edouard", "Remy"));
}

/* Version itérative de la recherche d'ascendant
 * Recherche un lien de parente en partant de 'qui' et en remontant la chaine de
 * parents pour essayer de tomber sur 'ancestor'. On arrete de remonter quand on
 * tombe sur -1 pour les parents, et on recherche dans la pile une autre branche
 * a remonter (a chaque etape on depile un element et on en empile entre 0 et 2.
 * Ca termine si le graphe est bien sans cycle).
 */
bool ascendantI(const EtatCivil &a, string qui, string ancetre) {
  vector<int> listeAncetre = {};
  listeAncetre.push_back(cherche(a, qui));
  while(listeAncetre[listeAncetre.size()-1] != cherche(a, ancetre)){
    int pc1 = a.table[cherche(a, currentName)].indParent1;
    int pc2 = a.table[cherche(a, currentName)].indParent2;
    if(pc1<0 and pc2<0){
      listeAncetre.pop_back();
      //not finished
    }
  }
}

TEST_CASE("ascendent itiratif") {
  // Remplacer la ligne suivante par le code adéquat
  throw runtime_error("code non implanté");
}



/* version recursive de la recherche d'ascendant. On utilise une fonction
 * auxiliaire pour ne pas faire plusieurs fois les tests de validite des indices
 */
bool ascendantAux(const EtatCivil &a, int iqui, int iancetre) {
  // Remplacer la ligne suivante par le code adéquat
  throw runtime_error("code non implanté");
}

bool ascendantR(const EtatCivil &a, string qui, string ancetre) {
  // Remplacer la ligne suivante par le code adéquat
  throw runtime_error("code non implanté");
}

TEST_CASE("ascendent recursif") {
  // Remplacer la ligne suivante par le code adéquat
  throw runtime_error("code non implanté");
}


int main(int argc, const char **argv) {
  Genre g = Genre::Masc;
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  cout<<g;

  EtatCivil a;
  a = creeEtatCivildeTest();
  imprimePersonne(a, "Remy");
  cout << a;

  return 0;
}
