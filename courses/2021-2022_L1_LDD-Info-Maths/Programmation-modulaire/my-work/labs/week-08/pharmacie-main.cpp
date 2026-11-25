#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "medicament.hpp"
#include "prescription.hpp"

Stock creeUnStockdeTest() {
  Stock s;
  s.table.clear();
  s.table.push_back({"panadol", 20, 4, 3.5f});
  s.table.push_back({"aspirine", 2, 12, 6.f});
  s.table.push_back({"nexium", 0, 10, 12.5f});
  return s;
}

int main(int argc, const char **argv) {

  Stock s = creeUnStockdeTest();
  Prescription p;
  //p.lirePrescription(s);
  return 0;
}
