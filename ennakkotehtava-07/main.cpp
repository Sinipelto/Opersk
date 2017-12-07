// Ennakkotehtävä 07

//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -koodipohja
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Opiskelija {
    string nimi;
    unsigned int opnum;
};

bool aakkosittain(const Opiskelija &op1, const Opiskelija &op2) {
    // Apufunktio sort-funktiolle, lajittelee Opiskelijat nimen
    // mukaan aakkosittain kasvavaan järjestykseen
    if (op1.nimi < op2.nimi) {
        return true;
    }return false;
}

bool opnumeron_mukaan(const Opiskelija *viite1, const Opiskelija *viite2) {
    // Apufunktio sort-funktiolle, lajittelee Opiskelijat kasvavaan järjestykseen
    // opiskelijanumeron mukaan
    if (viite1->opnum < viite2->opnum) {
        return true;
    }return false;
}

int main() {
    vector<Opiskelija> oprek = {
        { "Teekkari, Tiina",           52401 },
        { "Ylikuuskajaskari, Jaska",  186112 },
        { "Repolainen, Reijo",        117118 },
        { "Teekkari, Teemu",          196196 },
        { "Santaholma, Santtu",       173421 },
    };

    vector<Opiskelija*> opiskelijaosoittimet = { };

    // Laitetaan opiskelijaosoittimet-vektoriin kaikkien oprek:iin
    // talletettujen opiskelijoiden muistiosoitteet.
    for ( vector<Opiskelija>::size_type i = 0; i < oprek.size(); ++i ) {
        opiskelijaosoittimet.push_back( &oprek.at(i) );
    }

    sort(oprek.begin(), oprek.end(), aakkosittain);

    sort(opiskelijaosoittimet.begin(), opiskelijaosoittimet.end(), opnumeron_mukaan);

    //------------------------------------------------------------------//
    // Tässä kohdassa kumpikin vektori on järjestetty oman vertailu-    //
    // kriteerinsä perusteella kasvavaan järjestykseen. Tätä tilannetta //
    // havainnollistetaan tehtävänannon kuvassa, joka esittää           //
    // lajittelun jälkeistä lopputilannetta.                            //
    //------------------------------------------------------------------//

    // Tulostetaan opiskelijoiden tiedot näytölle kuumankin edellä
    // lajitellun vektorin avulla, jotta nähdään onko lajittelu onnistunut.

    cout << "Opiskelijat nimen mukaisessa järjestyksessa:" << endl
         << "--------------------------------------------" << endl;
    for ( Opiskelija opisk : oprek ) {
        cout << setw(24) << left << opisk.nimi
             << setw(6) << right << opisk.opnum << endl;
    }

    cout << endl;

    cout << "Opiskelijat numeron mukaisessa järjestyksessa:" << endl
         << "----------------------------------------------" << endl;
    for ( Opiskelija* opisk_ptr : opiskelijaosoittimet ) {
        cout << setw(24) << left << opisk_ptr->nimi
             << setw(6) << right << opisk_ptr->opnum << endl;
    }
}
