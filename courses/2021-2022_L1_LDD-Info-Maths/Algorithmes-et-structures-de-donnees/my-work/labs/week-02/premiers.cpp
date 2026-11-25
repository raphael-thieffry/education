#include<iostream>
using namespace std;
bool estDiviseur(int a, int b){
    return b%a==0;
}
bool estPremier(int n){
    for(int i = 2; i<n;i++){
        if(estDiviseur(i,n)){
            return false;
        }
    }
    return true;
}
void premiersBornes(int n){
    for(int i = 1; i<n;i++){
        if(estPremier(i)){
            cout<<i<<";";
        }
    }
    cout<<endl;
}
int main(){
    int n;
    cout<<"Chiffre : ";
    cin>>n;
    premiersBornes(n);
}