// Harjoitustyo 02
// Kauppalista

// Ohjelma lukee syotetiedostosta kauppalistan
// ja tallentaa sen tietorakenteeseen, jossa
// sen sisaltamia tietoja voidaan kasitella.

// Ohjelmassa voidaan tutkia tarjolla olevia
// kauppaketjuja ja niiden valikoimia, seka
// vertailla halvimpia tuotteiden hintoja.

#include "splitter.hh"
#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Luodaan struct-rakenne tuotteille
// joka sisaltaa tuotteen nimen ja hinnan
struct Tuote {
    string tuotenimi;
    double hinta;
};

// Maaritellaan kaantajalle tietorakennealiakset
using tuotelista = vector<Tuote>;
using liikelista = map<string, tuotelista>;
using ketjulista = map<string, liikelista>;

bool tiedostonluku(const string& tiedostonimi, ketjulista& lista);

int main() {
    // Muodostetaan tietorakenne kauppalistalle
    ketjulista kauppalista;

    // Valitetaan kauppalistarakenne tiedostonlukufunktiolle
    // viiteparametrina, jolloin se voidaan taydentaa tiedostonlukufunktion sisalla

    if (!tiedostonluku("tuotetiedot.txt", kauppalista)) {
        cout << "Virhe: syotetiedostoa ei saatu luettua." << endl;
        return 0;
    }

    Splitter komento;
    string syote;

    while (true) {
        // Komentokayttoliittyma
        cout << "tuotehaku> ";
        getline(cin, syote);

        // Paloitellaan luettu syote osiin valilyonneittain
        komento.aseta_paloiteltava_merkkijono(syote);
        komento.paloittele(' ');

        if (syote == "lopeta") {
            return 0;
        }

        else if (komento.hae_kentta(0) == "kauppaketjut" && komento.kenttien_lukumaara() == 1) {
            // Kaydaan lapi kaikki kauppaketjut ja tulostetaan niiden nimet

            for (auto ketju : kauppalista) {
                cout << ketju.first << endl;
            }
        }

        else if (komento.hae_kentta(0) == "myymalat" && komento.kenttien_lukumaara() == 2) {
            // Kaydaan lapi ketjulistaa, kunnes loydetaan haluttu ketju ja tulostetaan sen
            // kaikki myymalat ja lopetetaan
            string ketju = komento.hae_kentta(1);

            if (kauppalista.count(ketju) == 0) {
                cout << "Virhe: etsittya myymalaa ei loydy." << endl;
                continue; // Lopetetaan komennon suoritus tahan
            }

            for (auto ketjuhaku : kauppalista) {

                if (ketjuhaku.first == ketju) {

                    for (auto kauppa : ketjuhaku.second) {
                        cout << kauppa.first << endl;
                    }
                    break; // Optimoinnin vuoksi lapikayminen lopetetaan tahan
                }
            }
        }

        else if (komento.hae_kentta(0) == "halvin" && komento.kenttien_lukumaara() == 2) {
            vector<pair<string,string>> halvimmat; // Vektori johon tallennetaan halvimmat {ketju,kauppa} yhdistelmat
            string nimi = komento.hae_kentta(1); // etsittavan tuotteen nimi
            double halvin = 0; // Muuttuja, johon tallennetaan halvimman tuotteen hinta
            bool bit = false; // Apumuuttuja tuotteiden olemassaolon kasittelyyn

            for (auto ketjut : kauppalista) {

                for (auto kaupat : ketjut.second) {

                    for (auto tuotteet : kaupat.second) {

                        if (tuotteet.tuotenimi == nimi) {

                            if (!bit) {
                                halvin = tuotteet.hinta; // asetetaan hinnalle jokin alkuarvo
                            }

                            bit = true;
                            double hinta = tuotteet.hinta;

                            if (hinta < halvin && hinta > 0) {
                                halvimmat.clear();
                                halvin = hinta;
                                halvimmat.push_back({ketjut.first, kaupat.first});
                            }

                            else if (hinta == halvin && hinta > 0) {
                                halvin = hinta;
                                halvimmat.push_back({ketjut.first, kaupat.first});
                            }
                        }
                    }
                }
            }

            if (bit == false) {
                cout << "Tuote ei kuulu valikoimiin." << endl;
            }

            else if (halvimmat.empty()) {
                cout << "Tuote on tilapaisesti loppu kaikkialta." << endl;
            }

            else { // Tulostus, kun ainakin yksi halvin hinta loytyy
                cout << fixed << setprecision(2) << halvin << " euroa" << endl;

                for (auto parit : halvimmat) {
                    cout << parit.first << " " << parit.second << endl;
                }
            }
        }

        else if (komento.hae_kentta(0) == "tuotevalikoima" && komento.kenttien_lukumaara() == 3) {
            string ketju = komento.hae_kentta(1);
            string sijainti = komento.hae_kentta(2);

            if (kauppalista.count(ketju) == 0) {
                cout << "Virhe: kauppaketjua ei ole olemassa." << endl;
                continue;
            }

            else if (kauppalista[ketju].count(sijainti) == 0) {
                cout << "Virhe: kyseista kauppaa ei ole tassa kauppaketjussa." << endl;
                continue;
            }

            vector<pair<string,double>> tuotetiedot;

            for (auto ketjut : kauppalista) {

                if (ketjut.first == ketju) {

                    for (auto kaupat : ketjut.second) {

                        if (kaupat.first == sijainti) {

                            for (auto tuotteet : kaupat.second) {
                                tuotetiedot.push_back({tuotteet.tuotenimi, tuotteet.hinta});
                            }
                        }
                    }
                }
            }

            sort(tuotetiedot.begin(), tuotetiedot.end()); // Lajitellaan tuotteet aakkosjarjestykseen

            for (auto tuotetieto : tuotetiedot) { // Kaydaan lapi kaikki tuotteet

                if (tuotetieto.second != -1) {
                    cout << fixed << setprecision(2)
                         << tuotetieto.first << " " << tuotetieto.second << endl;
                }
                else { // Korvataan loppuneiden tuotteiden hinta sanalla "loppu"
                    cout << tuotetieto.first << " " << "loppu" << endl;
                }
            }
        }

        else if (komento.hae_kentta(0) == "tuotenimet" && komento.kenttien_lukumaara() == 1) {
            // Luodaan vektori, johon kerataan kaikkien tuotteiden nimet, mutta ei lisata vektoriin
            // jo vektorissa olevia samannimisia tuotenimia.
            vector<string> tuotenimet;

            for (auto ketjut : kauppalista) {

                for (auto kaupat : ketjut.second) {

                    for (auto tuotteet : kaupat.second) {

                        auto iter = find(tuotenimet.begin(), tuotenimet.end(), tuotteet.tuotenimi);

                        if (iter != tuotenimet.end()) { // Mikali tuotenimi on jo vektorissa
                            iter = tuotenimet.begin(); // Siiretaan iteraattori takaisin vektorin alkuun
                        }

                        else { // Mikali tuotenimea ei loytynyt vektorista, lisataan se sinne
                            tuotenimet.push_back(tuotteet.tuotenimi);
                        }
                    }
                }
            }

            sort(tuotenimet.begin(), tuotenimet.end()); // Asetetaan tuotenimet aakkosjarjestykseen

            for (auto nimet : tuotenimet) { // Tuotenimien tulostus
                cout << nimet << endl;
            }
        }

        else {
            cout << "Virhe: tuntematon komento tai virhe komennossa!" << endl;
        }
    }
}

