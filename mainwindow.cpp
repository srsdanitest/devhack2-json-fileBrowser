#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filess.h"
#include <vector>
#include<iostream>
#include<QTreeWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(filess* testt,int dimensiune,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setText("TopLevelDirectory");
    //linia de sub pentru tree
    QTreeWidget * tree = ui->treeWidget;
    vector<QTreeWidgetItem *> iteme;
    for(int k=0;k<dimensiune;k++)
    {
        QTreeWidgetItem * item=new QTreeWidgetItem();
        QString tempo = QString::fromStdString(testt[k].returnName());
        item->setText(0,tempo);
        if(testt[k].returnType()==false)
            item->setIcon(0,QIcon(":/new/prefix1/images.png"));
        else
            item->setIcon(0,QIcon(":/new/prefix1/file.jpg"));
        iteme.push_back(item);
        if(testt[k].returnParentID()==-1)
            tree->addTopLevelItem(iteme[k]);
        else
            iteme[testt[k].returnParentID()]->addChild(iteme[k]);
    }

    for(int i=0;i<dimensiune;i++)
    {
        if(testt[i].returnParentID()==-1&&testt[i].returnType()==false)
        {
            QString qstr = QString::fromStdString(testt[i].returnName());
            ui->listWidget->addItem(qstr);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
