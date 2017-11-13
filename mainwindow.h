#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"filess.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(filess*,int,QWidget *parent = 0); //create this custom constructor to get the vector with files/directory. int from size of vector
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