bool tiedostonluku(const string& tiedostonimi, ketjulista& lista) {
    // Funktio yrittaa lukea halutun tiedoston olettaen sen sisaltavan
    // tuotetiedot puolipistein eroteltuina. Jos tiedoston lukeminen ei onnistu
    // palauttaa falsen, muulloin yrittaa lukea tiedoston olettaen sen olevan
    // virheeton ja palauttaa truen.

    ifstream tiedosto(tiedostonimi);

    if (!tiedosto) { // Mikali tiedostonluku epaonnistuu
        return false;
    }

    // Maaritellaan tarvittavat muuttujat
    Splitter halkoja;
    Tuote tuote;

    ketjulista ketjut; // map<string,map>
    liikelista liikkeet; // map<string,vector>

    string ketju;
    string liike;
    string tuotenimi;
    string hinta_string;
    double hinta;

    // Oletetaan, etta tiedostossa ei ole virheita, joten
    // virhetarkasteluja tiedoston sisallolle ei tehda.
    // Kaydaan lapi tiedoston rivit

    for (string rivi;getline(tiedosto, rivi);) {

        halkoja.aseta_paloiteltava_merkkijono(rivi);
        halkoja.paloittele(';');

        // Poimitaan tiedostorivilta tiedot muuttujiin
        ketju = halkoja.hae_kentta(0);
        liike = halkoja.hae_kentta(1);
        tuotenimi = halkoja.hae_kentta(2);
        hinta_string = halkoja.hae_kentta(3);

        if (hinta_string != "loppu") {
            hinta = stod(hinta_string);
            tuote = {tuotenimi, hinta};
        }

        else {
            tuote = {tuotenimi, -1}; // Jos tuote on loppu, sen hinta on -1 (double)
        }

        if ((ketjut.empty()) || ketjut.count(ketju) == 0) { // ei loydeta ketjua ketjuista
            liikkeet.clear();
            liikkeet.insert({liike, {tuote}});
            ketjut.insert({ketju, liikkeet});
        }

        else if (ketjut.at(ketju).count(liike) == 0) { // jos kauppaa ei loydy ketjusta
            ketjut.at(ketju).insert({liike, {tuote}});
        }

        else {
            for (auto valittu_tuote : ketjut.at(ketju).at(liike)) {

                // Tarkistetaan onko tuotelistassa jo samannimisia tuotteita
                if (valittu_tuote.tuotenimi == tuotenimi) {
                    tuotelista& vektori = ketjut.at(ketju).at(liike); // Luodaan viitemuuttuja tuotevektoriin
                    auto iter = vektori.begin();
                    vektori.erase(iter); // Poistetaan olemassa oleva tuote
                }
            }
            ketjut.at(ketju).at(liike).push_back(tuote); // Lisätään uusi tuote vektoriin
        }
    }

    tiedosto.close(); // Suljetaan viela tiedosto muistin vapauttamiseksi
    lista = ketjut; // Lopuksi tallennetaan valmis kauppalista main-funktion muuttujaan
    return true; // Lopuksi palautetaan tosi onnistumisesta
}
