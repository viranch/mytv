#ifndef MYTV_H
#define MYTV_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QUrl>
#include <QNetworkReply>

class SettingsDlg;
class RssEngine;
class Feed;
class Transmission;

class MyTv : public QObject
{
    Q_OBJECT
public:
    explicit MyTv(QObject *parent = 0);
    ~MyTv();

signals:
    void quit();

public slots:
    void showSettings();
    void fetchFeeds();
    void processFeeds(QUrl feedUrl, QList<Feed*> data);
    void sortFeeds(QList<Feed*> data);
    void updateFeeds(QStringList titles);
    void updateSearch(QMenu *entry, QList<Feed*> data);
    void clear();
    void update();
    void openTorrent(QAction *entry);
    void showMenu(QSystemTrayIcon::ActivationReason reason);
    void torrentAdded(QString result, QString name);
    void handleError(QNetworkReply::NetworkError e);

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
    QUrl m_feedBaseUrl;
    int m_timeout;
    Transmission *m_transmission;

};

#endif // MYTV_H
