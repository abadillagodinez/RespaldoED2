#include "mainwindow.h"
#include <QApplication>
#include <thread>
#include <iostream>
#include "prueba.h"

using namespace std;

/*EJEMOPLO DEL THREAD
void foo()
{
    for (int i = 0; i < 100; i++){
        cout << "i_foo es: " << i << endl;
    }
}

void bar(int x)
{
    for (int i = x; i < 100; i++){
        cout << "i_bar es: " << i << endl;
    }
}*/

int main(int argc, char *argv[])
{
    /* EJEMPLO DEL THREAD
    thread first (bar,4);     // spawn new thread that calls foo()
    thread second (foo);  // spawn new thread that calls bar(0)

    cout << "main, foo and bar now execute concurrently...\n";

    //synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    cout << "foo and bar completed.\n";
    */

    QApplication a(argc, argv);
    prueba *pr = new prueba();
    pr->start();
    //thread t(&prueba::ejecutarEnElThread);
    cout << "Ya empezo a ejecutar el thread\n";
    MainWindow w;
    w.show();

    return a.exec();
}
