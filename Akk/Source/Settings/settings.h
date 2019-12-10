#pragma once

#include <QSettings>

class Settings : public QObject {
    Q_OBJECT

  private:
    QSettings * settings = nullptr;
    QHash<QString, QString> languages;

    static Settings * m_settings;

  public:
    static Settings * Instance();

    void initLanguages();

    const QString getLanguage();
    void setLanguage(const QString & language);

    const QString getDefaultFile();
    const QString getDefaultFileAlias();
    void setDefaultFile(const QString & file);

    const QHash<QString, QString> getLanguages();
    const QString getLanguageAlias();

  private:
    explicit Settings(QObject * parrent = nullptr);
    ~Settings() = default;
};
