#include <iostream>
#include <cstdlib>
using namespace std;
int recherche(int t[], int val, int debut, int fin){ //fin exclue
    int milieu = (debut+fin)/2;
    if(fin == debut)
        return -1;
    if(val == t[milieu])
        return milieu;
    if(milieu > val){
        return recherche(t, val, debut, milieu);
    }else{
        return recherche(t, val, milieu+1, fin);
    }
}
void echange(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void triselection(int t[], int n){
    if(n <= 1) return;
    int max = t[0];
    int indMax = 0;
    for(int i = 1; i < n; i++){
        if(max < t[i]){
            max = t[i];
            indMax = i;
        }
    }
    echange(t[n-1], t[indMax]);
    triselection(t, n-1);
}

int pivot(int T[], int deb, int fin){
    int tabM[3];
    tabM[0] = T[(deb+fin)/2];
    tabM[1] = T[fin-1];
    tabM[2] = T[0];
    triselection(tabM, 3);
    if(T[(deb+fin)/2] == tabM[1]) return (deb+fin)/2;
    if(T[deb] == tabM[1]) return deb;
    return fin;
}

int partitionner(int T[], int deb, int fin){
    int p = pivot(T, deb, fin);
    int valP = T[p];
    echange(T[p],T[fin-1]);
    int limit = deb;
    for(int i = deb; i<fin-1; i++){
        if(T[i] <= valP){
            echange(T[limit], T[i]);
            limit++;
        }
    }
    echange(T[limit],T[fin-1]);
    return limit;
}

int nieme(int T[], int n, int deb, int fin){
    cout<<"debut : "<<deb<<"|"<<"fin : "<<fin<<endl;
    int pivot = partitionner(T, deb, fin);
    cout<<"pivot : "<< pivot<<endl;
    if(pivot == n)
        return pivot;
    if(pivot < n)
        return nieme(T, n, pivot+1, fin);
    else
        return nieme(T, n, deb, pivot);
}

void affiche(ostream& out, int t[], int deb, int fin){
    out<<"[";
    for(int i = deb; i<fin; i++){
        out<<t[i]<<", ";
    }
    out<<"]"<<endl;;
}

int main(){
    cout<<"tests:"<<endl;
    int t[49];
    int end = 0;
    for(int i=0;i<100;i+=2){
        t[end] = i;
        end++;
    }
    cout<<"end : "<<end<<endl;
    cout<<recherche(t, 98, 0, 50)<<endl;
    affiche(cout, t, 0, end);
    cout<<t[nieme(t, end-1, 0, end)]<< endl;
    affiche(cout, t, 0, end);
    cout<<t[49]<<endl;
}

