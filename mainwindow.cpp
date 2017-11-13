#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filess.h"
#include <vector>
#include<fstream>
#include<iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->label_2->setText("TopLevelDirectory");
}

MainWindow::MainWindow(filess* testt,int dimensiune,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->setText("TopLevelDirectory");
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
