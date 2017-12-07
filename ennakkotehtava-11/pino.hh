#ifndef PINO_HH
#define PINO_HH

// Linkkilistojen käsittely kiinteinä
// listoina on hyvin hankalaa ja epäkäytännöllistä,
// kuten tästä ohjelmasta voidaan huomata.
// Kun listan kokoa tarvitsee muuttaa, joudutaan alustamaan
// uusi lista avuksi.

class Pino {
public:
    Pino();

    ~Pino();

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

    // Palauttaa true jos listarakenne on täynnä
    bool full() const;

private:
    int *taulu_;
    unsigned int size_;
    unsigned int size_max_;
};

#endif // PINO_HH
