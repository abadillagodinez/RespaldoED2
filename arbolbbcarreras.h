#ifndef ARBOLBBCARRERAS_H
#define ARBOLBBCARRERAS_H

class ArbolAVLCursos;

#include <iostream>
#include "stringParser.h"
#include "nododebst.h"


using namespace std;


class ArbolDeCarreras{
public:
    ArbolDeCarreras(){
        raiz = NULL;
    }

    ~ArbolDeCarreras(){}
    void insertE(int pCodCarrera, string pNombreCarrera){
        if(raiz == NULL){
            NodoDeBST *newE = new NodoDeBST(pCodCarrera, pNombreCarrera);
            raiz = newE;
        }
        else{
            raiz->insertBinary(pCodCarrera, pNombreCarrera);
        }
    }

    bool isElementIn(NodoDeBST *raiz, int pCodCarrera){
        if(raiz == NULL){
            return false;
        }
        else if(raiz->codCarrera == pCodCarrera){
            return true;
        }
        else if(raiz->codCarrera < pCodCarrera){
            return isElementIn(raiz->Hder, pCodCarrera);
        }
        else if(raiz->codCarrera > pCodCarrera){
            return isElementIn(raiz->Hizq, pCodCarrera);
        }
    }

    void MostrarAux(NodoDeBST *raiz, int n){
        if(raiz != NULL){ // Si el árbol no está vacío
            MostrarAux(raiz->Hder, n+2);
            for(int i = 0; i < n; i = i+2)
                cout << "  ";
            cout << raiz->codCarrera << "  " << raiz->nombreCarrera <<  endl;
            MostrarAux(raiz->Hizq, n+2);
        }
    }

    void Mostrar(){
        MostrarAux(this->raiz, 0);
    }

    void CargarCarreras(){
        ifstream file;
        file.open("Carreras.txt");
        string fromfile;
        String *data=new String();
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            stringstream pos1;
            pos1 << data->getPos(1);
            int nuevoCodCarrera;
            pos1 >> nuevoCodCarrera;
            insertE(nuevoCodCarrera, data->getPos(2));
            //CargarCursos(buscarNodo(raiz, nuevoCodCarrera));
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
        }
    }

    void CargarCursos(NodoDeBST *CarreraActual){
        if(CarreraActual){
            CarreraActual->cursos->CargarCursos(CarreraActual->codCarrera);//-> hacer el codigo de cargar los cursos en la carrera
        }
    }

    NodoDeBST *buscarNodo(NodoDeBST *pRaiz, int codCarrera){
        NodoDeBST *res = NULL;
        if(pRaiz->codCarrera == codCarrera){
            res = pRaiz;
        }
        else if(pRaiz->codCarrera < codCarrera){
            res=buscarNodo(pRaiz->Hder, codCarrera);
        }
        else if(pRaiz->codCarrera > codCarrera){
            res=buscarNodo(pRaiz->Hizq, codCarrera);
        }
        return res;
    }
    
    void imprimir(){
        if(raiz!=NULL){
            raiz->imprimir();
        }else{
            cout<<"No existen carreras"<<endl;
        }
    }
    
    NodoDeBST *raiz;


    bool isVoid(){
        return raiz == NULL;
    }

};
#endif // ARBOLBBCARRERAS_H
