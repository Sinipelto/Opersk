#include "pino.hh"
#include <iostream>

using namespace std;

int main() {
    // Pääfunktio testaukseen

    Pino<int> pino;
    Pino<double> doublepino;
    Pino<string> sanapino;

    pino.print(); // Testitulostus tyhjälle listalle
    // Lisätään pari alkiota
    doublepino.push_front(5.5);
    doublepino.push_front(4.4478);
    doublepino.print();
    pino.print();
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

    pino.pop_front();
    pino.print();

    cout << "Lista takaperin" << endl;
    pino.takaperin();
    pino.print();

    pino.pop_front();
    pino.print();

    pino.takaperin();
    pino.print();
    cout << "Koko: " << pino.size() << endl;

    sanapino.push_front("hello");
    sanapino.push_front("world");

    sanapino.takaperin();
    sanapino.print();

    return 0;
}
