#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>

class Popup : public QWidget {
    Q_OBJECT

    // Свойство полупрозрачности
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

  private:
    QLabel label;        // Label с сообщением
    QGridLayout layout;  // Размещение для лейбла
    QPropertyAnimation animation;  // Свойство анимации для всплывающего сообщения
    double popupOpacity;       // Свойства полупрозрачности виджета
    QTimer * timer = nullptr;  // Таймер, по которому виджет будет скрыт
    QPoint center;

    static Popup * m_instance;
    bool needCorrection = true;

  public:
    static Popup * Instance();

    void updateGeometry();
    void updateCenter(const QPoint center);

  private:
    explicit Popup(QWidget * parent = nullptr);
    ~Popup() = default;

    void setPopupOpacity(double opacity);
    double getPopupOpacity() const;

  protected:
    void paintEvent(QPaintEvent * event);  // Фон будет отрисовываться через метод перерисовки

  public slots:
    void setPopupText(const QString & text);  // Установка текста в уведомление
    void show();  // Собственный метод показа виджета
                  // Необходимо для преварительной настройки анимации

  private slots:
    void hideAnimation();  // Слот для запуска анимации скрытия
    void hide();  // По окончании анимации, в данном слоте делается проверка, виден ли виджет, или
                  // его необходимо скрыть
};
