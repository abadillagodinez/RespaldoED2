/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArbolGrupos.h
 * Author: Sir Than II
 *
 * Created on May 4, 2018, 12:26 AM
 */

#ifndef ARBOLGRUPOS_H
#define ARBOLGRUPOS_H
#include <iostream>
#pragma once

#include "ArbolAA.h"

using namespace std;

class nodoGrupo{
public:
    int codGrupo;
    bool negro;//true significa que es negro
    nodoGrupo* hder;
    nodoGrupo* hizq;
    nodoGrupo* padre;
    
    nodoAA* miembros;
    string codCarrera;
    string codCurso;
    string codProfesor;
    int cupoTotal;
    int cupoCongelado;
    int cupoMatriculado;
    
    nodoGrupo(){
        codGrupo=-1;
        hder=NULL;
        hizq=NULL;
        padre=NULL;
    }
    
    nodoGrupo(int n,string ncodCarrera,string ncodCurso, string ncodProfesor,
    string ncupoTotal, string ncupoCongelado, string ncupoMatriculado){
        codGrupo=n;
        hder=NULL;
        hizq=NULL;
        padre=NULL;
        negro=false;
        //
        codCarrera=ncodCarrera;
        codCurso=ncodCurso;
        codProfesor=ncodProfesor;
        stringstream total(ncupoTotal);
        stringstream congelado(ncupoCongelado);
        stringstream matriculado(ncupoMatriculado);
        total>>cupoTotal;
        congelado>>cupoCongelado;
        matriculado>>cupoMatriculado;
        miembros=new nodoAA();
        miembros->armarEstCurso(miembros,codCurso,std::to_string(codGrupo));
        imprimirNodo();
    }
    
    bool isHoja(){
        return hder==NULL && hizq==NULL;
    }
    
    bool esLaRaiz(){
        return padre==NULL;
    }
    
    string datosGrupo(){
        string s="";
        s+="Codigo de Carrera: "+codCarrera+"\n";
        s+="Codigo Curso: "+codCurso+"\n";
        s+="Codigo de Grupo: "+std::to_string(codGrupo)+"\n";
        s+="Cupos Totales: "+std::to_string(cupoTotal)+"\n";
        s+="Cupos Congelados: "+std::to_string(cupoCongelado)+"\n";
        s+="Cupos Matriculado: "+std::to_string(cupoMatriculado)+"\n";
        return s;
    }
    
    void imprimirNodo(){
        cout<<"Valor: "<<codGrupo<<endl;
        cout<<"Color: ";
        if(negro){
            cout<<"Negro"<<endl;
        }else{
            cout<<"Rojo"<<endl;
        }
    }
    
    void imprimir(){
        cout<<datosGrupo()<<endl;
        if(miembros!=NULL){
            cout<<"Miembros: "<<endl;
            miembros->imprimir();
        }
    }
    
    void imprimirNodos(){
        if(isHoja()){
            if(esLaRaiz()){
                cout<<"LA RAIZ2"<<endl;
            }
            imprimir();
        }else{
            if(hizq!=NULL){
                hizq->imprimir();
            }
            if(esLaRaiz()){
                cout<<"LA RAIZ"<<endl;
            }
            imprimirNodo();
            if(hder!=NULL){
                hder->imprimir();
            }
        }
    }
    
};

class arbolGrupo{
public:
    nodoGrupo* raiz;
    static bool rootInProblems;
    
    arbolGrupo(){
        raiz=NULL;
    }
    
