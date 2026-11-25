#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <iomanip>

// Ce n'est qu'un exemple de résolution de l'exercice constituant le TP1,
// il n'y a pas unicité de la solution, vous pouvez très bien faire quelque
// chose de parfait qui ne ressemble pas à ce que j'ai écrit là.

// g++ tp01_correction.cpp -o e.exe -O3 --std=c++17 -Wall && ./e.exe

namespace partie1
{

  struct base_matrix
  {
    base_matrix ( int sz, int total_size) 
                : storage(total_size), size(sz) 
    {}

    [[nodiscard]] int height() const { return size;     }
    [[nodiscard]] int width()  const { return height(); }

    [[nodiscard]] virtual double get(int, int) const = 0;
    virtual void   set(int, int, double) = 0;
    virtual std::string get_name() = 0;
    // le = 0 permet de déclarer une fonction virtuelle pure (c'est à dire abstraite, sans implémentation) :
    // Pour devenir des classes concrètes (qu'il est possible instancier, contrairement à new),
    // les classes filles devront impérativement implémenter toutes les méthodes virtuelles pures.

    virtual ~base_matrix() = default;

    protected:
    std::vector<double> storage;
    int size;
  };

  struct dense_matrix : public base_matrix
  {
    explicit dense_matrix(int n) : base_matrix(n, n*n) {}

    [[nodiscard]] double get(int l, int c) const override   
    { 
      return storage[c + l * width()]; 
    }

    void set(int l, int c, double v)  override
    { 
      storage[c + l * width()] = v; 
    }

    std::string get_name()
    {
      return "dense";
    }
  };

  struct diagonal_matrix : public base_matrix
  {
    explicit diagonal_matrix(int n) : base_matrix(n,n) {}

    [[nodiscard]] double get(int l, int c) const override    
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

    std::string get_name()
    {
      return "diagonale";
    }
  };

  double trace(base_matrix const& base_matrix)
  {
    double res = 0;
    assert(base_matrix.height() == base_matrix.width());
    std::size_t size = base_matrix.height();
    for (std::size_t i = 0; i < size; ++i)
    {
      res += base_matrix.get(i, i);
    }
    return res;
  }

  base_matrix* make_matrix(int matrix_size, bool use_diag_matrix)
  {
    // Initialisation de la matrice :
    // Allocation et remplissage avec des nombres (la valeur des cellules importe peu)
    base_matrix* m;
    if (use_diag_matrix)
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

  // Bench veut dire "effectuer un benchmark", c'est à dire une évaluation des performances
  // -> https://fr.wikipedia.org/wiki/Test_de_performance
  // sans oublier le "#include<chrono>"

  // Surcharge de la fonction bench_matrix
  void bench_matrix(std::size_t repeat_count, base_matrix* m)
  {
    // Si on ne se sert pas du résultat de trace, le compilateur va réaliser que faire les calculs
    // ne sert à rien, il va donc optimiser le code en n'exécutant tout simplement pas la boucle.
    double nasty_compiler = 0;

    auto start = std::chrono::system_clock::now();
    /* Code donc le temps est à mesurer (en secondes) */

    for (std::size_t i = 0; i < repeat_count; ++i)
    {
      nasty_compiler += trace(*m);
    }

    auto stop  = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = stop - start;
    auto elapsed_time = duration.count(); // temps en secondes, nombre décimal

    // J'ai rajouté le get_name() pour un affichage plus simple ici
    std::cout << "Matrice " << m->get_name()
              << " taille " << m->height() << " : "
              << elapsed_time << " seconde.s."
              << "   osef(" << nasty_compiler << ")"
              << "\n"; // équivalent à std::endl();
  }

  void bench_matrix(std::size_t repeat_count, int matrix_size, bool use_diag_matrix)
  {
    base_matrix* m = make_matrix(matrix_size, use_diag_matrix);

    bench_matrix(repeat_count, m);

    delete m;
  }

  

  int main_base()
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
    return 0;
  }

  int main_q1()
  {
    trace(dense_matrix{3});
    trace(diagonal_matrix{3});
    return 0;
  }

