#include <cassert>
#include <iostream>
#include <string>

#include <copy_ptr.hpp>

copy_ptr<std::string> foo()
{
  return copy_ptr<std::string>(new std::string("rvalue"));
}

int main() {
  copy_ptr<std::string> a(new std::string("a"));
  copy_ptr<std::string> b(new std::string("b"));

  copy_ptr<std::string> a_copy;
  a_copy = a;

  copy_ptr<std::string> some_lvalue (foo());

  assert(*a == "a");
  assert(*b == "b");
  assert(*a_copy == "a");

  copy_ptr<std::string> b_moved(std::move(b));
  assert(*b_moved == "b");
  assert(b == false);

  copy_ptr<std::string> a_copy_moved = std::move(a_copy);
  assert(*a_copy_moved == "a");
}
