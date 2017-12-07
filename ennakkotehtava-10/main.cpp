#include "lista.hh"
#include <iostream>

using namespace std;

int main() {
    // Pääfunktio tietorakenteen testaamiseen
    Lista lista;

    // Lisätään muutama alkio listaan
    lista.lisaa_alkio_loppuun("pelaa peleja");
    lista.lisaa_alkio_loppuun("hae toita");
    lista.lisaa_alkio_loppuun("pese pyykit");
    lista.lisaa_alkio_loppuun("siivoa");
    lista.lisaa_alkio_loppuun("jarjestele");
    // Tulostetaan lista
    lista.tulosta();
    cout << "\n";
    cout << "Poistetaan alkio 'siivoa'" << endl;
    lista.poista_alkio("siivoa");
    lista.tulosta();
    cout << endl;
    return 0;
}
