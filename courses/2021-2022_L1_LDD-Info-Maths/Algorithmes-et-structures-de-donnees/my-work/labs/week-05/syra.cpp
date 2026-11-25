#include<iostream>
#include<string>

using namespace std;

void syracuse(int &v){
    if(v%2){
        v*=3;
        v++;
    }else{
        v=v/2;
    }
}
int longueurTransient (int un){
    int i=0;
    while(un != 1){
        syracuse(un);
        i++;
    }
    return i;
}


int main() {
    for(int i = 1; i<=1000; i++){
        cout<<i<<":"<<longueurTransient(i)<<endl;
    }

    return 0;
}
