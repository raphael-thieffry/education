#include <stdexcept>
#include<iostream>
#include<iomanip>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


TEST_SUITE_BEGIN("Structure Date");

struct Date {
  int jour, mois, annee;
};

/** Surcharge de << pour afficher une Date sous le format jj/mm/aaaa
* @param[in] d : Date
**/
std::ostream& operator<< (std::ostream &out, Date d) {
    // Remplacer la ligne suivante par le code adéquat
    out << d.jour <<"/"<< d.mois << "/"<< d.annee;
    return out;
}

/** Surcharge de == pour verifier que deux dates d1 et d2 sont egales
* @param[in] d1 : Date
* @param[in] d2 : Date
* @return le booléen correspondant au test
**/
bool operator==(Date d1, Date d2) {
    return d1.jour == d2.jour and d1.mois == d2.mois and d1.annee == d2.annee;
}

/** Surcharge de != pour verifier que deux dates d1 et d2 sont differentes
* @param[in] d1 : Date
* @param[in] d2 : Date
* @return le booléen correspondant au test
**/
bool operator!=(Date d1, Date d2) {
    return !(d1==d2);
}


TEST_CASE("surcharge ==  et !=") {
   CHECK(Date{1, 1, 2000} == Date{1, 1, 2000});
   CHECK_FALSE(Date{1, 1, 2000} == Date{1, 1, 2018});
   CHECK_FALSE(Date{1, 1, 2000} != Date{1, 1, 2000});
   CHECK(Date{1, 1, 2000} != Date{1, 1, 2018});
}


/** Verifie si une année est bissextile
* @param[in] annee : un entier
* @return le booléen correspondant au test
**/
bool estBissextile(int annee) {
  return (annee % 4 == 0 and annee % 100 != 0) or (annee % 400 == 0);
}


TEST_CASE("fonction estBissextile") {
  CHECK(estBissextile(2000));
  CHECK(estBissextile(2004));
  CHECK(estBissextile(1600));
  CHECK(estBissextile(0));
}



/** Le nombre de jours qu'il y a dans un mois
* @param[in] annee : un entier
* @param[in] mois : un entier entre 1 et 12
* @return le nombre de jours du mois
**/
int nbJourMois(int mois, int annee) {
  switch (mois) {
    case 1 : case 3 : case 5 :
    case 7 : case 8 : case 10 : case 12 : return 31;
    case 4 : case 6 : case 9 : case 11  : return 30;
    case 2 :
      if (estBissextile(annee)) return 29;
      else                      return 28;
    default: throw range_error("Mois invalide");
  }
}

TEST_CASE("fonction nbJourMois") {
   CHECK(nbJourMois(2, 2000) == 29);
  CHECK(nbJourMois(2, 2000)== 29);
  CHECK(nbJourMois(2, 2004)== 29);
  CHECK(nbJourMois(2, 1600)== 29);
  CHECK(nbJourMois(2, 0)==29);
  CHECK(nbJourMois(12, 2000)==31);
}

/** Verifie si une Date est correcte
* @param[in] d : une Date
* @return le booléen correspondant au test
**/
bool estCorrecteDate(Date d) {
  if (d.mois <= 0 or d.mois > 12) return false;
  if (d.jour <= 0) return false;
  return d.jour <= nbJourMois(d.mois, d.annee);
}

/** Surcharge de >> pour lire une Date
**/
std::istream& operator>> (std::istream &in, Date &d) {
    do{
      in >> d.jour >> d.mois >> d.annee;
    }while(not(estCorrecteDate(d)));
    return in;
}


/** Lendemain d'une Date
*  @param[in] d : une date
**/
Date lendemain(Date d) {
  d.jour++;
  if (d.jour > nbJourMois(d.mois, d.annee)) {
    d.jour = 1;
    d.mois++;
    if (d.mois == 13) {
      d.mois = 1;
      d.annee++;
    }
  }
  return d;
}

/** Surcharge de < pour verifier si une date d1 est avant une date d2
* @param[in] d1 : Date
* @param[in] d2 : Date
* @return le booléen correspondant au test
**/
bool operator<(Date d1, Date d2) {
    if(d1.annee == d2.annee){
      if(d1.mois == d2.mois){
        if(d1.jour == d2.jour){
          return false;
        }else{
          return d1.jour < d2.jour;
        }
      }else{
        return d1.mois < d2.mois;
      }
    }else{
      return d1.annee < d2.annee;
    }
}

TEST_CASE("surcharge <") {
   CHECK_FALSE(Date{1, 1, 2000} < Date{1, 1, 1999});
   CHECK_FALSE(Date{1, 1, 2000} < Date{1, 1, 2000});
   CHECK(Date{1, 1, 2000} < Date{28, 3, 2003});
   CHECK_FALSE(Date{1, 12, 2000} < Date{1, 1, 2000});
   CHECK_FALSE(Date{25, 1, 2000} < Date{1, 1, 2000});
}


