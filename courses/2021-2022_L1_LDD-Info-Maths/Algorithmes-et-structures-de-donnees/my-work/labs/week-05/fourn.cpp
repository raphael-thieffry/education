#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Fourniture{
    int code, achete, vendu;
    string nom;
    float prix;
};
void saisie(Fourniture &f){
    int c,a,v;
    string n;
    float p;
    cout<<"code :";
    cin>>c;
    cout<<"nb acheté ? :";
    cin>>a;
    cout<<"nb vendu ? :";
    cin>>v;
    cout<<"nom produit :";
    cin>>n;
    cout<<"prix :";
    cin>>p;
    f = Fourniture{c,a,v,n,p};
}
void affiche(Fourniture const &f){
    cout<<"code :"<<       f.code<< endl;
    cout<<"nb acheté :"<<f.achete<< endl;
    cout<<"nb vendu :"<<  f.vendu<< endl;
    cout<<"nom produit :"<< f.nom<< endl;
    cout<<"prix :"<<       f.prix<< endl;
}
void vente(Fourniture &f, int n){
    f.vendu+=n;
}
void stock(Fourniture f, int &stock){
    stock = f.achete-f.vendu;
}
typedef vector<Fourniture> Catalogue;
void addFour(Catalogue &c, Fourniture f){
    c.push_back(f);
}
void bilan(Catalogue c){
    for(auto v : c){
        cout<<"nom produit :"<<v.nom<< endl;
        cout<<"prix :"<<       v.prix<< endl;
        int s;
        stock(v,s);
        cout<<"stock :"<<s<<endl;
    }
}
void retire(Catalogue &c, int code){
    Catalogue d;
    for(auto v : c){
        if(code != v.code){
            d.push_back(v);
        }
    }
    c = d;
}
int main() {
    return 0;
}
