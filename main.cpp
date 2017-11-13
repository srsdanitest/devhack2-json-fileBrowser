#include "mainwindow.h"
#include <QApplication>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include <QTimer>
#include <QtNetwork>
#include<iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <algorithm>
#include "filess.h"
#include <QtCore>

void afiseazaNumeCorectat(filess* clasecufisiere,int cautat,
                          int *parentshere,int indent,int dimensiune, int *afisat)
{
for(int i=0;i<dimensiune;i++)
    if(afisat[i]==0&&cautat==parentshere[i])
    {   cout<<"|";
        for(int j=0;j<indent;j++)
            std::cout<<"    ";
        if(indent!=0)
            std::cout<<"|_";
        std::cout<<clasecufisiere[i].returnName()<<endl;
        afisat[i]=1;
        afiseazaNumeCorectat(clasecufisiere,i,parentshere,indent+1,dimensiune,afisat);
    }
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QNetworkAccessManager manager;
    QNetworkRequest req(QUrl("http://www.mready.net/devacademy/input1.json"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager.get(req);

    QJsonObject json;

    while(!reply->isFinished())
    {
    qApp->processEvents();
    }
    QByteArray response_data = reply->readAll();
    QJsonDocument jsdoc1 = QJsonDocument::fromJson(response_data);
    vector<filess> fisiere;
    vector <QJsonObject> filesandfolders;
    vector<int> parentshere;
    QJsonObject jsdoc2=jsdoc1.object();
    QJsonArray jsdoc3=jsdoc2.take("file_system").toArray();
    for(int i=0;i<jsdoc3.size();i++)
    {
        filesandfolders.push_back(jsdoc3[i].toObject());
        parentshere.push_back(-1);
    }
    for(unsigned int ii=0;ii<filesandfolders.size();ii++)
    {
        if(filesandfolders[ii].value("contents").toArray().isEmpty()==false)
        {
            QJsonArray temp1=filesandfolders[ii].take("contents").toArray();
            for(int jj=0;jj<temp1.size();jj++)
            {filesandfolders.push_back(temp1[jj].toObject());

                parentshere.push_back(ii);}
        }
    }
    for(unsigned int i=0;i<filesandfolders.size();i++)
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
    std::cout<<"file_system:\n";
    int *vizitat=new int[fisiere.size()];
    for(unsigned int i=0;i<filesandfolders.size();i++)
        vizitat[i]=0;
    afiseazaNumeCorectat(&fisiere[0],-1,&parentshere[0],0,fisiere.size(),vizitat);

    MainWindow w(&fisiere[0],fisiere.size());
    w.show();
    a.exec();
    return a.exec();
}
