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
        srand(time(NULL));
        emit cambiarLabel(i);
        int milisec = rand() % 1200 + 500;
        QThread::msleep(milisec);
    }
    for(int i = 0; i < 10; i++){
        srand(time(NULL));
        emit moverLabels();
        int milisec = rand() % 1200 + 500;
        QThread::msleep(milisec);
    }
}
