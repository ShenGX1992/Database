#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    if(!createConnection())
       return 1;
    MainWindow w;
    w.show();

    return a.exec();
}
