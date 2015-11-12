#-------------------------------------------------
#
# Project created by QtCreator 2012-10-08T01:28:26
#
#-------------------------------------------------

QT       += core gui widgets network xml

TARGET = mytv

TEMPLATE = app

SOURCES += main.cpp \
    mytv.cpp \
    settingsdlg.cpp \
    rssengine.cpp \
    feed.cpp \
    transmission.cpp \
    trdialog.cpp

HEADERS += \
    mytv.h \
    settingsdlg.h \
    rssengine.h \
    feed.h \
    transmission.h \
    trbackend.h \
    trdialog.h

RESOURCES += \
    resources.qrc

ICON = images/appicon.icns

FORMS += \
    settingsdlg.ui \
    trdialog.ui

QMAKE_INFO_PLIST = Info.plist
