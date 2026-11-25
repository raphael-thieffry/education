/** @file
 * Filtres de seuillage
 **/


/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @author Raphael Thieffry || Confiance : 3/5 car peu de test éffectués mais aucune erreur lors de l'utilisation
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
ImageGris renormalise(ImageGris img);

/** Filtre de seuillage
 * @author Raphael Thieffry || Confiance : 5/5 passe tous les tests, compréhension d'execution intuitive
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de 
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil);

/** Filtre de double seuillage
* @author Raphael Thieffry || Confiance : 4,5/5 passe les tests, vérification par chargé de TD, mais resultats que a 99% ressemblants aux corrigés (imparfait)
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil);

/** Filtre de double seuillage iteratif
 * @author Raphael Thieffry || Confiance : 4,5/5 passe les tests, vérification par chargé de TD, mais resultats que a 99% ressemblants aux corrigés (imparfait)
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, 
				int seuilFaible, int nbAmeliorations);

