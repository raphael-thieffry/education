#include <iostream>
#include <cmath>

using namespace std;

struct Complexe {
    float re, im;
};


void initComplexe(Complexe *c, float reel, float imaginaire){
    c->re = reel;
    c->im = imaginaire;
}

bool egaleComplexe(Complexe a, Complexe b){
    return (a.re == b.re) && (a.im == b.im);
}

void ajouterComplexe(Complexe *a, Complexe b){
    a->re = a->re + b.re;
    a->im = a->im + b.im;
}

float moduleComplexe(Complexe c){
    return sqrt(pow(c.re, 2) + pow(c.im, 2));
}

void multiplierComplexe(Complexe *a, Complexe b){
    float temp = a->re;
    a->re = a->re * b.re - (a->im*b.im);
    a->im = temp*b.im+a->im*b.re;
}

bool znResteBorne(Complexe c){
    Complexe zn;
    initComplexe(&zn, 0, 0);
    for( int i = 0; i<1000; i++){
        multiplierComplexe(&zn, zn);
        ajouterComplexe(&zn,c);
        if(moduleComplexe(zn)>2){
            return false;
        }
    }
    return true;
}

void mandelbrot(){
    const float xmin = -2;
    const float xmax = 0.5;
    const float ymin = -1.1;
    const float ymax = 1.1;
    const int xresol = 79;
    const int yresol = 39;
    for(int i=0; i<=yresol; i++) {
        for(int j=0; j<=xresol; j++) {
            Complexe z;
            initComplexe(&z, (xresol-j)*xmin/xresol+j*xmax/xresol,
                             (yresol-i)*ymax/yresol+i*ymin/yresol);
            if(znResteBorne(z)) {
                    cout << '#';
            }
            else {
                    cout << ' ';
            }
        }
        cout << endl;
    }
}

int main(){
    mandelbrot();
    return 0;
}
