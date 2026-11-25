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

void deplacer_tete(liste *l1, liste *l2){
	if(l1->nbelem == 0){
		return;
	}
	l1->nbelem--;
	l2->nbelem++;
	elem* a = l1->tete;
	l1->tete = a->next;
	a->next = l2->tete;
	l2->tete = a;
}

liste *renverser(liste *l){
	liste* res = nouvelle_liste();
	while(l->tete != NULL){
		deplacer_tete(l, res);
	}
	liberer_liste(l);
	return res;
}

liste *decouper(liste *l){
	if(l->nbelem == 1){
		throw std::runtime_error("liste a 1 element");
	}
	if(l->nbelem == 2){
		liste *l2 = nouvelle_liste();
		l2->tete = l->tete->next;
		l2->nbelem = 1;
		l->nbelem = 1;
		l->tete->next = NULL;
		return l2;
	}
	elem *j = l->tete;
	elem *p = l->tete;
	int elementsInl = 1;
	while(j->next != NULL and j->next->next != NULL){
		j = j->next->next;
		p = p->next;
		elementsInl++;
	}
	int oldCard = l->nbelem;
	l->nbelem = elementsInl;
	elem *deb2 = p->next;
	p->next = NULL;
	liste *l2 = nouvelle_liste();
	l2->tete = deb2;
	l2->nbelem = oldCard-elementsInl;
	return l2;
}

liste *fusionner(liste *l1, liste *l2){
	int tailleL1 = l1->nbelem;
	int tailleL2 = l2->nbelem;
	liste *res = nouvelle_liste();
	while(l1->tete != NULL and l2->tete != NULL){
		if(l1->tete->val < l2->tete->val){
			deplacer_tete(l1,res);
		}else{
			deplacer_tete(l2,res);
		}
	}
	while(l1->tete != NULL){
		deplacer_tete(l1,res);
	}
	while(l2->tete != NULL){
		deplacer_tete(l2,res);
	}
	res->nbelem = tailleL1 + tailleL2;
	liberer_liste(l1);
	liberer_liste(l2);
	return renverser(res);
}

liste *tri_fusion(liste *l){
	if (l->nbelem < 2){
		return l;
	}
	liste *l2 = decouper(l);
	l = tri_fusion(l);
	l2 = tri_fusion(l2);
	return fusionner(l,l2);
}

void dedup(liste *l){
	//prend liste triée
	elem *e = l->tete->next;
	elem *PrevE = l->tete;
	while(e->next!=NULL) {
		if(PrevE->val == e->val){
			PrevE->next = e->next;
			free(e);
			e = PrevE->next;
		}else{
			e = e->next;
			PrevE = PrevE->next;
		}
	}
	//traitement des deux derniers
	if(PrevE->val == e->val){
		PrevE->next = e->next;
		free(e);
		e = PrevE->next;
	}
}

liste *intersection(liste *l1, liste *l2){
	dedup(l1);dedup(l2);
	liste *res = nouvelle_liste();
	elem *e1 = l1->tete;
	elem *e2 = l2->tete;
	while(e2->next!=NULL and e1->next!=NULL) {
		if(e1->val > e2->val){
			e2 = e2->next;
		}else if(e1->val < e2->val){
			e1 = e1->next;
		}else{
			ajouter_en_tete(res, e1->val);
			e1 = e1->next;
			e2 = e2->next;
		}
	}
	return res;
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
	liste *l3 = nouvelle_liste();
	for (int i = 0; i < N; i++)
		ajouter_en_tete(l3, rand()%100);
	afficher_liste(l3);
	deplacer_tete(l3,l2);
	afficher_liste(l2);
	afficher_liste(l3);
	l3 = renverser(l3);
	afficher_liste(l3);
	/*liste *ltest = nouvelle_liste();
	ajouter_en_tete(ltest,3);
	ajouter_en_tete(ltest,4);
	afficher_liste(ltest);
	afficher_liste(renverser(ltest));*/
	liste* l3t = tri_fusion(l3);
	afficher_liste(l3t);
	max = chercher_maximum(l3t);
	truth = est_triee(l3t);
	std::cout << "Maximum t3t = " << max << std::endl;
	std::cout << "t3t triee ? = " << truth << std::endl;
	liste *l69 = nouvelle_liste();
	for (int i = 0; i < N; i++)
		ajouter_en_tete(l69, 18);
	for (int i = 18; i > 0; i--)
		ajouter_en_tete(l69, i);
	afficher_liste(l69);
	dedup(l69);
	afficher_liste(l69);
	afficher_liste(intersection(l69, l3t));
	return 0;
}

