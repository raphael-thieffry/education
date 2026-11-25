#include <iostream>
using namespace std;
int pgcd(int a, int b){
    if(b == 0) return a;
    return pgcd(b, a%b);
}

int main(){
    pgcd(12,13);
}