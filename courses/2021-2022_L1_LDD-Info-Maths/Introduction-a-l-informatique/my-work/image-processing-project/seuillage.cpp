#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"

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

ImageGris seuillage(ImageGris img, int seuil) { 
    for(int i = 0; i < img.size(); i++)
        for(int j = 0; j < img[0].size(); j++)
            if(img[i][j] >= seuil)
                img[i][j] = 0.;
            else
                img[i][j] = 255.;
    return img;
}

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



ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris imgContour = seuillage(imgIntensite, seuilFort);
    ImageGris imgFinale;
    for(int k = 0; k<nbAmeliorations; k++){
        imgFinale = doubleSeuillage(imgIntensite, imgContour, seuilFaible);
        imgContour = imgFinale;
    }
    return imgContour;
}

