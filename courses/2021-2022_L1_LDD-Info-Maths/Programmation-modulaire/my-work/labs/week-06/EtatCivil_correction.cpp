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
void imprimeIndPersonne(const EtatCivil &a, int ind);
int cherche(const EtatCivil &a, string nom);
void imprimePersonne(const EtatCivil &a, string nom);
void imprimeEtatCivil(const EtatCivil &a);
int personne(EtatCivil &a, string sonNom, Genre s);
bool mariage(EtatCivil &a, string lun, string lautre);
bool naissance(EtatCivil &a, string qui, Genre s, string parent1, string parent2);
bool ascendantI(const EtatCivil &a, string qui, string ancetre);
bool ascendantR(const EtatCivil &a, string qui, string ancetre);

// Surcharge de l'operator << pour enum Genre
std::ostream &operator<<(std::ostream &out, Genre g) {
  if (g == Genre::Masc)
    out << "Genre masculin";
  else
    out << "Genre feminin";
  return out;
}

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

// Surcharge de l'operateur << pour struct état civil
std::ostream &operator<<(std::ostream &out, EtatCivil a) {
  if (a.table.size() == 0) {
    out << "L'état civil est vide" << endl;
  } else {
    for (size_t i = 0; i < a.table.size(); i += 1) {
      imprimeIndPersonne(a, i);
    }
  }
  return out;
}

void initialise(EtatCivil &a, string nom) {
  a.nomEtatCivil = nom;
  a.table.clear(); // autre possibilité: a.table = vector<Personne>(0);
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

/* fonction auxiliaire, pour faciliter l'ecriture des autres fonctions
 * Elle prend un indice de personne en second parametre
 */
void imprimeIndPersonne(const EtatCivil &a, int ind) {
  cout << "\nPersonne[" << ind << "] : \n" << endl << a.table[ind];
  if (a.table[ind].enfants.size() > 0) {
    cout << "Nom des enfants : ";
    for (size_t i = 0; i < a.table[ind].enfants.size(); i = i + 1) {
      cout << a.table[a.table[ind].enfants[i]].nom << " ";
    }
    cout << "\n";
  }
}

/*
 * Renvoie l'indice dans le tableau qui correspond a la personne ou -1 si
 * aucune personne de ce nom n'a ete enregistree.
 */
int cherche(const EtatCivil &a, string nom) {
  for (size_t i = 0; i < a.table.size(); i++) {
    if (nom == a.table[i].nom)
      return i;
  }
  return -1;
}

TEST_CASE("cherche une personne") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(cherche(a, "Noemie") == 2);
  // Ajouter d'autre exemples ici
  CHECK(cherche(a, "Armand") == 6);
  CHECK(cherche(a, "Antoine") == -1);
}

/* imprime les infos d'une personne dont on passe le nom en parametre */
void imprimePersonne(const EtatCivil &a, string nom) {
  int ind = cherche(a, nom);
  if (ind < 0) {
    throw invalid_argument("Nom incorrect dans imprimePersonne: ");
  } else {
    imprimeIndPersonne(a, ind);
  }
}

void imprimeEtatCivil(const EtatCivil &a) {
  if (a.table.size() == 0) {
    cout << "L'état civil est vide" << endl;
  } else {
    for (size_t i = 0; i < a.table.size(); i += 1) {
      imprimeIndPersonne(a, i);
    }
  }
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
  if (sonNom.size() == 0) {
    return -3;
  }; /* pas de nom vide */
  if (cherche(a, sonNom) != -1) {
    return -2;
  }
  vector<int> enfants;  // vector vide.
  Personne p = {sonNom, s, -1, -1, -1, enfants};
  a.table.push_back(p);
  return a.table.size() - 1;
}

TEST_SUITE_BEGIN("Structure EtatCivil");

