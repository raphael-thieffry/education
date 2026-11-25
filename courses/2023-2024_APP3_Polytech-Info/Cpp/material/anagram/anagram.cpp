/* Anagrammes */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

// RAPPEL: ne pas changer les signatures
std::string normalize(std::string const &v) {
  // A REMPLIR
}

bool are_anagrams(std::string const &v1, std::string const &v2) {
  // A REMPLIR
}

std::vector<std::string> load() {
  // A REMPLIR
}

using dictionary = std::multimap<std::string, std::string>;

dictionary convert(std::vector<std::string> &vect) {
  // A REMPLIR
}

std::vector<std::string> anagrams(dictionary const &dict,
                                  std::string const &s) {
  // A REMPLIR
}

int main() { return 0; }
