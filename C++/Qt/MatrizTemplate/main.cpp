#include "matrizui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL, "C");
    MatrizUI w;
    w.show();
    return a.exec();
}
