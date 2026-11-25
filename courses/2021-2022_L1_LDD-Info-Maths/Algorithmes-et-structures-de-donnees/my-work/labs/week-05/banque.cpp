#include <iostream>
using namespace std;

int compte1 = 1000;
int compte2 = 2000;
int compte3 = 1500;
int compte4 = 3000;

void etat_comptes();
bool virement(int &compte_orig, int &compte_dest, int somme);

void etat_comptes() {
  cout << "Etat des comptes : " << endl;
  cout << "Compte n 1 : " << compte1 << endl;
  cout << "Compte n 2 : " << compte2 << endl;
  cout << "Compte n 3 : " << compte3 << endl;
  cout << "Compte n 4 : " << compte4 << endl;
}
bool virement(int &compte_orig, int &compte_dest, int somme){
  if(compte_orig-somme<0)return false;
  compte_orig -= somme;
  compte_dest +=somme;
  return true;
}
int main() {
  bool v;
  etat_comptes();
  v = virement(compte1, compte2, 100);
  cout<<"virement "<< (v? "effectué": "impossible")<< endl;
  etat_comptes();
  return 0;
}
