#ifndef PINO_HH
#define PINO_HH

#include <iostream>

// Linkkilistojen käsittely kiinteinä
// listoina on hyvin hankalaa ja epäkäytännöllistä,
// kuten tästä ohjelmasta voidaan huomata.
// Kun listan kokoa tarvitsee muuttaa, joudutaan alustamaan
// uusi lista avuksi.

using namespace std;

template <typename T>

class Pino {
public:
    Pino();

    // empty palauttaa true, jos linkitetty lista
    // ei sisällä yhtään alkiota.
    bool empty() const;

    // push front lisää parametrina syötetyn arvon linkkilistan alkuun
    void push_front(const T &lisattava);

    // Kääntää listan järjestyksen toisinpäin
    void takaperin();

    // pop front poistaa alkion listan alusta
    // jos poisto tapahtuu, palauttaa true
    bool pop_front();

    // Tulostusmetodi debuggausta varten
    void print() const;

    // Palauttaa alkioiden määrän Pinossa
    int size() const;

    // Palauttaa true jos listarakenne on täynnä
    bool full() const;

private:
    T *taulu_;
    int size_;
    int size_max_;
};

#endif // PINO_HH

template <typename T>

Pino<T>::Pino() {
    size_ = 0;
    // Aloituskoko on 1
    size_max_ = 1;
    taulu_ = new T[size_max_];
}

template <typename T>

bool Pino<T>::empty() const {
    // Palauttaa tiedon, onko lista tyhjä
    if (size_ == 0) {
        return true;
    }return false;
}

template <typename T>

void Pino<T>::print() const {
    // Tulostusmetodi listalle.
    // Formaatti: { a, b, c, d,..., z }
    cout << "{";
    for (int i=0;i < size_;i++) {
        if (i != 0) {
            cout << ",";
        }
        cout << " ";
        cout << taulu_[i];
    }
    cout << " }" << endl;
}
template <typename T>

void Pino<T>::push_front(const T &lisattava) {
    if (full()) {
        // Laajennetaan taulukkoa, mikäli täynnä
        size_max_ += 5;
        T *taulu2 = new T[size_max_];
        for (int i=0;i < size_;i++) {
            taulu2[i] = taulu_[i];
        }
        // Vapautetaan aikaisemman taulun muisti
        delete[] taulu_;
        taulu_ = taulu2; // Osoitin uuteen taulukkoon
    }

    for (int i=size_;i>0;i--) {
        // Siirretään kaikki alkiot yhdellä eteenpäin
        taulu_[i] = taulu_[i-1];
    }
    taulu_[0] = lisattava; // Lisätään uusi alkio listan alkuun
    size_++; // Kirjataan lisäys

}

template <typename T>

bool Pino<T>::full() const {
    // Palauttaa tiedon, onko lista täynnä (kiinteä koko)
    if (size_ == size_max_) {
        return true;
    }return false;
}

template <typename T>

bool Pino<T>::pop_front() {
    if (empty()) {
        // Jos lista on tyhjä
        return false;
    }

    size_max_ = size_ + 3; // Säädetään maksimikoko uudelleen
    T *taulu2 = new T[size_max_];
    for (int i=1;i<size_;i++) {
        taulu2[i-1] = taulu_[i];
    }

    delete[] taulu_; // Vapautetaan vanhan taulukon muisti
    taulu_ = taulu2;
    size_--;
    return true;
}

template <typename T>

int Pino<T>::size() const {
    return size_;
}

template <typename T>

void Pino<T>::takaperin() {
    // Metodi kääntää listan alkiot takaperoiseen järjestykseen
    if (size() <= 1) {
        return;
    }

    T *taulu2 = new T[size_max_];
    int j = size_ - 1;
    for (int i=0;i<size_;i++) {
        taulu2[j] = taulu_[i];
        --j;
    }
    delete[] taulu_;
    taulu_ = taulu2;
}
