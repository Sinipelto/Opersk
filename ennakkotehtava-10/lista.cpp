#include "lista.hh"
#include <iostream>
#include <string>

using namespace std;

Lista::Lista():
    // Oletusrakentaja
    ensimmaisen_osoite_(nullptr),
    viimeisen_osoite_(nullptr) {

}

Lista::~Lista() {
    Listan_alkio* vapautettavan_osoite;

    while ( ensimmaisen_osoite_ != nullptr ) {
        vapautettavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_= ensimmaisen_osoite_->seuraavan_osoite;
        delete vapautettavan_osoite;
    }
}

void Lista::tulosta() const {
    Listan_alkio* tulostettavan_osoite = ensimmaisen_osoite_;
    int jarjestysnumero = 1;

    while ( tulostettavan_osoite != nullptr ) {
        cout << jarjestysnumero << ". "
             << tulostettavan_osoite->tehtava << endl;
        ++jarjestysnumero;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }
}

void Lista::lisaa_alkio_loppuun(const string& lisattava_tehtava) {
    Listan_alkio* uuden_osoite
            = new Listan_alkio{lisattava_tehtava, nullptr, nullptr};

    if ( ensimmaisen_osoite_ == nullptr ) {
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }

    else {
        uuden_osoite -> edellisen_osoite = viimeisen_osoite_;
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}

bool Lista::poista_alkio_alusta(string& poistettu_tehtava) {
    if ( onko_tyhja() ) {
        return false;
    }

    Listan_alkio* poistettavan_osoite = ensimmaisen_osoite_;
    poistettu_tehtava = poistettavan_osoite->tehtava;

    if ( ensimmaisen_osoite_ == viimeisen_osoite_ ) {
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
    }

    else {
        ensimmaisen_osoite_
                = ensimmaisen_osoite_->seuraavan_osoite;
    }

    delete poistettavan_osoite;
    return true;
}

bool Lista::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }

    else {
        return false;
    }
}

void Lista::poista_alkio(const string& poistettava_tehtava) {
    // Luodaan osoitin, jolla listan alkioita käydään läpi
    Listan_alkio* nykyisen_osoite = ensimmaisen_osoite_;

    // Käydään läpi listan alkiot
    while (nykyisen_osoite != nullptr) {
        // Mikäli nykyisen alkion tehtävä vastaa poistettavaa tehtävää
        if (nykyisen_osoite -> tehtava == poistettava_tehtava) {
            // Asetetaan edellinen alkio osoittamaan nykyisen alkion yli
            // ja seuraava alkion edellisen alkion osoitin osoittamaan
            // yhden alkion yli taaksepäin
            nykyisen_osoite->edellisen_osoite
                    -> seuraavan_osoite = nykyisen_osoite->seuraavan_osoite;
            nykyisen_osoite -> seuraavan_osoite -> edellisen_osoite
                    = nykyisen_osoite -> edellisen_osoite;
            // Poistetaan alkio muistista
            delete nykyisen_osoite;
            // Lopetetaan funktion suoritus
            return;
        }

        else {
            // Siirrytään seuraavaan osoitteeseen
            nykyisen_osoite = nykyisen_osoite ->seuraavan_osoite;
        }
    }
}
