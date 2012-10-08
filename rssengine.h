#ifndef RSSENGINE_H
#define RSSENGINE_H

#include <QObject>
#include <QUrl>
#include <QVariant>
#include "feed.h"

class QNetworkAccessManager;
class QNetworkReply;

class RssEngine : public QObject
{
    Q_OBJECT
public:
    explicit RssEngine(QObject *parent = 0);
    void fetchFeed(QUrl feed);
    
signals:
    void feedUpdated(QList<Feed*> data);
    
public slots:

private slots:
    void parseFeed(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    
};

#endif // RSSENGINE_H
