//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright Ā© 2017  opersk@tut.fi
//------------------------------------------------

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

using namespace std;


vector<string> jaa_sanoiksi(const string& paloiteltava);
double plus_operaatio(double vasen_operandi, double oikea_operandi);


using Operaatiofunktiotyyppi = decltype(&plus_operaatio);  // *****


const map<string, Operaatiofunktiotyyppi> OPERAATIOT = {   // *****
    { "+",  plus_operaatio },                              // *****
};


int main() {
    string syote;

    while ( true ) {
        cout << "syota laskuoperaattori> ";
        getline(cin, syote);

        if ( syote.empty() ) {
            cout << "Nakemiin!" << endl;
            break;

        }

        vector<string> kentat = jaa_sanoiksi(syote);

        if ( kentat.size() != 3 ) {
            cout << "Virhe: syotteen oltava muotos: luku oper luku" << endl;
            continue;
        }

        string operaattori = kentat.at(1);
        double vasen = stod(kentat.at(0));
        double oikea = stod(kentat.at(2));

        if ( OPERAATIOT.find(operaattori) == OPERAATIOT.end() ) {
            cout << "Virhe: tuntematon laskuoperaattori!" << endl;

        } else {

            cout << "Tulos: "
                 << OPERAATIOT.at(operaattori)(vasen, oikea)  // *****
                 << endl;
        }
    }
}


vector<string> jaa_sanoiksi(const string& paloiteltava) {
    istringstream rivivirta(paloiteltava);

    string sana;
    vector<string> tulos;

    while ( rivivirta >> sana ) {
        tulos.push_back(sana);
    }

    return tulos;
}


double plus_operaatio(double vasen_operandi, double oikea_operandi) {
    return vasen_operandi + oikea_operandi;
}
