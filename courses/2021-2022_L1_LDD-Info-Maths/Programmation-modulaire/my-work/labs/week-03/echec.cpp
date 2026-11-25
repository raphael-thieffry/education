#include <stdexcept>
// Correction pour l'exercice d'echec
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <exception>
#include <string>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
                                       << " line " << __LINE__ << ": " #test << endl



const array<array<string, 6>, 3> pieces = { {
    {u8"♙", u8"♖", u8"♘", u8"♗", u8"♕", u8"♔"},
    {u8"♟", u8"♜", u8"♞", u8"♝", u8"♛", u8"♚"},
    {" "} } };
void checkUnicode() {
  cout << u8"♙♖♘♗♔♕♟♜♞♝♚♛" << endl;
}


enum class CouleurPiece { noir, blanc, vide };
const array<string, 3> stringCouleur { "n", "b", " " };

enum class SortePiece { pion, tour, cavalier, fou, dame, roi, vide };
const array<string, 7> stringSorte { "p", "t", "c", "f", "d", "r", " " };

struct Piece {
  CouleurPiece couleur;
  SortePiece sorte;
};

// Les pièces de la première ligne de l'échiquier dans l'ordre
// de leur position initiale.
static const array<SortePiece, 8> lignePieces = {
  SortePiece::tour, SortePiece::cavalier, SortePiece::fou,
  SortePiece::roi, SortePiece::dame, SortePiece::fou,
  SortePiece::cavalier, SortePiece::tour};

struct Coord {
  int lig;  // ligne
  int col;  // colonne    // Remplacer la ligne suivante par le code adéquat
};
using Echiquier = array<array<Piece, 8>,8>;
bool operator==(Coord a, Coord b){
  return (a.col == b.col and a.lig == b.lig);
}
bool operator!=(Coord a, Coord b){
  return not(a==b);
}
void testEgalCoord() {
  Coord a = {69,42};
  Coord b = {42,69};
  Coord c = {3,4};
  ASSERT((Coord {1, 2} == Coord {1, 2}));
  ASSERT(a!=b);
  ASSERT(a==a);
  ASSERT(c!=b);
}
bool operator==(Piece a, Piece b) {
    return (a.couleur==b.couleur and a.sorte==b.sorte);
}
bool operator!=(Piece a, Piece b) {
    return not(a==b);
}
std::ostream& operator<< (std::ostream &out, Coord a) {
  out << "(" << a.col << "," << a.lig << ")";
  return out;
}



void testEgalPiece() {
  ASSERT((Piece {CouleurPiece::noir, SortePiece::pion} ==
          Piece {CouleurPiece::noir, SortePiece::pion}));
  ASSERT((Piece {CouleurPiece::blanc, SortePiece::pion} !=
          Piece {CouleurPiece::noir, SortePiece::pion}));
  ASSERT((Piece {CouleurPiece::blanc, SortePiece::vide} ==
          Piece {CouleurPiece::blanc, SortePiece::vide}));

}

std::ostream& operator<<(std::ostream &out, SortePiece t) {
  out << stringSorte[int(t)];
  return out;
}

std::ostream& operator<<(std::ostream &out, CouleurPiece c) {
  out << stringCouleur[int(c)];
  return out;
}

std::ostream& operator<<(std::ostream &out, Piece a) {
    int row = 2;
    int col = 0;
    switch(a.couleur){
        case CouleurPiece::blanc : row = 0; break;
        case CouleurPiece::noir : row = 1; break;
        case CouleurPiece::vide : row = 2; break;
    }
    if(row != 2){
        col = int(a.sorte);
    }
    out<< pieces[row][col];
    return out;
}

Echiquier createEchiquier() {
  Echiquier res;
  array<Piece, 8> lvide;
  array<Piece, 8> lbpion;
  array<Piece, 8> lnpion;
  for(int i = 0; i<8;i++){
    lvide[i] = {CouleurPiece::vide, SortePiece::vide};
    lnpion[i] = {CouleurPiece::noir, SortePiece::pion};
    lbpion[i] = {CouleurPiece::blanc, SortePiece::pion};
  }
  CouleurPiece c = CouleurPiece::noir;
  for(int i = 0; i<8;i++){
    if(i == 0 or i == 7){
      int k = 0;
      for(auto sorte : lignePieces){
        res[i][k] = {c, sorte};
        k++;
      }
    }else if(i == 1 or i == 6){
      if(bool(int(c))){ //c==1 <=> c == True <=> c == blanc
        res[i] = lbpion;
      }else{
        res[i] = lnpion;
        c = CouleurPiece(1);
      }
    }else{
      res[i] = lvide;
    }
  }
  return res;
}


Echiquier createEchiquier(string s) {
  Echiquier e;
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0 ; j < 8 ; j++) {
      e[i][j] = { CouleurPiece::vide, SortePiece::vide };
    }
  }
  int pos = 0;
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0 ; j < 8 ; j++) {
      char c = s[pos]; pos++;
      Piece p;
      if (c == ' ') p = { CouleurPiece::vide, SortePiece::vide };
      else {
        if (isupper(c))
          p.couleur = CouleurPiece::blanc;
        else
          p.couleur = CouleurPiece::noir;
        switch (tolower(c)) {
          case 'r': p.sorte = SortePiece::roi; break;
          case 'd': p.sorte = SortePiece::dame; break;
          case 'f': p.sorte = SortePiece::fou; break;
          case 'c': p.sorte = SortePiece::cavalier; break;
          case 't': p.sorte = SortePiece::tour; break;
          case 'p': p.sorte = SortePiece::pion; break;
          default:
            throw invalid_argument("Pièce inconnue");
        }
      }
      e[i][j] = p;
    }
  }
  return e;
}

Echiquier Einit = createEchiquier("tcfrdfct"
                                  "pppppppp"
                                  "        "
                                  "        "
                                  "        "
                                  "        "
                                  "PPPPPPPP"
                                  "TCFRDFCT");

Echiquier ETaverner1889 = createEchiquier("   fttf "
                                          "  C    F"
                                          "        "
                                          "  p    D"
                                          "  p  r  "
                                          "     P  "
                                          "    P RT"
                                          "  C  TF ");


// Pas de vérification que le déplacement est valide
Echiquier deplacePiece(Echiquier e, Coord ci, Coord cf) {
    if(ci == cf){return e;};
    Piece pieceIni = e[ci.lig][ci.col];
    if(pieceIni.couleur == CouleurPiece::vide){
      throw invalid_argument("Pas de piece à cet emplacement");
    }
    e[cf.lig][cf.col] = pieceIni;
    e[ci.lig][ci.col] = {CouleurPiece::vide, SortePiece::vide};
    return e;
}

// std::ostream& affichageSimple(std::ostream &out, const Echiquier& e){
std::ostream& operator<<(std::ostream &out, const Echiquier& e){
  for (int i = 0 ; i < 8 ; i++) {
    out << "|";
    for (int j = 0 ; j < 8 ; j++ ) {
      out << e[i][j] << "|";
    }
    out << endl;
  }
  out << endl;
  return out;
}

int main() {
  testEgalCoord();
  testEgalPiece();
  checkUnicode();
  Echiquier e = createEchiquier();
  cout<<e;
  e = deplacePiece(e, {0,1}, {2,0});
  cout<<e;
  return 0;
}
