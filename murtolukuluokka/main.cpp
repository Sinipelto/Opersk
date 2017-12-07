// Ohjelmassa on toteutettu luokka Murtoluku, jolle voidaan tehdä
// tyypillisiä murtoluvuille mahdollisia matemaattisia operaatioita,
// kuten yhteen- ja vähennyslasku, kerto- ja jakolasku sekä kääteisluku
// ja vastaluku. Luokan julkisia rajapintoja on demonstroitu main-funktiossa
// laskemalla eräs murtolukulauseke, jonka alkutilanteen voi päätellä käytetyistä
// luvuista. Sievennysmetodi puuttuu luokasta täysin.


#include <iostream>

using namespace std;

class Murtoluku {
public:
    Murtoluku();
    Murtoluku(int osoittaja);
    Murtoluku(int osoittaja, int nimittaja);
    Murtoluku pluslasku(Murtoluku lisattava) const;
    Murtoluku miinuslasku(Murtoluku lisattava) const;
    Murtoluku kertolasku(Murtoluku kerrottava) const;
    Murtoluku jakolasku(Murtoluku jaettava) const;
    Murtoluku vastaluku() const;
    Murtoluku kaanteisluku() const;
    void tulosta() const;

private:
    int osoittaja_;
    int nimittaja_;

};

int main() {
    // Lasketaan tehtävänannon mukainen lauseke:

    // Määritellään tarvittavat murtoluvut
    Murtoluku m1(4,5);
    Murtoluku m2(5,8);
    Murtoluku m3(1,8);
    Murtoluku m4(2,3);
    Murtoluku m5(1,7);

    // Lasku 1
    cout << "Lasku 1:\n" << endl;
    Murtoluku m12 = m1.miinuslasku(m2);
    m12.tulosta();

    // Lasku 2
    cout << "Lasku 2:\n" << endl;
    Murtoluku m123 = m12.pluslasku(m3);
    m123.tulosta();

    // Lasku 3
    cout << "Lasku 3:\n" << endl;
    Murtoluku m45 = m4.kertolasku(m5);
    m45.tulosta();

    // Lasku 4
    cout << "Lasku 4:\n" << endl;
    Murtoluku mfinal = m123.jakolasku(m45);
    mfinal.tulosta();
    cout << "Laskut suoritettu." << endl;

    return 0;


}

Murtoluku::Murtoluku() { // Oletusrakentaja
    osoittaja_ = 0;
    nimittaja_ = 1; {

    }
}

Murtoluku::Murtoluku(int osoittaja) { // Vain osoittaja annettu
    osoittaja_ = osoittaja;
    nimittaja_ = 1;
}

Murtoluku::Murtoluku(int osoittaja, int nimittaja) { // Koko murtoluku syötetty
    if ((osoittaja < 0 and nimittaja < 0) or (osoittaja > 0 and nimittaja < 0)) {
        osoittaja = -(osoittaja);
        nimittaja = -(nimittaja);

    }


    osoittaja_ = osoittaja;
    nimittaja_ = nimittaja;
}

void Murtoluku::tulosta() const { // Metodi tarvitsee iostream-kirjastoa (cout)
    cout << osoittaja_ << "\n"
         << "-" << "\n" << nimittaja_ << "\n" << endl;

}

Murtoluku Murtoluku::pluslasku(Murtoluku lisattava) const {
    int uusi_nimittaja = nimittaja_*lisattava.nimittaja_;
    int uusi_osoittaja = osoittaja_*lisattava.nimittaja_ + nimittaja_*lisattava.osoittaja_;
    return Murtoluku(uusi_osoittaja,uusi_nimittaja);
}

Murtoluku Murtoluku::miinuslasku(Murtoluku vahentaja) const {
    return pluslasku(vahentaja.vastaluku());
}

Murtoluku Murtoluku::vastaluku() const {
    return Murtoluku(-osoittaja_,nimittaja_);
}

Murtoluku Murtoluku::kaanteisluku() const {
    return Murtoluku(nimittaja_,osoittaja_);
}

Murtoluku Murtoluku::kertolasku(Murtoluku kerrottava) const {
    int osoittaja = osoittaja_ * kerrottava.osoittaja_;
    int nimittaja = nimittaja_ * kerrottava.nimittaja_;

    return Murtoluku(osoittaja,nimittaja);

}

Murtoluku Murtoluku::jakolasku(Murtoluku jaettava) const {
    jaettava = jaettava.kaanteisluku();

    int osoittaja = osoittaja_ * jaettava.osoittaja_;
    int nimittaja = nimittaja_ * jaettava.nimittaja_;

    return Murtoluku(osoittaja,nimittaja);
}
