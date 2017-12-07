// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

#ifndef RAKENNE_HH
#define RAKENNE_HH

#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

using namespace std;


// Vastaa vector<pair<string,string>>
class Rakenne {

public:
    Rakenne();
    ~Rakenne();
    bool lisaa_alkio(const string&eka, const string& toka);
    bool aseta_sisalto(string syote, const string& poistettava);
    void tyhjenna();
    void tulosta_ekat() const;
    void tulosta_materiaalit(const string& esine) const;
    bool tyhja() const;
    bool askarreltavissa(const string& esine, const Rakenne& reseptit) const;
    bool onko_pari(const string& eka, const string& toka) const;
    bool onko_listassa(const string& sana) const;
    bool onko_eka(const string& sana) const;
    bool onko_toka(const string& sana) const;
    bool lista_listassa(const Rakenne& lista);

private:
    struct Alkio {
        string eka;
        string toka;
        shared_ptr<Alkio> seuraava;
    };

    size_t koko_;
    shared_ptr<Alkio> ensimmainen_ptr_;
    shared_ptr<Alkio> viimeinen_ptr_;

};

#endif // RAKENNE_HH
