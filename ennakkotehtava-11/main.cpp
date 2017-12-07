#include "pino.hh"
#include <iostream>

using namespace std;

int main() {
    // Pääfunktio testaukseen
    int poistettu;
    Pino pino;

    pino.print(); // Testitulostus tyhjälle listalle
    // Lisätään pari alkiota
    pino.push_front(50);
    pino.push_front(10);
    pino.push_front(192);
    pino.push_front(19);
    pino.print();

    cout << "Listan koko: ";
    cout << pino.size() << endl;

    // Kokeillaan ylittää listan koko
    pino.push_front(40);
    pino.push_front(33);
    pino.push_front(22);
    pino.print();

    pino.pop_front(poistettu);
    pino.print();

    cout << "Lista takaperin" << endl;
    pino.takaperin();
    pino.print();

    pino.pop_front(poistettu);
    pino.print();

    pino.takaperin();
    pino.print();
    cout << "Koko: " << pino.size() << endl;

    return 0;
}
