// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

// Tämä on ohjelman päämoduuli.
// Ohjelma lukee ensin valitun tiedoston
// Mikäli tiedostonluku onnistuu, ohjelma
// käynnistää käyttöliittymän.

#include "tiedostonluku.hh"
#include "kayttoliittyma.hh"
#include "rakenne.hh"

using namespace std;


int main() {
    // Luodaan rakenne resepteille
    Rakenne data;

    // Luetaan syötetiedosto
    if (!tiedostonluku(data)) {
        cout << "Virhe: tiedostoa ei voitu lukea." << endl;
        return 1;
    }

    else {
        cout << "Tuotantoketjut luettu onnistuneesti." << endl;
        // Suoritetaan käyttöliittymä
        // Välitetään tiedostosta reseptit käyttöliittymään
        kayttoliittyma(data);
        return 0;
    }
}
