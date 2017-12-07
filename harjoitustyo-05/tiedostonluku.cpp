// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

// Tämä moduuli lukee halutusta tiedostosta reseptit
// rivi kerrallaan, mikäli ne ovat oikeassa formaatissa.

#include "tiedostonluku.hh"

using namespace std;


bool tiedostonluku(Rakenne& rakenne) {
    // Funktio lukee halutun tiedoston ja palauttaa
    // bool-arvon tiedostoluvun onnistumisesta.
    // sekä tallentaa tiedot haluttuun rakenteeseen

    string nimi;
    cout << "Syotetiedosto: ";
    getline(cin, nimi);

    ifstream tiedosto(nimi);

    if (!tiedosto) {
        // Jos tiedostoa ei löydy tai sen avaaminen ei onnistu
        return false;
    }

    string rivi; // Rivimuuttujan alustus

    // Asetetaan regex-säännöt
    const string tyhja("[[:space:]]*");
    const string osa("_*[[:alpha:]]+(_+[[:alpha:]_]*)*");
    const string kommentti("#.*");

    regex tyhja_rivi(tyhja);
    regex kommenttirivi(tyhja + kommentti);
    regex datarivi(tyhja + osa + tyhja + ":" + tyhja + osa + tyhja);

    // Käydään läpi tiedoston rivit
    while (getline(tiedosto,rivi)) {

        if (regex_match(rivi,tyhja_rivi)) {
            continue;
        }

        else if (regex_match(rivi, kommenttirivi)) {
            continue;
        }

        else if (regex_match(rivi, datarivi)) {
            // Mikäli rivi on oikeanlainen

            while(rivi.find(" ") != string::npos) {
                rivi.erase(rivi.find(" "), 1);
            }

            string::size_type valimerkki = rivi.find(":");
            // Tallennetaan tiedot muuttujiin
            const string alku = rivi.substr(0,valimerkki);
            const string loppu = rivi.substr(valimerkki + 1, rivi.size());

            // Tallennetaan muuttujat tietorakenteeseen
            if (rakenne.onko_pari(alku, loppu)) {
                // Tarkistetaan, onko resepti jo olemassa rakenteessa
                return false;
            }
            rakenne.lisaa_alkio(alku, loppu);
        }

        else {
            return false;
        }
    }
    return true; // Onnistuttaessa palautetaan tosi
}
