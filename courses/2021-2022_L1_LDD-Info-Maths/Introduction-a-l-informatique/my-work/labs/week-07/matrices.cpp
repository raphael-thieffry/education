#include <stdexcept>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

typedef vector<vector<int>>  Matrice;

Matrice matriceVide (0);
Matrice matriceCarre       = { { 1,  4, 9 },
                          { 4, 11, 6 },
                          { 9, 12, 7 }};
Matrice matriceRectangulaire={ { 1,  2, 3 },
                          { 9, 12, 7 }};
Matrice matriceSymetrique = { { 1,  2, 3 },
                         { 2, 11, 4 },
                         { 3,  4, 0 }};


/** Teste si une matrice est symétrique
 * @param t une matrice carrée
 * @return true si t[i][j] == t[j][i] pour tout i,j, false sinon
 **/
bool estSymetrique(Matrice t) {
	int k = 0;
	int nbelmt = 0;
	for ( int i = 0; i < t.size(); i++ ) {
    	for ( int j = 0; j < t[j].size(); j++ ) {
    		nbelmt++;
    	}
    }
    for(int j = 0; j<t.size(); j++){
    	for(int i = 0; i<t.size(); i++){
    		if(t[j][i] == t[i][j]){
    			k++;
    		}
    	}
    }
    if(k==nbelmt-t.size()){ //-t.size() pour ignorer la diagonale
    	return true;
    }else{
    	return false;
    }
}

void estSymetriqueTest() {
    CHECK(     estSymetrique(matriceVide) );
    CHECK( not estSymetrique(matriceCarre) );
    CHECK(     estSymetrique(matriceSymetrique) );
}


/** somme deux matrices dont les dimensions sont identiques
 * @param t1 une matrice
 * @param t2 une matrice
 * @return la matrice t1 + t2
 **/
Matrice somme(Matrice t1, Matrice t2) {
	if(t1.size()>0 and t1.size() == t2.size()){
    	Matrice t3;
		t3 = Matrice(t1.size());
		for(int i = 0; i<t1.size(); i++){
			t3[i] = vector<int>(t1.size());
		}
		for(int j = 0; j<t1.size(); j++){
			for(int i = 0; i<t1[0].size(); i++){
				t3[j][i] = t1[j][i]+t2[j][i];
			}
		}
		return t3;
    }else{
    	return matriceVide;
    }
}


void sommeTest() {
	/*for ( int i = 0; i < somme(matriceCarre, matriceSymetrique).size(); i++ ) {
		for ( int j = 0; j < somme(matriceCarre, matriceSymetrique)[0].size(); j++ ) {
			cout << setw(2) << somme(matriceCarre, matriceSymetrique)[i][j] << " ";
		}
    cout << endl;
}*/
    CHECK( somme(matriceCarre, matriceSymetrique) == Matrice({{ 2, 6, 12 }, { 6, 22, 10 }, { 12, 16, 7 }}) );
}

/** produit de deux matrices dont les dimensions sont compatibles
 * @param t1 une matrice
 * @param t2 une matrice
 * @return la matrice t1 * t2 (produit matriciel)
 **/
Matrice produit(Matrice t1, Matrice t2) {
	Matrice t3;
	t3 = Matrice(t1.size());
	for(int i = 0; i<t1.size(); i++){
		t3[i] = vector<int>(t1[0].size());
	}
	
	for(int h = 0; h< t1[0].size(); h++){
		for(int w = 0; w< t1.size(); w++){
			for(int i = 0; i< t2.size(); i++){
				t3[h][w]+=t1[h][i]*t2[i][w];
			}
		}
	}
    
	return t3;	
}


void produitTest() {
    CHECK( produit(matriceCarre, matriceCarre) == Matrice({{ 98, 156, 96 }, { 102, 209, 144 }, { 120, 252, 202 }}) );
}

int main() {
    cout << "Lancement des tests. Si tout marche bien, rien ne devrait s'afficher ci dessous." << endl; 
    // Lance tous les tests
    estSymetriqueTest();
    sommeTest();
    produitTest();
}

