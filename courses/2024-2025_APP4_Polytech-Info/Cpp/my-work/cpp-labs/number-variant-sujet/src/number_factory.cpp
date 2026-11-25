#include "number_factory.hpp"
#include "types.hpp"

#include <sstream>

// Implementez ici
// number_t number_factory(std::string const &kind, std::string const &text)

number_t number_factory(std::string const &kind, std::string const &text) {
  std::istringstream iss(text);
  if (kind == "integer") {
    int i;
    iss >> i;
    return i;
  } else if (kind == "real") {
    double d;
    iss >> d;
    return d;
  } else if (kind == "fraction") {
    double n, d;
    iss >> n >> d;
    return fraction_t{n, d};
  } else if (kind == "complex") {
    double r, i;
    iss >> r >> i;
    return std::complex<double>{r, i};
  } else {
    return number_t{};
  }
}
