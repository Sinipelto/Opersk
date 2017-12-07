// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

// Tämä moduuli sisältää ohjelmassa
// tarvittavan tietorakenteen. Tietorakenne
// on yhteensopiva sekä reseptien että repun
// toimintojen suhteen.

#include "rakenne.hh"

using namespace std;


Rakenne::Rakenne():
    // Listan rakentaja, alustaa
    // kokomuuttujan ja osoittimet.
    koko_(0),
    ensimmainen_ptr_(nullptr),
    viimeinen_ptr_(nullptr) {
}


Rakenne::~Rakenne() {
    // Listan destruktori
    // Vapauttaa dynaamisesti varatut muistipaikat
    // rakenneolion tuhoutuessa ja nollaa koon.
    ensimmainen_ptr_ = nullptr;
    viimeinen_ptr_ = nullptr;
    koko_ = 0;
}


bool Rakenne::tyhja() const {
    // Palauttaa tiedon, onko lista tyhjä.
    if (koko_ == 0) {
        return true;
    } return false;
}


bool Rakenne::lisaa_alkio(const string& eka, const string& toka) {
    // Metodi lisää halutut kentät listan loppuun alkioksi.
    // Palauttaa false jos yritetään lisätä jo olemassa olevaa alkiota.
    if (eka == "" or toka == "") {
        return true;
    }

    shared_ptr<Alkio> ptr = ensimmainen_ptr_;

    // Suoritetaan virhetarkastelu annetuille syötteille
    while (ptr != nullptr) {
        // Tyhjiä ei hyväksytä
        // Ei samoja alkioita
        if (onko_pari(eka, toka)) {
            return false;
        }
        ptr = ptr->seuraava;
    }
    shared_ptr<Alkio> uusi(new Alkio{eka,toka,nullptr});

    if (tyhja()) {
        // Tyhjään rakenteeseen lisäys
        uusi -> seuraava = nullptr;
        ensimmainen_ptr_ = uusi;
        viimeinen_ptr_ = uusi;
        koko_++;
        return true;
    }

    viimeinen_ptr_ ->seuraava = uusi;
    viimeinen_ptr_ = uusi;
    koko_++;
    return true;
}

bool Rakenne::onko_pari(const string &eka, const string &toka) const {
    shared_ptr<Alkio> ptr = ensimmainen_ptr_;

    while (ptr != nullptr) {
        if (ptr->eka == eka and ptr->toka == toka) {
            return true;
        }
        ptr = ptr->seuraava;
    }
    return false;
}


void Rakenne::tyhjenna() {
    // Metodi tuhoaa rakenteen sisällön
    ensimmainen_ptr_ = nullptr;
    viimeinen_ptr_ = nullptr;
    koko_ = 0;
}


void Rakenne::tulosta_ekat() const {
    // Tulostaa kaikkien alkioiden ensimmäiset kentät
    // allekkain lisäysjärjestyksessä, hyödyllinen erityisesti
    // kun käytössä on vain ensimmäinen kenttä.
    if (!tyhja()) {
        shared_ptr<Alkio> ptr = ensimmainen_ptr_;
        while (ptr != nullptr) {
            cout << ptr->eka << endl;
            ptr = ptr->seuraava;
        }
    }
}


bool Rakenne::aseta_sisalto(string syote, const string& poistettava) {
    // Poistaa syötteestä halutun sanan ja tallentaa lopun syötteen
    // alkioina rakenteeseen, erotinmerkkinä välilyönti.
    tyhjenna(); // Tyhjennetään repun sisältö
    size_t pos = syote.find(poistettava);
    syote.erase(pos, poistettava.size() + 1); // Poistetaan haluttu osa
    syote += " "; // Lisätään ylimääräinen välilyönti
    string sana;

    while (syote.find(" ") != string::npos) {
        // Käydään läpi syötteen sanat
        size_t vali = syote.find(" ");
        sana = syote.substr(0, vali);
        if (!lisaa_alkio(sana, "null")) {
            return false;
        }
        syote.erase(0, vali + 1);
    }
    return true;
}


bool Rakenne::askarreltavissa(const string& esine, const Rakenne& reseptit) const {
    // Tutkii, onko haluttu esine/materiaali askarreltavissa nykyisillä materiaaleilla.
    shared_ptr<Alkio> resepti_ptr = reseptit.ensimmainen_ptr_;
    int laskuri = 0; // Kirjataan reseptien osumat ylös

    while (resepti_ptr != nullptr) {
        // Käydään läpi tarvittavat materiaalit
        if (resepti_ptr->eka == esine) {
            laskuri++;
            // Esineen materiaali löydetty resepteistä
            if (!onko_eka(resepti_ptr->toka)) {
                // Jos materiaali ei ole repussa
                return false;
            }
        }
        resepti_ptr = resepti_ptr -> seuraava;
    }
    if (laskuri > 0) {
        return true;
    } return false;
}


bool Rakenne::onko_listassa(const string& sana) const {
    // Kertoo, onko tutkittava esine/materiaali listassa.
    if (onko_eka(sana) or onko_toka(sana)) {
        return true;
    } return false;
}


bool Rakenne::onko_eka(const string& sana) const {
    // Kertoo, onko string structin eka-kentässä missään listan alkiossa.
    shared_ptr<Alkio> ptr = ensimmainen_ptr_;

    while (ptr != nullptr) {
        if (ptr->eka == sana) {
            return true;
        }
        ptr = ptr->seuraava;
    }
    return false;
}


bool Rakenne::onko_toka(const string& sana) const {
    // Kertoo, onko string structin toka-kentässä missään listan alkiossa.
    shared_ptr<Alkio> ptr = ensimmainen_ptr_;

    while (ptr != nullptr) {
        if (ptr->toka == sana) {
            return true;
        }
        ptr = ptr->seuraava;
    }
    return false;
}

bool Rakenne::lista_listassa(const Rakenne &lista) {
    // Tarkistaa, onko listan alkiot jo olemassa listassa.
    shared_ptr<Alkio> ptr = lista.ensimmainen_ptr_;

    while (ptr != nullptr) {
        if (!onko_listassa(ptr->eka)) {
            return false;
        }
        ptr = ptr->seuraava;
    }
    return true;
}


void Rakenne::tulosta_materiaalit(const string& esine) const {
    // Tulostaa kaikki halutun esineen tekemiseen tarvittavat materiaalit.
    shared_ptr<Alkio> ptr = ensimmainen_ptr_;
    // Alustetaan taulukko materiaaleja varten
    const int koko_vakio = koko_;
    string *mat = new string[koko_vakio];

    for (size_t i = 0; i < koko_;i++) {
        mat[i] = "";
    }

    while (ptr != nullptr) {
        if (ptr->eka == esine) {
            // Poimitaan vastaavista esineistä
            // tarvittu materiaali taulukkoon
            for (size_t i = 0; i < koko_;i++) {
                if (mat[i] == "") {
                    mat[i] = ptr->toka;
                    break;
                }
            }

        }
        ptr = ptr->seuraava;
    }
    // Lajitellaan taulukko aakkosjärjestykseen
    sort(&mat[0],&mat[koko_vakio]);
    for (size_t i = 0; i < koko_;i++) {
        if (mat[i] != "") {
            cout << mat[i] << endl;
        }
    }

    delete[] mat;
}
