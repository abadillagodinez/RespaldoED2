#include "prueba.h"

prueba::prueba()
{

}

prueba::~prueba(){
}

void prueba::ejecutarEnElThread(){
    int i = 0;
    while(i < 2000){
        //cout << "i es: " << i << endl;
        i++;
    }
    //cout << "Se acabo la ejecucion del thread, hizo " << i << " repeticiones" << endl;
}

void prueba::start(){
    thread t(&prueba::ejecutarEnElThread);
    t.detach();
}
