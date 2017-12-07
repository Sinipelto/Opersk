// Ennakkotehtava 05
// Moduulien kayton harjoittelu

// Ohjelmassa on toteutettu laskinkayttoliittyma
// splitter luokan avulla, joka sijaitsee erilisena
// moduulina. Moduulit on include-komennon avulla sisallytetty
// tahan paaohjelmaan.

#include "splitter.hh"
#include "laskin.hh"
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <iomanip>

using namespace std;

int main() {

    string komento;
    unsigned int lukumaara;

    while (true) {
        komento.clear();
        cout << "laskin> ";
        getline(cin,komento);

        // Luodaan syotteesta splitterolio ja tarkastellaan syotteen oikeellisuutta
        Splitter osat(komento);
        lukumaara = osat.paloittele(' ', false);

        // Mikali komento on tyhja, lopetetaan
        // Mikali komento ei koostu kolmesta osasta, siirrytaan uuteen kierrokseen.
        if (komento.empty()) {
            cout << "Kiitos ja nakemiin!" << endl;
            return 0;

        }

        // Mikali komennon syntaksi ei vastaa oletettua (a operandi b)
        else if (lukumaara != 3) {
            cout << "Virheellinen komento!" << endl;
            continue;

        }

        else {
            Laskin laskin;

            try {
                double luku1 = stod(osat.hae_kentta(0));
                double luku2 = stod(osat.hae_kentta(2));

                if (osat.hae_kentta(1) == "+") {
                    cout << setprecision(3) << laskin.yhteenlasku(luku1, luku2) << endl;
                }

                else if (osat.hae_kentta(1) == "-") {
                    cout << setprecision(3) << laskin.vahennyslasku(luku1,luku2) << endl;
                }

                else if (osat.hae_kentta(1) == "*") {
                    cout << setprecision(3) << laskin.kertolasku(luku1,luku2) << endl;
                }

                else if (osat.hae_kentta(1) == "/")  {
                    cout << setprecision(3) << laskin.jakolasku(luku1,luku2) << endl;
                }

                else {
                    cout << "Virheellinen operandi!" << endl;
                }
            }

            catch (exception &e) {
                cout << "Syotit virheelliset arvot!" << endl;
                continue;

            }
        }
    }
}
