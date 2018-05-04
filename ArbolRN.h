#ifndef ARBOLRN_H
#define ARBOLRN_H

#ifdef __cplusplus

#include <iostream>
#include <fstream>
#include <sstream>
#include "StringParser.h"
#include "ArbolAA.h"

using namespace std;

class nodoRN{//nodo de curso
public:
    nodoRN* padre;
    nodoRN* hizq;
    nodoRN* hder;
    int llave;//codigo de grupo
    bool negro;//si no es negro es rojo, negro=true significa que el nodo es negro
    
    nodoAA* miembros;
    string codCarrera;
    string codCurso;
    string codProfesor;
    int cupoTotal;
    int cupoCongelado;
    int cupoMatriculado;
    bool abierto=true;
    
    nodoRN(){
        padre=NULL;
        hizq=NULL;
        hder=NULL;
        llave=-1;
        negro=false;
    }
    
    nodoRN(int i){
        padre=NULL;
        hizq=NULL;
        hder=NULL;
        llave=i;
        negro=false;
    }
    
    nodoRN(int i, nodoRN* pp,string ncodCarrera,string ncodCurso,
    string ncodProfesor,string ncupoTotal, string ncupoCongelado, string ncupoMatriculado){
        padre=pp;
        hizq=NULL;
        hder=NULL;
        llave=i;
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
        miembros->armarEstCurso(miembros,codCurso,std::to_string(llave));
    }
    
    void imprimirNodo(){
        cout<<"Valor: "<<llave<<endl;
        cout<<"Color: ";
        if(negro){
            cout<<"Negro"<<endl;
        }else{
            cout<<"Rojo"<<endl;
        }
    }
    
    string datosGrupo(){
        string s="";
        s+="Codigo de Carrera: "+codCarrera+"\n";
        s+="Codigo Curso: "+codCurso+"\n";
        s+="Codigo de Grupo: "+std::to_string(llave)+"\n";
        s+="Cupos Totales: "+std::to_string(cupoTotal)+"\n";
        s+="Cupos Congelados: "+std::to_string(cupoCongelado)+"\n";
        s+="Cupos Matriculado: "+std::to_string(cupoMatriculado)+"\n";
        return s;
    }
    
    void imprimirArbol(nodoRN* raiz){
        if(raiz->esHoja()){
            if(raiz->esLaRaiz())
                cout<<"Es la raiz"<<endl;
            raiz->imprimirNodo();
        }else{
            if(raiz->hizq!=NULL){
                cout<<"Hijos izq de "<<raiz->llave<<endl;
                raiz->hizq->imprimirArbol(raiz->hizq);
            }
            if(raiz->esLaRaiz())
                cout<<"Es la raiz"<<endl;
            raiz->imprimirNodo();
            if(raiz->hder!=NULL){
                cout<<"Hijos der de "<<raiz->llave<<endl;
                raiz->hder->imprimirArbol(raiz->hder);
            }
        }
    }
    
    bool esLaRaiz(){return padre==NULL;}
    
    bool esHoja(){return hder==NULL && hizq==NULL;}
    
    bool tioAplicable(nodoRN* root){
        cout<<"YO:"<<root->llave<<"papi: "<<root->padre->llave<<endl;
        if(root->padre->padre->hder==root->padre){
            cout<<"DERECHO"<<endl;
            if(root->padre->padre->hizq!=NULL){
                if(!root->padre->padre->hizq->negro&!root->padre->negro){
                    return true;
                }else{
                    cout<<"Mi Tio es negro izq"<<endl;
                    return false;
                }
            }else{
                cout<<"NO existe Tio Izq"<<endl;
                return false;
            }
        }else{
            cout<<"IZQUIERDO"<<endl;
            if(root->padre->padre->hder!=NULL){
                if(!root->padre->padre->hder->negro&!root->padre->negro){
                    return true;
                }else{
                    cout<<"Mi Tio es negro der"<<root->padre->padre->hder->llave<<endl;
                    return false;
                }
            }else{
                cout<<"NO existe Tio Der"<<endl;
                return false;
            }
        }
    }
            
