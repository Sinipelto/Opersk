#include "laskin.hh"

using namespace std;

Laskin::Laskin() {

}

double Laskin::yhteenlasku(const double &luku1, const double &luku2){
    return (luku1 + luku2);
}

double Laskin::vahennyslasku(const double &luku1, const double &luku2) {
    return (luku1-luku2);
}

double Laskin::kertolasku(const double &luku1, const double &luku2) {
    return (luku1*luku2);
}

double Laskin::jakolasku(const double &luku1, const double &luku2) {
    return (luku1/luku2);
}
