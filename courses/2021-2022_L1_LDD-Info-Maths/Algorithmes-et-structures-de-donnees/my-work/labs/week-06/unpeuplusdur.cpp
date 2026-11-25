#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

int *maximum(int *a, int *b){
    if(*a > *b){
        return a;
    }else{
        return b;
    }
}
int main() {
    int a,b;
    a=17;b=25;
    int* pa = &a;
    int* pb = &b;
    cout<< a << " " << b <<endl;
    *maximum(pa,pb) = *maximum(pa,pb)*2;
    cout<< a << " "<< b <<endl;
}

