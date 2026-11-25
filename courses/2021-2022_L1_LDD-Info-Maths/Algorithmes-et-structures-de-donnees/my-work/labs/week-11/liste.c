#include <iostream>
#include <cstdlib>

struct elem {
	elem *next;
	int   val;
};

struct liste {
	elem *tete;
	int   nbelem;
};

liste *nouvelle_liste() {
	liste *l = (liste *)malloc(sizeof(liste));
	l->tete = NULL;
	l->nbelem = 0;
	return l;
}

void liberer_liste(liste *l) {
	elem *e = l->tete;
	while (e != NULL) {
		elem *tmp = e->next;
		free(e);
		e = tmp;
	}
	free(l);
}

void afficher_liste(liste *l) {
	elem *e = l->tete;
	while (e != NULL) {
		std::cout << e->val << " ";
		e = e->next;
	}
	std::cout << std::endl;
}

void ajouter_en_tete(liste *l, int val) {
	elem *e = (elem *)malloc(sizeof(elem));
	e->val  = val;
	e->next = l->tete;
	l->tete = e;
	l->nbelem++;
}

void ajouter_en_queue(liste *l, int val) {
	elem *e = (elem *)malloc(sizeof(elem));
	e->val  = val;
	e->next = NULL;
	if (l->tete == NULL) {
		l->tete = e;
		l->nbelem = 1;
	} else {
		elem *iter = l->tete;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = e;
		l->nbelem++;
	}
}

int chercher_maximum(liste *l) {
	if (l->nbelem == 0)
		return -1;
	int max = l->tete->val;
	elem *e = l->tete->next;
	while (e != NULL) {
		if (e->val > max)
			max = e->val;
		e = e->next;
	}
	return max;
}

void supprimer_valeur(liste *l, int val) {
	if (l->nbelem == 0)
		return;
	elem *e = l->tete;
	if (e->val == val) {
		l->tete = e->next;
		l->nbelem--;
		free(e);
		return;
	}
	while (e->next != NULL) {
		if (e->next->val == val) {
			elem *tmp = e->next;
			e->next = tmp->next;
			l->nbelem--;
			free(tmp);
			return;
		}
		e = e->next;
	}
}

bool est_triee(liste *l){
	if(l->nbelem == 0 or l->nbelem == 1){
		return true;
	}

	elem *current = l->tete;
	int lastV = current->val;

	for(current = current->next; current->next != NULL; current = current->next){
		int v = current->val;
		if(v<lastV){
			return false;
	std::cout << "test" << std::endl;
		}
		lastV = v;
	}
	if(current->val < lastV){
		return false;
	}
	return true;
}

int supprimer_maximum(liste *l){
	if (l->nbelem == 0)
		return -1;

	//si 1 elem
	if(l->nbelem == 1){
		int max1Elem = l->tete->val;
		elem *first = l->tete;
		l->tete = first->next;
		l->nbelem--;
		free(first);
		return max1Elem;
	}
	
	//si au moins 2 elem
	int max = l->tete->next->val;
	elem *e = l->tete;
	elem *prevMax = e;
	while (e->next != NULL) {
		if (e->next->val > max){
			max = e->next->val;
			prevMax = e;
		}
		e = e->next;
	}
	//check max 1er
	if(l->tete->val > max){
		max = l->tete->val;
		//On le sup
		elem *oldFirst = l->tete;
		l->tete = oldFirst->next;
		l->nbelem--;
		free(oldFirst);
		return max;
	}
	//on sup le max
	elem *tmp = prevMax->next;
	prevMax->next = tmp->next;
	l->nbelem--;
	free(tmp);
	return max;
}

liste *triSelection(liste *l){
	liste *r = nouvelle_liste();
	int &SizeR = r->nbelem;
	int &SizeL = l->nbelem;
	while(!(l->nbelem == 0)){
		int max = chercher_maximum(l);
		int oldC = SizeL + SizeR;
		supprimer_valeur(l, max);
		ajouter_en_tete(r,max);
		if((SizeL + SizeR)!=oldC){
			std::cout << "ça marche pas"<<std::endl;
		}
		if(!est_triee(r)){
			std::cout << "pas trié"<<std::endl;
		}
	}
	liberer_liste(l);
	return r;
}

liste *triSelectionMaisMieux(liste *l){
	liste *r = nouvelle_liste();
	int &SizeR = r->nbelem;
	int &SizeL = l->nbelem;
	while(!(l->nbelem == 0)){
		int oldC = SizeL + SizeR;
		int max = supprimer_maximum(l);
		ajouter_en_tete(r,max);
		if((SizeL + SizeR)!=oldC){
			std::cout << "ça marche pas"<<std::endl;
		}
		if(!est_triee(r)){
			std::cout << "pas trié"<<std::endl;
		}
	}
	liberer_liste(l);
	return r;
}



#define N 30

int main() {
	liste *l = nouvelle_liste();
	liste *l1 = nouvelle_liste();
	for (int i = 0; i < N; i++)
		ajouter_en_tete(l, rand()%100);
	ajouter_en_tete(l1, 1);
	ajouter_en_tete(l1, 2);
	ajouter_en_tete(l1, 1);
	afficher_liste(l);
	liste *l2 = triSelectionMaisMieux(l);
	afficher_liste(l2);
	int max = chercher_maximum(l2);
	bool truth = est_triee(l2);
	std::cout << "Maximum = " << max << std::endl;
	std::cout << "triee ? = " << truth << std::endl;
	supprimer_valeur(l2, max);
	afficher_liste(l2);
	liberer_liste(l2);
	return 0;
}

