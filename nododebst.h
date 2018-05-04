#ifndef NODODEBST_H
#define NODODEBST_H
class ArbolAVLCursos;
#include <iostream>
#include "arbolavlcursos.h"
using namespace std;

class NodoDeBST{
public:
    NodoDeBST(int pCodCarrera, string pNombreCarrera){
        codCarrera = pCodCarrera;
        nombreCarrera = pNombreCarrera;
        Hizq = NULL;
        Hder = NULL;
    }

    ~NodoDeBST(){}

    /**
     * @brief metodo que retorna si es hoja o no
     * @return bool
     */
    bool isLeaf(){
        return (Hizq == NULL && Hder == NULL);
    }

    /**
     * @brief inserta de manera binaria en el arbol
     * @param pCodCarrera
     */
    void insertBinary(int pCodCarrera, string pNombreCarrera){
        if(pCodCarrera < codCarrera){
            if(Hizq == NULL){
                Hizq = new NodoDeBST(pCodCarrera, pNombreCarrera);
            }
            else{
                Hizq->insertBinary(pCodCarrera, pNombreCarrera);
            }
        }
        else{
            if(Hder == NULL){
                Hder = new NodoDeBST(pCodCarrera, pNombreCarrera);
            }
            else{
                Hder->insertBinary(pCodCarrera, pNombreCarrera);
            }
        }
    }

private:
    int codCarrera;
    NodoDeBST *Hizq;
    NodoDeBST *Hder;
    string nombreCarrera;
    ArbolAVLCursos *cursos = new ArbolAVLCursos();
    friend class ArbolDeCarreras;
    friend class ArbolAVLCursos;
};
#endif // NODODEBST_H
