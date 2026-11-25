#include <iostream>
#include <sstream>
#include <complex>
#include <vector>
#include <memory>
#include <cassert>
 
//------------------------------------------------------------------------------------------
// Implémentez une classe number avec les fonctions abstraites suivantes:
//
//  - une fonction print prenant un std::ostream en parametere et retournant std::ostream&
//  - une fonction square ne prenant aucun parametere et retournant un unique_ptr de number
//------------------------------------------------------------------------------------------
class number
{
  public:
  virtual std::ostream& print(std::ostream& os) const = 0;
  virtual std::unique_ptr<number> square()      const = 0;
  virtual ~number() {}
};
// arzopa
//------------------------------------------------------------------------------------------
// Complétez et corriger les classes suivantes pour que les tests de la fonction tests()
// compilent et passent avec succès.
//------------------------------------------------------------------------------------------
class integer : public number
{
  public:
  integer(std::ptrdiff_t n) : value_(n) {}

  std::ostream& print(std::ostream& os) const override
  {
    return os << "Integer(" << value_ << ")";
  }

  std::unique_ptr<number> square() const override
  {
    return std::make_unique<integer>(value_*value_);
    // return std::make_unique<integer>(value_*value_);
  }

  private:
  std::ptrdiff_t value_;
};

class real : public number
{
  public:
  real(double n) : value_(n) {}

  std::ostream& print(std::ostream& os) const override
  {
    return os << "Real(" << value_ << ")";
  }

  std::unique_ptr<number> square() const override
  {
    return std::make_unique<real>(value_*value_);
  }

  private:
  double value_;
};

class complex : public number
{
  public:
  complex(double r, double i)     : value_(r,i) {}
  complex(std::complex<double> n) : value_(n) {}

  std::ostream& print(std::ostream& os) const override
  {
    return os << "Complex" << value_;
  }

  std::unique_ptr<number> square() const override
  {
    return std::make_unique<complex>(value_*value_);
  }

  private:
  std::complex<double> value_;
};

void test()
{
  // Test integer::print
  {
    integer i(4);
    i.print(std::cout) << std::endl;

    std::ostringstream str;
    i.print(str);
    assert( str.str() == "Integer(4)");
  }

  // Test real::print
  {
    real    r(3.5);
    r.print(std::cout) << std::endl;

    std::ostringstream str;
    r.print(str);
    assert( str.str() == "Real(3.5)");
  }

  // Test complex::print
  {
    complex z(3.5,-0.25);
    z.print(std::cout) << std::endl;

    std::ostringstream str;
    z.print(str);
    assert( str.str() == "Complex(3.5,-0.25)");
  }

  // Test integer::square
  {
    integer i(4);
    auto p = i.square();
    p->print(std::cout) << std::endl;

    std::ostringstream str;
    p->print(str);
    assert( str.str() == "Integer(16)");
  }

  // Test real::square
  {
    real    r(3.5);
    auto p = r.square();
    p->print(std::cout) << std::endl;

    std::ostringstream str;
    p->print(str);
    assert( str.str() == "Real(12.25)");
  }

  // Test complex::square
  {
    complex z(3,-5);
    auto p = z.square();
    p->print(std::cout) << std::endl;

    std::ostringstream str;
    p->print(str);
    assert( str.str() == "Complex(-16,-30)");
  }
}

double roll(double min, double max)
{
  return (max - min) * (rand() / (1.*RAND_MAX)) + min;
}

//------------------------------------------------------------------------------------------
// Corrigez la fonction lotsanumbers pour qu'elle compile et s'exécute sans erreur
//------------------------------------------------------------------------------------------
void lotsanumbers(int n)
{
  std::vector<std::unique_ptr<number>> values(n);

  for(auto& p : values)
  {
    auto i = static_cast<int>( roll(0,3) );

    switch(i)
    {  
      case 0 : p = std::make_unique<integer>(roll(1,100)); break;
      case 1 : p = std::make_unique<real>(roll(-10,10)); break;
      case 2 : p = std::make_unique<complex>(roll(-5,5),roll(-5,5)); break;
    };
  }

  for(auto const& p : values)
    p->print(std::cout) << std::endl;
}

int main()
{
  test();
  lotsanumbers(10);
  
  return 0;
}