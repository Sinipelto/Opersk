// Ennakkotehtava 04
// Ystavyyssuhteet

#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, map<int, string>> lajit = {
        { "Keihas", {
              { 1, "Heimo Heittaja" },
              { 2, "Kalle Keihas" },
              { 3, "Tom of Finland" }
          }},
        { "Seivas", {
              {1, "Hilkka Hyppaaja" },
              {2, "Taina Tanko" },
              {3, "Sinikka Seivas"}
          }},
        { "Kuula", {
              { 1, "Kalevi Kuula" },
              { 2, "Pete Kauppinen" },
              { 3, "Simo Jayha" }
          }}
    };

    string syote = "";
    int arvo = 0;

    while (arvo != -1) {
        cout << "t: tulosta, l: lisaa kilpailija" << endl;
        getline(cin, syote);

        if (syote == "t") {

            for (auto laji : lajit) {
                cout << laji.first << endl;
                auto sijoitus_ja_nimi = laji.second;
                for (auto sijoitukset : sijoitus_ja_nimi) {
                    cout << sijoitukset.first << ". " << sijoitukset.second << endl;
                }
                cout << endl;
            }}

        else if (syote == "l") {
            string laji = "";
            string kilpailija = "";
            cout << "Syota laji:" << endl;
            getline(cin, laji);

            int lajin_kilpailijoiden_maara = lajit[laji].size();

            cout << "Syota kilpailija:" << endl;
            getline(cin, kilpailija);

            lajit[laji][lajin_kilpailijoiden_maara + 1] = kilpailija;
        }

        else {
            cout << "Virhe: Tuntematon syote!" << endl;
        }
    }

}
