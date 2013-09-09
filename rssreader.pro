#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T01:28:26
#
#-------------------------------------------------

QT       += core gui widgets network xml

TARGET = rssreader

TEMPLATE = app

SOURCES += main.cpp \
    rssreader.cpp \
    settingsdlg.cpp \
    rssengine.cpp \
    feed.cpp \
    transmission.cpp \
    trdialog.cpp

HEADERS += \
    rssreader.h \
    settingsdlg.h \
    rssengine.h \
    feed.h \
    transmission.h \
    trbackend.h \
    trdialog.h

RESOURCES += \
    resources.qrc

FORMS += \
    settingsdlg.ui \
    trdialog.ui
