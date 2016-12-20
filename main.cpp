#include "maineditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainEditor w;
    w.show();

    return a.exec();
}
