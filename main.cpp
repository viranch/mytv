#include <QApplication>
#include "rssreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Viranch, Inc.");
    QApplication::setApplicationName("RSS Reader");

    RssReader r;
    QObject::connect(&r, SIGNAL(quit()), &a, SLOT(quit()));
    a.setQuitOnLastWindowClosed(false);
    
    return a.exec();
}