  int main_q2()
  {
  
    bench_matrix(100000000, 10, false);
    bench_matrix(5000000, 100, false);
    bench_matrix(1000000, 500, false);
    /*
    Matrice dense taille 10 : 
        Temps pris : 1.88904 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 9e+09
    Matrice dense taille 100 : 
        Temps pris : 1.14186 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.95e+10
    Matrice dense taille 500 : 
        Temps pris : 1.17188 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 2.495e+11
    */

    bench_matrix(100000000, 10, true);
    bench_matrix(5000000, 100, true);
    bench_matrix(1000000, 500, true);
    /*
    Matrice diagonale taille 10 : 
        Temps pris : 1.91369 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.5e+09
    Matrice diagonale taille 100 : 
        Temps pris : 1.13229 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 3.2375e+11
    Matrice diagonale taille 500 : 
        Temps pris : 1.16787 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.485e+11
    */

    return 0;
  }

  // Globalement on a les mêmes temps, cette question n'est utile que dans certains cas bien spécifiques
  // où le compilateur optimise beaucoup les choses.
  // Vous n'aurez pas ça à l'exam, pas d'inquiétude.
  int main_q3()
  {
    std::cout << "Saisissez la lettre \"f\" ou une autre lettre :\n";
    char c;
    std::cin >> c;

    base_matrix* p1;
    base_matrix* p2;
    std::size_t matrix_size = 100;    

    if(c == 'f')
    {
      std::cout << "Lettre \"f\" reçue.\n";
      p1 = make_matrix(matrix_size, false);
      p2 = make_matrix(matrix_size, true);
    }
    else
    {
      std::cout << "Autre lettre que \"f\" reçue.\n";
      p1 = make_matrix(matrix_size, true);
      p2 = make_matrix(matrix_size, false);
    }
  
    bench_matrix(5000000, p1);
    bench_matrix(5000000, p2);
    /*
    Lettre "f" reçue.
    Matrice dense taille 100 : 
        Temps pris : 1.13533 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.95e+10
    Matrice diagonale taille 100 : 
        Temps pris : 1.16866 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 2.475e+10
    
    Autre lettre que "f" reçue.
    Matrice diagonale taille 100 : 
        Temps pris : 1.11992 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 2.475e+10
    Matrice dense taille 100 : 
        Temps pris : 1.12706 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.95e+10
    */

    // On a globalement les mêmes résultats.   

    return 0;
  }

}









namespace partie2
{

  struct base_matrix
  {
    base_matrix ( int sz, int total_size) 
                : storage(total_size), size(sz) 
    {}

    [[nodiscard]] int height() const { return size;     }
    [[nodiscard]] int width()  const { return height(); }

    // J'ai supprimé get de base_matrix, et ajouté trace en abstraite
    virtual double trace() = 0;
    virtual void   set(int, int, double) = 0;

    virtual std::string get_name() = 0;
    // le = 0 permet de déclarer une fonction virtuelle pure (c'est à dire abstraite, sans implémentation) :
    // Pour devenir des classes concrètes (qu'il est possible instancier, contrairement à new),
    // les classes filles devront impérativement implémenter toutes les méthodes virtuelles pures.

    virtual ~base_matrix() = default;

    protected:
    std::vector<double> storage;
    int size;
  };

  struct dense_matrix : public base_matrix
  {
    explicit dense_matrix(int n) : base_matrix(n, n*n) {}

    // Suppression du mot clé "override"
    [[nodiscard]] double get(int l, int c) const   
    { 
      return storage[c + l * width()]; 
    }

    void set(int l, int c, double v)  override
    { 
      storage[c + l * width()] = v; 
    }

    std::string get_name()
    {
      return "dense";
    }

    double trace() override
    {
      double res = 0;
      assert(height() == width());
      // Ces 3 écritures sont équivalentes :
      //   this -> width();
      //   (*this).width();
      //           width();
      std::size_t size = height();
      for (std::size_t i = 0; i < size; ++i)
      {
        res += get(i, i);
      }
      return res;
    }
  };

