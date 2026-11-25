#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;


/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};

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
    fichier_c << "P2" << endl << img[0].size() << " " << img.size() << endl;
    fichier_c << 255 << endl;
    for(int i = 0; i < img.size(); i++) {
        for(int j = 0; j < img[i].size(); j++){
            fichier_c << (int)img.at(i).at(j) << " ";
        }
        fichier_c << endl;
      //  cout<<"ecriture"<<endl;

    }
    fichier_c.close();
}

ImageGris intensiteH(ImageGris img) {
    ImageGris res;

    res = ImageGris(img.size());
    for(int i = 0; i<img.size();i++){
        res[i] = vector<double>(img[i].size());
        
        for(int j = 0; j<img[i].size();j++){
            if((i != 0 and j != 0) and (i != img.size()-1 and j != img[0].size()-1)){
                res[i][j] = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
            }else{
                res[i][j] = 0;
            }
        }
    }
    return res;
}



/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img) {
    ImageGris res;

    res = ImageGris(img.size());
    for(int i = 0; i<img.size();i++){
        
        //cout<<"nouvelle ligne intensV"<<endl;
        res[i] = vector<double>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            if((i != 0 and j != 0) and (i != img.size()-1 and j != img[0].size()-1)){
                //cout<<"je calcule"<<endl;
                res[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1]- img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
                
            }else{
                //cout<<"je fais rien"<<endl;
                res[i][j] = 0;
            }
           // cout<< i<<" "<<j<< endl;
            //cout<<"#####"<<endl;
       }
    }
    return res;
}



/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img) {
    cout<<"debut intensite"<<endl;
    ImageGris res;
    ImageGris intensV = intensiteV(img);
    ImageGris intensH = intensiteH(img);
    res = ImageGris(img.size());
    for(int i = 0; i<img.size();i++){
        //cout<<"Nouvelle ligne "<<endl;
        res[i] = vector<double>(img[i].size());
        
        for(int j = 0; j<img[i].size();j++){
            if((i != 0 and j != 0) and (i != img.size()-1 and j != img[0].size()-1)){
                double vij = intensV[i][j];
                double hij = intensH[i][j];
                res[i][j] = sqrt(vij*vij+hij*hij);
            }else{
                res[i][j] = 0;
            }
            //cout<<"----"<<endl;
        }
           cout<<"intensite : " << i+1 <<"/"<<img.size()<< endl;
    }
    //cout<<"intensite tout court"<<endl;
    return res;
}

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/** Lissage
 * @param img une image en teintes de gris
 * @return img mais lissée
 **/
ImageGris lissage(ImageGris img){
    ImageGris res;
    res = ImageGris(img.size());
    int ajib = 1; //ajustement i before
    int ajia = 1; //ajustement i after etc...
    int ajjb = 1; 
    int ajja = 1; 

    for(int i = 0; i<img.size();i++){
        res[i] = vector<double>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            if(i<=0){
                ajib = 0;
            }
            if(j<=0){
                ajjb = 0;
            }
            if(i>=img.size()-1){
                ajia = 0;
            }
            if(j>=img[i].size()-1){
                ajja = 0;
            }
            res[i][j] = (img[i][j]+img[i-ajib][j]+img[i+ajia][j]+img[i][j-ajjb]+img[i][j+ajja])/5.;   

        }
    }
    return res;
}



/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
ImageGris renormalise(ImageGris img) {
    ImageGris res;
    double max = 0;
    res = ImageGris(img.size());
    for(int i = 0;i<img.size();i++){
        res[i] = vector<double>(img[i].size());
        for(int j = 0;j<img[i].size();j++){
            if(img[i][j] > max){
                max = img[i][j];
            }
        }
    }
    for(int i = 0;i<img.size();i++){
        for(int j = 0;j<img[i].size();j++){
            if(img[i][j] > 0){
                res[i][j] = (img[i][j]/max)*255;
            }else{
                res[i][j] = 0;
            }
        }
    }
    return res;
    
}


/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil) {
    ImageGris res;
    res = ImageGris(img.size());

    for(int i = 0; i<img.size();i++){
        res[i] = vector<double>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            if(img[i][j] < seuil){
                res[i][j] = 255;
            }else{
                res[i][j] = 0;
            }
        }
    }
    return res;
}


