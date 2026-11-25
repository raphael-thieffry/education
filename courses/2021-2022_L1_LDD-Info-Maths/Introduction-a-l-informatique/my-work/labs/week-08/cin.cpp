#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

int main () {
    int a;
    int b;
    cout<< "valeur de a ?"<<endl;
    cin>>a;
    cout<< "valeur de b ?"<<endl;
    cin>>b;
    ofstream fichier;                           // Déclaration
    fichier.open("multiplication.txt");                    // Ouverture
    fichier << a << " fois " << b << " vaut " << a*b << endl;           // Écriture
    fichier.close();  
}


