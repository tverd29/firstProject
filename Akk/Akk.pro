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
    main.cpp \
    Source\akkwindow.cpp \
    Source\account.cpp \
    Source\dialogaddedit.cpp \
    Source\coder.cpp \
    Source/AkksModel/AccountModel.cpp \
    Source/AkksModel/AccountStorage.cpp \
    Source/AkksModel/AccountView.cpp

HEADERS += \
    Include\akkwindow.h \
    Include\account.h \
    Include\dialogaddedit.h \
    Include\coder.h \
    Include/AkksModel/AccountModel.h \
    Include/AkksModel/AccountStorage.h \
    Include/AkksModel/AccountView.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    myapp.rc \
    akks.ico \
    akks \
    yourappname.exe.manifest

#win32: LIBS += -LC:/OpenSSL-Win32/lib/ -lopenssl

#INCLUDEPATH += C:/OpenSSL-Win32/include
#DEPENDPATH += C:/OpenSSL-Win32/include


#win32: LIBS += -LC:/OpenSSL-Win32/lib/VC/static/ -llibcrypto32MD

#INCLUDEPATH += C:/OpenSSL-Win32/lib/VC/static
#DEPENDPATH += C:/OpenSSL-Win32/lib/VC/static
