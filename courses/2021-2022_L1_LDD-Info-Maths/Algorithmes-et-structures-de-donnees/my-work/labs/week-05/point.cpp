#include<iostream>
#include<string>
#include<cmath>
using namespace std;

struct Point {
    float x, y;
};
void litPoint (Point &p) {
cout << "abscisse ? "; cin >> p.x ;
cout << "ordonnee ? "; cin >> p.y ;
}
float abscisse(Point p) {
return p.x ;
}
float ordonnee(Point p) {
return p.y ;
}
void affichePoint (Point p) {
cout << "abscisse "; cout << p.x ;
cout << "ordonnee "; cout << p.y ;
}
bool conf(Point p1, Point p2, Point &p3){
    bool v = not(p1.x == p2.x && p1.y == p2.y);
    if(!v){
        p3.x = (p1.x+p2.x)/2;
        p3.y = (p1.y+p2.y)/2;
    }else{
        p3 = p2;
    }
    return v;
}
float distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x)+(p1.y - p2.y) * (p1.y - p2.y));
}
const float e = 1e-6 ;
bool EgalApproche(float x, float y) {
    return (fabs(x-y) < e*fabs(x)) && (fabs(x-y) < e*fabs(y));
}
int main() {
    Point q = Point{69,69};
    Point x = Point{-69,-96};
    Point m;
    conf(q,x,m);
    cout<<EgalApproche((distance(q,x)),(distance(m,q)+distance(m,x)))<<endl;
    return 0;
}
