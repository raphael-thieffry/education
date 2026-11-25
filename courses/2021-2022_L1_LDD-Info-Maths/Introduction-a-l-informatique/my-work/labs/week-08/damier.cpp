#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ofstream fichier;                           // Déclaration
    fichier.open("images/damier-automatique.pbm");                    // Ouverture
    fichier << "P1" << endl << "100 100"<<endl;           // Écriture
    for(int i = 0; i < 100;i++){
        for(int j = 0; j < 100;j++){
            if(i%2 == 0){
                if(j%2 == 0){
                    fichier<<"0 ";
                }else{
                    fichier<<"1 ";
                }
            }else{
                if(j%2 == 0){
                    fichier<<"1 ";
                }else{
                    fichier<<"0 ";
                }
            }
        }
        fichier<<endl;
    }
    fichier.close(); 
}

