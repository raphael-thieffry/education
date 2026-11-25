#include <iostream>
#include <vector>
#include <cassert>
#include<chrono>

struct base_matrix
{
  base_matrix ( int sz, int total_size) 
              : storage(total_size), size(sz) 
  {}

  [[nodiscard]] int height() const { return size;     }
  [[nodiscard]] int width()  const { return height(); }

  virtual base_matrix* add(const base_matrix& other) = 0;

  [[nodiscard]] virtual double trace() const = 0;

  protected:
  std::vector<double> storage;
  int size;
};

struct dense_matrix : public base_matrix
{
  explicit dense_matrix(int n) : base_matrix(n, n*n) {}

  [[nodiscard]] double get(int l, int c) const   
  { 
    return storage[c + l * width()]; 
  }

  base_matrix* add(const base_matrix& other) override
  {
    //cannot do get since it is specific for each implementation ; instead we have to define a new method in the base class 
    auto* result = new dense_matrix(size);
    for(int l = 0;l<height();++l)
      for(int c = 0;c<width();c++)
        result->set(l,c, get(l,c) + other.get(l,c));
    return result;
  };


  void set(int l, int c, double v) 
  { 
    storage[c + l * width()] = v; 
  }

  [[nodiscard]] double trace() const override
  {
    double sum = 0.;
    for(int i = 0; i < height(); ++i)
      sum += get(i,i);
    return sum;
  }
};

struct diagonal_matrix : public base_matrix
{
  explicit diagonal_matrix(int n) : base_matrix(n,n) {}

  [[nodiscard]] double get(int l, int c) const    
  {
    if(l == c)  return storage[c];
    else        return 0.; 
  }

  void set(int l, int c, double v)
  { 
    assert(   l == c 
          &&  "access to diagonal matrix requires similar row and col"
          );
    if(l == c) storage[c] = v;
  }
  
  [[nodiscard]] double trace() const override
    {
      double sum = 0.;
      for(int i = 0; i < height(); ++i)
        sum += get(i,i);
      return sum;
    }
};

// double trace(base_matrix const& base_matrix)
// {
//   double sum = 0.;
//   for(int i = 0; i < base_matrix.height(); ++i)
//     sum += base_matrix.get(i,i);
//   return sum;
// }

int main()
{
  dense_matrix d(3);
  
  for(int l = 0;l<d.height();++l)
    for(int c = 0;c<d.width();c++)
      d.set(l,c, (1+c) + 100.*(l+1));

  for(int l = 0;l<d.height();++l)
  {
    for(int c = 0;c<d.width();c++)
      std::cout << d.get(l,c) << " ";
    std::cout << "\n";
  }

  diagonal_matrix dg(3);
  
  for(int l = 0;l<dg.height();++l)
    dg.set(l,l, (1+l) + 100.*(l+1));

  for(int l = 0;l<dg.height();++l)
  {
    for(int c = 0;c<dg.width();c++)
      std::cout << dg.get(l,c) << " ";
    std::cout << "\n";
  }


  dense_matrix d2(10000);
  diagonal_matrix dg2(10000);
  for(int l = 0;l<dg2.height();++l)
    dg2.set(l,l, (1+l) + 100.*(l+1)), d2.set(l,l, (1+l) + 100.*(l+1));

  auto start = std::chrono::system_clock::now();
  for(int i = 0; i < 1000; ++i)
    d2.trace();
  auto stop  = std::chrono::system_clock::now();
  std::chrono::duration<double> duration = stop - start;
  auto elapsed_dense = duration.count();

  start = std::chrono::system_clock::now();
  for(int i = 0; i < 1000; ++i)
    dg2.trace();
  stop  = std::chrono::system_clock::now();
  duration = stop - start;
  auto elapsed_diag = duration.count();

  std::cout << "dense matrix trace: " << elapsed_dense << "s\n";
  std::cout << "diagonal matrix trace: " << elapsed_diag << "s\n";


  char c;
  std::cin >> c;

  base_matrix* p1;
  //base_matrix* p2;


  if(c == 'd')
  {
    p1 = new dense_matrix(10000);
    //p2 = new diagonal_matrix(200);
  }
  else
  {
    p1 = new diagonal_matrix(10000);
    //p2 = new dense_matrix(200);
  }

  start = std::chrono::system_clock::now();
  for(int i = 0; i < 1000; ++i)
    p1->trace();
  stop  = std::chrono::system_clock::now();
  duration = stop - start;
  auto elapsed = duration.count();

  std::cout << "base matrix : " << elapsed << "s\n";

  delete p1;
}
