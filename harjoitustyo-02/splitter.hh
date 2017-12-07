// Splitter-luokan kirjasto
// (c) Aps ( mallivastaus )

#ifndef SPLITTER_HH
#define SPLITTER_HH

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

// unsigned int -tyypin avulla voidaan käsitellä arvoja,
// jotka ovat suurempia tai yhtäsuuria kuin nolla (etumerkittömiä),
// eli siis luonnollisia lukuja (ℕ).
const unsigned int SPLITTER_VIRHE = 0;

class Splitter {
  public:
    Splitter(const string& paloiteltava_merkkijono = "");

    void aseta_paloiteltava_merkkijono(const string& merkkijono);

    unsigned int paloittele(char erotinmerkki, bool ohita_tyhjat = false);

    unsigned int kenttien_lukumaara() const;

    string hae_kentta(unsigned int kentan_numero) const;

  private:
    string paloiteltava_;
    vector<string> kentat_;
};

#endif // SPLITTER_HH