TEST_CASE("Ajout d'une personne") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  CHECK(personne(a, "Lamia", Genre::Fem) == 8);
  CHECK(personne(a, "Lamia", Genre::Fem) == -2);
  CHECK(personne(a, "Antoine", Genre::Masc) == 9);
  CHECK(personne(a, "Antoine", Genre::Masc) == -2);
  CHECK(personne(a, "Noemie", Genre::Masc) == -2);
  CHECK(personne(a, "", Genre::Masc) == -3);
}


bool mariage(EtatCivil &a, string lun, string lautre) {
  int ilun = cherche(a, lun), ilautre = cherche(a, lautre);
  if (ilun < 0 or ilautre < 0 or ilun == ilautre) {
    return false;
  }
  if (a.table[ilun].indConjoint != -1 or a.table[ilautre].indConjoint != -1) {
    return false;
  }
  a.table[ilun].indConjoint = ilautre;
  a.table[ilautre].indConjoint = ilun;
  return true;
}

TEST_CASE("Mariage de deux personnes") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  personne(a, "Lamia", Genre::Fem);
  CHECK(mariage(a, "Lamia", "Yuri"));
  CHECK_FALSE(mariage(a, "Guillaume", "Yuri"));
}

/* Enregistre la naissance (en creant la personne) et renvoie true/false selon
 * qu'elle est validee ou pas.
 * Les parents doivent exister et etre maries (entre eux !)
 * S'il y a une erreur, la nouvelle personne n'est PAS enregistree.
 */
bool naissance(EtatCivil &a, string qui, Genre s, string p1, string p2) {
  int iqui, ip1, ip2;

  ip1 = cherche(a, p1);
  ip2 = cherche(a, p2);
  // ATTENTION: ici ne pas utiliser la fonction mariage de la question
  // precedente car celle-ci ne teste pas si deux personnes sont mariees
  // mais elle les marient s'ils etaient celibataires ! On doit donc
  // refaire les tests, mais ici plus simples.
  if (ip1 == -1 or ip2 == -1 or
      a.table[ip1].indConjoint != ip2
      // ce dernier test est inutile si la fonction mariage est correcte:
      // si l'un est conjoint de l'autre, la reciproque doit etre vraie aussi
      // !
      or a.table[ip2].indConjoint != ip1) {
    return false;
  }

  // essayer d'ajouter le nouveau-ne
  iqui = personne(a, qui, s);
  if (iqui < 0) {
    return false;
  }

  // enregistrer la filiation dans les deux sens: de l'enfant vers les
  // parents et l'inverse.
  a.table[iqui].indParent1 = ip1;
  a.table[ip1].enfants.push_back(iqui);

  a.table[iqui].indParent2 = ip2;
  a.table[ip2].enfants.push_back(iqui);

  return true;
}

TEST_CASE("Naissance d'un bébé") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  personne(a, "Lamia", Genre::Fem);
  mariage(a, "Lamia", "Yuri");
  CHECK(naissance(a, "Christophe", Genre::Masc, "Lamia", "Yuri"));
  CHECK_FALSE(naissance(a, "Dina", Genre::Masc, "Noemie", "Yuri"));
}

/* Version itérative de la recherche d'ascendant
 * Recherche un lien de parente en partant de 'qui' et en remontant la chaine de
 * parents pour essayer de tomber sur 'ancestor'. On arrete de remonter quand on
 * tombe sur -1 pour les parents, et on recherche dans la pile une autre branche
 * a remonter (a chaque etape on depile un element et on en empile entre 0 et 2.
 * Ca termine si le graphe est bien sans cycle).
 */
bool ascendantI(const EtatCivil &a, string qui, string ancetre) {
  vector<int> pile;
  int iqui = cherche(a, qui), iancetre = cherche(a, ancetre);
  if (iqui < 0 or iancetre < 0) {
    return false;
  }
  pile.push_back(iqui);  // On empile l'indice de depart
  // pile des indices des personnes a tester: on remonte dans l'arbre
  // genealogique.
  while (pile.size() > 0) {
    int courant = pile[pile.size() - 1];
    pile.pop_back();
    if (courant == iancetre) {
      return true;
    } else {
      // ajouter ses parents, si connus, dans la pile des personnes a
      // tester
      int i1 = a.table[courant].indParent1;
      int i2 = a.table[courant].indParent2;
      if (i1 != -1) {
        pile.push_back(i1);
      }
      if (i2 != -1) {
        pile.push_back(i2);
      }
    }
  }
  /* fin de la boucle: on a visite tous les ancetres sans trouver indParent */
  return false;
}

