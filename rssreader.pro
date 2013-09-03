#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T01:28:26
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rssreader

TEMPLATE = app

SOURCES += main.cpp \
    rssreader.cpp \
    settingsdlg.cpp \
    rssengine.cpp \
    feed.cpp

HEADERS += \
    rssreader.h \
    settingsdlg.h \
    rssengine.h \
    feed.h

RESOURCES += \
    resources.qrc

FORMS += \
    settingsdlg.ui
