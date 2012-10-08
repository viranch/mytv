#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T01:28:26
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = rssreader
CONFIG   += app_bundle lib_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rssreader.cpp \
    settingsdlg.cpp \
    rssengine.cpp

HEADERS += \
    rssreader.h \
    settingsdlg.h \
    rssengine.h

RESOURCES += \
    resources.qrc

FORMS += \
    settingsdlg.ui
