#ifndef RSSREADER_H
#define RSSREADER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include "settingsdlg.h"
#include "rssengine.h"

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

private:
    QSystemTrayIcon *m_tray;
    QMenu *m_trayMenu;
    SettingsDlg *m_dlg;
    RssEngine *m_engine;
    QMap<QUrl, QPair<> > m_feeds;
    
};

#endif // RSSREADER_H
