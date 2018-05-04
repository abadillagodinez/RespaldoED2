/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mostradorJonathan.h
 * Author: Sir Than II
 *
 * Created on May 4, 2018, 3:52 AM
 */

#ifndef MOSTRADORJONATHAN_H
#define MOSTRADORJONATHAN_H

#include "ColaDeAtencion.h"
#include "arbolbbcarreras.h"
#include "Estudiantestree.h"
#include "ProfesoresTree.h"
#include <iostream>

using namespace std;


class nodoMostrador{
public:
    nodoMostrador* siguiente;
    nodoMostrador* anterior;
    NodoDAtencion* actual;
    bool ocupado;
    int cantidadAtendidos;
    ArbolB* estudiantes;
    ArbolBp* profes;
    ArbolDeCarreras* carreras;
    ColaDeAtencion* fila;
    int estado;
    
    nodoMostrador(ColaDeAtencion* col){
        siguiente=this;
        anterior=this;
        actual=NULL;
        ocupado=false;
        cantidadAtendidos=0;
        estado=0;
        fila=col;
    }
    
    int StrTL(string s){
        stringstream p;
        p<<s;
        int i;
        p>>i;
        return i;
    }


    void atender(NodoDAtencion *cliente){
        estudiante* estudianteBD=estudiantes->buscarEstudiante(cliente->idEstudiante);
        if(estudianteBD!=NULL){
            NodoDeBST* carrera=carreras->buscarNodo(carreras->raiz,estudianteBD->codCarrera);
            if(carrera!=NULL){
                NodeAVL* curso=carrera->cursos->buscarNodo(carrera->cursos->root,
                        carrera->codCarrera,StrTL(cliente->codCurso));
                if(curso!=NULL){
                    stringstream ss;
                    int codGrup;
                    ss << cliente->codGrupo;
                    ss >> codGrup;
                    nodoGrupo* grupo = curso->grupos->buscarNodo(curso->grupos->raiz, to_string(curso->codCarrera), to_string(curso->codCurso), codGrup);
                    if(grupo!=NULL){
                        switch(cliente->accion){
                        case 1:matricular(estudianteBD,grupo);break;
                        case 2:desmatricular(estudianteBD,grupo);break;
                        case 3:congelar(estudianteBD,grupo);break;
                            default:cout<<"Eso no se puede hacer joven: "<<estudianteBD->nombre<<endl;break;
                        }
                    }else{
                        cout<<"El grupo del estudiante atendido no esta registrado"<<endl;
                        //cliente->atendido=true;
                    }
                }else{
                    cout<<"El curso del estudiante atendido no esta registrado"<<endl;
                    //cliente->atendido=true;
                }
            }else{
                cout<<"La carrera del estudiante atendido no esta registrado"<<endl;
                //cliente->atendido=true;
            }
        }else{
            cout<<"El estudiante atendido no esta registrado"<<endl;
            //cliente->atendido=true;
        }
        //fila->eliminar1();
        //cout<<"avanza?"<<endl;
    }

        //return this;
    
    
    void static matricular(estudiante* estudiante, nodoGrupo* grupo){
        if(grupo->cupoMatriculado+grupo->cupoCongelado==grupo->cupoTotal){
            cout<<"Grupo lleno no se puede matricular, lo sentimos: "+estudiante->nombre<<endl;
        }else{
            grupo->cupoMatriculado++;
            grupo->miembros->anadirNodo(grupo->miembros, estudiante->idEstudiante, to_string(grupo->codGrupo),grupo->codCurso);
        }
        
    }
    
    void static desmatricular(estudiante* estudiante, nodoGrupo* grupo){
        if(grupo->cupoMatriculado+grupo->cupoCongelado==0){
            cout<<"El grupo no tiene estudiantes matriculados, no es posible desmatricular: "+estudiante->nombre<<endl;
        }else{
            grupo->cupoMatriculado--;
        }
    }
    
    
    void static congelar(estudiante* estudiante, nodoGrupo* grupo){
        if(grupo->cupoMatriculado==0){
            cout<<"El grupo no tiene estudiantes matriculados, no es posible congelar: "+estudiante->nombre<<endl;
        }else{
            grupo->cupoCongelado++;
        }
    }
    
    friend class mostradores;
    friend class nodoMostrador;
};

class mostradores{
public:
    nodoMostrador* primero;
    nodoMostrador* segundo;
    nodoMostrador* tercero;
    
    mostradores(ColaDeAtencion* fila){
        primero=new nodoMostrador(fila);
        primero->siguiente=new nodoMostrador(fila);
        segundo=primero->siguiente;
        segundo->siguiente=new nodoMostrador(fila);
        tercero=segundo->siguiente;
        primero->anterior=tercero;
        tercero->siguiente=primero;
        segundo->anterior=primero;
        tercero->anterior=segundo;
    }
    
    void giveData(ArbolBp* profes,ArbolB* estudiantes,ArbolDeCarreras* carreras){
        primero->profes=profes;
        primero->estudiantes=estudiantes;
        primero->carreras=carreras;
        segundo->profes=profes;
        segundo->estudiantes=estudiantes;
        segundo->carreras=carreras;
        tercero->profes=profes;
        tercero->estudiantes=estudiantes;
        tercero->carreras=carreras;
    }
    
    
};



#endif /* MOSTRADORJONATHAN_H */

