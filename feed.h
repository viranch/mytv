#ifndef FEED_H
#define FEED_H

#include <QObject>
#include <QUrl>
#include <QVariant>

class Feed : public QObject
{
    Q_OBJECT
public:
    explicit Feed(QUrl url, QObject *parent = 0);
    void setProperty(QString key, QVariant value);
    QVariant property(QString key);
    inline QUrl url() { return m_url; }
    
signals:
    
public slots:

private:
    QUrl m_url;
    QMap<QString, QVariant> m_data;
    
};

#endif // FEED_H
