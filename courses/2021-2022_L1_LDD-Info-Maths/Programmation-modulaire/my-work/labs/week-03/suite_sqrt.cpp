#include <iostream>
#include <iomanip>

using namespace std;

int main(){
  int n;
  float a=2., un, un1; // u_n et u_{n+1}

  n = 0;  un = a;
  while (n<10) {
    un1 = (un + a/un)/2.;       // calcul de u_{n+1}
    n = n+1; un = un1;          // passage de n à n+1
    cout << "n=" << n << ", un=" << un << ", un^2=" << un*un << endl;
  }
  return 0;
}
