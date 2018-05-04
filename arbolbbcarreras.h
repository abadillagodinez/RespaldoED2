#ifndef ARBOLBBCARRERAS_H
#define ARBOLBBCARRERAS_H

class ArbolAVLCursos;

#include <iostream>
#include "stringParser.h"
#include "nododebst.h"
#include "ProfesoresTree.h"


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
    
    string getStringReporteCarreras(NodoDeBST* root){
        string s="";
        if(root->isLeaf()){
            s+=root->to_string()+"\n";
        }else{
            if(root->Hizq!=NULL){
                s+=getStringReporteCarreras(root->Hizq)+"\n";
            }
            s+=root->to_string()+"\n";
            if(root->Hder!=NULL){
                s+=getStringReporteCarreras(root->Hder)+"\n";
            }
        }
    }
    
    void reporteCarrera(){
        fstream file;
        file.open("Reporte_de_Carrera.txt");
        file<<getStringReporteCarreras(raiz);
        file.close();
    }

    void getReporteCursosCarrera(int idCarrera){
        ofstream file;
        file.open("Reporte_de_Carrera_"+std::to_string(idCarrera)+".txt");
        NodoDeBST* carrera=buscarNodo(raiz,idCarrera);
        file<<carrera->cursos->getStringReporteCarreras(carrera->cursos->root);
        file.close();
    }
    
    void reporteProfesoresCurso(int codCarrera,int codCurso,ArbolBp * profesores){
        ofstream file;
        file.open("ProfesoresCurso"+std::to_string(codCurso)+"Carrera"+
        std::to_string(codCarrera)+".txt");
        NodoDeBST *carrera=buscarNodo(codCarrera);
        if(carrera!=NULL){
            NodeAVL * cursos=carrera->cursos->buscarNodo(carrera->cursos->root,codCarrera,codCurso);
            if(cursos!=NULL){
                arbolGrupo* grups=cursos->grupos;
                string s=grups->stringProfesoresGrupo(grups->raiz,profesores);
                file<<s;
            }else{
                string s="No existe el curso especificado";
                file<<s;
            }
        }else{
            string s="No existe la carrera especificada";
            file<<s;
        }
        file.close();
    }
    
    
    void reporteEstGrupo(int codCarrera,int codCurso, int codGrupo,ArbolB* estudiantes){
        ofstream file;
        file.open("ProfesoresCurso"+std::to_string(codCurso)+"Carrera"+
        std::to_string(codCarrera)+".txt");
        NodoDeBST *carrera=buscarNodo(codCarrera);
        if(carrera!=NULL){
            NodeAVL * cursos=carrera->cursos->buscarNodo(carrera->cursos->root,codCarrera,codCurso);
            if(cursos!=NULL){
                nodoGrupo* grups=cursos->grupos->buscarNodo(cursos->grupos->raiz,
                        std::to_string(codCarrera),std::to_string(codCurso),codGrupo);
                if(grups!=NULL){
                    nodoAA* estCurso=grups->miembros;
                    string s=estCurso;
                }else{
                    string s="No existe el grupo especificado";
                    file<<s;
                }
            }else{
                string s="No existe el curso especificado";
                file<<s;
            }
        }else{
            string s="No existe la carrera especificada";
            file<<s;
        }
        file.close();
    }
};
#endif // ARBOLBBCARRERAS_H
