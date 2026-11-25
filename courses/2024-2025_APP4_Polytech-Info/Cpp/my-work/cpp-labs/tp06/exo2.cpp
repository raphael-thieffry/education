#include <memory>
#include <iostream>

template <class base_t, class derived_t = base_t> class cloneable {
public:
  virtual ~cloneable() {}

  virtual std::unique_ptr<base_t> clone() const {
    return std::make_unique<derived_t>(static_cast<derived_t const &>(*this));
  }
};

class mother_t : public cloneable<mother_t>
{
public:
  virtual void fct() const { std::cout << "mother_t" << std::endl; }
};

class daughter_t : public mother_t, public cloneable<mother_t, daughter_t> {
public:
  virtual void fct() const { std::cout << "daughter_t" << std::endl; }

  using cloneable<mother_t, daughter_t>::clone;
};



int main()
{
  auto p1 = std::make_unique<mother_t>();
  p1->fct();
  std::unique_ptr<mother_t> p2 = std::make_unique<daughter_t>();
  p2->fct();
  auto r = p2->clone();
  r->fct();
}