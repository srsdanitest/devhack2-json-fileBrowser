#include "mainwindow.h"
#include <QApplication>
#include <QUrl>
#include<iostream>
#include <string>
#include <QDebug>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QUrl tesst("http://www.mready.net/devacademy/input1.json");
    cout<<"yee";
    QUrl copy(tesst);
    copy.setQuery(copy.query(QUrl::FullyDecoded), QUrl::DecodedMode);
    qDebug() << tesst.toString();   // prints: http://example.com/?q=a%2B%3Db%26c
    qDebug() << copy.toString();
    return a.exec();
}
