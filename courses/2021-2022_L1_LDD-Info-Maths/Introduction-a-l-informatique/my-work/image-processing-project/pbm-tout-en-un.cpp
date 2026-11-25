#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>


using namespace std;

typedef vector<vector<int>> ImageNB;


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

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/

ImageNB lirePBM(string source) {
    ImageNB res;
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
            res = ImageNB(h);
            for(auto &sous_tableau : res){
                sous_tableau = vector<int>(w);
            }
            
        } else if(l > 2 && T[0][0] != '#'){
            for(string v: T){
                if(j >= w){
                    i++;
                    j = 0;
                }
                res[i][j] = stoi(v);
                j++;
            }
        }
    }
    fichier.close();
    return res;
}


/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream outputImg;
    outputImg.open(cible);
    if(not outputImg){
        throw runtime_error("Erreur à l'ouverture du fichier de de sortie");
    }
    outputImg << "P1" << endl;
    int w = img[0].size();
    int h = img.size();
    outputImg << w << " " << h << endl;
    for(int i = 0; i < img.size();i++){
        for(int j = 0; j < img[i].size();j++){
            if(img[i][j] == 1){
                outputImg << 1 << " ";
            }else{
                outputImg << 0 << " ";
            }
        }
        outputImg << endl;
    }
    outputImg.close(); 
}



/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    for(int i = 0; i<img.size(); i++){
        for(int j = 0; j<img[0].size(); j++){
            if(img[i][j] == 1){
                cout << "@ ";
            }else{
                cout << "  ";
            }
        }
        cout << endl;
    }
}


/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    
    ImageNB res;
    res = ImageNB(img.size());
    for(int i = 0; i<img.size(); i++){
        res[i] = vector<int>(img[i].size());
        for(int j = 0; j<img[i].size(); j++){
            if(img[i][j] == 1){
                res[i][j] = 0;
            }else{
                res[i][j] = 1;
            }
        }
    }
    return res;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    vector<vector<int>> test = {{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0},{0,1,0,1,0}};
    ecrirePBM( test , "pbm/test.pbm");
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
    
    //cout << "Fini" << endl;

}

int main(){
    testLirePBM();
    affichePBM(inversePBM(lirePBM("images/smiley.pbm")));
    return 0;
}

