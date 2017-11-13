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

void afiseazaNumeCorectat(filess* clasecufisiere,int cautat
                          ,int indent,int dimensiune, int *afisat)
{
for(int i=0;i<dimensiune;i++)
    if(afisat[i]==0&&cautat==clasecufisiere[i].returnParentID())
    {   cout<<"|";
        for(int j=0;j<indent;j++)
            std::cout<<"    ";
        if(indent!=0)
            std::cout<<"|_";
        std::cout<<clasecufisiere[i].returnName()<<endl;
        afisat[i]=1;
        afiseazaNumeCorectat(clasecufisiere,i,indent+1,dimensiune,afisat);
    }
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    //let's open the json file below
    QNetworkAccessManager manager;
    QNetworkRequest req(QUrl("http://www.mready.net/devacademy/input3.json"));      //modify source file
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager.get(req);
    QJsonObject json;
    while(!reply->isFinished())
    {
    qApp->processEvents();
    }
    QByteArray response_data = reply->readAll();
    QJsonDocument jsdoc1 = QJsonDocument::fromJson(response_data);
    //reading from http: done


    vector<filess> fisiere;                                                         //vector with files or folders
    vector <QJsonObject> filesandfolders;                                           //vector with everything from http. files are stored as json objects here
    vector<int> parentshere;                                                        //vector with parent unique ID.
    QJsonObject jsdoc2=jsdoc1.object();
    QJsonArray jsdoc3=jsdoc2.take("file_system").toArray();                         //take everything out file_system, copy inside an array.

    for(int i=0;i<jsdoc3.size();i++)                                                //everything that we read now it's just under file_system
    {                                                                               // so parent ID is set to -1
        filesandfolders.push_back(jsdoc3[i].toObject());
        parentshere.push_back(-1);
    }
    //unwrap as long as there are unwraped files
    for(unsigned int ii=0;ii<filesandfolders.size();ii++)
    {
        if(filesandfolders[ii].value("contents").toArray().isEmpty()==false)
        {
            QJsonArray temp1=filesandfolders[ii].take("contents").toArray();        //if content is not empty, add it's content to be unwraped.
            for(int jj=0;jj<temp1.size();jj++)
            {filesandfolders.push_back(temp1[jj].toObject());

                parentshere.push_back(ii);}                                         //don't forget parent id
        }
    }
    //store everything from QJson to our class. This makes things easier to read
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
    //output in console folder structure
    std::cout<<"file_system:\n";
    int *vizitat=new int[fisiere.size()];
    //we need to remember if we will visit any file or folder, otherwise we might display same thing multiple times
    for(unsigned int i=0;i<filesandfolders.size();i++)
        vizitat[i]=0;
    afiseazaNumeCorectat(&fisiere[0],-1,0,fisiere.size(),vizitat);    //call to show on console
    //args: vector with every file or folder, first parent id, vector with parents, 0 indent, size of parent or files and folders, and visited array.
    MainWindow w(&fisiere[0],fisiere.size());                                       //now jump to GUI
    w.show();
    a.exec();
    return a.exec();
}
