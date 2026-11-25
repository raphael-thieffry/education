#include <iostream>
using namespace std;

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    int a = 5;
    int b = 8;
    cout << "Le min de " << a << " et " << b << " est " << min(a,b) << endl;
}
