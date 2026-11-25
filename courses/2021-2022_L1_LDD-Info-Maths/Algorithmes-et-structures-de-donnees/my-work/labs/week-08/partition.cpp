#include <iostream>
using namespace std;

int partition(int n, int t){
    int plus;
    if(t == 1){
        return 1;
    }
    if(n>=t){
        plus = partition(n-t,t);
    }else{
        plus = 0;
    }
    return partition(n,t-1)+plus;
}
int main() {
    cout<<partition(5165151,1);
}