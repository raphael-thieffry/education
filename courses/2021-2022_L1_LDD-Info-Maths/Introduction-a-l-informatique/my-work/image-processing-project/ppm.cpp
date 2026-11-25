#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/

#include <iostream>
#include <fstream>
#include "image.h"
#include "ppm.h"

vector<string> split2(string chaine, char delimiter){  
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


Image lirePPM(string source) {
    Image ppm_tableau;
    ifstream ppm;
    ppm.open(source);
    string line;
    vector<string> T = {};
    int l = 1;
    int i = 0, j = 0, c = 1;
    int h, w;
    while(getline(ppm, line)){
        T = split2(line);
        if(l == 1 && T[0][0] != '#' && T[0] == "P3"){
            l++;
        } else if(l==1 && T[0][0] != '#'  && T[0] != "P3"){
            throw runtime_error("Le type d'image n'est pas P3");
        } else if(l == 2 && T[0][0] != '#'){
            l++;
            w = stoi(T[0]);
            h = stoi(T[1]);
            ppm_tableau = Image(h);
            for(auto &sous_tableau : ppm_tableau){
                sous_tableau = vector<Couleur>(w); //
            }
            
        } else if(l == 3 && T[0][0] != '#'){
            l++;
        } else if(l > 3 && T[0][0] != '#'){
            for(string v: T){
                if(j >= w){
                    i++;
                    j = 0;
                } 
                if(c == 1){
                    ppm_tableau[i][j].r = stod(v);
                    c++;
                }else if(c == 2){
                    ppm_tableau[i][j].g = stod(v);
                    c++;
                }else if(c == 3){
                    ppm_tableau[i][j].b = stod(v);
                    c = 1;
                    j++;
                }
            }
        }
    }
    ppm.close();
    return ppm_tableau;
}
void ecrirePPM(Image img, string cible) { //int ???!???
    ofstream fichier_c;
    fichier_c.open(cible);
    if (not fichier_c) throw runtime_error("Fichier non trouve: "+cible);
    fichier_c << "P3" << endl << img[0].size() << " " << img.size() << endl;
    fichier_c << 255 << endl;
    for(int i = 0; i < img.size(); i++) {
        for(int j = 0; j < img[i].size(); j++){
            fichier_c << (int)img.at(i).at(j).r << " " << (int)img.at(i).at(j).g << " " << (int)img.at(i).at(j).b << " ";
        }
        fichier_c << endl;   
    }
    fichier_c.close();
}
