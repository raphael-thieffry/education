#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
void minimum(int a, int b, int *r){
    if (a < b){
        *r = a;
    }else{
        *r = b;
    }
}

int main() {
    int val;
    int *p = &val;
    int a,b;
    a=17;b=25;
    minimum(a,b,p);
    cout<< (val==17) <<endl;
}

