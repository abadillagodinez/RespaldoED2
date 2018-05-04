#ifndef NODEAVL_H
#define NODEAVL_H
#include <iostream>
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
    }
    NodeAVL(){}
    ~NodeAVL(){}


private:
    NodeAVL *Hizq;
    NodeAVL *Hder;
    int height;
    int codCarrera;
    string nombre;
    int codCurso;
    //aqui va el atributo de arbolRojiNegro grupos = new arbolRojiNegro();




    friend class ArbolAVLCursos;

};


#endif // NODEAVL_H
