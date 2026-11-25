#include "printing.hpp"

#include "types.hpp"

#include <variant>

// On donne operator<< pour fraction_t. Notez qu'on renvoie une *reference*
// vers un std::ostream.
std::ostream &operator<<(std::ostream &o, fraction_t const &n) {
  return o << n.n << '/' << n.d;
}

// Implementez std::ostream &operator<<(std::ostream &o, number_t const &n)
// avec std::visit.

std::ostream &operator<<(std::ostream &o, number_t const &n) {
  return std::visit([&o](auto const &val) -> std::ostream & { return o << val; }, n);
}
