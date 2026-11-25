#include <iostream>
#include <vector>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
				       << " line " << __LINE__ << ": " #test << endl

struct Duree {
  int heures;
  int minutes;
  float secondes;
};

/** Converti une durée en Heures, Minutes, Secondes en secondes
 *  @param À compléter
 *  @return À compléter
 **/
float convertHMS2S(Duree hms) {
  return 60*60*hms.heures+60*hms.minutes+hms.secondes;
}

/** égalité des durées
 *  @param d1, d2 deux Duree
 *  @return true/false selon que d1 est égal à d2 ou non
 **/
bool egalHMS(Duree d1, Duree d2) {
  return d1.heures == d2.heures and d1.minutes == d2.minutes and d1.secondes == d2.secondes;
}

void testConvertHMS2S() {
  ASSERT( convertHMS2S({10,10,2}) == 36602 );
  ASSERT( convertHMS2S({0,0,2574354}) == 2574354 );
  ASSERT( convertHMS2S({24,0,0}) == 3600*24 );
  ASSERT( convertHMS2S({0,0,0}) == 0 );
}

/** À compléter
 *  @param À compléter
 *  @return À compléter
 **/
Duree convertS2HMS(float d) {
  int heures = int(d/3600);
  float d2 = d-3600*heures;
  int minutes = int(d2/60);
  float d3 = d2-60*minutes;
  float secondes = d3;
  return {heures, minutes, secondes};
}

void testConvertS2HMS() {
  Duree d;
  d = convertS2HMS(36602);
  cout<< d.secondes;
  ASSERT( d.heures == 10 and d.minutes == 10 and d.secondes == 2 );
  d = convertS2HMS(75);
  ASSERT( d.heures == 0 and d.minutes == 1 and d.secondes == 15 );
  ASSERT(egalHMS(convertS2HMS(convertHMS2S({0,0,12})), {0,0,12}));
  ASSERT(egalHMS(convertS2HMS(convertHMS2S({24,12,2})), {24,12,2}));
  ASSERT(egalHMS(convertS2HMS(convertHMS2S({14,12,2})), {14,12,2}));
}


void testHMS(Duree hms) {
  ASSERT(0<=hms.heures and 24>hms.heures and 0<=hms.minutes and 0<=hms.secondes and 60>hms.secondes and 60>hms.minutes);
}

int main() {
  testConvertHMS2S();
  testConvertS2HMS();

  for(float i = 0; i<=80000;i+=0.25){
    Duree d = convertS2HMS(i);
    testHMS(d);
    ASSERT(convertHMS2S(d) == i);
  }
}
