#pragma once

#include <cstdio>

// raii_file est une structure enveloppant un std::FILE* (la version "C++" de
// FILE*). Sa responsabilite est d'assurer l'unicite d'un std::FILE*, et de
// s'assurer que tous les fichiers sont fermes avec std::fclose lorsqu'ils
// sortent du scope.
//
// Pour faciliter les choses, raii_file propose une fonction de conversion vers
// std::FILE*, ce qui permet de l'utiliser directement avec les fonctions de
// cstdio (https://en.cppreference.com/w/cpp/header/cstdio).

struct raii_file {
private:
  std::FILE *_file_ptr;

public:
  // On donne un constructeur qui accepte un std::FILE*.
  raii_file(std::FILE *file_ptr) noexcept : _file_ptr(file_ptr) {}

  // Implementez un constructeur qui accepte un filename, un mode, et initialise
  // l'objet en ouvrant le fichier avec std::fopen.
  raii_file(const char *filename, const char *mode) : _file_ptr(std::fopen(filename, mode)) {}

  // Implementez la semantique de transfert, et faites en sorte que l'objet ne
  // soit pas copiable.
  
  raii_file(raii_file &&other) noexcept : _file_ptr(other._file_ptr) {
    //j'ai capté, ça marche
    other._file_ptr = nullptr;
  }

  raii_file& operator=(raii_file &&other) noexcept {
    std::swap(_file_ptr, other._file_ptr);
    return *this;

    //askip ça permet de caler x = y = z en faisant en sorte que ça ait du sens
  }

  // Implementez operator std::FILE*. La methode doit etre const.
  operator std::FILE*() const {
    return _file_ptr;
  }
};
