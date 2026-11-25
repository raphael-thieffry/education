#include "number-factory.hpp"

void test_numbers() {
  number_ptr_t p = std::make_unique<integer_t>(1);
  std::make_unique<real_t>(2.3)->display(); // Output: "(real) 2.3"
  p->display();                             // Output: "(integer) 1"
}

void test_factory() {
  number_factory_t fact;

  if (number_ptr_t q = fact.build("integer", "42"); q) {
    q->display();
  }

  if (number_ptr_t q = fact.build("real", "3.14"); q) {
    q->display();
  }

  if (number_ptr_t q = fact.build("darude", "sandstorm"); q) {
    q->display();
  }
}

int main() {
  test_numbers();
  test_factory();
  return 0;
}
