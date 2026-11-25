#include<iostream>
using namespace std;
double factorielle(int n){
    return n==0 ? 1 : n*factorielle(n-1);
}
double puissance(double n,int e){
    return e==0 ? 1 : n*puissance(n, e-1);
}
double exp(){
    int n;
    cout<<"n>0 : ";
    cin>>n;
    double x;
    cout<<"x : ";
    cin>>x;
    double res=0;
    for(int i = 0;i<n;i++){
        res+=puissance(x,i)/factorielle(i);
    }
    return res;
}
double expEfficace(double x, int n){
    double res = 0;
    double fact=1;
    double puis = 1;
    for(int i = 0;i<n;i++){
        res+=puis/fact;
        fact*=i+1;
        puis*=x;
    }
    return res;
}
int main(){
    int n;
    double x;
    cout<<"n :";
    cin>>n;
    cout<<"x :";
    cin>>x;
    cout<<"resultat : "<<expEfficace(x, n)<<endl;
    cout<<"resultat ancien : "<<exp()<<endl; 
 
}