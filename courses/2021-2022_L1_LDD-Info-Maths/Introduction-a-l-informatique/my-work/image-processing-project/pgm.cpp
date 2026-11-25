#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.h"
#include "pgm.h"


vector<string> split(string chaine, char delimiter){  
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


ImageGris lirePGM(string source) {
    ImageGris pgm_tableau;
    ifstream pgm;
    pgm.open(source);
    string line;
    vector<string> T = {};
    int l = 1;
    int i = 0, j = 0;
    int h, w;
    while(getline(pgm, line)){
        T = split(line);
        if(l == 1 && T[0][0] != '#' && T[0] == "P2"){
            l++;
        } else if(l==1 && T[0][0] != '#'  && T[0] != "P2"){
            throw runtime_error("Le type d'image n'est pas P2");
        } else if(l == 2 && T[0][0] != '#'){
            l++;
            w = stoi(T[0]);
            h = stoi(T[1]);
            pgm_tableau = ImageGris(h);
            for(auto &sous_tableau : pgm_tableau){
                sous_tableau = vector<double>(w);
            }
            
        } else if(l == 3 && T[0][0] != '#'){
            l++;
        } else if(l > 3 && T[0][0] != '#'){
            for(string v: T){
                if(j >= w){
                    i++;
                    j = 0;
                }
                pgm_tableau[i][j] = stod(v);
                j++;
            }
        }
    }
    pgm.close();
    if(pgm_tableau.size() == 0) throw runtime_error("Image vide");
    return pgm_tableau;
}

void ecrirePGM(ImageGris img, string cible)
{
    ofstream fichier_c;
    fichier_c.open(cible);
    if (not fichier_c)
        throw runtime_error("Fichier non trouve: " + cible);
    fichier_c << "P2" << endl
              << img[0].size() << " " << img.size() << endl;
    fichier_c << 255 << endl;
    for (int i = 0; i < img.size(); i++)
    {
        for (int j = 0; j < img[i].size(); j++)
        {
            fichier_c << (int)img.at(i).at(j) << " ";
        }
        fichier_c << endl;
    }
    fichier_c.close();
}

ImageGris inversePGM(ImageGris img)
{
    ImageGris img_inverse;
    img_inverse = ImageGris(img.size());
    for (int i = 0; i < img.size(); i++)
    {
        img_inverse[i] = vector<double>(img[i].size());
        for (int j = 0; j < img[i].size(); j++)
        {
            img_inverse[i][j] = 255 - img[i][j];
        }
    }
    return img_inverse;
}

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision)
{
    if (a.size() != b.size())
    {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i = 0; i < a[0].size(); i++)
        if (a[0].size() != b[i].size())
        {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision)
            {
                cout << "Valeur differentes en position " << i << "," << j
                     << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}
