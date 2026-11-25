#include<iostream>
#include<iomanip>
#include <vector>
using namespace std;
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
				       << " line " << __LINE__ << ": " #test << endl

struct Date {
  int jour, mois, annee;
};

/** Affiche une Date sous le format jj/mm/aaaa
* @param[in] d : la date
**/
void afficheDate(Date d) {
  cout << setfill('0') << setw(2) << d.jour << "/"
       << setfill('0') << setw(2) << d.mois << "/" << d.annee;
}

/** Teste si une année est bissextile
* @param[in] annee : un entier
* @return le booléen correspondant au test
**/
bool estBissextile(int annee) {
  return (annee % 4 == 0 and annee % 100 != 0) or (annee % 400 == 0);
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
    else                     return 28;
  default: return -1;
  }
}

/** Teste si une Date est correcte
* @param[in] d : une date
* @return le booléen correspondant au test
**/
bool estCorrecteDate(Date d) {
  if (d.mois <= 0 or d.mois > 12) return false;
  if (d.jour <= 0) return false;
  return d.jour <= nbJourMois(d.mois, d.annee);
}

/** Demande une Date à l'utilisateur
*   Si la date n'est pas correcte, une nouvelle date est demandée
* @return une Date
**/
Date lireDate() {
  Date res;
  bool erreur;
  do {
    cout << "jour ? "; cin >> res.jour;
    cout << "mois ? "; cin >> res.mois;
    cout << "annee ? "; cin >> res.annee;
    erreur = not estCorrecteDate(res);
    if (erreur) cout << "Date incorrecte !" << endl;
  } while (erreur);
  return res;
}

/** Le bug de l'an 2000
* @return le premier janvier 2000
**/
Date bugday() {
  return {1, 1, 2000};
}

/** Le bug de l'an 2000
* @param[out] d reçoit le bug day
**/
void bugdayRef(Date &d) {
  d = {1, 1, 2000};
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
bool avantDate(Date d1, Date d2){
  if(d1.annee == d2.annee){
    if(d1.mois == d2.mois){
      if(d1.jour == d2.jour){
        return false;
      }else if (d1.jour > d2.jour){
        return false;
      }
    }else if (d1.mois > d2.mois){
      return false;
    }
  }else if (d1.annee > d2.annee){
    return false;
  }
  return true;
}

Date ajouteDate(Date d, int n){
  for(int i = 0; i<n; i++){
    d = lendemain(d);
  }
  return d;
}

bool dateEgal(Date d1, Date d2){
    return d1.jour == d2.jour and d1.mois == d2.mois and d1.annee == d2.annee;
}
int differenceDate(Date d1, Date d2){
  Date avant = d2;
  Date apres = d1;
  if(avantDate(d1, d2)){
    avant = d1;
    apres = d2;
  }
  int counter = 0; 
  while(true){
    if(dateEgal(avant, apres)) break;
    avant = lendemain(avant);
    counter++;
  }
  return counter;
}
//samedi = 5
int jourDate(Date d){
  int dif = differenceDate({1,1,2000}, d);
  if(avantDate({1,1,2000},d)){
    return (dif+5)%7;
  }else if(dateEgal(d, {1,1,2000})){
    return 5;
  }else{
    return 6-(dif+1)%7;
  }
}
/*void testNewFunctionsTp1(){
  ASSERT(jourDate({1,5,1999}) == 5);
  ASSERT(jourDate({23,12,2003}) == 1);
  ASSERT(differenceDate({1,1,2000}, {1,2,2000}) == 31);
  ASSERT(ajouteDate({1,1,2000},31) == {1,2,2000});
  ASSERT(avantDate({1,1,2000},{28,3,2003}));
}*/
//*** Dommage, marche seulement en C++20 (mais depuis C99).
// Date bugdayInit() {
//   return { .jour = 1, .mois = 1, .annee = 2000 };
// }
vector<string> nom_mois = {
"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
"Aout", "Septembre", "Octobre", "Novembre", "Decembre"
};
vector<int> long_mois = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void calendrier(int annee){
  for(int i = 0; i<12;i++){
    string space = "";
    for(int l = 0; l<(22-int(nom_mois[i].length()))/2;l++){
      space+=" ";
    }
    cout<<space<<nom_mois[i]<<endl;
    cout<< " lu ma me je ve sa di"<<endl;
    int jourN1 = jourDate({1,i+1,annee});
    int jourMax = nbJourMois(i+1, annee);
    for(int j = 0; j<6;j++){ //semaine
      for(int k = 0; k<7;k++){ //jour 6*7=42 cases, 6 semaines
        if(j == 0 and k<jourN1){//pour la 1ere semaine on regarde combien de . sont necessaires
          cout << setfill(' ') << setw(3) << ".";
        }else if(k+(j*7)<jourMax+jourN1){
          cout << setfill(' ') << setw(3) << k+1+j*7-jourN1;
        }
      }
      cout<<endl;
    }
  }
}

int main() {
  Date d = {3, 11, 1974};

  Date aujourdhui;
  aujourdhui = lireDate();
  cout << "Aujoud'hui : ";
  afficheDate(aujourdhui);
  cout << endl;

  Date demain = lendemain(aujourdhui);

  cout << "Demain : ";
  afficheDate(demain);
  cout << endl;

  cout << "BugDay : ";
  afficheDate(bugday());
  cout << endl;

  cout << "BugDay Ref: ";
  bugdayRef(d);
  afficheDate(d);
  cout << endl;
  //testNewFunctionsTp1(); erreur dans la fonction assert elle meme
  calendrier(d.annee);
  cout << endl;
}
