/*
  Exercice 1 - Fraction

  Fournissez une implémentation d'une structure fraction représentant un nombre
  fractionnaire. Vous implémenterez sous forme de fonction ou d'opérateur
  surchargés les fonctionnalités suivantes:

  - addition fraction+fraction, entier+fraction, fraction+entier
  - soustraction fraction-fraction, entier-fraction, fraction-entier
  - multiplication fraction*fraction, entier*fraction, fraction*entier
  - division fraction/fraction, entier/fraction, fraction/entier
  - négation de fraction
  - conversion de la fraction en nombre réel double précision
  - insertion et extraction depuis un flux
*/

#include <iostream>

struct Fraction {
  // num/den
  int num, den;

  // Fraction& operator*=(Fraction const &right) {
  //   num = num * right.num;
  //   den = den * right.den;
  //   return *this;
  // }
};

Fraction& operator*=(Fraction &left, Fraction const &right) {
  left.num *= right.num;
  left.den *= right.den;
  return left;
}

Fraction operator+(Fraction const &left, Fraction const &right) {
  return {left.num * right.den + right.num * left.den, left.den * right.den};
}

Fraction operator+(Fraction const &left, int const &i) {
  return {left.num + i * left.den, left.den};
}

Fraction operator+(int const &i, Fraction const &right) {
  return {i * right.den + right.num, right.den};
}

Fraction operator-(Fraction const &left, Fraction const &right) {
  return {left.num * right.den - right.num * left.den, left.den * right.den};
}

Fraction operator-(Fraction const &left, int const &i) {
  return {left.num - i * left.den, left.den};
}

Fraction operator-(int const &i, Fraction const &right) {
  return {i * right.den - right.num, right.den};
}

// Unary operator minus : -num/den
Fraction operator-(Fraction const &f) { return {-f.num, f.den}; }

Fraction operator*(Fraction const &left, Fraction const &right) {
  return {left.num * right.num, left.den * right.den};
}

Fraction operator*(Fraction const &left, int const &i) {
  return {left.num * i, left.den};
}

Fraction operator*(int const &i, Fraction const &right) {
  return {right.num * i, right.den};
}

// Fraction& operator*=(Fraction &left, Fraction const &right) {
//   return left * right;
// }

Fraction operator/(Fraction const &left, Fraction const &right) {
  return {left.num * right.den, left.den * right.num};
}

Fraction operator/(Fraction const &left, int const &i) {
  return {left.num, left.den * i};
}

Fraction operator/(int const &i, Fraction const &right) {
  return {right.den * i, right.num};
}

// Écriture dans un flux
std::ostream &operator<<(std::ostream &os, Fraction const &f) {
  return os << '(' << f.num << '/' << f.den << ')';
}

// Extraction depuis un flux
std::istream &operator>>(std::istream &is, Fraction &f) {
  return is >> f.num >> f.den;
}

double to_double(Fraction const &f) {
  return static_cast<double>(f.num) / f.den;
}

int main(int, char **) {

  Fraction f;
  std::cout << f << std::endl;

  Fraction x{1, 2};
  Fraction y{2, 3};
  Fraction z{0, 0};

  std::cout << x + y << std::endl;
  std::cout << x + 1 << std::endl;

  //0std::cin >> z;
  //std::cout << "fraction entrée : " << z << std::endl;

  Fraction a = x;
  a *= y;
  std::cout << "x * y : " << (x * y) << "   x *= y : " << a << std::endl;
}
