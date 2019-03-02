#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QTranslator>

#include "Include\akkwindow.h"

int main(int argc, char * argv[]) {
    QApplication a(argc, argv);

    QSettings settings("settings_conf", QSettings::IniFormat);
    settings.beginGroup("main_settings");
    QString lang = settings.value("language", "").toString();
    QTranslator translator;
    if (lang.isEmpty()) {
        lang = QLocale::system().name();
        settings.setValue("language", lang);
    }
    settings.endGroup();

    QString z = QDir::currentPath();
    QString y = "V:/Git/First/Akk";
    if (translator.load("akk_" + lang, y)) {
        qApp->installTranslator(&translator);
    }

    AkkWindow w;
    w.show();

    return a.exec();
}
