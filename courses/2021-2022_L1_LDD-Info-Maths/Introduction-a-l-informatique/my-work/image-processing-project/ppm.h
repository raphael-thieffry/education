/** @file
 * Lecture et ecriture de fichiers au format PPM
 **/

#include <string>
#include "image.h"

/** Permet de creer un tableau composé de tout les mots/élements d'une chaine de caractère
 * @note Fonction supplémentaire 
 * @author Jérémy Wendels | Confiance : 5/5 car fonctionne dans tous les cas testés
 * @param string la chaine de caractère à séparer
 * @param char le délimiteur pour la séparation (par défaut un espace)
 * @return un tableau composé de tout les mots/elements de la chaines
 **/
vector<string> split2(string chaine, char delimiter = ' ');



/** Lit une image au format PPM, retourne un tableau de Couleur
 * @author Jérémy Wendels | Confiance : 5/5 car tests effectués et gestion commentaires fiable
 * @param source vers une image .ppm
 * @return une image
 **/
Image lirePPM(std::string source);



/**  Écrit une image dans un fichier PPM
 * @author Raphael Thieffry | Confiance : 5/5 passe tous les tests et résulats attendus
 * @param img une image
 * @param cible le nom d'un fichier PPM
 **/
void  ecrirePPM(Image img, std::string cible);


