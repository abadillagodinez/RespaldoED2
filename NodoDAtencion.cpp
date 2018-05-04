#include "NodoDAtencion.h"

NodoDAtencion::NodoDAtencion()
{
    idEstudiante = 0;
    codCurso = "";
    codGrupo = "";
    accion = 0;
    next = NULL;
    previous = NULL;
}

NodoDAtencion::NodoDAtencion(long pIdEstudiante, string pCodCurso, string pCodGrupo, int pAccion){
    idEstudiante = pIdEstudiante;
    codCurso = pCodCurso;
    codGrupo = pCodGrupo;
    accion = pAccion;
    next = NULL;
    previous = NULL;
}

NodoDAtencion::~NodoDAtencion()
{
    //dtor
}
