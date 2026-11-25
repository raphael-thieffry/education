#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

vector<string> jours = {"lundi", "mardi", "mercredi", "jeudi", "vendredi"};

/// BEGIN afficheOccupation
void afficheOccupation(vector<vector<bool>> s) {
    for ( int i = 0; i < s.size(); i++ ) {
    	cout<<jours[i]<<" ";
		for ( int j = 0; j < s[0].size(); j++ ) {
			cout << s[i][j] << " ";
		}
		cout << endl;
    }
}
/// END afficheOccupation

/// BEGIN tauxOccupation
double tauxOccupation(vector<vector<bool>> s) {
    double t = 0;
    for(int i; i<s.size();i++){
    	if(s[i] == true){
    		t++;
    	}
    }
    return t/s.size;
}
/// END tauxOccupation

int main() {
    vector<vector<bool>> occupationSalle;
    occupationSalle = vector<vector<bool>>(5);

    for (int i = 0; i < occupationSalle.size(); i++) {
        occupationSalle[i] = vector<bool> (11);
    }

    occupationSalle[1][1] = true;
    afficheOccupation(occupationSalle);
    cout << "taux occupation = " << tauxOccupation(occupationSalle) << "%" <<
         endl;

    return 0;
}

