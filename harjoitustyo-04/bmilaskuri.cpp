#include "bmilaskuri.hh"
#include "ui_bmilaskuri.h"

Bmilaskuri::Bmilaskuri(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bmilaskuri),
    bmi_(0)
{
    ui->setupUi(this);
    ui->spin_pituus->setFocus(); // Malliohjelmassa fokus spinbox pituudessa
    aseta_alkutila(); // Luodessa asetetaan laskuri alkutilaan

    connect(ui->actionAlkutila, SIGNAL(triggered()), this, SLOT(aseta_alkutila()) );

    connect(ui->actionMies, SIGNAL(triggered()), this, SLOT(aseta_mies()) );

    connect(ui->actionNainen, SIGNAL(triggered()), this, SLOT(aseta_nainen()) );

    connect(ui->actionLopeta, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->spin_paino, SIGNAL(valueChanged(int)), this, SLOT(tarkista_arvo(int)));

    connect(ui->spin_pituus, SIGNAL(valueChanged(int)), this, SLOT(tarkista_arvo(int)));
}

Bmilaskuri::~Bmilaskuri()
{
    delete ui;
}

void Bmilaskuri::laske_bmi(const int& paino, const int& pituus) {
    // Muutetaan kokonaisluvut reaaliluvuiksi
    double m = paino;
    double l = pituus/100.0; // Muutetaan pituus metreiksi
    bmi_ = m / (l*l); // Lasketaan BMI

    QString bmi_text;
    // Asetetaan Qstring tekstin arvoksi bmi, max. tarkkuus 4 desimaalia->
    bmi_text.setNum(bmi_, 'g', 6);
    ui->arvo_indeksi->setText(bmi_text); // Asetetaan bmi näytölle
    aseta_tulkinta(); // Tehdään bmi:stä tulkinta
}

void Bmilaskuri::aseta_alkutila() {
    // Metodi resetoi bmilaskurin oletustilaan
    ui->spin_paino->setValue(0);
    ui->spin_pituus->setValue(0);
    sukupuoli_ = false;
    aseta_nainen();
}

void Bmilaskuri::aseta_mies() {
    // Metodi asettaa laskurin sukupuolen mieheksi
    if (!sukupuoli_) {
        ui->actionNainen->setChecked(false);
        ui->actionMies->setChecked(true);
        return;
    }
    sukupuoli_ = false;
    ui->actionNainen->setChecked(false);
    ui->actionMies->setChecked(true);
    ui->arvo_gender->setText("mies");
    aseta_tulkinta();
}

void Bmilaskuri::aseta_nainen() {
    // Metodi asettaa laskurin sukupuolen naiseksi
    if (sukupuoli_) {
        ui->actionNainen->setChecked(true);
        ui->actionMies->setChecked(false);
        return;
    }
    sukupuoli_ = true;
    ui->actionNainen->setChecked(true);
    ui->actionMies->setChecked(false);
    ui->arvo_gender->setText("nainen");
    aseta_tulkinta();
}

void Bmilaskuri::aseta_tulkinta() {
    // Metodi asettaa tulkinnan BMI:n ja
    // sukupuolen perusteella
    if (bmi_ == 0.0) {
        // Mikäli bmi on 0, sitä ei tulkita.
        return;
    }

    if (sukupuoli_) {
        // Jos nainen
        if (bmi_ <= 19.1) {
            ui->arvo_tulkinta->setText("alipainoa");
        }

        else if (bmi_ > 19.1 and bmi_ <= 25.8)  {
            ui->arvo_tulkinta->setText("normaali");
        }

        else if (bmi_ > 25.8 and bmi_ <= 27.3) {
            ui->arvo_tulkinta->setText("lievää ylipainoa");
        }

        else if (bmi_ > 27.3 and bmi_ <= 32.2) {
            ui->arvo_tulkinta->setText("ylipainoa");
        }

        else {
            ui->arvo_tulkinta->setText("paljon ylipainoa");
        }
    }

    else {
        // Jos mies
        if (bmi_ <= 20.7) {
            ui->arvo_tulkinta->setText("alipainoa");
        }

        else if (bmi_ > 20.7 and bmi_ <= 26.4) {
            ui->arvo_tulkinta->setText("normaali");
        }

        else if (bmi_ > 26.4 and bmi_ <= 27.8) {
            ui->arvo_tulkinta->setText("lievää ylipainoa");
        }

        else if (bmi_ > 27.8 and bmi_ <= 31.1) {
            ui->arvo_tulkinta->setText("ylipainoa");
        }

        else {
            ui->arvo_tulkinta->setText("paljon ylipainoa");
        }
    }
}

void Bmilaskuri::tarkista_arvo(int arvo) {
    // Tarkistaa, ettei pituus tai paino ole
    // asetettu nollaksi ja kutsuu bmi:n laskumetodia
    int paino = ui->spin_paino->value();
    int pituus = ui->spin_pituus->value();

    if (paino == 0 or pituus == 0 or arvo == 0) {
        bmi_ = 0.0;
        ui->arvo_indeksi->setText("-");
        ui->arvo_tulkinta->setText("-");
    }

    else {
        laske_bmi(paino, pituus);
    }
}
