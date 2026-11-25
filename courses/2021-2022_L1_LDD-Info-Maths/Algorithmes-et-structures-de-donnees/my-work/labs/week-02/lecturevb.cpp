#include<iostream>
using namespace std;
int lectureVB(int min, int max){
    bool rewind = false;
    int res;
    if(min>max){int temp=min;min=max;max=temp;}
    do{
        if(rewind){cout<<"Erreur (en dehors des bornes)"<<endl;};
        cout<<"Un chiffre entre "<<min<<" et "<<max<<" : ";
        cin>>res;
        rewind = true;
    }while(res>max or res<min);
    return res;
}
int main(){
    cout<<lectureVB(0,23)<<endl;
}