    void insertar(int n,string ncodCarrera,string ncodCurso, string ncodProfesor,
    string ncupoTotal, string ncupoCongelado, string ncupoMatriculado ){
        if(raiz==NULL){
            cout<<"FCU"<<endl;
            raiz= new nodoGrupo(n,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
            raiz->negro=true;
        }else{
            rootInProblems=false;
            bool derecho=false;//que se fue por el lado derecho
            if(n>raiz->codGrupo){
                nodoGrupo* nodo=new nodoGrupo(n,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                if(raiz->hder!=NULL){
                    insertarEnNodo(raiz->hder,nodo);
                }else{
                    raiz->hder=nodo;
                    raiz->hder->padre=raiz;
                }
                derecho=true;
            }else if(n<raiz->codGrupo){
                nodoGrupo* nodo=new nodoGrupo(n,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                if(raiz->hizq!=NULL){
                    insertarEnNodo(raiz->hizq,nodo);
                }else{
                    raiz->hizq=nodo;
                    raiz->hizq->padre=raiz;
                }
            }else{
                cout<<"Elemento repetido"<<endl;
            }
            cout<<"Root in problems?"<<rootInProblems<<endl;
            if(rootInProblems){
                if(derecho){
                    if(tioAplicable(raiz->hder)){
                        aplicarTio(raiz->hder);
                        cout<<"tio aplicado en root"<<endl;
                    }else{
                        raiz=rotarRaiz(raiz->hder);
                         cout<<"rotacion aplicada en raiz;"<<endl;
                    }
                }else{
                    if(tioAplicable(raiz->hizq)){
                        aplicarTio(raiz->hizq);
                        cout<<"tio aplicado en root"<<endl;
                    }else{
                        raiz=rotarRaiz(raiz->hizq);
                        cout<<"rotacion aplicada en raiz;"<<endl;
                    }
                }
            }
            raiz->negro=true;
        } 
    }
    
    void insertarEnNodo(nodoGrupo* origen, nodoGrupo* nodo){
        bool rojosRepetidos;
        if(nodo->codGrupo>origen->codGrupo){
            if(origen->hder==NULL){
                origen->hder=nodo;
                origen->hder->padre=origen;
            }else{
                insertarEnNodo(origen->hder,nodo);
            }
            if(!origen->negro&&!origen->hder->negro){
               rojosRepetidos=true; 
            }
        }else if(nodo->codGrupo<origen->codGrupo){
            if(origen->hizq==NULL){
                origen->hizq=nodo;
                origen->hizq->padre=origen;
            }else{
                insertarEnNodo(origen->hizq,nodo);
            }
            if(!origen->negro&&!origen->hizq->negro){
               rojosRepetidos=true; 
            }
        }else{
            cout<<"Elemento repetido"<<endl;
        }
        
        if(rojosRepetidos){
            cout<<"Se despicho tere"<<endl;
            if(origen->padre->esLaRaiz()){
                rootInProblems=true;
                cout<<"things are going down"<<endl;
                return;
            }else{
                if(tioAplicable(origen)){
                    aplicarTio(origen);
                }else{
                    rotar(origen);
                }
            }
        }
    }
    
    bool tioAplicable(nodoGrupo* padre){
        if(padre->padre->hder==padre){
            if(padre->padre->hizq==NULL){
                return false;
            }else{
                if(padre->padre->hizq->negro){
                    return false;
                }else{
                    return true;
                }
            }
        }else{
            if(padre->padre->hder==NULL){
                return false;
            }else{
                if(padre->padre->hder->negro){
                    return false;
                }else{
                    return true;
                }
            }
        }
    }
    
    void aplicarTio(nodoGrupo* padre){
        if(padre->padre->hder=padre){
            changeColor(padre->padre->hizq);
        }else{
            changeColor(padre->padre->hder);
        }
        changeColor(padre->padre);
        changeColor(padre);
    }
    
    void changeColor(nodoGrupo* nodo){
        if(nodo->negro){
            nodo->negro=false;
        }else{
            nodo->negro=true;
        }
    }
    
    void rotar(nodoGrupo* root){
        switch(valorRotacion(root)){
            case 1:{
                rotacionSimpleDer(root);
                changeColor(root);
                changeColor(root->hder);
                cout<<" rotacion simple der"<<endl;
                break;
            }
            case 2:{
                rotacionDobleDer(root);
                cout<<" rotacion doble der "<<endl;
                break;
            }
            case 3:{
                rotacionSimpleIzq(root);
                changeColor(root);
                changeColor(root->hizq);
                cout<<" rotacion simple izq"<<endl;
                break;
            }
            case 4:{
                rotacionDobleIzq(root);
                cout<<" rotacion doble der"<<endl;
                break;}
            default: cout<<"Sin rotacion NANI?!!"<<endl;/*retiro=NULL*/;break;
        }
    }
    
    int valorRotacion(nodoGrupo* root){
        cout<<"Averiguar valor rotacion"<<endl;
        if(root->padre->hder==root){
            cout<<"Soy el huevo derecho de mi padre"<<endl;
            if(root->padre->padre->hizq==root->padre){
                cout<<"Y el es el huevo izquierdo de mi abuelo"<<endl;
                return 4;
            }else{
                cout<<"Y el es el huevo derecho de mi abuelo"<<endl;
                return 3;
            }
        }else{
            cout<<"Soy el huevo izquierdo de mi padre"<<endl;
            if(root->padre->padre->hder==root->padre){
                cout<<"Y el es el huevo derecho de mi abuelo"<<endl;
                return 2;
            }else{
                cout<<"Y el es el huevo izquierdo de mi abuelo"<<endl;
                return 1;
            }
        }
    }
    
    void rotacionSimpleDer(nodoGrupo* root){
        nodoGrupo* tata=root->padre;
        if(tata=tata->padre->hder){
            tata->padre->hder=root;
        }else{
            tata->padre->hizq=root;
        }
        root->padre=tata->padre;
        if(root->hder!=NULL){
            tata->hizq=root->hder;
            tata->hizq->padre=tata;
        }else{
            tata->hizq=NULL;
        }
        root->hder=tata;
        tata->padre=root;
        cout<<"Rotacion simple der terminada"<<endl;
    }
    
    void rotacionSimpleIzq(nodoGrupo* root){
        nodoGrupo* tata=root->padre;
        if(tata=tata->padre->hder){
            tata->padre->hder=root;
        }else{
            tata->padre->hizq=root;
        }
        root->padre=tata->padre;
        if(root->hizq!=NULL){
            tata->hder=root->hizq;
            tata->hder->padre=tata;
        }else{
            tata->hder=NULL;
        }
        root->hizq=tata;
        tata->padre=root;
        cout<<"Rotacion simple izq terminada"<<endl;
    }
    
    void rotacionDobleDer(nodoGrupo* root){
        rotacionSimpleDer(root);
        rotacionSimpleIzq(root);
        changeColor(root);
        changeColor(root->hizq);
    }
    
    void rotacionDobleIzq(nodoGrupo* root){
        rotacionSimpleIzq(root);
        rotacionSimpleDer(root);
        changeColor(root);
        changeColor(root->hder);
    }
    
    nodoGrupo* rotarRaiz(nodoGrupo* hijoRaiz){
        nodoGrupo* nuevaRaiz;
        switch(valorRotacionRaiz(hijoRaiz)){
            case 1:{
                nuevaRaiz=rotacionDobleIzqRaiz(hijoRaiz);
                break;
            }
            case 2:{
                nuevaRaiz=rotacionSimpleDerRaiz(hijoRaiz);
                break;
            }
            case 3:{
                nuevaRaiz=rotacionDobleDerRaiz(hijoRaiz);
                break;
            }
            case 4:{
                nuevaRaiz=rotacionSimpleIzqRaiz(hijoRaiz);
                break;
            }
            default:{
                cout<<"A la mierda la progra"<<endl; break;
            }
        }
        return nuevaRaiz;
    }
    
    int valorRotacionRaiz(nodoGrupo* hijoRaiz){
        if(hijoRaiz->padre->hizq==hijoRaiz){
            cout<<"Soy el hijo izquierdo de la raiz"<<endl;
            if(hijoRaiz->hder!=NULL){
                cout<<"Mi hijo es mi huevo derecho"<<endl;
                return 1;
            }else{
                cout<<"Mi hijo es mi huevo izquierdo"<<endl;
                return 2;
            }
        }else{
            cout<<"Soy el hijo derecho de la raiz"<<endl;
            if(hijoRaiz->hizq!=NULL){
                cout<<"Mi hijo es mi huevo izquiedo"<<endl;
                return 3;
            }else{
                cout<<"Mi hijo es mi huevo derecho"<<endl;
                return 4;
            }
        }
    }
    
    nodoGrupo* rotacionDobleIzqRaiz(nodoGrupo* hijoRaiz){
        nodoGrupo* root=hijoRaiz->padre;
        nodoGrupo* hijo=hijoRaiz->hder;
        hijoRaiz->hder=hijo->hizq;
        if(hijoRaiz->hder!=NULL){
            hijoRaiz->hder->padre=hijoRaiz;
        }
        root->hizq=hijo->hder;
        if(root->hizq!=NULL){
            root->hizq->padre=root;
        }
        hijo->hizq=hijoRaiz;
        hijo->hder=root;
        hijo->hizq->padre=hijo;
        hijo->hder->padre=hijo;
        hijo->padre=NULL;
        changeColor(hijo);
        changeColor(root);
        cout<<"RotacionDoble izq raiz terminada"<<endl;
        return hijo;
    }
    
    nodoGrupo* rotacionDobleDerRaiz(nodoGrupo* hijoRaiz){
        nodoGrupo* root=hijoRaiz->padre;
        nodoGrupo* hijo=hijoRaiz->hizq;
        hijoRaiz->hizq=hijo->hder;
        if(hijoRaiz->hizq!=NULL){
            hijoRaiz->hizq->padre=hijoRaiz;
        }
        root->hder=hijo->hizq;
        if(root->hder!=NULL){
            root->hder->padre=root;
        }
        hijo->hder=hijoRaiz;
        hijo->hizq=root;
        hijo->hder->padre=hijo;
        hijo->hizq->padre=hijo;
        hijo->padre=NULL;
        changeColor(hijo);
        changeColor(root);
        cout<<"RotacionDoble der raiz terminada"<<endl;
        return hijo;
    }
    
    nodoGrupo* rotacionSimpleDerRaiz(nodoGrupo* hijoRaiz){
        nodoGrupo* root=hijoRaiz->padre;
        root->hizq=hijoRaiz->hder;
        if(root->hizq!=NULL){
            root->hizq->padre=root;
        }
        hijoRaiz->hder=root;
        root->padre=hijoRaiz;
        hijoRaiz->padre=NULL;
        changeColor(hijoRaiz);
        changeColor(root);
        cout<<"Rotacionsimple der Raiz completada"<<endl;
        return hijoRaiz;
    }
    
    nodoGrupo* rotacionSimpleIzqRaiz(nodoGrupo* hijoRaiz){
        nodoGrupo* root=hijoRaiz->padre;
        root->hder=hijoRaiz->hizq;
        if(root->hizq!=NULL){
            root->hizq->padre=root;
        }
        hijoRaiz->hizq=root;
        root->padre=hijoRaiz;
        hijoRaiz->padre=NULL;
        changeColor(hijoRaiz);
        changeColor(root);
        cout<<"Rotacionsimple izq Raiz completada"<<endl;
        return hijoRaiz;
    }
    
    void imprimirArbol(){
        if(raiz==NULL){
            cout<<"no hay elementos en el arbol"<<endl;
        }else{
            raiz->imprimirNodos();
        }
    }
    
    int strToint(string s){
        stringstream p;
        p<<s;
        int i;
        p>>i;
        return i;
    }
    
    void cargarGrupos(string carrera,string curso){
        ifstream file;
        file.open("Grupos.txt");
        string fromfile;
        String *data=new String();
        //int datos=0;
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            //cout<<data->getPos(1)<<"!="<<carrera<<"&& "<<data->getPos(2)<<"!="<<curso<<endl;
            if(data->getPos(1)==carrera&&curso==data->getPos(2)){
                insertar(strToint(data->getPos(3)),data->getPos(1),data->getPos(2),
                    data->getPos(4),data->getPos(5),data->getPos(6),data->getPos(7));
                imprimirArbol();
            }
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
        }
    }
    
    nodoGrupo *buscarNodo(nodoGrupo *pRaiz, string codCarrera, string codCurso, int codGrupo){
        nodoGrupo *res = NULL;
        if(pRaiz->codCarrera == codCarrera&&pRaiz->codCurso==codCurso&&pRaiz->codGrupo==codGrupo){
            res = pRaiz;
        }
        else if(pRaiz->codGrupo < codGrupo){
            res=buscarNodo(pRaiz->hder, codCarrera,codCurso,codGrupo);
        }
        else if(pRaiz->codGrupo > codGrupo){
            res=buscarNodo(pRaiz->hizq, codCarrera,codCurso,codGrupo);
        }
        return res;
    }
    
    int StrTL(string s){
        stringstream p;
        p<<s;
        int i;
        p>>i;
        return i;
    }
    
    string stringProfesoresGrupo(nodoGrupo* gp,ArbolBp * profesores){
        string s="";
        if(gp->isHoja()){
            profesor* tcj=profesores->buscarEstudiante(StrTL(gp->codProfesor));
            s+=tcj->to_string();
            return s;
        }else{
            if(gp->hizq!=NULL){
                s+=stringProfesoresGrupo(gp->hizq,profesores);
            }
            profesor* tcj=profesores->buscarEstudiante(StrTL(gp->codProfesor));
            s+=tcj->to_string();
            if(gp->hder!=NULL){
                s+=stringProfesoresGrupo(gp->hder,profesores);
            }
            return s;
        }
    }
    
    
    
};

bool arbolGrupo::rootInProblems=false;



#endif /* ARBOLGRUPOS_H */

