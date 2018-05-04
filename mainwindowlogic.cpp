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
        emit moverLabels(1);
        int milisec = rand() % 1200 + 500;
        QThread::msleep(milisec);
    }

}


void MainWindowLogic::ejecutarAcciones(){
    //cin.get();
    int atendidos = 0;
    while (atendidos < getCantidadDeAtenciones()){
        clock_t startTime = clock(); //Start timer
        double secondsPassed;
        double secondsToDelay = 2;
        bool flag = true;
        while(flag){
            secondsPassed = (clock() - startTime) / CLOCKS_PER_SEC;
            if(!fila->colaVacia()){
                NodoDAtencion *actual = fila->popElement();
                if(primero().joinable()){
                    primero(mesas->primero->atender, actual);
                }
                head->accion(carreras, actual->idEstudiante, actual->codCurso, actual->codGrupo, actual->accion);
                atendidos = mesas->primero->cantidadAtendidos + mesas->segundo->cantidadAtendidos + mesas->tercero->cantidadAtendidos;
            }
            if(secondsPassed >= secondsToDelay){
                flag = false;
                cout << "Atendiendo, por favor espere..." << endl;
                //cout << "han pasado " << secondsPassed << endl;
            }
        }
        fila->cargarDatos();
    }
    //cout << atendidos << endl;
}

int MainWindowLogic::getCantidadDeAtenciones(){
    string archivoAbrir = "Atencion.txt";
    fstream archivo(archivoAbrir.c_str());
    string linea;
    if (!archivo.is_open()){
        cout << "abrio el archivo" << endl;
        archivo.open(archivoAbrir.c_str(), ios::in);
    }
    int i = 0;
    while(getline(archivo, linea)){
        i++;
    }
    return i;
}
