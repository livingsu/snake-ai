#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    qDebug()<<"success";

    return a.exec();
}

//加背景音乐
