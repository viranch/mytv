#include "rssengine.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDomDocument>
#include <QDateTime>
#include <QStringList>

#include <QDebug>

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
    QDomElement item = root.firstChildElement("channel").firstChildElement("item");

    QString title = item.firstChildElement("title").text();
    QString pubDate = item.firstChildElement("pubDate").text();
    QStringList dateToks = pubDate.split(" ");
    if (dateToks.size()>5) {
        pubDate = QStringList(dateToks.mid(0, 5)).join(" ");
    }
    QDateTime date = QDateTime::fromString(pubDate, "ddd, dd MMM yyyy hh:mm:ss");

    QList<QVariant> data;
    data << title << date;

    emit feedUpdated(QPair<QUrl, QVariant>(reply->url(), QVariant(data)));
}
