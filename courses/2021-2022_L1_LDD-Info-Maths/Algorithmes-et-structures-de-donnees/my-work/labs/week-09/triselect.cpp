#include <iostream>
using namespace std;

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
    echange(T[p],T[fin]);
    int limit = deb;
    for(int i = deb; i<fin; i++){
        if(T[i] <= valP){
            echange(T[limit], T[i]);
            limit++;
        }
    }
    echange(T[limit],T[fin]);
    return limit;
}
void trirapide(int T[], int deb, int fin){
    if(deb < fin){
        int p = partitionner(T, deb, fin);
        trirapide(T,deb, p-1);
        trirapide(T,p+1, fin);
    }
}
void triTableauToutesTaille(int T[], int n){
    if(n>=100){
        trirapide(T, 0, n-1);
    }else{
        triselection(T, n);
    }
}
int main(){
    int size = 900;
    int range = 900;
    int t[size];
    for(int i = 0; i < size; i++){
        t[i] = rand() % range;
    }
    for(int i = 0; i < size; i++){
        cout<<t[i]<<endl;
    }
    cout<<"---------------------------------"<<endl;
    triTableauToutesTaille(t, size);
    for(int i = 0; i < size; i++){
        cout<<t[i]<<endl;
    }
}