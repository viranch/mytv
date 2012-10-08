#include <QApplication>
#include "rssreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RssReader r;
    QObject::connect(&r, SIGNAL(quit()), &a, SLOT(quit()));
    
    return a.exec();
}
