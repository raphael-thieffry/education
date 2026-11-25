#include<iostream>
#include<string>

using namespace std;

void permuter(int &c, int &d) {
	int temp;
	temp = c; c = d; d = temp; 
}
void ordonner(int &a, int &b){
  if(a>b){
    permuter(a,b);
  }
}

int main() {
  int a,b,c,d,e;
  cin>>d>>e;
  ordonner(d,e);
  cout<<d<<" "<<e<<endl;
  cin>>a>>b>>c;
  ordonner(a,b);
  ordonner(b,c);
  ordonner(a,b);
  cout<<a<<" "<<b<<" "<<c<<endl;


    return 0;
}
