#include "rssreader.h"
#include "settingsdlg.h"

#include <QSettings>
#include <QDateTime>

RssReader::RssReader(QObject *parent) :
    QObject(parent)
{
    m_engine = new RssEngine(this);
    connect(m_engine, SIGNAL(feedUpdated(QList<Feed*>)), this, SLOT(showFeeds(QList<Feed*>)));

    m_dlg = new SettingsDlg();
    connect(m_dlg, SIGNAL(settingsUpdated()), this, SLOT(fetchFeeds()));

    m_trayMenu = new QMenu();
    m_marker = m_trayMenu->addSeparator();
    m_trayMenu->addAction("Refresh", this, SLOT(fetchFeeds()));
    m_trayMenu->addAction("Settings...", m_dlg, SLOT(show()));
    m_trayMenu->addAction("Quit", this, SIGNAL(quit()));

    m_tray = new QSystemTrayIcon(QIcon(":/images/feedicon.png"), this);
    m_tray->setContextMenu(m_trayMenu);
    m_tray->show();

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(fetchFeeds()));
    fetchFeeds();
}

RssReader::~RssReader()
{
    delete m_trayMenu;
    delete m_dlg;
}

void RssReader::fetchFeeds()
{
    m_feeds.clear();

    QSettings s;
    QList<QVariant> urlList = s.value("feeds").toList();
    foreach(QVariant value, urlList) {
        m_engine->fetchFeed(value.toUrl());
    }
    if (urlList.size() == 0) {
        clear();
    }

    m_refreshTimer->start(s.value("refreshInterval", 1).toInt() * 60 * 60 * 1000);
}

void RssReader::showFeeds(QList<Feed*> data)
{
    m_feeds << data;

    QMap<QDateTime, QString> titles;
    foreach(Feed *f, m_feeds) {
        titles.insertMulti(f->property("date").toDateTime(), f->property("title").toString());
    }
    QList<QDateTime> dates = titles.uniqueKeys();
    qSort(dates);
    QStringList sortedTitles;
    foreach(QDateTime dt, dates) {
        foreach(QString t, titles.values(dt)) {
            sortedTitles << dt.toString("MMM d") + " - " + t;
        }
    }

    QSettings s;
    int count = s.value("itemCount", 10).toInt();
    int size = sortedTitles.size();
    if (size > count) {
        sortedTitles = sortedTitles.mid(size-count);
    }

    clear();
    QAction *prev = m_marker;
    foreach(QString title, sortedTitles) {
        QAction *act = new QAction(title, m_trayMenu);
        m_trayMenu->insertAction(prev, act);
        m_menuEntries << act;
        prev = act;
    }
}

void RssReader::clear()
{
    foreach(QAction *entry, m_menuEntries) {
        m_trayMenu->removeAction(entry);
    }
    m_menuEntries.clear();
}
