#include <iostream>
using namespace std;

void croissant(int n){
    if(n <= 0){
        cout<<0<<" ";
    }else{
        croissant(n-1);
        cout<<n<<" ";
    }
}
void decroissant(int n){
    if(n <= 0){
        cout<<0<<" ";
    }else{
        cout<<n<<" ";
        decroissant(n-1);
    }
}
int main() {
    croissant(69);
    cout<<endl;
    decroissant(69);
}