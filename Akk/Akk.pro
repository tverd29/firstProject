#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T12:28:04
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Akk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Source/AkksModel/AccountItemDelegate.cpp \
    Source/Popup/Popup.cpp \
    Source/Utils/LineEdit.cpp \
    Source/settings.cpp \
    Source/settingsDialog.cpp \
    main.cpp \
    Source\akkwindow.cpp \
    Source\dialogaddedit.cpp \
    Source\coder.cpp \
    Source/AkksModel/AccountModel.cpp \
    Source/AkksModel/AccountView.cpp \
    Source/AkksModel/AccountItem.cpp \
    Source/AkksModel/AccountProxy.cpp

HEADERS += \
    Source/AkksModel/AccountItemDelegate.h \
    Source/Popup/Popup.h \
    Source/Utils/LineEdit.h \
    Source/settings.h \
    Source/settingsDialog.h \
    Source\akkwindow.h \
    Source\dialogaddedit.h \
    Source\coder.h \
    Source/AkksModel/AccountModel.h \
    Source/AkksModel/AccountView.h \
    Source/structs.h \
    Source/AkksModel/AccountItem.h \
    Source/AkksModel/AccountProxy.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    myapp.rc \
    akks.ico \
    akks \
    yourappname.exe.manifest

TRANSLATIONS = Language/akk_en.ts \
    Language/akk_ru.ts

CODECFORSRC     = UTF-8

win32:RC_ICONS += ..\3rdParty\akks.ico

VERSION = 1.1.0.0
