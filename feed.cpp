#include "feed.h"

Feed::Feed(QUrl url, QObject *parent) :
    QObject(parent)
{
    m_url = url;
}

void Feed::setProperty(QString key, QVariant value)
{
    m_data[key] = value;
}

QVariant Feed::property(QString key)
{
    return m_data[key];
}
