#include "mainwindowlogic.h"
//thread de carga de datos y movimiento de atencion
MainWindowLogic::MainWindowLogic()
{

}


void MainWindowLogic::run(/*recibe la cola de atecion*/){

    /* primero se carga la cola en logica y depues se envia
     * por medio del cambiar label, despues es donde se hace
     * el ciclo grande de atencion, con sus respectivos emits para la
     * interfaz */
    for(int i = 0; i < 10; i++){
        emit cambiarLabel(i);
        QThread::msleep(500);
    }
    for(int i = 0; i < 10; i++){
        emit moverLabels();
        QThread::msleep(500);
    }
}
