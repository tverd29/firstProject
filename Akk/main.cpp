#include <QApplication>
#include <QDir>
#include <QTranslator>

#include "Source/Settings/settings.h"
#include "Source/akkwindow.h"

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    auto settings = Settings::Instance();
    settings->initLanguages();
    auto langs = settings->getLanguages();
    auto lang  = settings->getLanguage();
    QTranslator translator;

    if (lang.isEmpty()) {
        lang = QLocale::system().name();
        if (!langs.contains(lang)) {
            lang = "en_US";
        }
        settings->setLanguage(lang);
    }

    if (translator.load("akk_" + lang, QDir::currentPath() + "/Language")) {
        qApp->installTranslator(&translator);
    }

    AkkWindow w;
    w.show();

    return a.exec();
}
