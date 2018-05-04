#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mainwindowlogic.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QLabel>
#include <time.h>
#include <iostream>
#include <thread>
#include <QTimer>
#include <QThread>
#include <stdlib.h>
#include <sstream>
#include <exception>
#include <QMessageBox>

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
    void atender(int);

private slots:
    void on_btnProfesoresDeUnCurso_clicked();

    void on_btnCursosDeUnaCarrera_clicked();

    void on_btnEstudianteDeUnGrupo_clicked();

    void on_btnEstudiantesDeUnCarrera_clicked();

    void on_btnProfesoresDeUNACarrera_clicked();

private:
    void wait();
    bool is_int(string valor);

};

#endif // MAINWINDOW_H

