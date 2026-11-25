#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;


/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double>> ImageGris;

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
    return pgm_tableau;
}

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream fichier_c;
    fichier_c.open(cible);
    if (not fichier_c) throw runtime_error("Fichier non trouve: "+cible);
    fichier_c << "P2" << endl << img.at(0).size() << " " << img.size() << endl;
    fichier_c << 255 << endl;
    for(int i = 0; i < img.size(); i++) {
        for(int j = 0; j < img.at(i).size(); j++){
            fichier_c << (int)img.at(i).at(j) << " ";
        }
        fichier_c << endl;   
    }
    fichier_c.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
    ImageGris img_inverse;
    img_inverse = ImageGris(img.size());
    for(int i = 0; i < img.size(); i++) {
        img_inverse.at(i) = vector<double>(img.at(i).size());
        for(int j = 0; j < img.at(i).size(); j++){
            img_inverse.at(i).at(j) = 255 - img.at(i).at(j);
        }
    }
    return img_inverse;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}


int main() {
    lirePGMTest();
    lirePGM("./images/brain.pgm");
    inversePGMTest();
    return 0;
}

