//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include "todo_rakenne.hh"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


Todo::Todo() {
}

// ----- Uuden tehtavan lisääminen todo-listalle ------------------------------

bool Todo::lisaa_tehtava(int kiireellisyys, const string& kuvaus) {
    if ( kiireellisyys < MIN_KIIREELLISYYS
         or kiireellisyys > MAX_KIIREELLISYYS ) {

        return false;
    }

    if ( todo.find(kiireellisyys) == todo.end() ) {
        todo.insert( { kiireellisyys, {} } );
    }

    todo.at(kiireellisyys).push_back(kuvaus);

    return true;
}


// ----- Tehtävien tulostamiseen liittyvät metodit ja apumetodit --------------

void Todo::tulosta_lista_rekursiolla(
        int rivinumero, int kiireellisyys,
        Tehtavalista::const_iterator it,
        Tehtavalista::const_iterator loppu) const {

    if ( it == loppu ) {
        return;

    } else {

        cout << setw(2) << rivinumero << ". taso " << kiireellisyys << ": "
             << '"' << *it << '"' << endl;

        ++it;
        ++rivinumero;

        tulosta_lista_rekursiolla(rivinumero, kiireellisyys, it, loppu);
    }
}


void Todo::tulosta_mappi_rekursiolla(Todo_map::const_reverse_iterator it,
                                     Todo_map::const_reverse_iterator loppu,
                                     int rivinumero) const {
    if ( it ==loppu ) {
        return;

    } else {

        int kiireellisyystaso = it->first;

        tulosta_lista_rekursiolla(rivinumero, kiireellisyystaso,
                                  it->second.begin(), it->second.end());

        rivinumero += it->second.size();
        ++it;

        tulosta_mappi_rekursiolla(it, loppu, rivinumero);
    }
}


void Todo::listaa_tehtavat() const {
    tulosta_mappi_rekursiolla(todo.rbegin(), todo.rend(), 1);
}

// ----- Tehtävälistan tallentaminen tiedostoon apumetodeineen ----------------

bool Todo::talleta_lista_tiedostoon_rekursiolla(
        Tehtavalista::const_iterator it,
        Tehtavalista::const_iterator loppu,
        int taso,
        ofstream& virta) const {

    if ( not virta ) {
        return false;

    } else if ( it == loppu ) {
        return true;

    } else {

        virta << taso << ";" << *it << endl;

        ++it;

        return talleta_lista_tiedostoon_rekursiolla(it, loppu, taso, virta);
    }
}


bool Todo::talleta_mappi_tiedostoon_rekursiolla(
        Todo_map::const_iterator it,
        Todo_map::const_iterator loppu,
        ofstream& virta ) const {

    if ( it == loppu ) {
        return true;

    } else {

        if ( not talleta_lista_tiedostoon_rekursiolla(
                 it->second.begin(), it->second.end(),
                 it->first, virta) ) {

            return false;
        }

        ++it;

        return talleta_mappi_tiedostoon_rekursiolla(it, loppu, virta);
    }
}


bool Todo::talleta_tiedostoon(ofstream& virta) const {
    return talleta_mappi_tiedostoon_rekursiolla(
                todo.begin(), todo.end(), virta);
}


bool Todo::onko_tyhja() const {
    // Palauttaa tiedon, onko tietorakenne tyhjä
    if (todo.empty()) {
        return true;
    }return false;
}


string Todo::poista_kiireellisin() {
    // Metodi poistaa rakenteesta aikaisimmin lisätyn
    // korkeimman kiireellisyystason tehtävän ja palauttaa
    // sen nimen stringinä. Olettaa, että todo ei ole tyhjä.

    string nimike;

    // Käydään läpi kiireellisyystasot 5-1
    for (int taso = 5; taso > 0 ; taso--) {

        // Etsitään, löytyykö kiireellisyystasoa
        if (todo.find(taso) != todo.end()) {
            Todo_map::iterator it = todo.end();
            it--; // mapin viimeinen indeksi
            nimike = *it -> second.begin(); // Poimitaan nimike
            it -> second.erase(it -> second.begin()); // Poistetaan aikaisimmin lisätty tehtävä
            if (it -> second.empty()) {
                // Poistetaan tyhjä kiireellisyystaso
                todo.erase(it);
            }
            break;
        }
    }
    return nimike; // Palautetaan tehtävänimike
}
