#include <iostream>
#include "NodoDAtencion.h"
#include <fstream>
#include "string.h"
#include <sstream>
#pragma once
using namespace std;

class ColaDeAtencion
{
   private:
   int frente;
   int fondo;
   int disponibles;
   int indiceArchivo;
   NodoDAtencion *arreglo [10];


public:
    ColaDeAtencion();
    ~ColaDeAtencion();
    void cargarDatos();
    string getCodGrupo(string linea);
    string getCodCurso(string linea);
    int getAccion(string linea);
    int getIdEstudiante(string linea);
    bool colaVacia(){return fondo < frente;}
    void pushElement(NodoDAtencion *v);
    void imprimir();
    NodoDAtencion* popElement();
    
    friend class nodoMostrador;
};
