
// RArray : Resizable Array - Tableau redimensionnable
// Tableau dont les éléments sont stockés entre les indices 0 et nb-1

// tab : contient les éléments du tableau
// nb : nombre d'éléments du tableau
// cap : taille du tableau en mémoire

typedef struct {
  int *tab;
  int nb;
  int cap;
} RArray;

// Construit un RArray vide de capacite c strictement positive
RArray init(int c);

// Renvoie le nombre d'éléments de r
int size(RArray r);

// Renvoie l'élément stocké à l'indice ind de r si ind est entre 0 et nb-1
int get(RArray r, int ind);

// Vide le tableau
void clear(RArray *r);

// Renvoie 0 si val n'appartient pas à r, un entier non nul sinon
int contains(RArray r, int val);

// Renvoie l'indice de val si val est présent, -1 sinon
int indexR(RArray r, int val);

// Redimensionne r avec une capacité strictement supérieure
void resize(RArray *r);

// Ajoute val à r, en le redimensionnant si besoin
void add(RArray *r, int val);

// Supprime l'élément à l'indice ind et le renvoie
int removeInd(RArray *r, int ind);

void afficher(RArray r);
