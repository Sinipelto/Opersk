#include "bmilaskuri.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bmilaskuri w;
    w.show();

    return a.exec();
}
