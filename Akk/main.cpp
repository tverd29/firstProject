#include <QApplication>
#include <QDir>
#include <QTranslator>

#include "Source/Settings/settings.h"
#include "Source/akkwindow.h"

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    QString lang = Settings::Instance()->getLanguage();
    QTranslator translator;
    if (lang.isEmpty()) {
        lang = QLocale::system().name();
        Settings::Instance()->setLanguage(lang);
    }

    if (translator.load("akk_" + lang, QDir::currentPath() + "/Language")) {
        qApp->installTranslator(&translator);
    }

    AkkWindow w;
    w.show();

    return a.exec();
}
