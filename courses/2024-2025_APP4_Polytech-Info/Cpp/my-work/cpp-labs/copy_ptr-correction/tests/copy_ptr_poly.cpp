#include <algorithm>
#include <cassert>
#include <string>

#include <copy_ptr.hpp>

/// [FR]
/// Classe parente. Son interface permet d'acceder a une copie de sa valeur via
/// get_value(), et d'obtenir un pointeur vers un clone de sa valeur via
/// clone().
///
/// [EN]
/// Parent class. Its interface allows accessing a copy of its value through
/// get_value(), and obtaining a pointer to a new clone of itself through
/// clone().
struct parent_t {
  virtual ~parent_t() = default;
  virtual parent_t *clone() const { return new parent_t(); }
  virtual std::string get_value() const { return "parent_value"; }
};

/// [FR]
/// Classe enfant. Elle herite de parent_t et permet de stocker une valeur
/// dynamique. get_value() permet d'obtenir cette valeur.
///
/// [EN]
/// Child class. It inherits from parent_t and allows to store a dynamic value.
/// get_value() allows to obtain that value.
struct child_t : parent_t {
  std::string value_;

  child_t(std::string value) : value_(std::move(value)) {}
  std::string get_value() const override { return value_; }
  parent_t *clone() const override { return new child_t(value_); }
};

int main() {
  copy_ptr<parent_t> mother_v(new parent_t());
  copy_ptr<parent_t> daughter_v(new child_t("child_value"));

  assert(mother_v->get_value() == "parent_value");
  assert(daughter_v->get_value() == "child_value");

  copy_ptr<parent_t> daughter_clone_v(daughter_v);
  assert(daughter_clone_v->get_value() == "child_value");

  copy_ptr<parent_t> daughter_moved_v(std::move(daughter_v));
  assert(daughter_moved_v->get_value() == "child_value");
  assert(!daughter_v);
}
