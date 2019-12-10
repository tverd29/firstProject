#include "settings.h"

Settings * Settings::m_settings = nullptr;

Settings * Settings::Instance() {
    if (!m_settings) {
        m_settings = new Settings();
    }
    return m_settings;
}

void Settings::initLanguages() {
    this->languages.insert("en_US", "English");
    this->languages.insert("ru_RU", "Русский");
}

void Settings::save() {
    this->tempDefaultFile = this->getDefaultFile();
    this->tempLanguage    = this->getLanguage();
}

void Settings::restore() {
    this->setDefaultFile(this->tempDefaultFile);
    this->setLanguage(this->tempLanguage);
}

const QString Settings::getLanguage() {
    return settings->value("language", QVariant()).toString();
}

void Settings::setLanguage(const QString & language) {
    settings->setValue("language", language);
}

const QString Settings::getDefaultFile() {
    return settings->value("defaultFile", QVariant()).toString();
}

const QString Settings::getDefaultFileAlias() {
    auto values = settings->value("defaultFile", QVariant()).toString().split('/');
    if (values.count() > 0) {
        return values.last();
    }
    return QString();
}

void Settings::setDefaultFile(const QString & file) {
    settings->setValue("defaultFile", file);
}

const QHash<QString, QString> Settings::getLanguages() {
    return this->languages;
}

const QString Settings::getLanguageAlias() {
    return this->languages.value(this->getLanguage());
}

Settings::Settings(QObject * parent) : QObject(parent) {
    this->settings = new QSettings("settings_conf", QSettings::IniFormat);
}
