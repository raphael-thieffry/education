#include <stdexcept>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

enum class Genre { Masc, Fem };

// Surcharge de l'operator << pour enum Genre
std::ostream &operator<<(std::ostream &out, Genre g) {
  if (g == Genre::Masc) out << "Genre masculin";
  else out << "Genre feminin";
  return out;
}

struct Personne {
  string nom;
  Genre genre;
  // indices dans le champ table de l'état civil de son conjoint et de
  // ses parents ou -1 si l'information est inconnue
  int indConjoint, indParent1, indParent2;
  vector<int> enfants;  // indices des enfants (vecteur eventuellement vide)
};

// Surcharge de l'operator << pour struct personne
std::ostream &operator<<(std::ostream &out, Personne P) {
  out << "Nom " << P.nom << endl << P.genre << endl << "Statut : ";
  if (P.indConjoint == -1) {
    out << "Celibat.";
  } else {
    out << "Mariée" << endl;
    out << "Indice conjoint : " << P.indConjoint;
  }
  out << endl << "Indices parents : (";
  if (P.indParent1 != -1) {
    out << P.indParent1 << ", ";
  } else {
    out << "inconnu, ";
  }
  if (P.indParent2 != -1) {
    out << P.indParent2;
  } else {
    out << "inconnu";
  }
  out << ")\n";
  if (P.enfants.size() > 0) {
    out << "Nb d'enfants : " << P.enfants.size() << endl;
  }
  return out;
}

struct EtatCivil {
  string nom;     // Nom de l'état civil. Exemple: "Ville de Paris"
  vector<Personne> table;  // description des personnes de cet état civil

  void initialise(string nom);
  int cherche(string nom) const;
  void imprimePersonne(string nom) const;
  void imprimeEtatCivil() const;
  int personne(string sonNom, Genre s);
};

void EtatCivil::initialise(string nom){ 
  nom = nom;
  table = {};
}
int EtatCivil::cherche(string nom) const{
  for(size_t i = 0; i<table.size(); i++){
    if(table[i].nom == nom){
      return i;
    }
  }
  return -1;
}
void EtatCivil::imprimePersonne(string nom) const{ 
    int ind = cherche(nom);
  if (ind < 0) {
    throw invalid_argument("Nom incorrect dans imprimePersonne: ");
  } else {
      cout << "\nPersonne[" << ind << "] : \n" << endl << table[ind];
  if (table[ind].enfants.size() > 0) {
    cout << "Nom des enfants : ";
    for (size_t i = 0; i < table[ind].enfants.size(); i = i + 1) {
      cout << table[table[ind].enfants[i]].nom << " ";
    }
    cout << "\n";
  }
  }
};
int EtatCivil::personne(string sonNom, Genre s){
  if (sonNom.size() == 0) {
    return -3;
  }; /* pas de nom vide */
  if (cherche(sonNom) != -1) {
    return -2;
  }
  vector<int> enfants;  // vector vide.
  Personne p = {sonNom, s, -1, -1, -1, enfants};
  table.push_back(p);
  return table.size() - 1;
}
void EtatCivil::imprimeEtatCivil() const{ 
  if (table.size() == 0) cament avec son nom dans la base de données du stock et renvoie
son indice dans le tableau ou -1 si elle ne le trouve pas. Tester la fonc
    cout << "L'état civil est vide" << endl;
  } else {
    int ind;
    for (size_t i = 0; i < table.size(); i += 1) {
      ind = i;
      cout << "\nPersonne[" << ind << "] : \n" << endl << table[ind];
  if (table[ind].enfants.size() > 0) {
          cout << "Nom des enfants : ";
          
    for (size_t i = 0; i < table[ind].enfants.size(); i = i + 1) {
      cout << table[table[ind].enfants[i]].nom << " ";
    }
    cout << "\n";
    }
  }
}
}

EtatCivil creeEtatCivildeTest() {
  EtatCivil demo;
  demo.initialise("Etat civil de Test");
  demo.table.push_back({"Remy", Genre::Masc, 1, -1, -1, {2, 3}});
  demo.table.push_back({"Camille", Genre::Fem, 0, -1, -1, {2, 3}});
  demo.table.push_back({"Noemie", Genre::Fem, -1, 0, 1, {}});
  demo.table.push_back({"Guillaume", Genre::Masc, -1, 0, 1, {4}});
  demo.table.push_back({"Dodi", Genre::Masc, 6, -1, 3, {7}});
  demo.table.push_back({"Sylvaine", Genre::Fem, -1, -1, -1, {6}});
  demo.table.push_back({"Armand", Genre::Masc, 4, -1, 5, {7}});
  demo.table.push_back({"Yuri", Genre::Fem, -1, 4, 6, {}});
  return demo;
}

TEST_CASE("cherche une personne") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(a.cherche("Noemie") == 2);
  // Ajouter d'autre exemples ici
  CHECK(a.cherche("Armand") == 6);
  CHECK(a.cherche("Antoine") == -1);
}

int main(int argc, const char **argv) {

  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit())
    return test_result;

  EtatCivil a;
  a = creeEtatCivildeTest();
  cout << a.nom << endl;
  //a.imprimeIndPersonne(2);
  a.imprimePersonne("Armand");
  a.imprimeEtatCivil();

  return (0);
}
