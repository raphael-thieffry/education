#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct Garage {
    string nom;
    int nbvoitures;
    int capacite;
    int CA;
};

struct Voiture {
    string code;
    float prix;
    Garage *position;
};

void ajouteVoiture(vector<Voiture> &stock, string code, float prix) {
    bool isin = false;
    for(auto v : stock){
        if(v.code == code){
            isin = true;
        }
    }
    if(not(isin)){stock.push_back(Voiture{code, prix, NULL});}
}

void ajouteGarage(vector<Garage> &lieux, string nom, int capacite) {
    lieux.push_back(Garage{nom, 0, capacite,0});
}

void afficheStock(vector<Voiture> stock) {
    for(auto v : stock){
        cout<< "code : "<<v.code<<endl<< "prix : "<<v.prix<<endl<<"garage : "<< (*v.position).nom<<endl;
        cout<<"------------------------"<<endl;
    }
}

void afficheLieux(vector<Garage> lieux) {
    for(auto g : lieux){
        cout<<"nom : " <<g.nom <<"|"<< "capacite : " <<g.capacite <<"|"<< "CA : " <<g.CA;
        cout<<"|"<< "nbre de voitures : " <<g.nbvoitures ;
    }
}

Voiture *chercheVoiture(vector<Voiture> &stock, string code) {
    for(auto &v : stock){
        if(v.code == code){
            return &v;
        }
    }
    return NULL;
}

Garage *chercheGarage(vector<Garage> &lieux) {
    for(auto &g : lieux){
        if(g.capacite-g.nbvoitures > 0){
            return &g;
        }
    }
    return NULL;
}

bool exposeVoiture(vector<Voiture> &stock, vector<Garage> &lieux, string code) {
    Voiture *cv = chercheVoiture(stock,code);
    Garage *cg =chercheGarage(lieux);
    if((*cv).position != NULL or cg == NULL or NULL == cv){
        return false;
    }
    (*cv).position = cg;
    (*cg).nbvoitures += 1;
    return true;
}

bool vendVoiture(vector<Voiture> &stock, string code) {
    Voiture *cv = chercheVoiture(stock,code);
    if(cv == NULL) return false;
    Garage * g = cv->position;
    if(g == NULL) return false;
    cv->position = NULL;
    g->nbvoitures -=1;
    return true;
}

int main() {
    /* À faire */
}

