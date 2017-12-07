#ifndef PAAIKKUNA_HH
#define PAAIKKUNA_HH

#include <QMainWindow>

namespace Ui {
class Paaikkuna;
}

class Paaikkuna : public QMainWindow
{
    Q_OBJECT

public:
    explicit Paaikkuna(QWidget *parent = 0);
    ~Paaikkuna();

public slots:
    void set_progress(int value=20);

private slots:
    void on_value_a_textChanged(const QString &arg1);

    void on_value_b_textChanged(const QString &arg1);

    void on_value_c_textChanged(const QString &arg1);

    void on_solvebutton_clicked();

private:
    Ui::Paaikkuna *ui;
    int a_;
    int b_;
    int c_;
};

#endif // PAAIKKUNA_HH
