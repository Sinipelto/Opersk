//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include "todo_rakenne.hh"
#include <fstream>
#include <string>
#include <algorithm> // Tarvitaan count()

using namespace std;


// ----------------------------------------------------------------------------
// lue_tehtavatiedosto
// -------------------
// Funktio lukee parametrina saamansa tietovirran avulla tehtävälistatiedoston
// ja lisää sieltä saamansa tiedot tehtavarakenteeseen.  Jos tiedostossa
// on virheellisiä rivejä, funktion on palautettava false.  Jos tiedosto on
// virheetön, paluuarvon oltava true.  Tiedoston lukemin tämän funktion
// avulla EI SAA TULOSTAA NÄYTÖLLE MITÄÄN, sillä virheilmoitusten tulostuksesta
// on huolehdittu pääohjelmassa.
//
// KOKO TIEDOSTON LUKEMINEN ON TOTEUTETTAVA REKURSION AVULLA.  Tämä funktio,
// eikä sen avuksi itse toteutetut apufunktiot saa sisältää yhtään silmukka-
// rakennetta.  Silmukkarakenteet ovat tässä yhteydessä työn hylkäämisperuste.
//
// Funktion paluuarvo ja parametrien tyypit ja määrä on säilytettävä.
// ET SIIS SAA MUUTTAA LUE_TEHTAVATIEDOSTO-FUNKTION RAJAPINTAA.
// ----------------------------------------------------------------------------
bool lue_tehtavatiedosto(ifstream& virta, Todo& tehtavarakenne) {
    string rivi;

    // Luetaan rivi tiedostosta
    if (! getline(virta, rivi)) {
        // Jos tiedosto on luettu loppuun,
        // palautetaan tosi
        return true;
    }

    // Käydään läpi tiedostorivin virheettömyys

    // Puolipiste toisena
    if (not (rivi.at(1) == ';')) {
        return false;
    }

    // Poimitaan tehtävän nimike riviltä
    string tehtava = rivi.substr(2);

    // Tehtävänimike ei saa olla tyhjä tai sisältää
    // pelkästään välilyöntejä
    if (tehtava == "") {
        return false;
    }

    // Voidaan olettaa, että count palauttaa ei-negatiivisen kokonaisluvun
    else if (tehtava.size() == unsigned(count(tehtava.begin(), tehtava.end(), ' '))) {
        return false;
    }

    // Muutetaan rivin ensimmäinen merkki kokonaisluvuksi
    int kiiretaso = rivi.at(0) - '0';

    // Yritetään tallentaa tehtävä tehtävärakenteeseen
    if (! tehtavarakenne.lisaa_tehtava(kiiretaso, tehtava)) {
        return false;
    }

    // Palautetaan rekursiivisesti true tai false
    return lue_tehtavatiedosto(virta, tehtavarakenne);
}