  struct diagonal_matrix : public base_matrix
  {
    explicit diagonal_matrix(int n) : base_matrix(n,n) {}

    // Suppression du mot clé "override"
    [[nodiscard]] double get(int l, int c) const    
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

    std::string get_name()
    {
      return "diagonale";
    }

    double trace() override
    {
      double res = 0;
      std::size_t size = height();
      for (std::size_t i = 0; i < size; ++i)
      {
        res += get(i, i);
      }
      return res;
    }
  };

  

  base_matrix* make_matrix(int matrix_size, bool use_diag_matrix)
  {
    // Initialisation de la matrice :
    // Allocation et remplissage avec des nombres (la valeur des cellules importe peu)
    base_matrix* m;
    if (use_diag_matrix)
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

  // Bench veut dire "effectuer un benchmark", c'est à dire une évaluation des performances
  // -> https://fr.wikipedia.org/wiki/Test_de_performance
  // sans oublier le "#include<chrono>"

  // Surcharge de la fonction bench_matrix
  void bench_matrix(std::size_t repeat_count, base_matrix* m)
  {
    // Si on ne se sert pas du résultat de trace, le compilateur va réaliser que faire les calculs
    // ne sert à rien, il va donc optimiser le code en n'exécutant tout simplement pas la boucle.
    double nasty_compiler = 0;

    auto start = std::chrono::system_clock::now();
    /* Code donc le temps est à mesurer (en secondes) */

    for (std::size_t i = 0; i < repeat_count; ++i)
    {
      nasty_compiler += m->trace();
    }

    auto stop  = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = stop - start;
    auto elapsed_time = duration.count(); // temps en secondes, nombre décimal

    // J'ai rajouté le get_name() pour un affichage plus simple ici
    std::cout << "Matrice " << m->get_name()
              << " taille " << m->height() << " : "
              << elapsed_time << " seconde.s."
              << "   osef(" << nasty_compiler << ")"
              << "\n"; // équivalent à std::endl();
  }

  void bench_matrix(std::size_t repeat_count, int matrix_size, bool use_diag_matrix)
  {
    base_matrix* m = make_matrix(matrix_size, use_diag_matrix);

    bench_matrix(repeat_count, m);

    delete m;
  }


  int main_q4()
  {
  
    bench_matrix(100000000, 10 , false);
    bench_matrix(5000000  , 100, false);
    bench_matrix(1000000  , 500, false);
    /*
    Matrice dense taille 10      : 0.732985 seconde.s.   osef(9e+09)
    Matrice dense taille 100     : 0.380011 seconde.s.   osef(4.95e+10)
    Matrice dense taille 500     : 0.401471 seconde.s.   osef(2.495e+11)

    Matrice diagonale taille 10  : 0.720553 seconde.s.   osef(4.5e+09)
    Matrice diagonale taille 100 : 0.338783 seconde.s.   osef(2.475e+10)
    Matrice diagonale taille 500 : 0.381869 seconde.s.   osef(1.2475e+11)
    */

    bench_matrix(100000000, 10 , true);
    bench_matrix(5000000  , 100, true);
    bench_matrix(1000000  , 500, true);
    /*
    Matrice diagonale taille 10 : 
        Temps pris : 1.91369 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.5e+09
    Matrice diagonale taille 100 : 
        Temps pris : 1.13229 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 3.2375e+11
    Matrice diagonale taille 500 : 
        Temps pris : 1.16787 seconde.s.
        Pour ne pas que le compilateur ne zappe les calculs : 4.485e+11
    */

    return 0;
  }

}

int main_q4_comparaison()
{
  std::cout << "Appel get virtuel : ";
  partie1::bench_matrix(100000000, 10 , false);
  std::cout << "Appel get concret : ";
  partie2::bench_matrix(100000000, 10 , false);

  std::cout << "Appel get virtuel : ";
  partie1::bench_matrix(5000000, 100 , false);
  std::cout << "Appel get concret : ";
  partie2::bench_matrix(5000000, 100 , false);

  std::cout << "Appel get virtuel : ";
  partie1::bench_matrix(1000000, 500 , false);
  std::cout << "Appel get concret : ";
  partie2::bench_matrix(1000000, 500 , false);

  /*
  Appel get virtuel : Matrice dense taille 10 : 1.66515 seconde.s.   osef(9e+09)
  Appel get concret : Matrice dense taille 10 : 0.644446 seconde.s.   osef(9e+09)
  Appel get virtuel : Matrice dense taille 100 : 1.13234 seconde.s.   osef(4.95e+10)
  Appel get concret : Matrice dense taille 100 : 0.354279 seconde.s.   osef(4.95e+10)
  Appel get virtuel : Matrice dense taille 500 : 1.20764 seconde.s.   osef(2.495e+11)
  Appel get concret : Matrice dense taille 500 : 0.394479 seconde.s.   osef(2.495e+11)
  */

  // Donc les enfants, les appels virtuels c'est super pour les fonctionnalités et la facilite de développent,
  // mais si vous effectuez de (très très) nombreux à une méthode virtuelle, ça peut vous coûter cher en performances.

  // Speedup environ 2.5 à 3 sur ma machine avec :
  // g++ (Ubuntu 11.4.0-2ubuntu1~20.04) 11.4.0
  // g++ tp01_correction.cpp -o e.exe -O3 --std=c++17 -Wall && ./e.exe

  // Cas particulier de pour une matrice de taille 1 ; on a le même temps !
  // Car dans les deux cas on fait un seul appel virtuel :
  // - matrix.trace() est un appel virtuel et on fait un appel concret à get(0, 0)
  // - matrix.trace() est un appel concret et on fait un appel virtuel à get(0, 0)

  std::cout << "Appel get virtuel : ";
  partie1::bench_matrix(300000000, 1 , false);
  std::cout << "Appel get concret : ";
  partie2::bench_matrix(300000000, 1 , false);
  /*
  Appel get virtuel : Matrice dense taille 1 : 0.717368 seconde.s.   osef(0)
  Appel get concret : Matrice dense taille 1 : 0.712769 seconde.s.   osef(0)
  */

  return 0;
}






namespace question5
{
  enum matrix_type{diagonal, dense};

