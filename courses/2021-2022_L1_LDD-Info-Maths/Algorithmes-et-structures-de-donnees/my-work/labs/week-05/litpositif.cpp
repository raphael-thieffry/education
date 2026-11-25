#include<iostream>
#include<string>

using namespace std;

void litpositif(int &val, int &e) {
  int resultat;
  int i = 0;
  do {
    cout << "Donner la valeur d'un entier positif : ";
    cin >> resultat;
    i++;
  } while (resultat < 0);
  e = i-1;
  val = resultat;
}

int main() {
  int val,e;
  litpositif(val,e);
  cout<<val<<"    "<<e<<endl;
    return 0;
}
