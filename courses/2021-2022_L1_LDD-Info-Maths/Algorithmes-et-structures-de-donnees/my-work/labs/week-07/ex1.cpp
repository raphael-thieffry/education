#include <iostream>
using namespace std;

struct vecteur{
    int taille;
    int *data;
    int allocSize;
};
vecteur *creer_vecteur(){
    vecteur *v = (vecteur*)malloc(sizeof(vecteur));
    v->data = (int*)malloc(sizeof(int));
    v->allocSize = 1;
    v->taille = 0;
    return v;
}
void afficher_vecteur(vecteur *v){
    cout<<'[';
    for(int i = 0; i < v->taille-1; i++){
        cout<<(v->data)[i]<<',';
    }
    if(v->taille-1>=0)cout<<(v->data)[v->taille-1];
    cout<<']'<<endl;
}
void liberer_vecteur(vecteur *v){
    free(v->data);
}
void agrandir(vecteur *v){
    if(v->taille == v->allocSize){
        v->data = (int*)realloc(v->data, (v->allocSize)*2*sizeof(int));
        v->allocSize = (v->allocSize)*2;
    }
}
void ajouter_en_queue(vecteur *v, int val){
    agrandir(v);
    int taille = v->taille;
    (v->data)[taille] = val;
    v->taille = taille+1;
}
void ajouter_en_tete(vecteur *v, int val){
    agrandir(v);
    int *start = (v->data);
    for(int i = (v->taille); i>0;i--){
        (start[i]) = (start[i-1]);
    }
    *start = val;
    v->taille +=1;
}
void reduire(vecteur *v){
    if(v->allocSize/2 >= v->taille){
        v->allocSize = (v->allocSize)/2;
        if(v->allocSize == 0) v->allocSize = 1;
        v->data = (int*)realloc(v->data, (v->allocSize)*sizeof(int));
    }
}
int retirer_en_queue(vecteur *v){
    if(v->taille==0)return 0;
    int last = (v->data)[v->taille-1];
    v->taille -= 1;
    reduire(v);
    return last;
}
int retirer_en_tete(vecteur *v){
    if(v->taille==0)return 0;
    int last = *(v->data);
    int *start = (v->data);
    for(int i = 0; i<(v->taille);i++){
        (start[i]) = (start[i+1]);
    }
    v->taille -= 1;
    reduire(v);
    return last;
}
int vecteur_get(vecteur *v, int index){
    if(index < v->taille and index >=0){
        return (v->data)[index];
    }else{
        return 0;
    }
}
void vecteur_set(vecteur *v, int index, int val){
    if(index < v->taille and index >=0){
        (v->data)[index] = val;
    }
}
int main(){
    vecteur *v = creer_vecteur();
    ajouter_en_queue(v, 18);
    ajouter_en_tete(v, 125);
    afficher_vecteur(v);
    retirer_en_queue(v);
    afficher_vecteur(v);
    retirer_en_tete(v);
    afficher_vecteur(v);
    for(int i = 0; i<10;i++){
        ajouter_en_queue(v, 18);
    }
    afficher_vecteur(v);
}