#include<iostream>
#include<vector>
using namespace std;
double lectureVB(double min, double max){
    bool rewind = false;
    double res;
    if(min>max){double temp=min;min=max;max=temp;}
    do{
        if(rewind){cout<<"Erreur (en dehors des bornes)"<<endl;};
        cout<<"Un chiffre entre "<<min<<" et "<<max<<" : ";
        cin>>res;
        rewind = true;
    }while(res>max or res<min);
    return res;
}
vector<double> emprunt(double s0, double r, double im){
    double reste = s0;
    int moisCounter = 0;
    double i=0;
    double itot = 0;
    while(reste > 0){
        moisCounter++;
        i =im*reste/100;
        itot+=i;
        reste = reste + i - r;
    }
    vector<double> ret;
    ret = vector<double>(2);
    ret[0]=itot;
    ret[1] = moisCounter;
    return ret;
}
int main(){
    double pret;
    cout<<"Ton prêt ? (>0): ";
    cin>>pret;
    double r;
    cout<<"Tu rembourse cb par mois ? (>0): ";
    cin>>r;
    double im = lectureVB(0.1,1.5);
    cout<<"nombre de mois de payement : "<<emprunt(pret,r,im)[1]<<endl;
    cout<<"total interets payés : "<<emprunt(pret,r,im)[0]<<endl;
}