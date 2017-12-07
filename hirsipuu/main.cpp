// Yksinkertainen hirsipuuohjelma toteutettuna C++:lla.
// Komentorivikayttoliittyma


#include <iostream>
#include <string>

using namespace std;

int main() {

    string arvattava; // Muuuttuja, jossa alkuperainen oikea sana
    string arvaus; // Muuttuja, joka on aluksi tyhja, mutta taydentyy arvauksilla
    string kirjain; // Tietynhetkinen arvattava kirjainmuuttuja
    string arvatut; // Merkkijono kaikista jo kertaalleen arvatuista kirjaimista
    int pituus; // Arvattavan sanan pituus
    int yritys = 0; // Yrityskertojen maara

    cout << "Tervetuloa hirsipuuhun! Syota arvattava sana ja sen jalkeen arvaa se.\n"
            "Virheellisista syotteista ja saman kirjaimen\narvaamisesta uudelleen ei "
            "rokoteta pisteita. 10 arvauskertaa. \n\n" << endl;

    cout << "Syota arvattava sana (ilman skandeja!): ";

    cin >> arvattava;
    cout << endl;
    pituus = arvattava.length();

    for (int i=0;i<15;i++) {
        cout << "\n" << endl;
    }
    cout << "Naytto puhdistettu.\n\n" << endl;

    for (int i = 0; i < pituus;i++) { // Alustetaan arvattu sana alaviivoilla
        arvaus += "_";
    }

    while (yritys <= 10) { // Paalohko, jossa arvaaminen suoritetaan

        cout << "Sinulla on " << (10-yritys) << " arvausta jaljella." << endl;
        cout << "Tahan mennessa arvattu: " << arvaus << endl;

        cout << "Syota arvattava kirjain: ";
        cin >> kirjain;
        cout << endl;

        if (kirjain.length() != 1) {
            cout << "Syota vain yksi merkki!\n" << endl;
            continue;
        }

        else if (arvatut.find(kirjain) != string::npos) {
            cout << "Kyseinen kirjain on jo arvattu!\n" << endl;
            continue;
        }


        else {

            try { // Tarkistetaan, onko syotetty merkki kokonaisluku
                stoi(kirjain); // Stoi toimii, koska tutkitaan vain yhtä merkkiä

            }

            catch (exception) { // Jos syote ei ole kokonaisluku, kaapataan poikkeus

                if (arvattava.find(kirjain) != string::npos) { // Mikali kirjain loytyy arvattavasta sanasta

                    string kopio = arvattava;

                    for (int i = 0;i < pituus;i++) {
                        if (kopio.at(i) == kirjain.at(0)) {
                            int sijainti = kopio.find(kirjain);
                            arvaus.replace(sijainti,1,kirjain);
                            kopio.replace(sijainti,1,"0");

                        }
                    }

                    cout << "Hyva! Oikea arvaus!\n" << endl;

                    if (arvaus.find("_") == string::npos) { // Mikali sanassa ei ole enaa tuntemattomia kirjaimia
                        cout << "Onneksi olkoon! Arvasit sanan!\n" << endl;
                        cout << "Sana oli " << "'" << arvattava << "'\n" << endl;
                        cout << "Sinulla kului " << yritys + 1 << " yrityskertaa." << endl;
                        return 0; // Ohjelman suoritus paattyy tahan
                    }

                }

                arvatut += kirjain;
                yritys++; // Kaytetaan yksi arvauskerta
                continue;

            }

            cout << "Syota vain kirjaimia!\n" << endl;

        }

        }

    cout << "Et arvannut sanaa. " << "Oikea sana olisi ollut: " << arvattava << endl;

    return 0;
}
