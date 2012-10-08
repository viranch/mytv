#ifndef RSSENGINE_H
#define RSSENGINE_H

#include <QObject>
#include <QUrl>
#include <QVariant>

class QNetworkAccessManager;
class QNetworkReply;

class RssEngine : public QObject
{
    Q_OBJECT
public:
    explicit RssEngine(QObject *parent = 0);
    void fetchFeed(QUrl feed);
    
signals:
    void feedUpdated(QPair<QUrl, QVariant> data);
    
public slots:

private slots:
    void parseFeed(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    
};

#endif // RSSENGINE_H
