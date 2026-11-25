#pragma once

#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

// ====================================================
// 1. Heritage et interface | Inheritance and interface
// ====================================================

// [FR]
// La classe number_t ci-dessous definit une interface minimale pour des types
// de nombres.
// Supposons que T soit une classe qui herite de number_t: la methode T::display
// affiche sur la sortie standard le type T et la valeur stockee.

// [EN]
// The following number_t class defines a minimal interface for number types.
// Assuming T inherits number_t: The T::display method displays T's type and
// value on the standard output.

struct number_t {
  virtual void display() = 0;
  virtual ~number_t() = default;
};

// FR | On definit number_ptr_t qui permet de contenir un objet qui herite de
// number_t, quelque soit son type.
// EN | We define number_ptr_t which can contain an object that inherits
// number_t, regardless of its type.
using number_ptr_t = std::unique_ptr<number_t>;

// FR | Pour creer un number_ptr_t, il faut utiliser
// std::make_unique<T>(args...) ou T est un type qui herite de number_ptr_t et
// args... sont les arguments a passer au constructeur de T.

// EN | To build a number_ptr_t, you must use std::make_unique<T>(args...) where
// T is a type that inherits number_ptr_t and args... are the arguments to pass
// to a constructor of T.

// eg: number_ptr_t some_int = std::make_unique<integer_t>(10);

// FR | Definissez une classe integer_t qui herite de number et implemente ses
// methodes virtuelles. Sa valeur sera stockee dans un membre de type int.

// EN | Define the integer_t class that inherits number_t and implements its
// virtual methods. Its value has to be stored in an int member.

/**c*/
struct integer_t : number_t {
private:
  int value_;

public:
  integer_t() = default;
  integer_t(int v) : value_(v) {}

  void display() override { std::cout << "(integer) " << value_ << '\n'; }
};
/*c**/

// FR | De la même façon, definissez une classe real_t qui utilisera un champ de
// type double pour stocker une valeur numerique.

// EN | Similarly, define real_t that stores its value as a double.

/**c*/
struct real_t : number_t {
private:
  double value_;

public:
  real_t() = default;
  real_t(double v) : value_(v) {}

  void display() override { std::cout << "(real) " << value_ << '\n'; }
};
/*c**/

// ==================================
// 2. Usine a objets | Object factory
// ==================================

// FR | Une factory est un objet capable de creer sur demande des objets
// d'autres types. Il s'agit ici de creer a la demande des nombres ayant les
// types integer et real definis ci-dessus. La classe number_factory_t aura donc
// le squelette suivant:

// EN | A factory is an object capable of building objects of other types on
// demand. In our case, creating numbers using the previously implemented
// integer_t and real_t types on demand. The number_factory_t class has the
// following skeleton:

struct number_factory_t {

  // FR | La methode number_factory_t::build prend en parametre deux chaines de
  // caractere type et value.
  // Si type vaut "integer", un objet de type integer_t est cree a partir
  // de value. Si type vaut "real", un objet de type real_t est cree a
  // partir de value.

  // EN | The number_factory_t::build method takes two string parameters: type
  // and value.
  // If type equals "integer", an integer_t object is built from value. If type
  // equals "real", a real_t object is built from value.

  number_ptr_t build(std::string const &type, std::string const &value) {
    // https://en.cppreference.com/w/cpp/io/basic_istringstream
    std::istringstream iss(value);

    /**c*/
    if (type == "integer") {
      int val = int();
      iss >> val;
      return std::make_unique<integer_t>(val);
    }

    if (type == "real") {
      double val = double();
      iss >> val;
      return std::make_unique<real_t>(val);
    }

    return nullptr;
    /*c**/
  }
};

// Question:

// FR | Pourquoi est-ce que le programme plante si on execute
// fact.build("toto", 17)?
// EN | Why does the program crash when we run fact.build("toto", 17)?

// FR | Corrigez la methode number_factory_t::build pour qu'elle renvoie nullptr
// si jamais le nom de type passe en argument est inconnu.

// EN | Fix number_factory_t::build to return nullptr if the type passed as a
// parameter is unknown.

// Question:

// FR | Quelle est la garantie d'exception de votre methode
// number_factory_t::build? Quelle aurait ete sa garantie si elle lancait une
// exception au lieu de retourner nullptr?

// EN | What's number_factory_t::build's exception guarantee? What would it be
// if it threw an exception instead of returning nullptr?
