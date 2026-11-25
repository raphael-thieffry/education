#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Ensemble.hpp"


int cardinal(Ensemble e) {
    int c = 0;
    while(not e.estVide()){
        Objet o = e.element();
        e.retire(o);
        c++;
    }
    return c;
}
TEST_CASE("cardinalité") {
  CHECK(cardinal(Ensemble{}) == 0);
  CHECK(cardinal(Ensemble{ {{1,2,3,4,5,6,7,8,9,0}} }) == 10);
  CHECK(cardinal(Ensemble{ {{1,1,1,11,1,1,11,1}} }) == 2);
}


bool inclus(Ensemble e, Ensemble f) {
    int card = cardinal(e);
    if(cardinal(e)>cardinal(f)){
        return false;
    }
    for(int i = 0; i < card;i++){
        Objet o = e.element();
        e.retire(o);
        if(not(f.contient(o))){
            return false;
        }
    }
    return true;
}
TEST_CASE("Inclusion") {
  CHECK(inclus(Ensemble{},Ensemble{}));
  Ensemble naturel = Ensemble{ {{1,2,3,4,5,6,7,8,9,0}} };
  CHECK(inclus(Ensemble{ {{1,4,8}} }, naturel));
  CHECK_FALSE(inclus(Ensemble{ {{11}} }, naturel));
  CHECK(inclus(Ensemble{}, naturel));
}

bool operator==(Ensemble e, Ensemble f) {
    return cardinal(e) == cardinal(f) and inclus(e,f);
}
TEST_CASE("Egalité") {
  CHECK(Ensemble{} == Ensemble{});
  CHECK(Ensemble({1,2,3}) == Ensemble({3,2,1}));
  CHECK_FALSE(Ensemble({1,2,3}) == Ensemble({1,2,4}));
  CHECK_FALSE(Ensemble({1,2,3,4}) == Ensemble({1,2,3}));
}

Ensemble unionEns(Ensemble e, Ensemble f) {
    Ensemble res;
    while(!e.estVide()){
        Objet o = e.element();
        res.ajoute(o);
        e.retire(o);
    }
    while(!f.estVide()){
        Objet o = f.element();
        res.ajoute(o);
        f.retire(o);
    }
    return res;
}
TEST_CASE("Union") {
    CHECK(unionEns(Ensemble({1,2,3}),Ensemble({1,2,3})) == Ensemble({1,2,3}));
    CHECK(unionEns(Ensemble({1,2,3}),Ensemble({1,2,3,4,5})) == Ensemble({1,2,3,4,5}));
    CHECK(unionEns(Ensemble({1,2,3}),Ensemble({1,2,4})) == Ensemble({1,2,3,4}));
    CHECK(unionEns(Ensemble({1,2,3,4}),Ensemble({1,2,3})) == Ensemble({1,2,3,4}));
}


Ensemble interEns(Ensemble e, Ensemble f) {
    Ensemble res;
    while(not(e.estVide() or f.estVide())){
        Objet oE = e.element();
        e.retire(oE);
        if(f.contient(oE)){
            res.ajoute(oE);
        }
    }
    return res;
}
TEST_CASE("Intersection") {
    CHECK(interEns(Ensemble({1,2,3}),Ensemble({1,2,3})) == Ensemble({1,2,3}));
    CHECK(interEns(Ensemble({1,2,3}),Ensemble({1,2,3,4,5})) == Ensemble({1,2,3}));
    CHECK(interEns(Ensemble({1,2,3}),Ensemble({1,2,4})) == Ensemble({1,2}));
    CHECK(interEns(Ensemble({1,2,3,4}),Ensemble({1,2,3})) == Ensemble({1,2,3}));
}


ostream &operator<<(ostream &out, Ensemble e) {
    out<<"{";
    int card = cardinal(e);
    for(int i = 0; i < card;i++){
        Objet o = e.element();
        e.retire(o);
        out<<o<<", ";
    }
    out<<"}";
    return out;
}

Objet randomObj(){
  Objet o;
  o = rand() % MaxTaille;
  return o;
}

Ensemble randomEns (int n) {
    Ensemble res;
    for(int i = 0; i < n;i++){
        Objet o;
        do{
            o = randomObj();
        }while(res.contient(o));
        res.ajoute(o);
    }
    return res;
}

bool inclsExcls(){
    Ensemble a,b,c;
    a = randomEns((rand()%5) + 8);
    b = randomEns((rand()%5) + 8);
    c = randomEns((rand()%5) + 8);
    return cardinal(unionEns(unionEns(a,b),c)) == cardinal(a) + cardinal(b) + cardinal(c) - cardinal(interEns(a,b)) - cardinal(interEns(a,c)) - cardinal(interEns(b,c)) + cardinal(interEns(interEns(a,b), c));
}
TEST_CASE("Inclusion exclusion") {
    for(int i = 0; i <2000; i++){
        CHECK(inclsExcls());
    }
}


int main(int argc, const char **argv) {
  srand(time(NULL));
  cout<<Ensemble{ {{1,2,3,4,5,6,7,8,9,0}} }<<endl;;
  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;
  if (inclsExcls()) cout << "OK" << endl;
  else cout << "Faux" << endl;
  return 0;
}


