#include "loginwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Loginwidget w;
    w.show();
    return a.exec();
}
