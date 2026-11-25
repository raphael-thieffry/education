#include <iostream>
using namespace std;
struct elem{
    elem *link;
    int val;
};
struct liste{
    elem *root;
    int size;
};
liste *nouvelle_liste(){
    liste *l = (liste*)malloc(sizeof(liste));
    l->root = NULL;
    l->size = 0;
    return l;
}
void afficher_liste(liste *l){
    if(l->root == NULL){cout<<"[]"<<endl;return;}
    cout<<"[ ";
    for(elem *n = (l->root); n != NULL; n = n->link){
        cout<<n->val<<", ";
    }
    cout<<"]"<<endl;
}
void ajouter_en_tete(liste *l, int val){
    elem *e = (elem*)malloc(sizeof(elem));
    e->val = val;
    e->link = l->root;
    l->root = e;
    l->size++;
}
void supprimer_valeur(liste *l, int val){
    if(l->size == 0) return;
    //cherche
    if((l->root)->val == val){
        elem *supressed = l->root;
        elem *newRoot = supressed->link;
        free(supressed);
        l->root = newRoot;
        return;
        l->size--;
    }
    elem *n = (l->root);
    while((n->link)->val != val){
        if((n->link)->link == NULL and n->link->val != val){
            return; //si on est à l'avant dernier elem,
            // et que le dernier elem c'est pas ce qu'on veut, alors tu fais rien
        }
        n = n->link;
    }
    //n est le noeud avant le truc à supr
    elem *supressed = n->link;
    elem *newLink = supressed->link;
    free(supressed);
    n->link = newLink;
    l->size--;
}
int chercher_maximum(liste *l){
    int max = l->root->val;
    for(elem *n = (l->root)->link; n != NULL; n = n->link){
        if(n->val > max){
            max = n->val;
        }
    }
    return max;
}
void ajouter_en_queue(liste *l, int val){
    elem *n = (l->root);
    while((n->link) != NULL){
        n = n->link;
    }
    elem *e = (elem*)malloc(sizeof(elem));
    e->val = val;
    e->link = NULL;
    n->link = e;
    l->size++;
}
void liberer_liste(liste *l){
    elem *n = (l->root);
    while((n->link) != NULL){
        elem *tofree = n;
        n = n->link;
        free(tofree);
    }
    free(n);
    free(l);
}
int main(){
    liste *l = nouvelle_liste();
    ajouter_en_tete(l, 18);
    ajouter_en_tete(l, 24);
    afficher_liste(l);
    supprimer_valeur(l, 18);
    ajouter_en_tete(l, 125);
    afficher_liste(l);
    ajouter_en_queue(l,69);
    afficher_liste(l);
    cout<<chercher_maximum(l)<<endl;
    liberer_liste(l);
    afficher_liste(l);
    cout<< l->size << endl;
}