/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris res;
    res = ImageGris(imgIntensite.size());
    int ajib = 1; //ajustement i before
    int ajia = 1; //ajustement i after etc...
    int ajjb = 1; 
    int ajja = 1; 

    for(int i = 0; i<imgIntensite.size();i++){
        res[i] = vector<double>(imgIntensite[i].size());
        for(int j = 0; j<imgIntensite[i].size();j++){
            ajib = 1; //ajustement i before
            ajia = 1; //ajustement i after etc...
            ajjb = 1; 
            ajja = 1; 
            if(i<=0){
                ajib = 0;
            }
            if(j<=0){
                ajjb = 0;
            }
            if(i>=imgIntensite.size()-1){
                ajia = 0;
            }
            if(j>=imgIntensite[i].size()-1){
                ajja = 0;
            }  
            bool voisinimgcontour = (imgContour[i][j] == 0) or (imgContour[i-ajib][j] == 0) or (imgContour[i+ajia][j] == 0) or (imgContour[i][j-ajjb] == 0) or (imgContour[i][j+ajja] == 0);
            if(imgIntensite[i][j] > seuil and voisinimgcontour){
                res[i][j] = 0;
            }else{
                res[i][j] = 255;
            }
        }
    }
    return res;
}


/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    /*ImageGris res;
    res = ImageGris(imgIntensite.size());
    int ajib = 1; //ajustement i before
    int ajia = 1; //ajustement i after etc...
    int ajjb = 1; 
    int ajja = 1; */
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);
    /*for(int i = 0; i<imgIntensite.size();i++){
        res[i] = vector<double>(imgIntensite[i].size());
        
        for(int j = 0; j<imgIntensite[i].size();j++){
            if(i<=0){
                ajib = 0;
            }
            if(j<=0){
                ajjb = 0;
            }
            if(i>=imgIntensite.size()-1){
                ajia = 0;
            }
            if(j>=imgIntensite[i].size()-1){
                ajja = 0;
            }  
            bool supSeuil1 = imgIntensite[i][j]>seuilFaible or imgIntensite[i][j]>seuilFort;
            for(int k =0 ; k<nbAmeliorations; k++){
                bool voisinimgcontour = (imgContour[i][j] == 255) or (imgContour[i-ajib][j] == 255) or (imgContour[i+ajia][j] == 255) or (imgContour[i][j-ajjb] == 255) or (imgContour[i][j+ajja] == 255);

            }

            if(imgIntensite[i][j] > supSeuil1 and connectedLessThanNBA){
                res[i][j] = 0;
            }else{
                res[i][j] = 255;
            }
        }
    }*/
    ImageGris imgFinale;
    for(int k = 0; k<nbAmeliorations; k++){
        imgFinale = doubleSeuillage(imgIntensite, imgContour, seuilFaible);
        imgContour = imgFinale;
    }
    return imgContour;
}


void seuillageTest() {
    ImageGris test2 = doubleSeuillage(intensite(imgGrisTest), 400, 80, 4);
        for(int i = 0; i<test2.size();i++){
        for(int j = 0; j<test2[i].size();j++){
            cout<<test2[i][j]<<" ";
        }
        cout<<endl;
        }
        cout<<endl;
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
        
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")),80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 80), "seuillage/Lena.512.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Embryos.512.pgm"  )), 80), "seuillage/Embryos.512.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/House.256.pgm"  )), 80), "seuillage/House.256.pgm");
    }

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;

    ecrirePGM(doubleSeuillage(lirePGM("images/Lena.512.pgm"),
                              seuillage(intensite(lirePGM("images/Lena.512.pgm" )),80),70),
              "seuillage_double/Lena-unpas.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 500, 80, 100), "seuillage_double/Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 500, 80, 100), "seuillage_double/Lena.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Embryos.512.pgm"  )), 500, 80, 100), "seuillage_double/Embryos.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/House.256.pgm"  )), 500, 80, 100), "seuillage_double/House.256.pgm");
}


int main(){

    seuillageTest();
    doubleSeuillageTest();

    return 0;
}

