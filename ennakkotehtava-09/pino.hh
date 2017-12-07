#ifndef PINO_HH
#define PINO_HH

#include <memory>

using namespace std;

class Pino {
public:
    Pino();

    // empty palauttaa true, jos linkitetty lista
    // ei sisällä yhtään alkiota.
    bool empty() const;

    // push front lisää parametrina syötetyn arvon linkkilistan alkuun
    void push_front(const int &lisattava);

    // Kääntää listan järjestyksen toisinpäin
    void takaperin();

    // pop front poistaa alkion listan alusta
    // jos poisto tapahtuu, palauttaa true
    bool pop_front(int &poistettu);

    // Tulostusmetodi debuggausta varten
    void print() const;

    // Palauttaa alkioiden määrän Pinossa
    int size() const;

private:
    struct Alkio {
        int arvo;
        shared_ptr<Alkio> edellinen_osoite;
        shared_ptr<Alkio> seuraava_osoite;
    };
    shared_ptr<Alkio> eka_osoite_;
    shared_ptr<Alkio> vika_osoite_;
    int alkiomaara_;
};

#endif
