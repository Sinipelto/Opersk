#include <iostream>
#include <iomanip>


using namespace std;

class Kellonaika {
public:
    Kellonaika(int tunti, int minuutti);
    void tiktok();
    int hae_tunti() const;
    int hae_minuutti() const;
    void tulosta() const;
    int laske_ero(Kellonaika toinen_kello) const;
private:
    // Kello 00.00:sta kuluneet minuutit
    int kuluneet_minuutit_;
};

int main() {
    int tunnit;
    int minuutit;

    cout << "Syötä kellonaika muodossa xx\n";
    cout << "Oletetaan, että syöte tunneille on välillä\n"
         << "0-24 ja minuuteille 0-60.\n" << endl;
    cout << "Valitse kellonaika yksi:" << endl;
    cout << "tunnit: ";
    cin >> tunnit;
    cout << "minuutit: ";
    cin >> minuutit;
    cout << "\n";

    Kellonaika kello1(tunnit,minuutit);

    cout << "Sitten kellonaika kaksi:" << endl;
    cout << "tunnit: ";
    cin >> tunnit;
    cout << "minuutit: ";
    cin >> minuutit;
    cout << "\n";

    Kellonaika kello2(tunnit,minuutit);

    kello1.tulosta();
    kello2.tulosta();
    cout << endl;

    cout << "kellojen välinen aikaero minuutteina on ";
    cout << kello1.laske_ero(kello2);
    cout << " minuuttia." << endl;



}

Kellonaika::Kellonaika(int tunti, int minuutti):
    kuluneet_minuutit_(60 * tunti + minuutti) {

}

void Kellonaika::tiktok() {
    ++kuluneet_minuutit_;
    if ( kuluneet_minuutit_ >= 24 * 60 ) {
        kuluneet_minuutit_ = 0;
    }
}

int Kellonaika::hae_tunti() const {
    // Kun kokonaisluku jaetaan kokonaisluvulla
    // tuloksena on kokonaisluku (jakojäännös
    // heitetään menemään).

    return kuluneet_minuutit_ / 60;
}

int Kellonaika::hae_minuutti() const {
    return kuluneet_minuutit_ % 60;
}

void Kellonaika::tulosta() const {

    cout << setfill('0') << setw(2) << hae_tunti()

        << "."

        << setw(2) << hae_minuutti()
                   << endl;


}

int Kellonaika::laske_ero(Kellonaika toinen_kello) const {
    int tunti;
    int minuutti;
    int minuutit_eka = hae_minuutti();
    int minuutit_toka = toinen_kello.hae_minuutti();
    int tunnit_eka = hae_tunti();
    int tunnit_toka = toinen_kello.hae_tunti();

    if (tunnit_toka > tunnit_eka) {
        tunti = tunnit_toka - tunnit_eka;
    }

    else {
        tunnit_toka += 24;
        tunti = tunnit_toka - tunnit_eka;
    }

    if (minuutit_toka > minuutit_eka) {
        minuutti = minuutit_toka - minuutit_eka;

    }

    else {
        tunti -= 1;
        minuutit_toka += 60;
        minuutti = minuutit_toka - minuutit_eka;
    }

    int minuuttiero = tunti*60+minuutti;

    return minuuttiero;
}
