#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <ctype.h>  // tolower
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl

enum class Tril { faux, inc, vrai };

Tril saisie() {
  char c;
  bool ok = false;
  Tril res;
  do {
    cout << "Donner un tril (v/f/i) : ";
    cin >> c;
    switch (c) {
      case 'v' : case 'V' : res = Tril::vrai; ok = true; break;
      case 'f' : case 'F' : res = Tril::faux; ok = true; break;
      case 'i' : case 'I' : res = Tril::inc; ok = true; break;
      default : cout << "erreur !" << endl;
    }
  } while (not ok);
  return res;
}

void affiche(Tril t) {
  string res;
      switch (t) {
        case Tril::vrai : res = "vrai" ;   break;
        case Tril::faux : res = "faux";    break;
        case Tril::inc  : res = "inconnu"; break;
      default : cout << "erreur !" << endl;
    }
    cout<<res<<endl;
}

bool to_bool(Tril t) {
  switch(t){
    case Tril::vrai : return true;
    case Tril::faux : return false;
    case Tril::inc  : throw logic_error("Impossible de convertir inc en bool");break;
  }
}

Tril from_bool(bool b) {
  if(b){
    return Tril::vrai;
  }
  return Tril::faux;
}


Tril non(Tril t) {
  try{
    bool b = to_bool(t);
    return from_bool(!b);
  }catch(logic_error){
    return Tril::inc;
  }
}

void test_non() {
  ASSERT(non(Tril::vrai) == Tril::faux);
  ASSERT(non(Tril::faux) == Tril::vrai);
  ASSERT(non(Tril::inc) == Tril::inc);
}

Tril et(Tril a, Tril b) {
  if(a == Tril::faux or b == Tril::faux ) return Tril::faux;
  if(a == Tril::inc or b == Tril::inc) return Tril::inc;
  return Tril::vrai;
}

void test_et() {
  ASSERT(et(Tril::vrai,Tril::faux) == Tril::faux);
  ASSERT(et(Tril::vrai,Tril::vrai) == Tril::vrai);
  ASSERT(et(Tril::inc,Tril::faux) == Tril::faux);
  ASSERT(et(Tril::inc,Tril::vrai) == Tril::inc);
  ASSERT(et(Tril::inc,Tril::vrai) == et(Tril::vrai,Tril::inc));
  ASSERT(et(Tril::inc,Tril::inc) == et(Tril::inc,Tril::inc));
}

int main() {
  affiche(Tril::vrai);
  affiche(Tril::faux);
  affiche(Tril::inc);
  test_non();
  test_et();
//  test_ou();
//  test_et_ou();
  return EXIT_SUCCESS;
}
