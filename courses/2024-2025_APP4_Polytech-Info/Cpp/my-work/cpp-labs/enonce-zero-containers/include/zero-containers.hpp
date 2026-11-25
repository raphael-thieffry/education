#pragma once

#include <algorithm>
#include <vector>
using namespace std;
// =============================================================================
// ZERO-CONTAINERS - CONSIGNES
//
// Implementez les conteneurs suivants en ecrivant un minimum de code a l'aide
// de std::vector comme seul container, et des algorithmes de la bibliotheque
// standard. Vous devez ecrire le moins de code possible en suivant la regle du
// zero; par exemple vous ne *devez pas* implementer vous-meme les semantiques
// de transfert ou de copie.
//
// Soyez flemmard-e-s, et n'implementez que les fonctions qui sont decrites pour
// chaque conteneur.
// =============================================================================

// stack_t

//  stack_t &push(T val)
// Rajoute un element en-haut de la pile.

//  T &top()
// Permet d'acceder et de modifier l'element en-haut de la pile.

//  T const &top() const
// Permet d'acceder al'element en-haut de la pile sans le modifier.

//  stack_t &pop()
// Supprime l'element en-haut de la pile.

//  std::size_t size() const
// Renvoie la taille de la pile.

template <typename T> struct stack_t {
  public :
  stack_t &push(T val) {
    stack.push_back(val);
    return *this;
  }
  
  T &top() {
    return stack.back();
  }

  T const &top() const {
    return stack.back();
  }

  stack_t &pop() {
    stack.pop_back();
    return *this;
  }

  std::size_t size() const {
    return stack.size();
  }

  private :
  std::vector<T> stack;
};

// circular_buffer_t

//  circular_buffer_t &push_back(T val)
// Ajoute une valeur a la fin du circular buffer.

//  circular_buffer_t &insert(std::size_t pos, T val)
// Insere une valeur a une position donnee dans le circular buffer. L'insertion
// doit pouvoir se faire avec une coordonnee superieure a la taille du
// conteneur, en suivant la meme logique que l'operator[].

//  circular_buffer_t &erase(std::size_t pos)
// Supprime une valeur a une position donnee dans le circular buffer, toujours
// en suivant la meme logique que l'operator[] et insert.

//  T const &operator[](std::size_t i) const
// Permet d'acceder a une reference constante vers l'element d'indice i. Le
// conteneur etant un buffer "circulaire", on considere qu'on revient au debut
// du conteneur lorsqu'on depasse la valeur max de l'indice.

//  T &operator[](std::size_t i)
// Permet d'acceder a une reference vers l'element d'indice i. Le conteneur
// etant un buffer "circulaire", on considere qu'on revient au debut du
// conteneur lorsqu'on depasse la valeur max de l'indice.

//  std::size_t size() const
// Renvoie le nombre d'elements dans le circular buffer.

template <typename T> struct circular_buffer_t {
  circular_buffer_t &push_back(T val) {
    buffer.push_back(val);
    return *this;
  }

  circular_buffer_t &insert(std::size_t pos, T val) {
    //petit doute. On doit override la pos "pos" et autoriser [size + 1] to be inserted ou bien on laisse cette implémentation ?
    buffer.insert(buffer.begin() + pos%(buffer.size()), val);
    return *this;
  }

  circular_buffer_t &erase(std::size_t pos) {
    buffer.erase(buffer.begin() + pos%(buffer.size()));
    return *this;
  }

  T const &operator[](std::size_t i) const {
    return buffer[i % buffer.size()];
  }

  T &operator[](std::size_t i) {
    return buffer[i % buffer.size()];
  }

  std::size_t size() const {
    return buffer.size();
  }

  private :
  std::vector<T> buffer;
};

// sorted_vector_t

//  sorted_vector_t &push_back(T val)
// Ajoute une valeur dans le sorted_vector_t. Le vector doit toujours etre trie
// apres l'appel de cette fonction.

//  T const &operator[](std::size_t i) const
// Renvoie la valeur de rang i dans le vector. On ne permet pas les modifs pour
// eviter que l'ordre soit invalide.

//  sorted_vector_t &erase(std::size_t pos)
// Supprime la valeur au rang pos.

//  auto begin() const
// Renvoie un iterateur au debut du vector.

//  auto end() const
// Renvoie un iterateur a la fin du vector.

// std::size_t size() const
// Renvoie la taille du vector.

template <typename T> struct sorted_vector_t {
  sorted_vector_t &push_back(T val) {

    if(buffer.empty()) {
      buffer.push_back(val);
      return *this;
    }

    for(auto it = buffer.begin(); it != buffer.end(); ++it) {
      if(val < *it) {
        buffer.insert(it, val);
        return *this;
      }
    }

    return *this;
  }

  T const &operator[](std::size_t i) const {
    return buffer[i];
  }

  sorted_vector_t &erase(std::size_t pos) {
    buffer.erase(buffer.begin() + pos);
    return *this;
  }

  auto begin() const {
    return buffer.begin();
  }

  auto end() const {
    return buffer.end();
  }

  std::size_t size() const {
    return buffer.size();
  }

  private :
  std::vector<T> buffer;
};

