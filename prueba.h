#ifndef PRUEBA_H
#define PRUEBA_H
#include <iostream>
#include <thread>

using namespace std;
class prueba{
public:
    prueba();

    ~prueba();
    static void ejecutarEnElThread();
    void start();
};

#endif // PRUEBA_H
