#include "start_page.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start_page w;
    w.show();
    return a.exec();
}
