// Harjoitustyo 1
// Pankkitiliolion toteutus

// Ohjelmassa simuloidaan kevyesti
// kolmea pankkitilioliota ja niiden
// kayttaytymista komentojen avulla.

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

bool tarkista_tiliosoitin(const int &tili);

class Pankkitili {
public:
    Pankkitili(); // Oletusrakentaja ilman parametreja
    Pankkitili(const string &tilinro, const string &asiakasnro); // Vaihtoehtoinen rakentaja tilitietojen spesifioimiseksi

    void tulosta() const;
    double anna_saldo() const;

    void aseta_tiedot(const string &tilinumero, const string &asiakasnumero, const double &saldo);

    void pano(const double &maara);
    void otto(const double &maara);
    void otto_maara(const double &maara);

private:
    string tilinumero_;
    string asiakasnumero_;
    double saldo_;

};

using tililista = vector<Pankkitili>;

int main() {
    // Maaritellaan 3 pankkitilioliota
    Pankkitili t1("FI6969","12345");
    Pankkitili t2("FI2017","202020");
    Pankkitili t3("FI2222222","12456766");

    tililista tilit = {t1,t2,t3}; // Tallennetaan tilioliot vektoriin
    string komento; // Maaritellaan komentokehotteen syotemuuttuja

    tililista::iterator valittu_tili = tilit.begin(); // Luodaan iteraattori tililistalle ensimmaista tilia varten
    tililista::iterator kohdetili = tilit.begin(); // Luodaan iteraattori toista tilia varten

    while (true) {
        komento.clear(); // Varmistetaan etta komentomuuttuja on tyhja
        cout << "pankkitilitesti> ";
        getline(cin,komento);

        if (komento == "loppu") {
            // Komennon ollessa "loppu" ohjelman suoritus paattyy valittomasti
            return 0;
        }

        // Voidaan olettaa, etta annettu syote ei sisalla virheita
        // - viimeisena merkkina on ascii-merkki 1,2 tai 3
        int tili = komento[komento.size()-1] - '0';

        // Tarkastetaan ettei syotetty kohdetili ole sallitun alueen ulkopuolella
        if (not tarkista_tiliosoitin(tili)) {
            cout << "Virhe: virheellinen tili." << endl;
            continue; // Siirrytaan silmukassa uuteen kierrokseen
        }

        // Varmistetaan etta kohde on tyyppia pankkitililistan size type ja indeksi alkaa 0:sta
        tililista::size_type kohde = (tili-1);

        valittu_tili = tilit.begin()+kohde;
        //valittu_tili = tilit.at(kohde); // Asetetaan iteraattori osoittamaan pankkitilin haluttuun sijaintiin


        if (komento.find("tulosta") != string::npos) {
            valittu_tili -> tulosta();
        }

        else if (komento.find("aseta") != string::npos) {
            string uusi_tilinumero;
            string uusi_asiakasnumero;
            double uusi_saldo;
            cout << "Syota tilinumero: ";
            getline(cin,uusi_tilinumero);
            cout << "Syota saldo: ";
            cin >> uusi_saldo;
            cin.ignore(1);
            cout << "Syota asiakasnumero: ";
            getline(cin,uusi_asiakasnumero);

            if (uusi_saldo < 0) {
                cout << "Virhe: saldon oltava positiivinen." << endl;

            }

            valittu_tili -> aseta_tiedot(uusi_tilinumero,uusi_asiakasnumero,uusi_saldo);
            cout << "Tilin " << tili << " tiedot asetettu." << endl;

        }

        else if (komento.find("pano") != string::npos) {
            double maara;
            cout << "Syota rahamaara: ";
            cin >> maara;
            cin.ignore(1);
            if (maara >= 0) {
                valittu_tili -> pano(maara);
                cout << "Pano suoritettu tilille " << tili << "." << endl;
            }

            else {
                cout << "Virhe: virheellinen rahamaara." << endl;

            }

        }

        else if (komento.find("otto") != string::npos) {
            double maara;
            cout << "Syota rahamaara: ";
            cin >> maara;
            cin.ignore(1);
            if (maara >= 0) {
                if (valittu_tili -> anna_saldo() >= maara) {
                    valittu_tili -> otto(maara);
                    cout << "Otto suoritettu tililta " << tili << "." << endl;

                }

                else {
                    cout << "Virhe: Tililla ei ole tarpeeksi rahaa." << endl;

                }
            }

            else {
                cout << "Virhe: Syotetty rahamaara on virheellinen!" << endl;

            }

        }

        else if (komento.find("tilisiirto") != string::npos) {
            // Maaritetaan myos kohdetilin tiliolion sijainti
            int tili2 = komento[komento.size()-3] - '0';

            if (tarkista_tiliosoitin(tili2)) { // Mikali parametri annetulla valilla
                tililista::size_type kohde2 = tili2 - 1; // Muutetaan tililistan vastaavaksi indeksiksi
                kohdetili = tilit.begin() + kohde2;

                double siirtomaara;
                cout << "Syota siirtomaara: ";
                cin >> siirtomaara;
                cin.ignore(1);

                if (kohdetili -> anna_saldo() >= siirtomaara) {
                    valittu_tili -> pano(siirtomaara);
                    kohdetili -> otto(siirtomaara);
                }

                else {
                    cout << "Virhe: Lahtotililla ei ole tarpeeksi rahaa!" << endl;

                }

            }

            else {
                cout << "Virhe: yhta tai useampaa tilia ei loydy." << endl;
            }

        }

        else {
            cout << "Virhe: virheellinen komento." << endl;
        }

    }

}

Pankkitili::Pankkitili() {
    // Oletusrakentajan maarittely
    // oletusarvoilla
    tilinumero_ = "FI123456789012";
    asiakasnumero_ = "0123456";
    saldo_ = 0.00;
}

Pankkitili::Pankkitili(const string &tilinro, const string &asiakasnro) {
    // Erillinen rakentajamaarittely tietyilla parametriarvoilla
    tilinumero_ = tilinro;
    asiakasnumero_ = asiakasnro;
    saldo_ = 0.00;
}

void Pankkitili::tulosta() const {
    cout << fixed;
    cout << "Tilinumero: " << tilinumero_ << endl;
    cout << "Saldo: ";
    cout << setprecision(2) << saldo_ << endl;
    cout << "Asiakasnumero: " << asiakasnumero_ << endl;
}

void Pankkitili::aseta_tiedot(const string &tilinumero, const string &asiakasnumero, const double &saldo) {
    tilinumero_ = tilinumero;
    asiakasnumero_ = asiakasnumero;
    saldo_ = saldo;
}

void Pankkitili::pano(const double &maara) {
    saldo_ += maara;
}

void Pankkitili::otto(const double &maara) {
    saldo_ -= maara;
}

double Pankkitili::anna_saldo() const {
    return saldo_;
}

bool tarkista_tiliosoitin(const int &tili) {
    // Funktio tarkistaa, onko syotetty tilin sijainti
    // valilla 1-3 ja palauttaa true jos on ja false jos ei ole
    if (tili==1 or tili==2 or tili == 3) {
        return true;
    }
    return false;
}