TEST_CASE("ascendent itiratif") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  personne(a, "Lamia", Genre::Fem);
  mariage(a, "Lamia", "Yuri");
  naissance(a, "Christophe", Genre::Masc, "Lamia", "Yuri");
  CHECK(ascendantI(a, "Christophe", "Remy"));
  CHECK_FALSE(ascendantI(a, "Christophe", "Noemie"));
}



/* version recursive de la recherche d'ascendant. On utilise une fonction
 * auxiliaire pour ne pas faire plusieurs fois les tests de validite des indices
 */
bool ascendantAux(const EtatCivil &a, int iqui, int iancetre) {
  int i1, i2;
  if (iqui == iancetre) {
    return true;
  }
  // on remonte dans l'arbre a la recherche de l'ancetre. Plus efficace
  // que de descendre de l'ancetre vers les enfants qui explorerait aussi
  // les cousins (eloignes)
  i1 = a.table[iqui].indParent1;
  i2 = a.table[iqui].indParent2;
  return (i1 != -1 and ascendantAux(a, i1, iancetre)) or
         (i2 != -1 and ascendantAux(a, i2, iancetre));
}

bool ascendantR(const EtatCivil &a, string qui, string ancetre) {
  int iqui = cherche(a, qui), iancetre = cherche(a, ancetre);

  if (iqui < 0 or iancetre < 0) {
    return false;
  }
  // ca trivial qu'on regle tout de suite.
  if (iqui == iancetre) {
    return true;
  }
  return ascendantAux(a, iqui, iancetre);
}

TEST_CASE("ascendent recursif") {
  EtatCivil a;
  a = creeEtatCivildeTest();
  personne(a, "Lamia", Genre::Fem);
  mariage(a, "Lamia", "Yuri");
  naissance(a, "Christophe", Genre::Masc, "Lamia", "Yuri");

  CHECK(ascendantR(a, "Christophe", "Remy"));
  CHECK_FALSE(ascendantR(a, "Christophe", "Noemie"));
}

TEST_SUITE_END();


/* On utilise une fonction auxiliaire pour indiquer la génération et pour
 * ne pas faire plusieurs fois les tests de validite des indices
 */
void AfficheArbreGenePersonneAux(int ind, EtatCivil EC, int generation) {
    int i = 0;
    cout << "Individu ";
    if (ind == -1) {
        cout << "inconnu" << endl;
    } else {
        cout << ind << endl;
        for (i=0; i < generation; i++)
            cout << "   ";
        AfficheArbreGenePersonneAux(EC.table[ind].indParent1, EC, generation+1);
        for (i=0; i < generation; i++)
            cout << "   ";
        AfficheArbreGenePersonneAux(EC.table[ind].indParent2, EC, generation+1);
    }
}

void AfficheArbreGenePersonne(int ind, EtatCivil EC) {
    int generation = 1;
    if (ind >= EC.table.size())
        cout << "La personne d'indice " << ind << " n'existe pas." << endl;
    else
        AfficheArbreGenePersonneAux(ind, EC, generation);
}

/* Cl-dessous la fonction exit() permet de quitter immediatement le
 * programme (et pas seulement la fonction courante). Ici on s'en sert
 * pour quitter le programme des qu'un test echoue.
 * La convention est qu'on passe en parametre 0 si le programme est considere
 * en succes et autre chose (ici 1) si il est considere en echec
 */
int main(int argc, const char **argv) {

  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit())
    return test_result;

  EtatCivil a;
  a = creeEtatCivildeTest();
  imprimeIndPersonne(a, 0);
  cout << a;

  return (0);
}
