
/* 
 * File:   ArbolAA.h
 * Author: Sir Than II
 *
 * Created on April 26, 2018, 2:42 AM
 */

#ifndef ARBOLAA_H
#define ARBOLAA_H
#include <iostream>
#include <fstream>
#include <sstream>

#include "stringParser.h"

using namespace std;

class nodoAA{
public:
    nodoAA* hder;
    nodoAA* hizq;
//    arbolAA* arbolOrigen;
   // nodoAA* yo;
    int nivel;
    long valor;
    string codGrupo;
    string codCurso;
    
    
    nodoAA(){
        hder=NULL;
        hizq=NULL;
        //yo=this;
        nivel=0;
        valor=0;
    }
    
    nodoAA(int n){
        hder=NULL;
        hizq=NULL;
        //yo=this;
        valor=n;
        nivel=0;
    }
    
    nodoAA(long n, int n2,string ncodGrupo, string ncodCurso){
        hder=NULL;
        hizq=NULL;
        //yo=this;
        valor=n;
        codGrupo=ncodGrupo;
        codCurso=ncodCurso;
        nivel=n2;
    }
    
    bool esHoja(){
        return hder==NULL && hizq==NULL;
    }



    void anadirNodo(nodoAA* &root,long n,string ncodGrupo, string ncodCurso){
        if(root->nivel==0){
            root=new nodoAA(n,1,ncodGrupo,ncodCurso);
        }else{
            if(n>root->valor){
                cout<<"El nuevo es mayor"<<n<<">"<<root->valor<<endl;
                if(root->hder!=NULL){
                    root->hder->anadirNodo(root->hder,n,ncodGrupo,ncodCurso);
                }else{
                    root->hder=new nodoAA(n,root->nivel,ncodGrupo,ncodCurso);
                }
            }else if(n<root->valor){
                cout<<"El nuevo es menor"<<n<<"<"<<root->valor<<endl;
                if(root->hizq!=NULL){
                    root->hizq->anadirNodo(root->hizq,n,ncodGrupo,ncodCurso);
                }else{
                    root->hizq=new nodoAA(n,root->nivel,ncodGrupo,ncodCurso);
                }
            }else{
                cout<<"elemento repetido"<<endl;
                return;
            }
        }
        if(root->hizq!=NULL){
            if(root->nivel==root->hizq->nivel){
                rotacion(root);
            }
        }
        if(root->hder!=NULL){
            if(root->hder->hder!=NULL){
                if(root->nivel==root->hder->nivel&&root->nivel==root->hder->hder->nivel){
                    dividir(root);
                }
            }
        }
    }

    void rotacion(nodoAA* &root){
        nodoAA* aux=root->hizq;
        root->hizq=aux->hder;
        aux->hder=root;
        root=aux;
        cout<<"rotacion completada:"<<root->valor<<endl;
    }
    
    void dividir(nodoAA* &root){
        nodoAA* aux=root->hder;
        root->hder=aux->hizq;
        aux->hizq=root;
        aux->nivel++;
        root=aux;
        cout<<"division completada:"<<root->valor<<endl;
    }
    
    void imprimir(){
        cout<<"Valor:"<<valor<<endl;
        cout<<"CodCurso"<<codCurso<<endl;
        cout<<"CodGrupo"<<codGrupo<<endl;
        cout<<"Nivel:"<<nivel<<endl;
    }
    
    void preorder(nodoAA* &root){
        if(root->esHoja()){
            cout<<"ës hoja"<<endl;
            root->imprimir();
        }else{
            if(root->hizq!=NULL){
                root->hizq->preorder(root->hizq);
            }
            root->imprimir();
            if(root->hder!=NULL){
                root->hder->preorder(root->hder);
            }
        }
    }
    
    long StrTL(string s){
        stringstream p;
        p<<s;
        long i;
        p>>i;
        return i;
    }
    
    void armarEstCurso(nodoAA* &root,string curso, string grupo){
        ifstream file;
        file.open("Estudiante-Curso.txt");
        string fromfile;
        String *data=new String();
        int datos=0;
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
//            cout<<"cursos y grupos" <<endl;
//            cout<<data->getPos(2)<<endl;
//            cout<<data->getPos(3)<<endl;
            if(curso==data->getPos(2) && grupo==data->getPos(3)){
                anadirNodo(root,StrTL(data->getPos(1)),data->getPos(3),data->getPos(2));
//                cout<<"ESt curso anadido"<<endl;
//                //root->imprimir();
//                cout<<"printo"<<endl;
//                datos++;
            }
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                
                file.close();
            }
            //cout<<"Cuso anadido"<<endl;
        }//cout<<"CAntida de estcurso"<<datos<<endl;
        return;
    }
    
    nodoAA *buscarNodo(nodoAA *pRaiz,string codGrupo, string codCurso, long idEstudiantes){
        nodoAA *res = NULL;
        if(pRaiz->valor == idEstudiantes&&pRaiz->codCurso==codCurso&&pRaiz->codGrupo==codGrupo){
            res = pRaiz;
        }
        else if(pRaiz->valor < idEstudiantes){
            res=buscarNodo(pRaiz->hder, codGrupo,codCurso,idEstudiantes);
        }
        else if(pRaiz->valor > idEstudiantes){
            res=buscarNodo(pRaiz->hizq, codGrupo,codCurso,idEstudiantes);
        }
        return res;
    }
};


/*class arbolAA{
public:
    nodoAA* raiz;
    
    arbol(){
        raiz=NULL;
    }
    
    bool arbolVacio(){return raiz==NULL;}
    
    void insertar(nodoAA* &root,int n){
        if(root==NULL){
            root=new nodoAA(n);
            root->nivel++;
            raiz=root;
        }else{
            if(n>root->valor){
                if(root->hder!=NULL){
                    if(root->hder->valor<n){
                        insertar(root->hder,n);
                    }else{
                        nodoAA* aux=root->hder;
                        root->hder=new nodoAA(n);
                        root->hder->nivel++;
                        root->hder->hder=aux;
                    }
                    
                }else{
                    root->hder=new nodoAA(n);
                    root->hder->nivel++;
                }
            }else{
                if(root->hizq!=NULL){
                    insertar(root->hizq,n);
                }else{
                    root->hizq=new nodoAA(n);
                    root->hizq->nivel++;
                }
            }
        }
        if(root->hizq!=NULL){
            if(root->nivel==root->hizq->nivel){
                rotar(root);
            }
        }
        if(root->hder!=NULL){
            if(root->hder->hder!=NULL){
                if(root->nivel==root->hder->nivel&&root->nivel==root->hder->hder->nivel){
                    dividir(root);
                }
            }
        }
    }
    
    void rotar(nodoAA* &root){
        nodoAA* aux=root->hizq;
        root->hizq=aux->hder;
        aux->hder=root;
        root=aux;
        cout<<"rotacion completada:"<<root->valor<<endl;
    }
    
    void dividir(nodoAA* &root){
        nodoAA* aux=root->hder;
        root->hder=aux->hizq;
        aux->hizq=root;
        aux->nivel++;
        root=aux;
        cout<<"division completada:"<<root->valor<<endl;
    }
    
    void imprimirArbol(nodoAA* &root){
        if(root!=NULL){
            if(root->hizq!=NULL){
                imprimirArbol(root->hizq);
            }
            root->imprimir();
            if(root->hder!=NULL){
                imprimirArbol(root->hder);
            }
        }
    }
};*/



#endif


