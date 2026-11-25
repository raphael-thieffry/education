#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.h"


ImageGris CouleurAuGris( Image img ) {
    ImageGris res;
    res = ImageGris(img.size());

    for(int i = 0; i<img.size();i++){
        res[i] = vector<double>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            res[i][j] = 0.2126 * img[i][j].r + 0.7152 * img[i][j].g + 0.0722 * img[i][j].b;
        }
    }
    return res;
}

Image GrisACouleur( ImageGris img ) {
    Image res;
    res = Image(img.size());

    for(int i = 0; i<img.size();i++){
        res[i] = vector<Couleur>(img[i].size());
        for(int j = 0; j<img[i].size();j++){
            res[i][j].r = img[i][j];
            res[i][j].g = img[i][j];
            res[i][j].b = img[i][j];
        }
    }
    return res;
}