  struct dense_matrix; // forward declaration
  struct diagonal_matrix;

  struct base_matrix
  {
    base_matrix ( int sz, int total_size) 
                : storage(total_size), size(sz) {}
    int height() const { return size;     }
    int width()  const { return height(); }
    virtual void   set(int, int, double) = 0;
    virtual std::string get_name() = 0;
    virtual ~base_matrix() = default;

    // défini après pour avoir les structures dense et diagonal complètement déclarées
    // TODO mettre virtual
    // base_matrix* add(base_matrix* other); 
    virtual base_matrix* add(base_matrix* other) = 0;
    virtual base_matrix* do_add(dense_matrix* other) = 0;
    virtual base_matrix* do_add(diagonal_matrix* other) = 0;

    virtual void print() = 0;

    protected:
    std::vector<double> storage;
    int size;
  };

  struct dense_matrix : public base_matrix
  {
    explicit dense_matrix(int n) : base_matrix(n, n*n) {}
    double get(int l, int c) const { return storage[c + l * width()]; }
    void set(int l, int c, double v)  override {  storage[c + l * width()] = v;  }
    std::string get_name() { return "dense"; }
    base_matrix* add(base_matrix* other) override { return other->do_add(this); }
    
    // Défini dans la suite du code, après la définition complète de diagonal_matrix 
    base_matrix* do_add(dense_matrix* other) override;
    base_matrix* do_add(diagonal_matrix* other) override;

