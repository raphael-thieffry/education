#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.h"



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


ImageGris intensite(ImageGris img) {
    // cout<<"debut intensite"<<endl;
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
           //cout<<"intensite : " << i+1 <<"/"<<img.size()<< endl;
    }
    //cout<<"intensite tout court"<<endl;
    return res;
}


