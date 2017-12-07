#include "pino.hh"
#include <iostream>

using namespace std;

int main() {
    // Pääfunktio tietorakenteen testausta varten
    int poistettu;
    Pino pino;
    cout << "lisataan alkio arvolla 50 alkuun" << endl;
    pino.push_front(50);
    pino.print();

    cout << "lisataan alkio 20 alkuun" << endl;
    pino.push_front(20);
    pino.print();

    cout << "lisataan alkio arvolla 12 alkuun" << endl;
    pino.push_front(12);
    pino.print();

    cout << "lisataan alkio arvolla 44 alkuun" << endl;
    pino.push_front(44);
    pino.print();

    cout << "poistetaan alkio pinon alusta" << endl;
    pino.pop_front(poistettu);
    pino.print();
    cout << "poistetaan toinenkin alkio" << endl;
    pino.pop_front(poistettu);
    pino.print();

    cout << "lisataan muutama alkio" << endl;
    pino.push_front(22);
    pino.push_front(22);
    pino.push_front(16);
    pino.push_front(77);
    pino.print();
    cout << "kaannetaan alkiot takaperin" << endl;
    pino.takaperin();
    pino.print();

    return 0;
}

