// TIE-02200 Ohjelmoinnin peruskurssi
// Harjoitustyö 05

#ifndef KAYTTOLIITTYMA_HH
#define KAYTTOLIITTYMA_HH

#include "rakenne.hh"
#include <iostream>
#include <string>
#include <regex>

const string tyhja("[[:space:]]*");
const string tyhja_1("[[:space:]]+");
const string sana("_*[[:alnum:]]+_*");

void kayttoliittyma(Rakenne& reseptit);
string poimi_teksti(string& syote, const string&komento);

#endif // KAYTTOLIITTYMA_HH
