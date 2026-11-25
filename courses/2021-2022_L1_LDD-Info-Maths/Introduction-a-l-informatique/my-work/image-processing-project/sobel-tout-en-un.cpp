#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
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



/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/

ImageGris lirePGM(string source) {
    ImageGris pgm_tableau;
    ifstream pgm; 
    pgm.open(source); 
    if (not pgm) throw runtime_error("Fichier non trouve: "+source);
    string sfdata;
    pgm >> sfdata;
    if(sfdata[0] == '#'){
        throw runtime_error("Cette fonction ne sait pas gerer les commentaires");
    }
    if(sfdata == "P2"){
        int w, h, niveau_de_gris;
        pgm >> w;
        if(sfdata[0] == '#'){
        throw runtime_error("Cette fonction ne sait pas gerer les commentaires");
    }
        pgm >> h;
        if(sfdata[0] == '#'){
        throw runtime_error("Cette fonction ne sait pas gerer les commentaires");
    }
        pgm >> niveau_de_gris;
        if(sfdata[0] == '#'){
        throw runtime_error("Cette fonction ne sait pas gerer les commentaires");
    }

        pgm_tableau = ImageGris(h);
        for(int i = 0; i < h; i++){
            pgm_tableau[i] = vector<double>(w);
            for(int j = 0; j < w; j++){
                pgm >> sfdata;
                if(sfdata[0] == '#'){
        throw runtime_error("Cette fonction ne sait pas gerer les commentaires");
    }
                pgm_tableau[i][j] = stod(sfdata);
            }

        }
    }
    cout<<"lecture"<<endl;
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


/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
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


void testSobel() {
    //cout<<"1er test"<<endl;

    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
                  }),
              0.001
              ) );
    //cout<<"2eme"<<endl;
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    //cout<<"3eme"<<endl;
    
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    //cout<<"suite"<<endl;
    ImageGris intensgris = intensite(lissage(lirePGM("images/chat_ascii.pgm")));
    /*for(int i = 0; i<intensgris.size();i++){
        for(int j = 0; j<intensgris[i].size();j++){
            cout<<intensgris[i][j]<<" ";
        }
        cout<<endl;
    }*/
    ecrirePGM(intensgris, "sobel/testecriture.pgm");
    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Lena.512.pgm"   )), "sobel/Lena.512.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

