#include <stdexcept>
#include <iostream>
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"


/** Calcule la puissance d'un nombre par un exposant
* @param[in] nombre : un entier
* @param[in] exposant : un entier
* @return l'entier de valeur nombre puissance exposant
**/
int puissance(int nombre, int exposant) {
    int res = 1;
    for(int i = 0;i<exposant;i++){
      res*=nombre;
    }
    return res;
}



TEST_CASE("Test de la fonction puissance") {
  CHECK(puissance(10, 0) == 1);
  CHECK(puissance(2, 6) == 64);
  CHECK(puissance(7, 2) == 49);
  CHECK(puissance(65531512, 1) == 65531512);
  CHECK_FALSE(true == false);
}

int main(int argc, const char** argv){
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;

  // Calcule et affiche les puissances de 2
  for (int i=0; i<=20; i++) cout << puissance(2, i) << endl;

  return 0;
}