    void print() override
    {
      std::cout << "Matrice dense : \n";
      for (int i = 0; i < width(); ++i)
      {
        for (int j = 0; j < height(); ++j)
        {
          std::cout << std::setw(2) << get(i, j) << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }

  };

  struct diagonal_matrix : public base_matrix
  {
    explicit diagonal_matrix(int n) : base_matrix(n, n) {}
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

    base_matrix* add(base_matrix* other) override { return other->do_add(this); }

    // Défini dans la suite du code (même si là on aurait pu l'écrire directement)
    base_matrix* do_add(dense_matrix* other) override;
    base_matrix* do_add(diagonal_matrix* other) override;

    void print() override
    {
      std::cout << "Matrice diagonale : \n";
      for (int i = 0; i < width(); ++i)
      {
        for (int j = 0; j < height(); ++j)
        {
          std::cout << std::setw(2) << get(i, j) << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }
  };

  // Implémentation des méthodes pour diagonal_matrix
  base_matrix* diagonal_matrix::do_add(diagonal_matrix* other)
  {
    assert(height() == other->height());
    assert(width()  == other->width());
    diagonal_matrix* res = new diagonal_matrix{height()};
    for (int i = 0; i < height(); ++i)
    {
      res->set(i, i, get(i, i) + other->get(i, i));
    }
    return res;
  }

  base_matrix* diagonal_matrix::do_add(dense_matrix* other)
  {
    assert(height() == other->height());
    assert(width()  == other->width());
    dense_matrix* res = new dense_matrix{height()};
    for (int i = 0; i < width(); ++i)
    {
      for (int j = 0; j < height(); ++j)
      {
        res->set(i, j, get(i, j) + other->get(i, j));
      }
    }
    return res;
  }

  // Implémentation des méthodes pour dense_matrix
  base_matrix* dense_matrix::do_add(diagonal_matrix* other)
  {
    assert(height() == other->height());
    assert(width()  == other->width());
    dense_matrix* res = new dense_matrix{height()};
    for (int i = 0; i < width(); ++i)
    {
      for (int j = 0; j < height(); ++j)
      {
        res->set(i, j, get(i, j) + other->get(i, j));
      }
    }
    return res;
  }

  base_matrix* dense_matrix::do_add(dense_matrix* other)
  {
    assert(height() == other->height());
    assert(width()  == other->width());
    dense_matrix* res = new dense_matrix{height()};
    for (int i = 0; i < width(); ++i)
    {
      for (int j = 0; j < height(); ++j)
      {
        res->set(i, j, get(i, j) + other->get(i, j));
      }
    }
    return res;
  }
  

  base_matrix* make_matrix(int matrix_size, bool use_diag_matrix)
  {
    // Initialisation de la matrice :
    // Allocation et remplissage avec des nombres (la valeur des cellules importe peu)
    base_matrix* m;
    if (use_diag_matrix)
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


  void main_q5_config(int size, bool use_diag_matrix1, bool use_diag_matrix2)
  {
    base_matrix* m1 = make_matrix(size, use_diag_matrix1);
    base_matrix* m2 = make_matrix(size, use_diag_matrix2);
    m1->print();
    std::cout << "+ \n";
    m2->print();
    std::cout << "= \n";
    base_matrix* sum = m1->add(m2);
    sum->print();
    delete m1;
    delete m2;
    delete sum;
  }

  void main_q5()
  {
    main_q5_config(3, false, true);  std::cout << "\n------------------------ \n\n";
    main_q5_config(3, true , false); std::cout << "\n------------------------ \n\n";
    main_q5_config(3, true , true);  std::cout << "\n------------------------ \n\n";
    main_q5_config(3, false, false);
  }

}


// g++ tp01_correction.cpp -o e.exe -O3 --std=c++17 -Wall && ./e.exe
int main()
{
  std::cout << "Question 1 :\n";
  partie1::main_q1();
  std::cout << "\n\nQuestion 2 :\n";
  partie1::main_q2();
  std::cout << "\n\nQuestion 3 :\n";
  partie1::main_q3();
  std::cout << "\n\nQuestion 4 :\n";
  partie2::main_q4();
  std::cout << "\n\nQuestion 4, comparaison de la vitesse d'appel :\n";
  main_q4_comparaison();
  std::cout << "\n\nQuestion 5 :\n";
  question5::main_q5();
  return 0;
}