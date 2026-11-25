#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
using namespace std;

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"



struct ADN {
  vector<char> sequence;
  ADN(vector<char> a);
  ADN(int n);
  int nb_nucleotides();
  int occurence_nucleotide(char c);
  bool estADN();
  bool estADNVertebre();
};
ADN::ADN(int n) {
  array<char, 4> lettres = { 'A', 'T', 'G', 'C'};
  sequence = {};
  for(int i = 0; i < n; i++){
    sequence.push_back(lettres[rand() % 4]);
  }
}
ADN::ADN(vector<char> a){
  sequence = a;
}
bool ADN::estADNVertebre(){
  float prop = (float(occurence_nucleotide('G')+occurence_nucleotide('C'))/float(nb_nucleotides()));
  if(prop >= 0.45 or prop<=0.4) return false;
  return estADN();
}
bool ADN::estADN(){
  for(auto c : sequence){
    if(not(c=='A' or c=='T' or c=='G' or c=='C')){
      return false;
    }
  }
  return true;
}
int ADN::nb_nucleotides(){
  return sequence.size();
}
int ADN::occurence_nucleotide(char c){
  int count = 0;
  for(auto a : sequence){
    if(a == c){
      count++;
    }
  }
  return count;
}
TEST_CASE("occurence"){
  ADN t = ADN({'A', 'A','A','A','A','A','A','A','A','A','A'});
  CHECK(t.occurence_nucleotide('A') == t.nb_nucleotides());
  CHECK(t.occurence_nucleotide('B') == 0);
  CHECK((ADN{{ {'A', 'B', 'A'} }}).occurence_nucleotide('B') == 1);
}

TEST_CASE("estADN"){
  ADN t = ADN({'Z', 'O','Z','Z','A','P','T','D','R','A','A'});
  ADN t2 = ADN({'A','T','A','A'});
  CHECK_FALSE(t.estADN());
  CHECK(t2.estADN());
}

TEST_CASE("estADNVertebre"){
  ADN t = ADN({'Z', 'O','Z','Z','A','P','T','D','R','A','A'});
  ADN t2 = ADN({'A','T','A','A'});
  ADN vert = ADN({'A','A','A','A','A','A','A','G','C','G','C','C'});
  CHECK_FALSE(t.estADNVertebre());
  CHECK_FALSE(t2.estADNVertebre());
  CHECK(vert.estADNVertebre());
}
int main(int argc, const char **argv) {
  // Initialise la graine aléatoire
  srand(time(NULL));

  doctest::Context context(argc, argv);
  int test_result = context.run();
  if (context.shouldExit()) return test_result;


  return 0;
}
