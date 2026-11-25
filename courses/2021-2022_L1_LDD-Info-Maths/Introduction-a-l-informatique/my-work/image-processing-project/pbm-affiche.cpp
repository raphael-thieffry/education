#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>
#include "image.h"


/** Permet de creer un tableau composé de tout les mots/élements d'une chaine de caractère
 * @param string la chaine de caractère à séparer
 * @param char le délimiteur pour la séparation (par défaut un espace)
 * @return un tableau composé de tout les mots/elements de la chaines
 **/
vector<string> split(string chaine, char delimiter = ' '){
    string s = "";
    vector<string> T = {};
    for(int i = 0; i < chaine.size(); i++){
        if(chaine[i] == delimiter && s != ""){
            T.push_back(s);
            s = "";
        } else if(chaine[i] != delimiter) s += chaine[i];
    }
    if(s != "") T.push_back(s);
    return T;

}

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream fichier;
    fichier.open(source);
    string line;
    vector<string> T = {};
    int l = 1;
    int i = 0, j = 0;
    int h, w;
    while(getline(fichier, line)){
        T = split(line);
        if(l == 1 && T[0][0] != '#' && T[0] == "P1"){
            l++;
        } else if(l==1 && T[0][0] != '#'  && T[0] != "P1"){
            throw runtime_error("Le type d'image n'est pas P1");
        } else if(l == 2 && T[0][0] != '#'){
            l++;
            w = stoi(T[0]);
            h = stoi(T[1]);
            
        } else if(l > 2 && T[0][0] != '#'){
            for(string v: T){
                if(j >= w){
                    i++;
                    j = 0;
                    cout << endl;
                }   
                if(v == "0") cout << "  "; else cout << "@ ";
                j++;
            }
        }
    }
    fichier.close();
}
/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream inputImg;
    ofstream outputImg;
    inputImg.open(source);
    if(not inputImg){
        throw runtime_error("Erreur à l'ouverture du fichier d'entrée");
    }
    string dtCollect;
    inputImg >> dtCollect;
    if(dtCollect == "P1"){
        outputImg.open(cible);
        if(not outputImg){
            throw runtime_error("Erreur à l'ouverture du fichier de de sortie");
        }
        inputImg >> dtCollect;
        int w = stoi(dtCollect);
        inputImg >> dtCollect;
        int h = stoi(dtCollect);
        outputImg << "P1" << endl << w << " " << h << endl;           // Écriture
        for(int i = 0; i < h;i++){
            for(int j = 0; j < w;j++){
                inputImg >> dtCollect;
                outputImg << 1 - stoi(dtCollect) << " ";
            }
            outputImg << endl;
        }
        outputImg.close(); 
    }
    inputImg.close();
}



int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dosier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}
