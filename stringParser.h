/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stringParser.h
 * Author: Sir Than II
 *
 * Created on March 26, 2018, 9:39 PM
 */

#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#ifdef __cplusplus
#endif
    
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class nodoS{
    //nodos de string, es una lista simple
public:
    nodoS* siguiente;
    string palabra;
    
    nodoS(string np){
        palabra=np;
        siguiente=NULL;
    }
};

class String{
public:
    nodoS* primero;
    int cantPalabras;
    
    String(){
        primero=NULL;
        cantPalabras=0;
    }
    
    bool oracionTerminada(){return primero==NULL;}
    
    //añade una palabra al final
    void anadirPalabraF(string p){
        if(oracionTerminada()){
            primero= new nodoS(p);
        }else{
            nodoS * aux=primero;
            while(aux->siguiente!=NULL){
                aux=aux->siguiente;
            }
            aux->siguiente=new nodoS(p);
        }
    }
    
    //añade una palabra al inicio
    void anadirPalabraI(string p){
        if(oracionTerminada()){
            primero= new nodoS(p);
        }else{
            nodoS * aux=primero->siguiente;
            primero= new nodoS(p);
            aux->siguiente=primero;
        }
    }
    
    //recibe un string y lo divide por el simbolo s
    void fromSplit(string ff,char s){
        char * f= new char[ff.length()+1];
        strcpy(f,ff.c_str());
        char * pch;
        pch = strtok (f,";");
        while (pch != NULL)
        {
            string pp(pch);
            anadirPalabraF(pp);
            //printf ("%s\n",pch);
            pch = strtok (NULL, ";");
        }
    }
    
    //retorna el valor de la posicion que uno le ponga
    string getPos(int n){
        if(n==1){
            return primero->palabra;
        }else{
            int n2=2;
            nodoS *aux=primero->siguiente;
            while(n2<n && aux!=NULL){
                n2++;
                aux=aux->siguiente;
            }
            return aux->palabra;
        }
    }
    
    
    //borra la frase permitiendo su uso de nuevo
    void borrarFrase(){
        while(primero!=NULL){
            nodoS *aux=primero;
            primero=primero->siguiente;
            delete aux;
        }
    }
    
    
    //probar que haga las cosas bien
    void toString(){
        nodoS* aux=primero;
        while(aux!=NULL){
            cout<<aux->palabra<<endl;
            aux=aux->siguiente;
        }
    }
};


#ifdef __cplusplus
#endif

#endif /* STRINGPARSER_H */

