// Ennakkotehtävä 03

// Ohjelma sisältää splitter-luokan, jonka luoma splitterolio kykenee
// pilkkomaan merkkijonoja haluttujen välimerkkien mukaisesti.

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;


// unsigned int -tyypin avulla voidaan käsitellä arvoja,
// jotka ovat suurempia tai yhtäsuuria kuin nolla (etumerkittömiä),
// eli siis luonnollisia lukuja (ℕ).
const unsigned int SPLITTER_VIRHE = 0;

class Splitter {
  public:
    Splitter(const string& paloiteltava_merkkijono = "");

    // Asetetaan merkkijono, joka halutaan paloitella.
    // Idea on se, että sama Splitter-tyyppistä oliota
    // voidaan käyttää muidenkin kuin rakentajan parametrina
    // annettujen merkkijonojen paloitteluun.
    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    // Paloitellaan merkkijono parametrina annetun
    // erotinmerkin kohdalta osiin. Paluuarvona tieto
    // siitä, montako kenttää rivillä oli.
    // Jos ohita_tyhjat-parametrin arvo on true,
    // paloittelun tuloksena mahdollisesti syntyvät tyhjät kentät
    // jätetään pois lopputuloksesta.  Tämä on hyödyllinen ominaisuus,
    // jos halutaan jakaa merkkijono sanoiksi, mutta ei olla täysin
    // varmoja siitä, onko sanojen välissä yksi vai useampia
    // välilyöntejä: paloittelijaolio.paloittele(' ', true);
    unsigned int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    // Palauttaa tiedon siitä, montako kenttää aiemmin
    // suoritetun paloittelun tuloksena syntyi.  Käytännössä
    // paluuarvo on siis sama kuin paloittele-metodin paluuarvo
    // edellä.  Erona se, että paluuarvo on SPLITTER_VIRHE,
    // jos paloittele-metodia ei ole kutsuttu sen jälkeen,
    // kun paloiteltava merkkijono on viimeksi asetettu
    // (rakentajassa tai aseta_paloiteltava_merkkijono-metodissa).
    unsigned int kenttien_lukumaara() const;

    // Kun merkkijono on paloiteltu, tällä metodilla
    // voidaan pyytää Splitter-oliolta tietty kenttä.
    // Oletetaan että kentät on numeroitu vasemmalta
    // oikealle alkaen nollasta.  Jos paloittele-metodia
    // ei ole kutsuttu tai kentan_numero on liian
    // suuri rivillä olleiden kenttien lukumäärään
    // verrattuna, metodi tuottaa out_of_range-tyyppisen
    // poikkeuksen:
    //
    //     #include
    //     ...
    //     throw out_of_range("virheellinen kentan_numero");
    //
    string hae_kentta(unsigned int kentan_numero) const;

  private:
    // Lähtötieto: tätä merkkijonoa paloittele-metodi pätkiin osiin.
    string paloiteltava_;

    // paloittele-metodi tallentaa tuloksen tähän vektoriin, niin
    // että kun merkkijono on kerran paloiteltu, sen kenttiin päästään
    // käsiksi nopeasti.
    vector<string> kentat_;
};

//-----------------------------------------------------------------------------

int main() {
    Splitter paloittelija("a::bc:def::hijlkm");

    paloittelija.paloittele(':');  // Huomaa heittomerkit

    cout << "kenttia: " << paloittelija.kenttien_lukumaara() << endl;  // 6

    cout << paloittelija.hae_kentta(0) << endl;  // a
    cout << paloittelija.hae_kentta(4) << endl;  // (tyhjä)
    cout << paloittelija.hae_kentta(5) << endl;  // hijlkm

    for ( unsigned int i = 0; i < paloittelija.kenttien_lukumaara(); ++i ) {
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    paloittelija.aseta_paloiteltava_merkkijono(" A B  C   D    E     ");
    unsigned int kenttia = paloittelija.paloittele(' ', true);

    cout << "kenttia: " << kenttia << endl;  // 5

    for ( unsigned int i = 0; i < kenttia; ++i ) {
        string kasiteltava_kentta = paloittelija.hae_kentta(i);
        cout << i << ": [" << kasiteltava_kentta << "]" << endl;
    }

    //cout << paloittelija.hae_kentta(5) << endl;  // out_of_range
}

//-----------------------------------------------------------------------------

Splitter::Splitter(const string& paloiteltava_merkkijono):
    paloiteltava_(paloiteltava_merkkijono), kentat_( {} ) {
}


void Splitter::aseta_paloiteltava_merkkijono(const string& merkkijono) {
    paloiteltava_ = merkkijono;
    kentat_ = {};  // kentat.clear();
}


unsigned int Splitter::paloittele(char erotinmerkki, bool ohita_tyhjat) {
    // Tyhjennetään kentat_-vektori siltä varalta, että samaa oliota
    // on jo aiemmin käytetty jokin toisen merkkijonon paloitteluun,
    // minkä seurauksena vektorissa on jotain vanhaa tietoa.
    kentat_.clear();

    // alkukohta pitää kirjaa siitä, missä kohdassa merkkijonoa
    // on seuraava kenttä, jota ei vielä ole siirretty kentat_-vektoriin.
    string::size_type alkukohta = 0;
    string kentan_teksti;

    while ( true ) {
        // loppukohtaan etsitään find-metodilla, missä kohdassa
        // on ensimmäinen alkukohdan jälkeen tuleva erotinmerkki.
        string::size_type loppukohta;

        loppukohta = paloiteltava_.find(erotinmerkki, alkukohta);

        // Jos alkukohdan perästä ei löydy erotinmerkkiä, merkkojonossa
        // on enää yksi kenttä jäljellä (viimeinen kenttä, jonka perässä
        // ei ole erotinmerkkiä).  Käsitellään se erikseen silmukän perässä.
        if ( loppukohta == string::npos ) {
            break;
        }

        // Otetaan talteen kentän sisältö indeksien
        // alkukohta ja loppukohta välistä.
        kentan_teksti = paloiteltava_.substr(alkukohta, loppukohta - alkukohta);

        // Tyhjiä kenttiä ei tallenneta, mikäli parametri
        // ohita_tyhjat on true.
        if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
            kentat_.push_back(kentan_teksti);
        }

        // Siirretään alkukohta seuraavan käsittelemättömän
        // kentän ensimmäiseen merkkiin.
        alkukohta = loppukohta + 1;
    }

    // Otetaan viimeisen erotinmerkin perässä oleva teksti talteen.
    // koska se on rivin viimeinen kenttä.
    kentan_teksti = paloiteltava_.substr(alkukohta);

    if ( not (ohita_tyhjat and kentan_teksti.empty()) ) {
        kentat_.push_back(kentan_teksti);
    }

    return kentat_.size();
}


unsigned int Splitter::kenttien_lukumaara() const {
    // Paloittelua ei ole suoritettu, jos kentat_-vektori on tyhjä.
    if ( kentat_.size() == 0 ) {
        return SPLITTER_VIRHE;

    } else {

        return kentat_.size();
    }
}


string Splitter::hae_kentta(unsigned int kentan_numero) const {
    // Paloittelua ei ole suoritettu tai kentän numero on liian suuri.
    if ( kentat_.empty() or kentan_numero >= kentat_.size() ) {
        throw out_of_range("virheellinen kentan_numero");
    }

    return kentat_.at(kentan_numero);
}
