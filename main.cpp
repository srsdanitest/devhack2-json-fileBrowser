#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QFile>
#include<fstream>
#include <QTimer>
#include<iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include<string>
#include <algorithm>
#include <stdio.h>
#include "filess.h"
#include<QMessageBox>
#include <QtCore>
#include "qtdownload.h"

void afiseazaNume(int a, string fn)
{
    if(a==0)
    {   if(fn.substr(fn.find_last_of(".") + 1) == "mp3"||fn.substr(fn.find_last_of(".") + 1) == "wav"||fn.substr(fn.find_last_of(".") + 1) == "acc")
            std::cout<<"\t"<<fn<<endl;
    }
    if(a==1)
    {   if(fn.substr(fn.find_last_of(".") + 1) == "png"||fn.substr(fn.find_last_of(".") + 1) == "gif"||fn.substr(fn.find_last_of(".") + 1) == "bmp"
                ||fn.substr(fn.find_last_of(".") + 1) == "jpg"||fn.substr(fn.find_last_of(".") + 1) == "jpeg")
            std::cout<<"\t"<<fn<<endl;
    }
    if(a==2)
    {   if(fn.substr(fn.find_last_of(".") + 1) == "xls"||fn.substr(fn.find_last_of(".") + 1) == "pdf"||fn.substr(fn.find_last_of(".") + 1) == "doc")
            std::cout<<"\t"<<fn<<endl;
    }
    if(a==3)
    {   if(fn.substr(fn.find_last_of(".") + 1) == "txt")
            std::cout<<"\t"<<fn<<endl;
    }
    if(a==4)
    {   if(fn.substr(fn.find_last_of(".") + 1) == "mp4"||fn.substr(fn.find_last_of(".") + 1) == "mkv"||fn.substr(fn.find_last_of(".") + 1) == "mov")
            std::cout<<"\t"<<fn<<endl;
    }
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QtDownload dl;
    dl.setTarget("http://www.mready.net/devacademy/input3.json");

    dl.download();
    //quit when the download is done.
    QObject::connect(&dl, SIGNAL(done()), &a, SLOT(quit()));

    vector<filess> fisiere;
    std::cout<<"\nFile Download Done\n\n";
    QFile file_obj("input.json");
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open ";

        exit(1);
    }
    Q_ASSERT(file_obj.open(QFile::ReadOnly));
    QJsonDocument jsdoc1=QJsonDocument::fromJson(file_obj.readAll());
    file_obj.close();
   // remove( "input.json" );
    vector <QJsonObject> filesandfolders;
    vector<int> parentshere;
    QJsonObject jsdoc2=jsdoc1.object();
    QJsonArray jsdoc3=jsdoc2.take("file_system").toArray();
    for(int i=0;i<jsdoc3.size();i++)
    {
        filesandfolders.push_back(jsdoc3[i].toObject());
        parentshere.push_back(-1);
        //qDebug()<<filesandfolders[i].value("id");
    }
    int ii;
    for(ii=0;ii<filesandfolders.size();ii++)
    {
        if(filesandfolders[ii].value("contents").toArray().isEmpty()==false)
        {
            QJsonArray temp1=filesandfolders[ii].take("contents").toArray();
            for(int jj=0;jj<temp1.size();jj++)
            {filesandfolders.push_back(temp1[jj].toObject());

                parentshere.push_back(ii);}
        }
    }
    qDebug()<<"\nMusic:";
    for(int i=0;i<filesandfolders.size();i++)
        if(filesandfolders[i].value("type")=="file")
        {

            QJsonObject temp1=filesandfolders[i];
            QString text=temp1.value("name").toString();
            string numeString=text.toStdString().c_str();
            afiseazaNume(0,numeString);
        }
    qDebug()<<"\nPictures:";
    for(int i=0;i<filesandfolders.size();i++)
        if(filesandfolders[i].value("type")=="file")
        {

            QJsonObject temp1=filesandfolders[i];
            QString text=temp1.value("name").toString();
            string numeString=text.toStdString().c_str();
            afiseazaNume(1,numeString);
        }
    qDebug()<<"\nDocuments:";
    for(int i=0;i<filesandfolders.size();i++)
        if(filesandfolders[i].value("type")=="file")
        {

            QJsonObject temp1=filesandfolders[i];
            QString text=temp1.value("name").toString();
            string numeString=text.toStdString().c_str();
            afiseazaNume(2,numeString);
        }
    qDebug()<<"\nDownloads:";
    for(int i=0;i<filesandfolders.size();i++)
        if(filesandfolders[i].value("type")=="file")
        {

            QJsonObject temp1=filesandfolders[i];
            QString text=temp1.value("name").toString();
            string numeString=text.toStdString().c_str();
            afiseazaNume(3,numeString);
        }
    qDebug()<<"\nVideos:";
    for(int i=0;i<filesandfolders.size();i++)
        if(filesandfolders[i].value("type")=="file")
        {

            QJsonObject temp1=filesandfolders[i];
            QString text=temp1.value("name").toString();
            string numeString=text.toStdString().c_str();
            afiseazaNume(4,numeString);
        }
    for(int i=0;i<filesandfolders.size();i++)
    {
        QJsonObject temp1=filesandfolders[i];
        QString typeS=temp1.value("type").toString();
        bool here=true;
        string direct="directory";
        if (!direct.compare(typeS.toStdString().c_str()))
            here=false;
        QString nameS=filesandfolders[i].value("name").toString();
        fisiere.push_back(filess(temp1.value("id").toDouble(),here,nameS.toStdString().c_str(),parentshere[i]));
    }



    MainWindow w(&fisiere[0],fisiere.size());
    w.show();
    a.exec();
    return a.exec();
}
