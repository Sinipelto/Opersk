#include <iostream>
#include <map>
#include <string>

using namespace std;
using luettelo = map<string,string>;

int laske_nimet(const luettelo &puhelinluettelo, char nimen_alkukirjain, luettelo::const_iterator iter);

int main() {
    luettelo puhluettelo = {{"tindertoni","1234"},{"teemu","5542"},{"hilleri","4531"},{"simo","5693"},{"petteri","2201"}};
    cout << laske_nimet(puhluettelo, 't', puhluettelo.begin()) << endl;

    return 0;

}

int laske_nimet(const luettelo& puhelinluettelo,
                char nimen_alkukirjain, luettelo::const_iterator iter) {

    if (iter == puhelinluettelo.end()) {
        return 0;

    } else {
        bool onko = iter->first.at(0) == nimen_alkukirjain;

        iter++;
        return int(onko) + laske_nimet(puhelinluettelo, nimen_alkukirjain, iter);
    }
}
