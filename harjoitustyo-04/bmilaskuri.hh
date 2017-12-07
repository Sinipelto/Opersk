#ifndef BMILASKURI_HH
#define BMILASKURI_HH

#include <QMainWindow>

namespace Ui {
class Bmilaskuri;
}

class Bmilaskuri : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bmilaskuri(QWidget *parent = 0);
    ~Bmilaskuri();

    void laske_bmi(const int& paino, const int& pituus);
    void aseta_tulkinta();

public slots:
    void aseta_alkutila();
    void aseta_nainen();
    void aseta_mies();
    void tarkista_arvo(int arvo);

private:
    Ui::Bmilaskuri *ui;
    bool sukupuoli_; // true = nainen, false = mies
    double bmi_;
};

#endif // BMILASKURI_HH
