#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    int a = 17;
    int b = 23;
    ofstream fichier;                           // Déclaration
    fichier.open("essai.txt");                    // Ouverture
    fichier << a << " fois " << b << " vaut " << a*b << endl;           // Écriture
    fichier.close();                            // Fermeture
}


