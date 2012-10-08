#ifndef RSSREADER_H
#define RSSREADER_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class RssReader : public QObject
{
    Q_OBJECT
public:
    explicit RssReader(QObject *parent = 0);
    ~RssReader();
    
signals:
    void quit();
    
public slots:

private:
    QSystemTrayIcon *m_tray;
    QMenu *m_trayMenu;
    
};

#endif // RSSREADER_H
