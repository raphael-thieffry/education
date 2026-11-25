#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    int w = 1000;
    int h = 1000;
    ofstream fichier;                           // Déclaration
    fichier.open("images/degrade.pgm");                    // Ouverture
    fichier << "P2" << endl << w << " " << h << endl << w<< endl;           // Écriture
    for(int i = 0; i < h;i++){
        for(int j = 0; j < w;j++){
            fichier<<(j+i)/2<<" ";
        }
        fichier<<endl;
    }
    fichier.close(); 
}



