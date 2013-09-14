#include <QApplication>
#include "mytv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Viranch, Inc.");
    QApplication::setApplicationName("RSS Reader");

    MyTv r;
    QObject::connect(&r, SIGNAL(quit()), &a, SLOT(quit()));
    a.setQuitOnLastWindowClosed(false);
    
    return a.exec();
}
