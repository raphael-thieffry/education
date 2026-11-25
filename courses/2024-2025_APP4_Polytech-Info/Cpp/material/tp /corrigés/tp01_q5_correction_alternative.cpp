#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <iomanip>

// Exemple de correction alternative pour la question 5 bonus,
// sans utiliser de méthode virtuelle pour base_matrix

// g++ tp01_correction.cpp -o e.exe -O3 --std=c++17 -Wall && ./e.exe


namespace question5
{
  enum matrix_type{diagonal, dense};

  struct base_matrix
  {
    base_matrix ( int sz, int total_size, matrix_type ty) 
                : storage(total_size), size(sz), type(ty) {}
    int height() const { return size;     }
    int width()  const { return height(); }
    virtual void   set(int, int, double) = 0;
    virtual std::string get_name() = 0;
    virtual ~base_matrix() = default;
    matrix_type get_type() { return type; }

    // défini après pour avoir les structures dense et diagonal complètement déclarées
    // TODO mettre virtual
    base_matrix* add(base_matrix* other); 

    protected:
    std::vector<double> storage;
    int size;
    matrix_type type;
  };

  struct dense_matrix : public base_matrix
  {
    explicit dense_matrix(int n) : base_matrix(n, n*n, matrix_type::dense) {}
    double get(int l, int c) const { return storage[c + l * width()]; }
    void set(int l, int c, double v)  override {  storage[c + l * width()] = v;  }
    std::string get_name() { return "dense"; }
  };

  struct diagonal_matrix : public base_matrix
  {
    explicit diagonal_matrix(int n) : base_matrix(n, n, matrix_type::diagonal) {}
    // Suppression du mot clé "override"
    double get(int l, int c) const    
    {
      if(l == c)  return storage[c];
      else        return 0.; 
    }
    void set(int l, int c, double v) override
    { 
      assert(   l == c 
            &&  "access to diagonal matrix requires similar row and col"
            );
      if(l == c) storage[c] = v;
    }
    std::string get_name() { return "diagonale"; }
  };

  base_matrix* base_matrix::add(base_matrix* other)
  {
    assert(height() == other->height());
    assert(width()  == other->width());
    if ((get_type() == matrix_type::diagonal) && (other->get_type() == matrix_type::diagonal))
    {
      diagonal_matrix* m1 = static_cast<diagonal_matrix*>(this);
      diagonal_matrix* m2 = static_cast<diagonal_matrix*>(other);

      diagonal_matrix* res = new diagonal_matrix{height()};
      for (int i = 0; i < height(); ++i)
      {
        res->set(i, i, m1->get(i, i) + m2->get(i, i));
      }
      return res;
    }

    if ((get_type() == matrix_type::diagonal) && (other->get_type() == matrix_type::dense))
    {
      diagonal_matrix* m1 = static_cast<diagonal_matrix*>(this);
      dense_matrix* m2 = static_cast<dense_matrix*>(other);

      dense_matrix* res = new dense_matrix{height()};
      for (int i = 0; i < width(); ++i)
      {
        for (int j = 0; j < height(); ++j)
        {
          res->set(i, j, m1->get(i, j) + m2->get(i, j));
        }
      }
      return res;
    }

    if ((get_type() == matrix_type::dense) && (other->get_type() == matrix_type::diagonal))
    {
      diagonal_matrix* m1 = static_cast<diagonal_matrix*>(other);
      dense_matrix* m2 = static_cast<dense_matrix*>(this);

      dense_matrix* res = new dense_matrix{height()};
      for (int i = 0; i < width(); ++i)
      {
        for (int j = 0; j < height(); ++j)
        {
          res->set(i, j, m1->get(i, j) + m2->get(i, j));
        }
      }
      return res;
    }

    if ((get_type() == matrix_type::dense) && (other->get_type() == matrix_type::dense))
    {
      dense_matrix* m1 = static_cast<dense_matrix*>(other);
      dense_matrix* m2 = static_cast<dense_matrix*>(this);

      dense_matrix* res = new dense_matrix{height()};
      for (int i = 0; i < width(); ++i)
      {
        for (int j = 0; j < height(); ++j)
        {
          res->set(i, j, m1->get(i, j) + m2->get(i, j));
        }
      }
      return res;
    }

    return new dense_matrix{height()}; // <- ne doit jamais arriver
  }

  

  base_matrix* make_matrix(int matrix_size, matrix_type type)
  {
    // Initialisation de la matrice :
    // Allocation et remplissage avec des nombres (la valeur des cellules importe peu)
    base_matrix* m;
    if (type == matrix_type::diagonal)
    {
      m = new diagonal_matrix{matrix_size};
      for (std::size_t i = 0; i < (std::size_t)matrix_size; ++i)
      {
        m->set(i, i, i);
      }
    }
    else
    {
      m = new dense_matrix{matrix_size};
      for (std::size_t i = 0; i < (std::size_t)matrix_size; ++i)
      {
        for (std::size_t j = 0; j < (std::size_t)matrix_size; ++j)
        {
          m->set(i, j, i + j);
          // équivalent :
          // m -> set(i, j, i + j);
          // (*m).set(i, j, i + j);
        }
      }
    }
    return m;
  }

  // TODO mettre en virtual
  void print_matrix(base_matrix* m)
  {
    if (m->get_type() == matrix_type::dense)
    {
      std::cout << "Matrice dense : \n";
      std::cout << std::setw(3);
      dense_matrix* d = static_cast<dense_matrix*>(m);
      for (int i = 0; i < d->width(); ++i)
      {
        for (int j = 0; j < d->height(); ++j)
        {
          std::cout << std::setw(2) << d->get(i, j) << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }

    if (m->get_type() == matrix_type::diagonal)
    {
      std::cout << "Matrice diagonale : \n";
      diagonal_matrix* d = static_cast<diagonal_matrix*>(m);
      for (int i = 0; i < d->width(); ++i)
      {
        for (int j = 0; j < d->height(); ++j)
        {
          std::cout << std::setw(2) << d->get(i, j) << " ";
        }
        std::cout << "\n";
      }
    }
  }

  void main_q5_config(int size, matrix_type type1, matrix_type type2)
  {
    base_matrix* m1 = make_matrix(size, type1);
    base_matrix* m2 = make_matrix(size, type2);
    print_matrix(m1);
    std::cout << "+ \n";
    print_matrix(m2);
    std::cout << "= \n";
    base_matrix* sum = m1->add(m2);
    print_matrix(sum);
    delete m1;
    delete m2;
    delete sum;
  }

  void main_q5()
  {
    main_q5_config(3, matrix_type::dense, matrix_type::dense); std::cout << "\n------------------------ \n\n";
    main_q5_config(3, matrix_type::diagonal, matrix_type::dense); std::cout << "\n------------------------ \n\n";
    main_q5_config(3, matrix_type::diagonal, matrix_type::diagonal); std::cout << "\n------------------------ \n\n";
    main_q5_config(3, matrix_type::dense, matrix_type::diagonal);
  }

}


// g++ tp01_correction.cpp -o e.exe -O3 --std=c++17 -Wall && ./e.exe
int main()
{
  std::cout << "\n\nQuestion 5 alternative :\n";
  question5::main_q5();
  return 0;
}