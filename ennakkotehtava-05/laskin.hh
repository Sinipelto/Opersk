// Laskinmoduulin julkinen rajapinta

// Laskinmoduulin kirjastotiedosto

#ifndef LASKIN_HH
#define LASKIN_HH

using namespace std;

class Laskin {
public:
    Laskin();

    double yhteenlasku(const double &luku1, const double &luku2);

    double vahennyslasku(const double &luku1, const double &luku2);

    double kertolasku(const double &luku1, const double &luku2);

    double jakolasku(const double &luku1, const double &luku2);

private:
};

#endif // LASKIN_HH
