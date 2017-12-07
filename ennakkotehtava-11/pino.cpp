#include "pino.hh"
#include <iostream>

using namespace std;

Pino::Pino() {
    size_ = 0;
    // Aloituskoko on 1
    size_max_ = 1;
    taulu_ = new int[size_max_];
}

Pino::~Pino() {
    delete[] taulu_;
    size_ = 0;
}

bool Pino::empty() const {
    // Palauttaa tiedon, onko lista tyhjä
    if (size_ == 0) {
        return true;
    }return false;
}

void Pino::print() const {
    // Tulostusmetodi listalle.
    // Formaatti: { a, b, c, d,..., z }
    cout << "{";
    for (unsigned int i=0;i < size_;i++) {
        if (i != 0) {
            cout << ",";
        }
        cout << " ";
        cout << taulu_[i];
    }
    cout << " }" << endl;
}

void Pino::push_front(const int &lisattava) {
    if (full()) {
        // Laajennetaan taulukkoa, mikäli täynnä
        size_max_ += 5;
        int *taulu2 = new int[size_max_];
        for (unsigned int i=0;i < size_;i++) {
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

bool Pino::full() const {
    // Palauttaa tiedon, onko lista täynnä (kiinteä koko)
    if (size_ == size_max_) {
        return true;
    }return false;
}

bool Pino::pop_front(int &poistettu) {
    if (empty()) {
        // Jos lista on tyhjä
        return false;
    }
    // Kirjataan poistettava alkio ylös
    poistettu = taulu_[0];

    size_max_ = size_ + 3; // Säädetään maksimikoko uudelleen
    int *taulu2 = new int[size_max_];
    for (unsigned int i=1;i<size_;i++) {
        taulu2[i-1] = taulu_[i];
    }

    delete[] taulu_; // Vapautetaan vanhan taulukon muisti
    taulu_ = taulu2;
    size_--;
    return true;
}

int Pino::size() const {
    return size_;
}

void Pino::takaperin() {
    // Metodi kääntää listan alkiot takaperoiseen järjestykseen
    if (size() <= 1) {
        return;
    }

    int* taulu2 = new int[size_max_];
    int j = size_ - 1;
    for (unsigned int i=0;i<size_;i++) {
        taulu2[j] = taulu_[i];
        j--;
    }
    delete[] taulu_;
    taulu_ = taulu2;
}
