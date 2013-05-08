#ifndef RSSREADER_H
#define RSSREADER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QUrl>

class SettingsDlg;
class RssEngine;
class Feed;

class RssReader : public QObject
{
    Q_OBJECT
public:
    explicit RssReader(QObject *parent = 0);
    ~RssReader();

signals:
    void quit();

public slots:
    void fetchFeeds();
    void processFeeds(QUrl feedUrl, QList<Feed*> data);
    void sortFeeds(QList<Feed*> data);
    void updateFeeds(QStringList titles);
    void updateSearch(QMenu *entry, QList<Feed*> data);
    void clear();
    void update();
    void openTorrent(QAction *entry);
    void showMenu(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon *m_tray;
    QMenu *m_trayMenu;
    SettingsDlg *m_dlg;
    QTimer *m_refreshTimer;
    RssEngine *m_rssEngine;
    QList<Feed*> m_feeds;
    QAction *m_marker;
    QList<QAction*> m_menuEntries;
    QUrl m_url;
    int m_timeout;

};

#endif // RSSREADER_H
