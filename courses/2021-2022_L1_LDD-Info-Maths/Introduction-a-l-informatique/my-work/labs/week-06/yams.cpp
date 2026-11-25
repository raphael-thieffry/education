// -*- coding: utf-8 -*-
#include <iostream>
#include <vector>
#include <cstdlib>
#define CHECK(C) if ( !(C) ) { std::cerr << "Test failed: "#C << std::endl; }

using namespace std;
typedef vector<int> tableau;

int aleaint(int a, int b) {
    return (rand() % (b - a + 1) + a);
}

// Mettez ici les différentes fonctions nécessaires au jeu de Yams :

int pointsFigureYams(vector<int> des){
        if(des[0] ==  des[1] and des[2] == des[3]){
            if(des[0] ==  des[2] and des[2] == des[4]){
                if(des[1]<=6 and des[1]>=1){
                    int res = des[0]*5+60;
                    return res;
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
        }
}
tableau lanceDes() {
    vector<int> tab = {};
    for(int i = 1; i<6; i++){
        tab.push_back(aleaint(1,6));
    }
    return tab;
}
/** Fonction afficheDes
 * @param un tableau d'entiers
 **/
void afficheDes(vector<int> tab){
    for(auto valeur: tab){
        cout <<  valeur << endl;
    }
}
/** Fonction compteDes
 * @param Tableau d'entiers de 5 elements
 * @return Tableau de la quantité de chaque chiffre dans le tableau d'entrée
 **/
 tableau compteDes(vector<int> des) {
    vector<int> res = {0,0,0,0,0,0};
    if(des.size()==5){
        for(int i=0 ;i<des.size();){
            res[des[i]-1]++;
            i++;
        }
    }
    return res;
};
/** Fonction chercheDansTableau
 * @param n un entier
 * @param tab un tableau d'entiers
 * @return l'indice du tableau où n est present dans tab, et -1 sinon
 **/
int chercheDansTableau(int n,vector<int> tab){
    for(int i = 0; i<=tab.size()-1;i++){
        if(tab[i]==n){
            return i;
        }
    }
    return -1;
}


int pointsFigureBrelan(vector<int> des) {
  vector<int> compte = compteDes(des);

  int valeur = (chercheDansTableau(3, compte) + 1)
                      + (chercheDansTableau(4, compte) + 1)
                      + (chercheDansTableau(5, compte) + 1);

  if (valeur > 0) return (valeur * 3) + 10;
  else return 0;
};
int pointsFigureCarre(vector<int> des) {
    vector<int> compte = compteDes(des);
    
    int valeur = (chercheDansTableau(4, compte) + 1)
               + (chercheDansTableau(5, compte) + 1);

    if (valeur > 0) 
        return (valeur * 4) + 30;
    else
        return 0;
};
int pointsFigureFull(vector<int> des) {
    vector<int> compte = compteDes(des);
    int valeur2 = chercheDansTableau(2, compte) + 1;
    int valeur3 = chercheDansTableau(3, compte) + 1;

    if (valeur2 > 0 and valeur3 > 0) 
        return (valeur2 * 2) + (valeur3*3)+20;
    else
        return 0;
};

int pointsFigure(vector<int> des, string figure) {
  if(figure == "brelan") {
    return pointsFigureBrelan(des);
  } else if(figure == "full") {
    return pointsFigureFull(des);
  } else if(figure == "carre") {
    return pointsFigureCarre(des);
  } else if(figure == "yams") {
    return pointsFigureYams(des);
  }
  return 0;
};

int main() {
    // Initialisation de la fonction rand (pour les nombres aléatoires) :
    srand(time(0));

      // AVANT LA BOUCLE PRINCIPALE
  // On déclare les variables utilisées par la boucle principale :
  // VOTRE CODE ICI

  // BOUCLE PRINCIPALE
  string reponse;
  while (true) {
    // On lance les dés et on stocke le résultat dans la variable appropriée :
    
    vector<int> lance = lanceDes();

    // On affiche le résultat du lancé au joueur et on affiche un texte demandant quelle figure il choisit :
    afficheDes(lance);

    // On boucle tant que la réponse de l'utilisateur n'est pas brelan, carre, full ou yams ni exit : 
    do {
    	 cout<< "Euh tu choisis quoi ? " <<endl;
      cin >> reponse;
    } while (reponse != "brelan" and reponse != "full" 
         and reponse != "carre" and reponse != "yams" and reponse != "exit");

    // Si la réponse est exit on quitte l'application :
    if(reponse == "exit") { 
        return 0; 
    }

    // Si l'utilisateur a choisi une figure on calcule le nouveau score et on l'affiche :
    cout << "Tu obtiens "+ to_string(pointsFigure(lance, reponse)) + " points !" << endl;

  }
  // FIN DE LA BOUCLE PRINCIPALE
return 0;

}
