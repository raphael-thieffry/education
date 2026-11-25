#include <stdexcept>
#include <fstream>
#include <iostream>
using namespace std;

/** Image en vidéo inverse
* @param image1: le nom du fichier contenant l’image \'a lire
* @param image2: le nom du fichier pour l’image à écrire **/
void videoInverse(string image1, string image2){
    ifstream inputImg;
    ofstream outputImg;
    inputImg.open(image1);
    if(not inputImg){
        throw runtime_error("Erreur à l'ouverture du fichier d'entrée");
    }
    string dtCollect;
    inputImg >> dtCollect;
    if(dtCollect == "P2"){
        outputImg.open(image2);
        if(not outputImg){
            throw runtime_error("Erreur à l'ouverture du fichier de de sortie");
        }
        inputImg >> dtCollect;
        int w = stoi(dtCollect);
        inputImg >> dtCollect;
        int h = stoi(dtCollect);
        inputImg >> dtCollect;
        int shade = stoi(dtCollect);
        outputImg << "P2" << endl << w << " " << h << endl << shade << endl;           // Écriture
        for(int i = 0; i < h;i++){
            for(int j = 0; j < w;j++){
                inputImg >> dtCollect;
                outputImg <<shade-stoi(dtCollect)<<" ";
            }
            outputImg<<endl;
        }
        outputImg.close(); 
    }
    inputImg.close();
}

int main () {
    string image1, image2;
    cout << "Veuillez indiquer le nom de fichier de l'image à inverser." << endl;
    cin >> image1;
    cout << "Où voulez-vous sauvegarder l'image inversée ?" << endl;
    cin >> image2;
    videoInverse(image1, image2);
    return 0;
}

