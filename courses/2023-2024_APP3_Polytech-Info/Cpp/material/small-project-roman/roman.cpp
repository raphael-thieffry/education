#include <array>
#include <iostream>
#include <iterator>

#include "check.hpp"

std::string simple_roman_to_numerals(int i) {
  /*
    Q1. Implémentez simple_roman_to_numerals pour gérer les cas 1,2,3 =>
    I,II,III de la manière la plus simple possible.

  */

  /*
    Q2. Ajoutez le support pour gérer les cas 10,20,30 => X,XX,XXX
        de la manière la plus simple possible.
  */

  /*
    Q3. Analysez la structure de votre code pour en déduire un algorithme
        simple pour gérer tout les cas de la forme 1,2,3,10,20,30,11,12,13,...,
    100 ,200 ,300
  */

  /*
    Q4. Ajoutez le support pour V,L et les autres valeurs mono-caractère des
    nombres romains
  */

  /*
    Q5. Ajoutez le support pour IV,IX et les autres valeurs spéciales des
    nombres romains
  */
}

std::string struct_roman_to_numerals(int i) {
  /*
    Q6. Refactorisez le code de la première fonction pour utilisez une approche
        basée sur les données. Le code devra utiliser une structure de donnée
        adéquate pour stocker les règles de transformations et les parcourir de
    manière uniforme.

        Vérifiez que cette version passe les mêmes tests que la précédente.
  */
}

int main() {
  run_tests();
  return 0;
}
