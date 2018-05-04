#ifndef MAINWINDOWLOGIC_H
#define MAINWINDOWLOGIC_H
#include <QThread>
#include <QObject>
#include <iostream>
#include <stdlib.h>
#include "ColaDeAtencion.h"
#include "mostradorJonathan.h"
#include <thread>

using namespace std;
class MainWindowLogic : public QThread
{
    Q_OBJECT
public:
    MainWindowLogic();
    ColaDeAtencion *fila = new ColaDeAtencion();
    mostradores *mesas = new mostradores(fila);
    static std::thread primero;
    static std::thread segundo;
    static std::thread tercero;


//public slots:
    void run();
    int getCantidadDeAtenciones();
    void ejecutarAcciones();
signals:
    void cambiarLabel(int);
    void moverLabels(int);

};

#endif // MAINWINDOWLOGIC_H
