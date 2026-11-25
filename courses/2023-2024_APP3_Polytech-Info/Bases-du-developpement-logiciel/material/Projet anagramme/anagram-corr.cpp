#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include <vector>

std::vector<std::string> load() {
  std::vector<std::string> res;
  std::ifstream file("D:/Documents/Enseignement/ET3-Polytech/TD/assignment/miniproject/01-anagram/words.txt");
  std::string buf;
  std::cout<<"Loading file..."<<std::endl;
  while (std::getline(file, buf)) {
    if (!buf.empty())
      res.push_back(buf);
  }

  return res;
}

std::string normalize(std::string const &v) {
  std::string res = v;
  std::sort(res.begin(), res.end());
  return res;
}

bool anagram(std::string const &v1, std::string const &v2) {
  return normalize(v1) == normalize(v2);
}

using dictionary = std::multimap<std::string, std::string>;

dictionary convert(std::vector<std::string> &vect) {
  dictionary dict; 

  for (auto const &v : vect)
    dict.insert(std::make_pair(normalize(v), v));

  return dict;
}

std::vector<std::string> anagrams(dictionary const &dict,
                                  std::string const &s) {
  std::vector<std::string> res;
  auto it = dict.equal_range(normalize(s));
  bool found = false;
  for (auto i = it.first; i != it.second; ++i) {
    if (i->second == s)
      found = true;
    else
      res.push_back(i->second);
  }

  if (!found) {
    std::cout << "NOT FOUND !\n";
  }

  return res;
}

int main() {
  std::vector<std::string> words = load();

  std::cout << words.size() << " words\n" << words[words.size() - 1] << '\n';
  std::cout << normalize("ironique") << ", " << anagram("ironique", "onirique")
            << '\n';

  dictionary dict = convert(words);

  char const *test_words[] = {"anagram", "parrot", "abba", "insert", "silent"};

  for (auto w : test_words) {
    std::cout << w << ':';
    for (auto const &s : anagrams(dict, w))
      std::cout << ' ' << s;
    std::cout << '\n';
  }
}
