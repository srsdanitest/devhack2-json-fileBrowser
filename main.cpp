#include <QCoreApplication>
#include<fstream>
#include <QTimer>
#include<iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <algorithm>
#include "filess.h"
#include "downloadmanager.h"

void doThings()
{
    ifstream f("input.json");
    string s;
    int nowOpen=0;
    vector <filess> filesAndFolders;
    vector <long> parents;
    parents.push_back(0);
    for(int i=0;i<3;i++)
    {
        f>>s;
    }
    while(f>>s)
    {
        nowOpen++;
        string id,realid,tyype,realtyype,name,realname;
        f>>id>>realid>>tyype>>realtyype>>name>>realname;
        realid.erase(realid.size()-1,1);
        bool local1;
        if(realtyype=="\"file\",")
            local1=false;
        else
            local1=true;
        realname.erase(0,1);
        realname.erase(realname.size()-2,2);
        filesAndFolders.push_back(atol(realid.c_str()),local1,realname,parents[parents.size()-1]);
    }
}


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    DownloadManager manager;

    // This static single-shot timer fires instantly, only once,
    // while non-single-shot timers fire every interval milliseconds.
    QTimer::singleShot(0, &manager, SLOT(execute()));
    // manager.execute(); (This would be the same)
    app.exec();
    std::cout<<"\nFile Download Done\n\n";
    QFile file_obj("input.json");
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open ";
        exit(1);
    }
    doThings();

    //set parent it to zero;
}
