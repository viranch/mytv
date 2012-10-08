#include "rssreader.h"
#include "settingsdlg.h"

#include <QSettings>

RssReader::RssReader(QObject *parent) :
    QObject(parent)
{
    m_engine = new RssEngine(this);

    m_trayMenu = new QMenu();
    QAction *settingsAction = m_trayMenu->addAction("Settings...");
    QAction *quitAction = m_trayMenu->addAction("Quit");

    m_dlg = new SettingsDlg();
    connect(settingsAction, SIGNAL(triggered()), m_dlg, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));
    connect(m_dlg, SIGNAL(settingsUpdated()), this, SLOT(fetchFeeds()));

    m_tray = new QSystemTrayIcon(QIcon(":/images/feedicon.png"), this);
    m_tray->setContextMenu(m_trayMenu);
    m_tray->show();

    fetchFeeds();
}

RssReader::~RssReader()
{
    delete m_trayMenu;
    delete m_dlg;
}

void RssReader::fetchFeeds()
{
    QSettings s;
    foreach(QVariant value, s.value("feeds").toList()) {
        m_engine->fetchFeed(value.toUrl());
    }
}
