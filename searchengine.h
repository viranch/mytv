#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>

class SearchEngine : public QObject
{
    Q_OBJECT
public:
    explicit SearchEngine(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SEARCHENGINE_H
