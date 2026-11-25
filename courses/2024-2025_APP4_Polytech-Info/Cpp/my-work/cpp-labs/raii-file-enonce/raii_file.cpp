#include <cstdio>
#include <iostream>
#include <filesystem>

#include "raii_file.hpp"

int main(int, char const *[]) {

  std::cout << "Tests raii_file.cpp en cours...\n";
  std::cout << "dossier courant : " << std::filesystem::current_path() << std::endl;
  { // Ecriture
    raii_file some_file("okok.txt", "w");
    std::fprintf(some_file, "okok");
  }

  { // Lecture
    raii_file some_file("okok.txt", "r");
  }

  std::cout << "Tests raii_file.cpp passés.\n";
}
