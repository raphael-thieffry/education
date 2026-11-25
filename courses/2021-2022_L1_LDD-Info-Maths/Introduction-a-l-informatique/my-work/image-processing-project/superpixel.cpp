#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.h"


double distancePoints(Point p, Point c){
    double calc = 0.;
    for(int i = 0; i < p.size(); i++){
        calc += pow(p[i] - c[i], 2);
    }
    return sqrt(calc);
    
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
    double min = -1; 
    for(auto p2 : C){
        double dist = distancePoints(p, p2);
        if(dist < min && min >= 0){
            min = dist;
        }
    }
    return min;
}

int plusProcheVoisin(Point p, EnsemblePoints C){
    double min = -1;
    int i_min;
    for(int i = 0; i < C.size(); i++){
        double dist = distancePoints(p, C[i]);
        if(dist < min or min < 0){
            min = dist;
            i_min = i;
            // cout << "min : " << min << endl;
            // cout << "i_min : " << i_min << endl;
        }
    }
    return i_min;
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C, int k) {
    EnsemblePoints sous_ensemble;
    for(auto p : P){
        if(k == plusProcheVoisin(p, C)) sous_ensemble.push_back(p);
    }
    return sous_ensemble;
}
//ça permet d'avoir les p qui ressemblent le plus à c[k]

Point barycentre(EnsemblePoints Q) {
    Point s;
    s = Point(Q[0].size());
    for(auto &v : s){
        v = 0.;
    }
    int size = Q.size();
    for(auto v : Q){
        for(int i = 0; i < v.size(); i++){
            s[i] += v[i];
        }
    }
    for(auto &v :s){
        v /= size;
    }
    return s;

}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    EnsemblePoints newC;
    vector<EnsemblePoints> ListePAssocies;
    for(int n = 0; n < nbAmeliorations; n++){
        newC = {};
        for(int i = 0; i < C.size(); i++){
            ListePAssocies.push_back(sousEnsemble(P ,C, i));
        }
        for(int i = 0; i < ListePAssocies.size(); i++){
            if(ListePAssocies[i].size() != 0){
                newC.push_back(barycentre(ListePAssocies[i]));
            } else {
                newC.push_back(C[i]);
            } //raphael prend la releve : gros tableau a la meme taille que c, donc q c'est tout les nouveaux points de C (les bayrentres des elem de Gros tab), et si un elem de gros tab est vide, c bouge pas => reste le meme mon frero t au top
        }
        ListePAssocies = {};
        C = newC;
    }
    return C;
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}
//! idée de résolution : modification boucle for
EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints res = {};
    for(double a = 0; a<img.size();a+=mu){ //? Peut etre aller en facteur mu, eu lieu de faire a++ faire a+=mu 
//! t'es trop fort jérémy, le best ta trouvé l'erreur
    //mdr ça marhe toujours pas
        for(double b = 0; b<img[a].size();b+=mu){ //? pareil ici ?
            res.push_back({a,b,lambda*img[a][b].r,lambda*img[a][b].g,lambda*img[a][b].b});
        }
    }
    return res;
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    //Turn img into ensemble de point
    EnsemblePoints listePointsImg;
    for(double i = 0; i<img.size();i++){
        for(double j = 0; j<img[i].size();j++){
            listePointsImg.push_back({i,j,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b});
        }
    }
    return FAST_KMoyenne(listePointsImg, pivotSuperPixel(img,lambda,mu),nbAmeliorations);

}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations){
    Image imageRes;
    imageRes = Image(img.size());
    EnsemblePoints centresSuperPix  = superPixels(img, lambda, mu, nbAmeliorations);
    for(int i = 0; i<img.size(); i++){
        imageRes[i] = vector<Couleur>(img[i].size());
    }
    for(double i = 0; i<img.size();i+=1){
        
        for(double j = 0; j<img[i].size();j+=1){
            Point pointIJ = {i,j,lambda*img[i][j].r,lambda*img[i][j].g,lambda*img[i][j].b};
            int index = plusProcheVoisin(pointIJ, centresSuperPix);
            Couleur pixel;
            pixel.r = centresSuperPix[index][2]/lambda;
            pixel.g = centresSuperPix[index][3]/lambda;
            pixel.b = centresSuperPix[index][4]/lambda;
            imageRes[i][j] = pixel;
        }
    }

    //couche bleue
    Image imgBleue;
    imgBleue = Image(img.size());
    int ajja = 1; 
    int ajia = 1;
    for(int i = 0; i<img.size();i++){
        imgBleue[i] = vector<Couleur>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            ajja = 1;
            ajia = 1;
            if(j>=img[i].size()-1){
                ajja = 0;
            }              
            if(i>=img.size()-1){
                ajia = 0;
            }  
            bool voisinDroite = (imageRes[i][j + ajja].r == imageRes[i][j].r) 
                             && (imageRes[i][j + ajja].g == imageRes[i][j].g) 
                             && (imageRes[i][j + ajja].b == imageRes[i][j].b); 
            bool voisinBas    = (imageRes[i + ajia][j].r == imageRes[i][j].r) 
                             && (imageRes[i + ajia][j].g == imageRes[i][j].g) 
                             && (imageRes[i + ajia][j].b == imageRes[i][j].b);
            if(!voisinDroite || !voisinBas){
                imgBleue[i][j].b = 255;
                imgBleue[i][j].r = 0;
                imgBleue[i][j].g = 0;

            }else{
                imgBleue[i][j] = imageRes[i][j];
            }
        }
    }
    return imgBleue;
}
