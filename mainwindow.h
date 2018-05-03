#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainwindowlogic.h"
#include <QMainWindow>
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>
#include <time.h>
#include <iostream>
#include <thread>
#include <QTimer>
#include <QThread>
#include <stdlib.h>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowLogic *logic = new MainWindowLogic();
    Ui::MainWindow *ui;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mover();

public slots:
    void pintarLabel(int);
    void atender();

private:
    void wait();

};

#endif // MAINWINDOW_H

