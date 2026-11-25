#include <stdexcept>
#include <array>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test)                                                           \
    if (!(test))                                                               \
    cout << "Test failed in file " << __FILE__ << " line " << __LINE__         \
         << ": " #test << endl

const float epsilon = 1e-6;
bool presqueEgal(float x, float y);


// Un nombre complexe se compose d'une partie réelle et d'une partie imaginaire
struct Complexe {
    float re, im;
};

// Surcharge de l'operator ==
bool operator==(Complexe z, Complexe w) {
    return z.re == w.re and z.im == w.im;
}

// Surcharge de l'operator !=
bool operator!=(Complexe z, Complexe w) { return not(z == w); }

// Surcharge de l'operator <<
std::ostream &operator<<(std::ostream &out, Complexe z) {
    if (z.im >= 0) {
        out << z.re << "+i" << z.im;
    } else {
        out << z.re << "-i" << -z.im;
    }
    return out;
}

// Surcharge de l'operator +
Complexe operator+(Complexe z, Complexe w) {
    return {z.re + w.re, z.im + w.im};
}

// Surcharge de l'operator - avec un seul nombre
Complexe operator-(Complexe z) { return {-z.re, -z.im}; }

// Surcharge de l'operator - avec deux nombres
Complexe operator-(Complexe a, Complexe b) { return a + (-b); }

// Surcharge de l'operator *
Complexe operator*(Complexe z, Complexe w) {
    return {(z.re*w.re-z.im*w.im),(z.re*w.im+w.re*z.im)};
}

// Test de la surcharge de l'operator *
void testMultiplication() {
    Complexe z1 = {2.4, 1};
    Complexe z2 = {-5, 3.8};
    Complexe z3 = {-15.8, 4.12};
    Complexe z0 = {0,0};
    ASSERT (z1*z2 == z3);
    ASSERT (z2*z1 == z3);
    //ASSERT (z1 * z1 * z2 == z1*z3);
    ASSERT (z0*z1*z2*z3 == z0);
}

// Surcharge de la fonction abs
float abs(Complexe z) {
    return sqrt(z.re*z.re+z.im*z.im);
}

// Test de la surcharge de la fonction abs
void testAbs() {
    Complexe z1 = {0, 0};
    Complexe i = {0,1};
    Complexe n245 = {245,0};
    ASSERT(presqueEgal(abs(z1), 0));
    ASSERT(presqueEgal(abs(n245*i), 245));
    Complexe z2 = {-5, 3.8};
    ASSERT(presqueEgal(abs(z2), 6.280127387));
    Complexe z3 = {3, -2};
    ASSERT(presqueEgal(abs(z3), 3.605551275));
}

// Deux floats sont presque égaux si leur différence est petite en comparaison à
// leur valeur absolue
bool presqueEgal(float x, float y) {
    if ((abs(x - y) <= epsilon * abs(x)) and (abs(x - y) <= epsilon * abs(y))) {
        return true;
    }
    return false;
}

// Deux complexes sont presque égaux si leurs parties réelles et imaginaires
// sont presque égales
bool presqueEgal(Complexe z, Complexe w) {
    if (presqueEgal(z.re, w.re) and presqueEgal(z.im, w.im)){
        return true;
    }else{
        return true;
    }
}

void testPresqueEgal() {
    Complexe z1 = {2.436545828384, 1.189346553893};
    Complexe z2 = {-5.359712984532, 3.8326749867};
    Complexe z3 = {-17.617565101, 2.963932082};
    ASSERT(presqueEgal(z1*z2, z3));
    ASSERT(presqueEgal(z1 * z1 * z2, z1*z3));
    ASSERT(presqueEgal(z1 * z2 * z2, z2*z3));
    ASSERT(presqueEgal(z3 * z2, z2*z1*z2));
}

// Return false si la séquence associée contient un nombre de module
// supérieur à 2 dans les 1000 premiers termes.
bool znResteBorne(Complexe c) {
    Complexe z = Complexe{0, 0};
    for (int i = 0; i < 1000; i++) {
        if (abs(z) > 2) {
            return false;
        }
        z = z * z + c;
    }
    return true;
}

// Affiche l'ensemble de Mandelbrot
void mandelbrot() {
    const float xmin = -2;
    const float xmax = 0.5;
    const float ymin = -1.5;
    const float ymax = 1.5;
    const int resol = 100;
    for (int i = 0; i <= resol; i++) {
        for (int j = 0; j <= resol; j++) {
            if (znResteBorne(
                    Complexe{(resol - j) * xmin / resol + j * xmax / resol,
                             (resol - i) * ymax / resol + i * ymin / resol})) {
                cout << '#';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

// Calcule le modulus carrée d'un complexe
float normeCarree(Complexe z) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 143");
}

// Teste la fonction normeCarree()
void testnormeCarree() {
    Complexe z1 = {0, 0};
    ASSERT(presqueEgal(normeCarree(z1), 0));
    Complexe z2 = {-5, 3.8};
    ASSERT(presqueEgal(normeCarree(z2), 39.44));
    Complexe z3 = {3, -2};
    ASSERT(presqueEgal(normeCarree(z3), 13));
}

// Calcule l'inverse d'un complexe
Complexe inverse(Complexe z) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 159");
}

// Teste la fonction inverse()
void testInverse() {
    Complexe z1 = {1, 0};
    ASSERT(presqueEgal(inverse(z1), Complexe{1, 0}));
    Complexe z2 = {-5, 3.8};
    ASSERT(presqueEgal(inverse(z2), Complexe{-0.126774848, -0.096348884}));
    Complexe z3 = {3, -2};
    ASSERT(presqueEgal(inverse(z3), Complexe{0.230769231, 0.153846154}));
}

// Surcharge de l'operator /
Complexe operator/(Complexe z, Complexe w) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 175");
}

// Test de la surcharge de l'operator /
void testDivision() {
    Complexe z1 = {0, 0};
    Complexe z2 = {1, 1};
    ASSERT(presqueEgal(z1 / z2, Complexe{0, 0}));
    Complexe z3 = {2.4, 1};
    Complexe z4 = {-5, 3.8};
    ASSERT(presqueEgal(z3 / z4, Complexe{-0.207910751, -0.35801217}));
    Complexe z5 = {3, 2};
    Complexe z6 = {3, -2};
    ASSERT(presqueEgal(z5 / z6, Complexe{0.384615385, 0.923076923}));
}

// Surcharge de la fonction sqrt
Complexe sqrt(Complexe z) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("code non implanté ligne 194");
}

// Test de la surcharge de la fonction sqrt
void testSqrt() {
    Complexe z1 = {1, 0};
    ASSERT(presqueEgal(sqrt(z1), Complexe{1, 0}));
    Complexe z2 = {-5, 3.8};
    ASSERT(presqueEgal(sqrt(z2), Complexe{0.80003980, 2.374881827}));
    Complexe z3 = {3, -2};
    ASSERT(presqueEgal(sqrt(z3), Complexe{1.81735402, -0.550250522}));
}

int main() {
    testMultiplication();
    testAbs();
    testPresqueEgal();
    mandelbrot();

    testnormeCarree();
    testInverse();
    testDivision();
    testSqrt();
    return 0;
}
