#include "arithmetic.hpp"

#include "types.hpp"

// Definir les operateurs arithmetiques pour number_t ici

number_t operator+(number_t const &a, number_t const &b) {
  return std::visit([](auto const &aResolved, auto const &bResolved) -> number_t {
    return number_t{aResolved + bResolved};
  }, a, b);
}

number_t operator-(number_t const &a, number_t const &b){
  return std::visit([](auto const &aResolved, auto const &bResolved) -> number_t { return number_t{aResolved + bResolved};}, a, b);
}

number_t operator*(number_t const &a, number_t const &b){
  return std::visit([](auto const &aResolved, auto const &bResolved) -> number_t { return number_t{aResolved * bResolved};}, a, b);
}

number_t operator/(number_t const &a, number_t const &b){
  return std::visit(
    [](auto const &aResolved, auto const &bResolved) -> number_t { return number_t{aResolved / bResolved};}, a, b);
}

// ===
// Operateurs arithmetiques pour fraction_t
// ===

// ---
// fraction & fraction

// Definir les operateurs ici:
fraction_t operator+(fraction_t const &a, fraction_t const &b){
  return fraction_t{a.n * b.d + b.n * a.d, a.d * b.d};
};
fraction_t operator-(fraction_t const &a, fraction_t const &b){
  return fraction_t{a.n * b.d - b.n * a.d, a.d * b.d};
};
fraction_t operator*(fraction_t const &a, fraction_t const &b){
  return fraction_t{a.n * b.n, a.d * b.d};
};
fraction_t operator/(fraction_t const &a, fraction_t const &b){
  return fraction_t{a.n * b.d, a.d * b.n};
};

// ---
// fraction_t & double - les double sont convertis en fraction_t

fraction_t operator+(fraction_t const &f, double const &d) {
  return f + fraction_t{d, 1.};
}

fraction_t operator-(fraction_t const &f, double const &d) {
  return f - fraction_t{d, 1.};
}

fraction_t operator*(fraction_t const &f, double const &d) {
  return f * fraction_t{d, 1.};
}

fraction_t operator/(fraction_t const &f, double const &d) {
  return f / fraction_t{d, 1.};
}

fraction_t operator+(double const &d, fraction_t const &f) {
  return fraction_t{d, 1.} + f;
}

fraction_t operator-(double const &d, fraction_t const &f) {
  return fraction_t{d, 1.} - f;
}

fraction_t operator*(double const &d, fraction_t const &f) {
  return fraction_t{d, 1.} * f;
}

fraction_t operator/(double const &d, fraction_t const &f) {
  return fraction_t{d, 1.} / f;
}

// ---
// fraction_t & std::complex<double> - Les fraction_t sont converties en double

std::complex<double> operator+(fraction_t const &f,
                               std::complex<double> const &c) {
  return double(f) + c;
}

std::complex<double> operator-(fraction_t const &f,
                               std::complex<double> const &c) {
  return double(f) - c;
}

std::complex<double> operator*(fraction_t const &f,
                               std::complex<double> const &c) {
  return double(f) * c;
}

std::complex<double> operator/(fraction_t const &f,
                               std::complex<double> const &c) {
  return double(f) / c;
}

std::complex<double> operator+(std::complex<double> const &c,
                               fraction_t const &f) {
  return c + double(f);
}

std::complex<double> operator-(std::complex<double> const &c,
                               fraction_t const &f) {
  return c - double(f);
}

std::complex<double> operator*(std::complex<double> const &c,
                               fraction_t const &f) {
  return c * double(f);
}

std::complex<double> operator/(std::complex<double> const &c,
                               fraction_t const &f) {
  return c / double(f);
}
