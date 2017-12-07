#include "paaikkuna.hh"
#include "ui_paaikkuna.h"

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna)
{
    ui->setupUi(this);

    connect(ui->nollaus, SIGNAL( clicked() ),
            this, SLOT( nollaa_kaikki_arvot() ) );

    connect(ui->kmh_slider, SIGNAL( valueChanged(int) ),
            this, SLOT( aseta_naytto() ) );
}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::nollaa_kaikki_arvot() {
    ui->kmh_spinbox->setValue(0);
    ui->kmh_slider->setValue(0);
    ui->miles_lcd->display(0.0);
}

void Paaikkuna::aseta_naytto() {
    int value = ui->kmh_spinbox->value();
    double result = value*0.621371192;
    ui->miles_lcd->display(result);
}
