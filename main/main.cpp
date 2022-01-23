#include "widget.h"
#include <QApplication>
#include "cbridge.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBridge cb;
    Widget w(&cb);
    w.show();

    return a.exec();
}
