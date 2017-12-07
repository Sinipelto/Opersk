#include "pino.hh"
#include <iostream>
#include <memory>

using namespace std;

Pino::Pino():
    eka_osoite_(nullptr),
    vika_osoite_(nullptr),
    alkiomaara_(0) {
}

bool Pino::empty() const {
    if (eka_osoite_ == nullptr) {
        return true;
    }return false;
}

void Pino::push_front(const int &lisattava) {
    // Luodaan osoitin tyypille Alkio ja haetaan sille vapaa dynaaminen muistipaikka,
    // johon luodaan uusi alkio
    shared_ptr<Alkio> uusi_osoite(new Alkio{lisattava, nullptr, nullptr});
    if (empty()) {
        // Listan ollessa tyhjä asetetaan alku ja loppu
        // osoittamaan uuteen eli ensimmäiseen ja viimeiseen alkioon
        eka_osoite_ = uusi_osoite;
        vika_osoite_ = uusi_osoite;
    }

    else {
        // Asetetaan edeltävän ensimmäisen edeltävä osoitin osoittamaan
        // uuteen ensimmäiseen alkioon
        eka_osoite_ -> edellinen_osoite = uusi_osoite;
        // Asetetaan uuden alkion osoitin osoittamaan listan
        // (edelliseen) ensimmäiseen alkioon
        uusi_osoite -> seuraava_osoite = eka_osoite_;
        // Asetetaan eka_osoitin osoittamaan uuteen alkioon
        eka_osoite_ = uusi_osoite;
    }
    ++alkiomaara_;
}

bool Pino::pop_front(int &poistettu) {
    if (empty()) {
        return false;
    }
    // Tallennetaan poistettavan alkion arvo parametrimuuttujaan
    poistettu = eka_osoite_ -> arvo;
    // Nollataan seuraavan alkion edellistä osoittava osoitin
    eka_osoite_ -> edellinen_osoite = nullptr;
    // Asetetaan ensimmäisen alkion osoitin osoittamaan itseä seuraavaan
    // alkioon, jolloin sen varaama muistipaikka (alkio) vapautuu automaattisesti
    eka_osoite_ = eka_osoite_ -> seuraava_osoite;
    --alkiomaara_;
    return true;
}

void Pino::print() const {
    // Pinon tulostusmetodi, tulostaa pinon
    // alkiot niiden nykyisessä järjestyksessä

    // Luodaan osoitin osoittamaan ensimmäiseen alkioon
    shared_ptr<Alkio> osoitin = eka_osoite_;

    cout << "\nListan alkiot:" << endl;
    cout << "[";
    // Käydään läpi kaikki alkiot
    while (osoitin != nullptr) {
        cout << " ";
        // Tulostetaan alkion kenttä 'arvo'
        cout << osoitin -> arvo;
        // Siirretään osoitin seuraavaan alkioon
        osoitin = osoitin -> seuraava_osoite;
    }
    cout << " ]" << "\n" << endl;
}

int Pino::size() const {
    return alkiomaara_;
}

void Pino::takaperin() {
    // Metodi kääntää ei-tyhjän pinon alkiot
    // päinvastaiseen järjestykseen
    if (empty()) {
        return;
    }
    else if (alkiomaara_ == 1) {
        return;
    }

    int arvo;
    shared_ptr<Alkio> nykyinen = eka_osoite_;
    shared_ptr<Alkio> viimeinen = vika_osoite_;

    while (true) {
        // Tallennetaan nykyisen arvo välimuuttujaan
        arvo = nykyinen -> arvo;
        // Tallennetaan nykyiseen "viimeisen" arvo
        nykyinen -> arvo = viimeinen -> arvo;
        // tallennetaan "viimeiseen" nykyisen arvo
        viimeinen -> arvo = arvo;

        nykyinen = nykyinen -> seuraava_osoite;
        if (nykyinen == viimeinen) {
            break;
        }
        viimeinen = viimeinen -> edellinen_osoite;
        if (viimeinen == nykyinen) {
            break;
        }
    }
}
