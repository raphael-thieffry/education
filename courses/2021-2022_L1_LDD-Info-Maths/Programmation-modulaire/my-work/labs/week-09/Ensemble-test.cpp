#include <stdexcept>
#include <vector>
#include <string>
#include <random>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Ensemble.hpp"



TEST_CASE("Constructions") {
  Ensemble A{};
  CHECK_FALSE(A.contient(0));
  CHECK_FALSE(A.contient(1));
  A = Ensemble{{1}};
  CHECK_FALSE(A.contient(0));
  CHECK(A.contient(1));
  CHECK_FALSE(A.contient(2));
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 25");
}

TEST_CASE("Ajouter et retirer") {
  Ensemble A = Ensemble();
  CHECK_FALSE(A.contient(5));
  A.ajoute(5);
  CHECK(A.contient(5));
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 36");
}

TEST_CASE("Contient") {
  Ensemble A {};
  CHECK_FALSE(A.contient(5));
  CHECK_FALSE(A.contient(1));
  A.ajoute(5);
  CHECK(A.contient(5));
  CHECK_FALSE(A.contient(1));
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 49");
}


int main(int argc, const char **argv) {
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  return 0;
}
