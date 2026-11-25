/** @file
 * Lecture et ecriture de fichiers au format PGM
 **/


#include <string>
#include "image.h"

/** Permet de creer un tableau composé de tout les mots/élements d'une chaine de caractère
 * @author Jérémy Wendels | Confiance : 4,5/5
 * @param string la chaine de caractère à séparer
 * @param char le délimiteur pour la séparation (par défaut un espace)
 * @return un tableau composé de tout les mots/elements de la chaines
 **/
vector<string> split(string chaine, char delimiter = ' ');

/** Construire une image en teintes de gris depuis un fichier PGM
 * @author Jérémy Wendels | Confiance : 5/5  tous les tests sont passés, fonctionne comme voulu avec ecrirePGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(std::string source);

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @author Jérémy Wendels | Confiance : 5/5 tous les tests sont passés, images obtenus conformes aux attentes
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void  ecrirePGM(ImageGris img, std::string cible);

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision);

/** Construit une image cliché d'une image en niveau de gris
 * @author Jérémy Wendels | Confiance : 5/5 tous les tests sont passés, images obtenus conformes aux attentes
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/

ImageGris inversePGM(ImageGris img);


