#include "rssreader.h"
#include "settingsdlg.h"
#include "rssengine.h"
#include "feed.h"

#include <QSettings>
#include <QDateTime>
#include <QRegExp>
#include <QDesktopServices>
#include <QCursor>
#include <QApplication>
#include <QClipboard>

RssReader::RssReader(QObject *parent) :
    QObject(parent)
{
    m_rssEngine = new RssEngine(this);
    connect(m_rssEngine, SIGNAL(feedUpdated(QUrl,QList<Feed*>)), this, SLOT(processFeeds(QUrl,QList<Feed*>)));

    m_dlg = new SettingsDlg();
    connect(m_dlg, SIGNAL(settingsUpdated()), this, SLOT(update()));

    m_trayMenu = new QMenu();
    m_marker = m_trayMenu->addAction("Refresh", this, SLOT(fetchFeeds()));
    m_trayMenu->addAction("Settings...", m_dlg, SLOT(show()));
    m_trayMenu->addAction("Quit", this, SIGNAL(quit()));
    connect(m_trayMenu, SIGNAL(triggered(QAction*)), this, SLOT(openTorrent(QAction*)));

    m_tray = new QSystemTrayIcon(QIcon(":/images/feedicon.png"), this);
    m_tray->setContextMenu(m_trayMenu);
    m_tray->show();
#ifndef Q_WS_MAC
    connect(m_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showMenu(QSystemTrayIcon::ActivationReason)));
#endif

    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setSingleShot(true);
    connect(m_refreshTimer, SIGNAL(timeout()), this, SLOT(fetchFeeds()));

    update();
}

RssReader::~RssReader()
{
    delete m_trayMenu;
    delete m_dlg;
}

void RssReader::update()
{
    QSettings s;
    m_url = QUrl(s.value("feed").toString());
    m_timeout = s.value("refreshInterval", 1).toInt();

    fetchFeeds();
}

void RssReader::fetchFeeds()
{
    if (m_url.isEmpty()) {
        clear();
        return;
    }

    m_rssEngine->fetchFeed(m_url);

    m_refreshTimer->start(m_timeout * 3600000);
}

void RssReader::processFeeds(QUrl feedUrl, QList<Feed*> data)
{
    if (feedUrl == m_url) {
        sortFeeds(data);
    } else {
        QSettings s;
        int count = s.value("itemCount", 10).toInt();
        foreach(QAction *entry, m_menuEntries) {
            if (feedUrl == entry->data().toUrl()) {
                updateSearch(entry->menu(), data.mid(0, count)); // first 'count' items
                break;
            }
        }
    }
}

void RssReader::sortFeeds(QList<Feed*> data)
{
    if (data.isEmpty()) {
      return;
    }

    m_feeds.clear();
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

    updateFeeds(sortedTitles);
}

void RssReader::updateFeeds(QStringList titles)
{
    clear();
    QSettings s;
    QAction *prev = m_trayMenu->insertSeparator(m_marker);
    m_menuEntries << prev;
    foreach(QString title, titles) {
        QMenu *act = new QMenu(title, m_trayMenu);
        m_trayMenu->insertMenu(prev, act);
        m_menuEntries << act->menuAction();
        prev = act->menuAction();

        QRegExp rx(".* - (.* S\\d{2}E\\d{2}) .*");
        rx.indexIn(title);
        title = rx.cap(1);
        QString suff = s.value("searchSuffix").toString();
        if (!suff.isEmpty())
            title += " " + suff;
        title = title.replace(' ', '+');
        QUrl feedUrl = QUrl("http://torrentz.in/feed?q="+title);
        m_rssEngine->fetchFeed(feedUrl);
        act->menuAction()->setData(feedUrl);
    }
}

void RssReader::updateSearch(QMenu* entry, QList<Feed*> data)
{
    foreach(Feed* f, data) {
        QAction *act = entry->addAction(f->property("title").toString());
        act->setData(f->property("link").toString());
    }
}

void RssReader::clear()
{
    foreach(QAction *entry, m_menuEntries) {
        m_trayMenu->removeAction(entry);
    }
    m_menuEntries.clear();
}

void RssReader::openTorrent(QAction *entry)
{
    QString link = entry->data().toString();
    QRegExp rx("http://torrentz.in/(.*)$");
    rx.indexIn(link);
    QString hash = rx.cap(1).toUpper();
    QString filename = entry->text().replace(' ','.').toLower();
    QString torrent = "http://torcache.net/torrent/"+hash+".torrent?title="+filename;
    QApplication::clipboard()->setText(torrent);
}

void RssReader::showMenu(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        m_trayMenu->popup(QCursor::pos());
    }
}
