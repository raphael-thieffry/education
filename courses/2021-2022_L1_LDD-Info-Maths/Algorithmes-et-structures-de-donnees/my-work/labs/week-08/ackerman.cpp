#include <iostream>
using namespace std;

int ackerman(int m, int n, int unsigned &count){
    count++;
    if (m == 0) return n+1;
    if (m>0 and n == 0) return ackerman(m-1,1, count);
    return ackerman(m-1,ackerman(m, n-1, count), count);
}
int main(){
    int unsigned count = 0;
    cout<<ackerman(2,2, count)<<" "<<count<<endl;
    count = 0;
    cout<<ackerman(2,3, count)<<" "<<count<<endl;
    count = 0;
    cout<<ackerman(3,3, count)<<" "<<count<<endl;
    count = 0;
    cout<<ackerman(4,1, count)<<" "<<count<<endl;

}