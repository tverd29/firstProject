#include <QApplication>

#include "akkwindow.h"

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);
    AkkWindow w;
    w.show();

    return a.exec();
}
