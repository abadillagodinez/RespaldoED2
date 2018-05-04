#ifndef NODEAVL_H
#define NODEAVL_H
#include <iostream>
#include "ArbolGrupos.h"
using namespace std;
class NodeAVL
{
public:
    NodeAVL(int pCodCarrera, int pCodCurso, string pNombre){
        Hder = NULL;
        Hizq = NULL;
        codCarrera = pCodCarrera;
        codCurso = pCodCurso;
        nombre = pNombre;
        grupos=new arbolGrupo();
        grupos->cargarGrupos(std::to_string(codCarrera),std::to_string(codCurso));
    }
    NodeAVL(){}
    ~NodeAVL(){}
    
    string to_string(){
        string s="";
        s+="Codigo de la carrera: "+std::to_string(codCarrera)+"\n";
        s+="Codigo curso: "+std::to_string(codCurso)+"\n";
        s+="Nombre del curso: "+nombre+"\n";
        return s;
    }
    
    void imprimirNodo(){
        cout<<to_string()<<endl;
        grupos->imprimirArbol();
    }
    
    void imprimir(){
        if(esHoja()){
            imprimirNodo();
        }else{
            if(Hizq!=NULL){
                Hizq->imprimir();
            }
            imprimirNodo();
            if(Hder!=NULL){
                Hder->imprimir();
            }
        }
    }
    
    bool esHoja(){
        return Hizq==NULL&&Hder==NULL;
    }


    NodeAVL *Hizq;
    NodeAVL *Hder;
    int height;
    int codCarrera;
    string nombre;
    int codCurso;
    arbolGrupo* grupos;//los grupos que le pertenecen al curso
    //aqui va el atributo de arbolRojiNegro grupos = new arbolRojiNegro();




    friend class ArbolAVLCursos;

};


#endif // NODEAVL_H
