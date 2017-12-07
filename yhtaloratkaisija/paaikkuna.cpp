#include "paaikkuna.hh"
#include "ui_paaikkuna.h"

Paaikkuna::Paaikkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Paaikkuna),
    a_(0),
    b_(0),
    c_(0)
{
    ui->setupUi(this);
    ui->progressBar->reset();
    ui->errorlabel->clear();
    ui->diskriminantti->clear();
    ui->value_x1->setDigitCount(10);
    ui->value_x2->setDigitCount(10);

}

Paaikkuna::~Paaikkuna()
{
    delete ui;
}

void Paaikkuna::set_progress(int value) {
    ui->progressBar->setValue(value);
}

void Paaikkuna::on_value_a_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    a_ = value;
}

void Paaikkuna::on_value_b_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    b_ = value;
}

void Paaikkuna::on_value_c_textChanged(const QString &arg1)
{
    int value = arg1.toInt();
    c_ = value;
}


void Paaikkuna::on_solvebutton_clicked()
{    
    ui->errorlabel->clear();
    ui->value_x1->display(0);
    ui->value_x2->display(0);

    if (a_ == 0 and b_ == 0 and c_ == 0) {
        ui->errorlabel->setText("Anna kelvolliset luvut");
        return;
    }

    ui->progressBar->setValue(20);

    double diskriminantti = sqrt(pow(b_,2) - (4.0 * a_ * c_));
    QString disk_text;
    disk_text.setNum(diskriminantti, 'f', 6);
    ui->diskriminantti->setText(disk_text);

    if (disk_text == "nan") {
        ui->errorlabel->setText("Virhe: ei-reaalinen tulos");
        return;
    }

    double x1 = (- (b_ + diskriminantti) / 2.0 * a_);
    double x2 = (- (b_ - diskriminantti) / 2.0 * a_);


    ui->value_x1->display(x1);
    ui->value_x2->display(x2);

    ui->progressBar->setValue(100);

}
