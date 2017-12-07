#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

int main() {
    // Toimii linux-järjestelmässä, muttei windows-järjestelmässä,
    // käyttää joko /dev/random tai /dev/urandom

    random_device d; // Haetaan todellinen satunnaisarvo (ei-pseudo)
    mt19937 mt(d()); // Luodaan satunnaislukugeneraattori seedillä d
    uniform_int_distribution<int> dist(0,100); // Luvut välillä 0-100

    for (int i=1;i<101;++i) { // Generoidaan 100 satunnaista kokonaislukua
        cout << setw(3) << dist(mt) << " ";
        if (i % 10 == 0) {
            cout << "\n";
        }
    }

    cout << endl;

    return 0;
}