    void addNodo(nodoRN* &root, int valor, nodoRN* &laRaiz,string ncodCarrera,string ncodCurso,
    string ncodProfesor,string ncupoTotal, string ncupoCongelado, string ncupoMatriculado){
        bool rojosRepetidos=false;
        bool origenDerecho=false;
        if(root->llave==-1){
            root->llave=valor;
            root->codCarrera=ncodCarrera;
            root->codCurso=ncodCurso;
            root->codProfesor=ncodProfesor;
            root->cupoCongelado=strToint(ncupoCongelado);
            root->cupoMatriculado=strToint(ncupoMatriculado);
            root->cupoTotal=strToint(ncupoTotal);
            root->miembros=new nodoAA();
            root->miembros->armarEstCurso(root->miembros,root->codCurso,std::to_string(root->llave));
            root->padre=NULL;
            root->negro=true;
        }else{
            if(root->llave>valor){
                if(root->hizq==NULL){
                    root->hizq=new nodoRN(valor,root,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                }else{
                    root->hizq->addNodo(root->hizq,valor,laRaiz,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                }
                if(!root->negro&!root->hizq->negro){
                    rojosRepetidos=true;
                    cout<<"Rojos Repetidos: "<<root->llave<<" Y "<<root->hizq->llave<<endl;
                }
            }else if(root->llave <valor){
                if(root->hder==NULL){
                    root->hder=new nodoRN(valor,root,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                }else{
                    root->hder->addNodo(root->hder,valor,laRaiz,ncodCarrera,ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                }
                if(!root->negro&!root->hder->negro){
                    rojosRepetidos=true;
                    cout<<"Rojos Repetidos: "<<root->llave<<" Y "<<root->hder->llave<<endl;
                }
                origenDerecho=true;
            }else{
                if(codProfesor==ncodProfesor){
                    cout<<"Elemento Repetido"<<endl;
                }/*else{
                    root->hizq->addNodo(root->hizq,valor,laRaiz,ncodCarrera,
                            ncodCurso,ncodProfesor,ncupoTotal,ncupoCongelado,ncupoMatriculado);
                    if(!root->negro&!root->hizq->negro){
                        rojosRepetidos=true;
                        cout<<"Rojos Repetidosss "<<root->llave<<" Y "<<root->hizq->llave<<endl;
                    }
                }*/
                
            }
        }
        
        if(rojosRepetidos){
            if(origenDerecho){
                if(root->hder->tioAplicable(root->hder)){
                    cout<<"aplicarTio"<<endl;
                    aplicarTio(root,origenDerecho);
                }else{
                    cout<<"Rotar derecha"<<endl;
                    rotar(root->hder);
                }
            }else{
                if(root->hizq->tioAplicable(root->hizq)){
                    cout<<"aplicarTioizq"<<endl;
                    aplicarTio(root,origenDerecho);
                }else{
                    cout<<"RotarIzquierda"<<endl;
                    rotar(root->hizq);
                    //cout<<"Rotacion terminada"<<root->hizq->hder->llave<<"<-"<<root->llave<<"->"<<root->hder->hizq->llave<<endl;
                }
            }
        }
        cout<<"faq"<<endl;
        if(root!=NULL){
        cout<<"Fuckery :)"<<endl;
        if(root!=NULL&&root->esLaRaiz()){
            cout<<"is the root my brudah"<<endl;
            root->negro=true;
            laRaiz=root;
            //pasarParametros(root,laRaiz);
        }else{
            if(root->hder!=NULL&&root->hder->esLaRaiz()){
                cout<<"is the root my brudah"<<endl;
                root->hder->negro=true;
                laRaiz=root->hder;
            }else if(root->hizq!=NULL&&root->hizq->esLaRaiz()){
                cout<<"is the root my brudah"<<endl;
                root->hizq->negro=true;
                laRaiz=root->hizq;
            }else if(root->padre!=NULL&&root->padre->esLaRaiz()){
                cout<<"is the root my brudah"<<endl;
                root->padre->negro=true;
                laRaiz=root->padre;
            }else{
                cout<<"FUCK!!!!"<<endl;
            }
        }
        }else{
            cout<<"NULL pointer exception"<<endl;
            return;
        }
    }
    
    
    void changeColor(nodoRN* root){
        if(root->negro){
            cout<<root->llave<<"negra"<<endl;
            root->negro=false;
        }else{
            cout<<root->llave<<"roja"<<endl;
            root->negro=true;
        }
    }
    
    void aplicarTio(nodoRN* root,bool derecho){
        if(derecho){
            changeColor(root->padre->hizq);
            changeColor(root->padre);
            changeColor(root);
        }else{
            changeColor(root->padre->hder);
            changeColor(root->padre);
            changeColor(root);
        }
        
        if(root->padre->esLaRaiz()){
            root->padre->negro=true;
        }
        cout<<"Tio aplicado"<<endl;
    }
    
    void rotar(nodoRN* root){
        //nodoRN* retiro;
        switch(valorRotacion(root)){
            case 1:{
                rotacionSSDer(root);
//                changeColor(root->padre);
//                changeColor(root->padre->hder);
                cout<<" rotacion simple der"<<endl;
                break;
            }
            case 2:{
                rotacionDobleDer(root,root->padre->padre,root->padre);
                cout<<"now?"<<endl;
                cout<<" rotacion doble der "<<endl;
                break;
            }
            case 3:{
                rotacionSSIzq(root);
//                changeColor(root->padre);
//                changeColor(root->padre->hizq);
                cout<<" rotacion simple izq"<<endl;
                break;
            }
            case 4:rotacionDobleIzq(root);cout<<" rotacion doble der"<<endl;break;
            default: cout<<"Sin rotacion NANI?!!"<<endl;/*retiro=NULL*/;break;
        }
       // return retiro;
    }
    
    int valorRotacion(nodoRN* root){
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
    
    void rotacionSSIzq(nodoRN* hoja){
        cout<<"Rotacion SSIzq empezada"<<hoja->llave<<endl;
        nodoRN* papi=hoja->padre;
        papi->padre->hder=papi->hizq;
        papi->hizq=papi->padre;
        //papi->hizq->hder=papi->hizq;
        if(papi->padre->padre==NULL){
            cout<<"Root found"<<endl;
            papi->padre=NULL;
            //papi->hizq->padre=papi;
        }else{
            if(papi->padre->padre->hder==papi->padre){
                papi->padre->padre->hder=papi;
            }else{
                papi->padre->padre->hizq=papi;
            }
            papi->padre=papi->padre->padre;
           // papi->hizq->padre=papi;
        }
        papi->hizq->padre=papi;
        changeColor(papi);
        changeColor(papi->hizq);
        //return papi;
        cout<<"Rotacion SSIzq completada"<<endl;
    }
    
    void rotacionSSDer(nodoRN* hoja){
        cout<<"Rotacion SSDer empezada"<<hoja->llave<<endl;
        nodoRN* papi=hoja->padre;
        papi->padre->hizq=papi->hder;
        papi->hder=papi->padre;
        if(papi->padre->padre==NULL){
            cout<<"Root found"<<endl;
            papi->padre=NULL;
            papi->hder->padre=papi;
        }else{
            if(papi->padre->padre->hder==papi->padre){
                papi->padre->padre->hder=papi;
            }else{
                papi->padre->padre->hizq=papi;
            }
            papi->padre=papi->padre->padre;
            //papi->hder->padre=papi;
        }
        papi->hder->padre=papi;
        changeColor(papi);
        changeColor(papi->hder);
        cout<<"Rotacion SSDer completada"<<endl;
        //return papi;
    }
    
    void rotacionSimpleDer(nodoRN* &root){
        cout<<"Iniciando Rotacion simple der"<<endl;
        cout<<"YO: "<<root->llave<<" PAPI:"<<root->padre->llave<<endl;
        nodoRN* &aux=root->padre;
        bool raizmode=false;
        if(aux->esLaRaiz()){
            raizmode=true;
        }else{
            root->padre=aux->padre;
            root->padre->hder=root;
        }
        aux->hizq=root->hder;
        if(aux->hizq!=NULL){
            cout<<"papa"<<endl;
            aux->hizq->padre=aux;
        }
        aux->padre=root;
        root->hder=aux;
        if(raizmode){
            root->padre=NULL;
        }
        cout<<"Rotacion simple der terminada"<<endl;
        cout<<"YO: "<<root->llave<<" Hijo der:"<<root->hder->llave<<"Aux: "<<aux->llave<<endl;
        //cout<<"YO: "<<auxRaiz->llave<<" PAPI:"<<root->padre->llave<<endl;
    }
    
    void rotacionSimpleIzq(nodoRN* &root){
        cout<<"Iniciando Rotacion simple izq"<<endl;
        cout<<"YO: "<<root->llave<<" PAPI:"<<root->padre->llave<<endl;
        bool raizmode=false;
        nodoRN* &aux=root->padre;
        if(root->padre->esLaRaiz()){
            cout<<"el padre"<<root->padre->llave<<"es la raiz"<<endl;
            raizmode=true;
        }else{
            cout<<"el padre"<<root->padre->llave<<" no es la raiz"<<endl;
            root->padre=aux->padre;
            root->padre->hizq=root;
        }
        aux->hder=root->hizq;
        if(aux->hder!=NULL){
            aux->hder->padre=aux;
        }
        aux->padre=root;
        root->hizq=aux;
        if(raizmode){
            root->padre=NULL;
        }
        cout<<"Rotacion simple izq terminada"<<endl;
        cout<<"YO: "<<root->llave<<" hizq:"<<root->hizq->llave<<"aux"<<aux->llave<<endl;
    }
    
    void rotacionDobleDer(nodoRN* root,nodoRN* abuelo,nodoRN* tata){
        cout<<"Iniciando Rotacion doble der"<<root->llave<<endl;
//        nodoRN* &abuelo=root->padre->padre;
//        nodoRN* &tata=root->padre;
        tata->hizq=root->hder;
        if(root->hder!=NULL){
            tata->hizq->padre=tata;
        }
        abuelo->hder=root->hizq;
        if(root->hizq!=NULL){
            abuelo->hder->padre=abuelo;
        }
        root->hder=tata;
        root->hizq=abuelo;
        if(abuelo->padre!=NULL){
            if(abuelo->padre->hder==abuelo){
                abuelo->padre->hder=root;
            }else{
                abuelo->padre->hizq=root;
            }
        }else{
            cout<<"El abuelo es la raiz"<<endl;
        }
        //cout<<"here"<<abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<endl;
        if(abuelo->esLaRaiz()){
            cout<<"yis";
            root->padre=NULL;
        }else{
            cout<<"nos";
            root->padre=abuelo->padre;
        }
        //cout<<"here"<<abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<endl;
        abuelo->padre=root;
        //cout<<"here"<<abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<endl;
        tata->padre=abuelo->padre;
        //cout<<"here"<<abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<endl;
        changeColor(abuelo);
        //cout<<"here"<<abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<endl;
        changeColor(root);
        cout<<"Rotacion doble derecha terminada"<</*abuelo->hizq->llave<<"<-"<<abuelo->llave<<"->"<<abuelo->hder->llave<<*/endl;
        //return root;
    }
    
    void rotacionDobleIzq(nodoRN* &root){
        cout<<"Iniciando Rotacion doble izq"<<root->llave<<endl;
        nodoRN* &abuelo=root->padre->padre;
        nodoRN* &tata=root->padre;
        tata->hder=root->hizq;
        if(root->hizq!=NULL){
            tata->hder->padre=tata;
        }
        abuelo->hizq=root->hder;
        if(root->hder!=NULL){
            abuelo->hizq->padre=abuelo;
        }
        root->hizq=tata;
        root->hder=abuelo;
        if(abuelo->padre!=NULL){
            if(abuelo->padre->hder==abuelo){
                abuelo->padre->hder=root;
            }else{
                abuelo->padre->hizq=root;
            }
        }else{
            cout<<"El abuelo es la raiz"<<endl;
        }
        root->padre=abuelo->padre;
        abuelo->padre=root;
        tata->padre=root;
        changeColor(abuelo);
        changeColor(root);
        cout<<"Rotacion doble izq terminada"<</*abuelo->llave<<"<-"<<root->llave<<"->"<<tata->llave<<*/endl;
        //return root;
    }
    
    int strToint(string s){
        stringstream p;
        p<<s;
        int i;
        p>>i;
        return i;
    }
    
    void cargarGrupos(string carrera,string curso, nodoRN* &root){
        ifstream file;
        file.open("Grupos.txt");
        string fromfile;
        String *data=new String();
        //int datos=0;
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            cout<<data->getPos(1)<<"!="<<carrera<<"&& "<<data->getPos(2)<<"!="<<endl;
            if(data->getPos(1)==carrera&&curso==data->getPos(2)){
                
                addNodo(root,strToint(data->getPos(3)),root,data->getPos(1),data->getPos(2),
                    data->getPos(4),data->getPos(5),data->getPos(6),data->getPos(7));
                print();
            }
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
        }
        //addStudents();
    }
    
   /* void addStudents(){
        if(esHoja()){
            cout<<"codCurso:"<<codCurso<<" Cod grupo:"<<llave<<endl;
            miembros->armarEstCurso(miembros,codCurso,std::to_string(llave));
        }else{
            if(hizq!=NULL){
                hizq->addStudents();
            }
            cout<<"codCurso:"<<codCurso<<" Cod grupo:"<<llave<<endl;
            miembros->armarEstCurso(miembros,codCurso,std::to_string(llave));
            if(hder!=NULL){
                hder->addStudents();
            }
        }
    }*/
    
    void print(){
        if(esHoja()){
            cout<<datosGrupo()<<endl;
            if(miembros!=NULL){
                miembros->preorder(miembros);
            }else{
                cout<<"No tiene miembros"<<endl;
            }
        }else{
            if(hizq!=NULL){
                hizq->print();
                if(miembros!=NULL){
                    hizq->miembros->preorder(miembros);
                }else{
                    cout<<"No tiene miembros"<<endl;
                }
            } 
            cout<<datosGrupo()<<endl;
            if(miembros!=NULL){
            miembros->preorder(miembros);
            }else{
               cout<<"No tiene miembros"<<endl;
            }
            if(hder!=NULL){
                hder->print();
                if(miembros!=NULL){
                hder->miembros->preorder(miembros);
                }else{
                    cout<<"No tiene miembros"<<endl;
                }
            }
        }
        
    }
    
};



#endif

#endif /* ARBOLRN_H */