Date operator+(Date d, int n){
  /*int j = d.jour;
  int m = d.mois;
  int a = d.annee;
  int negJ = nbJourMois(m)-j;
  if(n<negJ){
    return Date{j+n,m,a};
  }
  n-=negJ;
  m++;
  int monthSum = 0;
  for(int i = 0;i<12-m;i++){
    int currentMonth = i+m;
    monthSum += nbJourMois(currentMonth);
  }
  if(estBissextile(int annee) and m>2){
    //tout se passe comme si on avait un jour en plus pour arriver au bout de l'année
    negM = 366-monthSum 
  }else{
    negM = 365-monthSum 
  }
  if(n<negM){
    int monthSum2 = 0;
    int currentMonth2 = 0;
    for(int i = 0;i<12-m;i++){
      currentMonth2 = i+m;
      monthSum2 += nbJourMois(currentMonth2);
      if(n<monthSum2){break;}
    }
    //currentMonth2 - 1 mois apres operation +
    return Date{monthSum2-n,currentMonth2 - 1,a};
  }
  n-=negM;*/
  d.jour += n;
  while(d.jour > nbJourMois(d.mois, d.annee)){
    d.jour-=nbJourMois(d.mois, d.annee);
    d.mois++;
    if(d.mois>12){
      d.mois = 1;
      d.annee++;
    }
  }
  return d;

  /*Date res = d;
  for(int i = 0; i<n; i++){
    res = lendemain(res);
  }
  return res;*/
}

TEST_CASE("Operateur + ") {
   CHECK((Date{1, 1, 2000} + 8) == Date{9, 1, 2000});
   CHECK((Date{1, 1, 2000} + 366) == Date{1, 1, 2001});
   CHECK((Date{1, 1, 2000} + 731) == Date{1, 1, 2002});
   CHECK_FALSE((Date{1, 1, 2000} + 365*12) == Date{1, 1, 2012});
}

int operator-(Date d1, Date d2){
  Date avant, apres;
  if(d2 < d1){
      avant = d2;
      apres = d1;
  }else if(d1 < d2){
      avant = d1;
      apres = d2;
  }else{
      return 0;
  }
  int ecartAnnee = apres.annee-avant.annee;
  int ecartMois = ecartAnnee*12+(apres.mois-1)-(avant.mois-1); //forcement positif
  int Djours = (apres.jour-avant.jour);
  int monthSum = 0;
  int currentMonth;
  int passedYears = 0;
  for(int i = 0;i<ecartMois;i++){
    currentMonth = ((i+avant.mois-1) % 12 ) + 1;
    if(currentMonth-1 == 0 and i!=0){
        passedYears++;
    }
    monthSum += nbJourMois(currentMonth, avant.annee+passedYears);
  }
  return monthSum+Djours;
}

TEST_CASE("Operateur - ") {
   CHECK((Date{1, 1, 2000} - Date{1, 1, 2001}) == 366);
   CHECK((Date{11, 7, 1644} - Date{6, 6, 1944}) == 109537 );
   CHECK((Date{6, 7, 1644} - Date{11, 6, 1944}) == 109547  );
   CHECK((Date{13, 5, 2006} - Date{26, 3, 2021}) == 5431   );

}

int jourDate(Date d){
  int diffJour = d - Date{1, 1, 2000};
  int resteDelaDivision = diffJour % 7;
  switch(resteDelaDivision){
    case 0 : return 5; //"samedi";
    case 1: return 6; //"dimanche";
    case 2: return 0; //"lundi";
    case 3: return 1; //"Mardi";
    case 4: return 2; //"Mercredi";
    case 5: return 3; //"Jeudi";
    case 6: return 4; //"Vendredi";
    default: return -1;
  }
}

TEST_CASE("fonction jourDate") {
   CHECK(jourDate({1, 1, 2000}) == 5 );
   CHECK(jourDate({28, 3, 2003}) == 4 );
   CHECK(jourDate({26, 3, 2005}) == 5 );
   CHECK(jourDate({31, 12, 1999}) == 4 ); //le code de la fonction ne fonctionne pas pour les dates anterieures à l'an 2000
}



TEST_SUITE_END();

int main(int argc, const char** argv) {

  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;


  Date aujourdhui;

  aujourdhui = {16, 02, 2022};
  cout << "Entrez la date d'aujourd'hui : ";
  cin >> aujourdhui;
  cout << "Aujoud'hui : ";
  cout << aujourdhui;
  cout << endl;

  Date demain = lendemain(aujourdhui);

  cout << "Demain : ";
  cout << demain;
  cout << endl;


  int n = 8;
  cout << "dans " << n << " jours c'est: ";
  cout << aujourdhui+n;
  cout << endl;

}
