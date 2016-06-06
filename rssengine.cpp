#include "rssengine.h"
#include "feed.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDomDocument>
#include <QDateTime>
#include <QStringList>

RssEngine::RssEngine(QObject *parent) :
    QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseFeed(QNetworkReply*)));
}

void RssEngine::fetchFeed(QUrl feed)
{
    m_manager->get(QNetworkRequest(feed));
}

void RssEngine::parseFeed(QNetworkReply *reply)
{
    QDomDocument doc;
    doc.setContent(reply->readAll());
    QDomElement root = doc.documentElement();
    QDomNodeList items = root.elementsByTagName("item");
    QList<Feed*> feeds;

    for(int i=0; i<items.size(); i++) {
        QDomElement item = items.at(i).toElement();
        QString title = item.firstChildElement("title").text();
        QString desc = item.firstChildElement("description").text();
        QString pubDate = item.firstChildElement("pubDate").text();
        QString link = item.firstChildElement("link").text();
        QStringList dateToks = pubDate.split(" ");
        if (dateToks.size()>5) {
            pubDate = QStringList(dateToks.mid(0, 5)).join(" ");
        }
        QDateTime date = QDateTime::fromString(pubDate, "ddd, dd MMM yyyy hh:mm:ss");

        Feed *data = new Feed(reply->url());
        data->setProperty("title", title);
        data->setProperty("date", date);
        data->setProperty("link", link);

        QRegExp rx("Size: (.*) Seeds: (.*) Peers: (.*) Hash: (.*)");
        if (rx.indexIn(desc) != -1) {
            data->setProperty("size", rx.cap(1));
            data->setProperty("seeds", rx.cap(2));
            data->setProperty("peers", rx.cap(3));
            QString hash = rx.cap(4);
            data->setProperty("hash", hash);
            data->setProperty("torcacheUrl", "http://torcache.net/torrent/"+hash.toUpper()+".torrent");
        }

        feeds << data;
    }

    emit feedUpdated(reply->request().url(), feeds);

    reply->deleteLater();
}
