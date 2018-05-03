#ifndef MAINWINDOWLOGIC_H
#define MAINWINDOWLOGIC_H
#include <QThread>
#include <QObject>
#include "iostream"

using namespace std;
class MainWindowLogic : public QThread
{
    Q_OBJECT
public:
    MainWindowLogic();

//public slots:
    void run();
signals:
    void cambiarLabel(int);
    void moverLabels();

};

#endif // MAINWINDOWLOGIC_H
