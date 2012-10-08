#include "rssreader.h"
#include "settingsdlg.h"

#include<QDebug>

RssReader::RssReader(QObject *parent) :
    QObject(parent)
{
    m_trayMenu = new QMenu();
    QAction *settingsAction = m_trayMenu->addAction("Settings...");
    QAction *quitAction = m_trayMenu->addAction("Quit");

    m_dlg = new SettingsDlg();
    connect(settingsAction, SIGNAL(triggered()), m_dlg, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SIGNAL(quit()));

    m_tray = new QSystemTrayIcon(QIcon(":/images/feedicon.png"), this);
    m_tray->setContextMenu(m_trayMenu);
    m_tray->show();
}

RssReader::~RssReader()
{
    delete m_trayMenu;
    delete m_dlg;
}
