#ifndef RSSREADER_H
#define RSSREADER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include "settingsdlg.h"
#include "rssengine.h"
#include "feed.h"

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
    void showFeeds(QList<Feed*> data);
    void clear();

private:
    QSystemTrayIcon *m_tray;
    QMenu *m_trayMenu;
    SettingsDlg *m_dlg;
    RssEngine *m_engine;
    QList<Feed*> m_feeds;
    QAction *m_marker;
    QList<QAction*> m_menuEntries;
    
};

#endif // RSSREADER_H
