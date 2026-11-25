#include <iostream>
#include <array>
#include <vector>
using namespace std;



void hanoi(int n,int depart, int arrive, /*array<vector<int>, 3> &state,*/ int autre){
    /*if(tour == 1){
        state = {{ {}, {}, {} }};
        for(int i=n;i>1;i--){
            state[0].push_back(i);
        }
    }*/
    //int num;
    if(n==0)return;
    //num = statechanger(depart, arrive, state);
    //cout<<"disque "<<n<<" de "<< depart << " vers "<< arrive<<endl;
    hanoi(n-1, depart, autre, arrive);
    //num = statechanger(depart, arrive, state);
    cout<<"disque "<<n<<" de "<< depart << " vers "<< arrive<<endl;
    hanoi(n-1, autre, arrive, depart);
}


int main(){
    array<vector<int>, 3> state;
    hanoi(3, 1, 3, 2);
    /*for(auto v : state){
        for(auto i:v) {
            cout<<i<<", ";
        }
        cout<<endl;
    }*/
}