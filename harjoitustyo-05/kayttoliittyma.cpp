// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

// Tämä on ohjelman käyttöliittymämoduuli, joka
// sisältää tarvittavan komentorivikäyttöliittymän
// sekä osaa tulkita käyttäjän antamia syötteitä
// ja suorittaa halutut komennot ohjelmassa.

#include "kayttoliittyma.hh"

using namespace std;


void kayttoliittyma(Rakenne& reseptit) {
    // Käyttöliittymäfunktio, jossa ohjelman varsinainen
    // käyttöliittymä suoriutuu. Lopetuskäskyllä ohjelman hallinta
    // siirtyy takaisin main-funktioon.

    Rakenne reppu; // Alustetaan repulle tietorakenne
    string syoterivi;

    // Määritellään regex-säännöt
    regex regex_lopeta(tyhja + "loppu" + tyhja);
    regex regex_nollaa(tyhja + "reppu" + tyhja);
    regex regex_tulosta(tyhja + "tulostareppu" + tyhja);
    regex regex_reppu(tyhja + "reppu" + tyhja_1 + "(" + sana + tyhja + ")" + "+" + tyhja);
    regex regex_askartelu(tyhja + "askarreltavissa" + tyhja + sana + tyhja);
    regex regex_materiaali(tyhja + "materiaalit" + tyhja_1 + "(" + sana + ")"+ "+" + tyhja);

    while (true) {
        //cout << tyhja + "reppu" + tyhja_1 + "(" + sana + tyhja_1 + ")" + "+" + tyhja << endl;
        cout << "testikayttoliittyma> ";
        getline(cin, syoterivi); // Luetaan käyttäjän syöte

        if (regex_match(syoterivi, regex_lopeta)) {
            // Käyttöliittymän suoritus lopetetaan
            return;
        }

        else if (regex_match(syoterivi, regex_tulosta)) {
            // Komento tulostaa repussa sijaitsevat tavarat.
            reppu.tulosta_ekat();
        }

        else if (regex_match(syoterivi, regex_nollaa)) {
            // Komento tyhjentää repun sisällön.
            reppu.tyhjenna();
            cout << "Reppu tyhjennetty." << endl;
        }

        else if (regex_match(syoterivi, regex_reppu)) {
            // Komento tyhjentää repun ja asettaa sinne uuden
            // halutun sisällön.
            Rakenne tavarat;
            if (!tavarat.aseta_sisalto(syoterivi, "reppu")) {
                cout << "Virhe: toistuvia tuotteita havaittu." << endl;
                reppu.tyhjenna();
                continue;
            }

            if (!reseptit.lista_listassa(tavarat)) {
                cout << "Virhe: Tavaraa ei ole olemassa." << endl;
                reppu.tyhjenna();
                continue;
            }

            reppu.aseta_sisalto(syoterivi, "reppu");
            cout << "Repun sisalto asetettu." << endl;
        }

        else if (regex_match(syoterivi, regex_askartelu)) {
            string esine = poimi_teksti(syoterivi, "askarreltavissa");

            if (!reseptit.onko_listassa(esine)) {
                cout << "Virhe: esinetta tai materiaalia ei ole olemassa." << endl;
                continue;
            }

            else if (reppu.onko_eka(esine)) {
                // Mikäli esine löytyy jo valmiiksi repusta
                cout << "On askarreltavissa." << endl;
            }

            else if (reppu.askarreltavissa(esine, reseptit)) {
                // Mikäli kaikki tarvittavat materiaalit löytyvät repusta
                cout << "On askarreltavissa." << endl;
            }

            else {
                cout << "Ei ole askarreltavissa." << endl;
            }
        }

        else if (regex_match(syoterivi, regex_materiaali)) {
            string esine = poimi_teksti(syoterivi, "materiaalit");

            if (!reseptit.onko_listassa(esine)) {
                cout << "Virhe: esinetta ei ole olemassa." << endl;
                continue;
            }

            reseptit.tulosta_materiaalit(esine);
        }

        else {
            // Mikäli komento oli virheellinen
            cout << "Virhe: virheellinen tai tuntematon komento." << endl;
        }
    }
}


string poimi_teksti(string& syote, const string& komento) {
    // Poistaa syötteestä komennon ja palauttaa
    // sen parametrin merkkijonona oletus= 1 parametri.
    size_t sana = syote.find(komento);
    syote.erase(sana, komento.size());
    while (syote.find(" ") != string::npos) {
        syote.erase(syote.find(" "), 1);
    }
    return syote;
}
