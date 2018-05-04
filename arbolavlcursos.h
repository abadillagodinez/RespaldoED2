#ifndef ARBOLAVLCURSOS_H
#define ARBOLAVLCURSOS_H
#include <iostream>
#include "nodeavl.h"
#include <sstream>
#include <fstream>
#include "stringParser.h"

using namespace std;
class ArbolAVLCursos
{
public:
    ArbolAVLCursos(){
        root = NULL;
    }

    ~ArbolAVLCursos(){
    }


    void insert(int pCodCarrera, int pCodCurso, string pNombre){
        insertBalanced(root, pCodCarrera, pCodCurso, pNombre);
    }

    NodeAVL* insertBalanced(NodeAVL* &pRaiz, int pCodCarrera, int pCodCurso, string pNombre){
        //cout << "1. pRaiz es: " << pRaiz << endl;
        if(pRaiz == NULL){
            pRaiz = new NodeAVL(pCodCarrera, pCodCurso, pNombre);
            //cout << "2. pRaiz es: " << pRaiz << endl;
        }
        else if(pCodCurso < pRaiz->codCurso){
            pRaiz->Hizq = insertBalanced(pRaiz->Hizq, pCodCarrera, pCodCurso, pNombre);

            if(getHeight(pRaiz->Hizq) - getHeight(pRaiz->Hder) == 2){
                if(pCodCurso < pRaiz->Hizq->codCurso){
                    pRaiz = rotacionSimpleDerecha(pRaiz);
                }
                else{
                    pRaiz = rotacionDobleDerecha(pRaiz);
                }
            }
        }
        else if(pCodCurso > pRaiz->codCurso){
            pRaiz->Hder = insertBalanced(pRaiz->Hder, pCodCarrera, pCodCurso, pNombre);

            if(getHeight(pRaiz->Hder) - getHeight(pRaiz->Hizq) == 2){
                if(pCodCurso > pRaiz->Hder->codCurso){
                    pRaiz = rotacionSimpleIzquierda(pRaiz);
                }
                else{
                    pRaiz = rotacionDobleIzquierda(pRaiz);
                }
            }
        }
        pRaiz->height = max(getHeight(pRaiz->Hizq), getHeight(pRaiz->Hder))+1;
        return pRaiz;
    }

    void Mostrar(NodeAVL* pRaiz, int n){
        if(pRaiz != NULL){ // Si el árbol no está vacío
            Mostrar(pRaiz->Hder, n+2);
            for(int i = 0; i < n; i++)
                cout << "  ";
            cout << pRaiz->codCurso << endl;
            Mostrar(pRaiz->Hizq, n+2);
        }
    }

    void makeEmptyAux(NodeAVL *pRaiz){
        if(pRaiz == NULL){
            return;
        }
        makeEmptyAux(pRaiz->Hder);
        makeEmptyAux(pRaiz->Hizq);
        delete pRaiz;
    }

    void makeEmpty(){
        makeEmptyAux(root);
    }

    void imprimir(){
        Mostrar(root, 0);
    }
    
    void imprimirArbol(){
        if(root==NULL){
            cout<<"No existen cursos de esa carrera"<<endl;
        }else{
            root->imprimir();
        }
    }

    void CargarCursos(int Carrera){
        ifstream file;
        file.open("Cursos.txt");
        string fromfile;
        String *data=new String();
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            //archivo con formato: codCarrera;codCurso;nombre
            stringstream pos1;
            pos1 << data->getPos(1);
            int nuevoCodCarrera;
            pos1 >> nuevoCodCarrera;
            stringstream pos2;
            pos2 << data->getPos(2);
            int nuevoCodCurso;
            pos2 >> nuevoCodCurso;
            if(Carrera == nuevoCodCarrera){
               insert(nuevoCodCarrera ,nuevoCodCurso ,data->getPos(3));
            }
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
        }
    }

private:

    NodeAVL *root;
    bool isVoid(){
        return root == NULL;
    }


    NodeAVL* rotacionDobleIzquierda(NodeAVL *pRaiz){
        pRaiz->Hder = rotacionSimpleDerecha(pRaiz->Hder);
        return rotacionSimpleIzquierda(pRaiz);
    }


    NodeAVL* rotacionDobleDerecha(NodeAVL *pRaiz){
        pRaiz->Hizq = rotacionSimpleIzquierda(pRaiz->Hizq);
        return rotacionSimpleDerecha(pRaiz);
    }


    NodeAVL* rotacionSimpleIzquierda(NodeAVL *pRaiz){
        NodeAVL *aux = pRaiz->Hder;
        pRaiz->Hder = aux->Hizq;
        aux->Hizq = pRaiz;
        pRaiz->height = max(getHeight(pRaiz->Hizq), getHeight(pRaiz->Hder))+1;
        aux->height = max(getHeight(pRaiz->Hder), pRaiz->height)+1;
        return aux;
    }

    NodeAVL* rotacionSimpleDerecha(NodeAVL *pRaiz){
        NodeAVL *aux = pRaiz->Hizq;
        pRaiz->Hizq = aux->Hder;
        aux->Hder = pRaiz;
        pRaiz->height = max(getHeight(pRaiz->Hizq), getHeight(pRaiz->Hder))+1;
        aux->height = max(getHeight(aux->Hizq), pRaiz->height)+1;
        return aux;
    }


    int getHeight(NodeAVL* pRaiz){
        return (pRaiz == NULL ? -1 : pRaiz->height);
    }

    int getBalance(NodeAVL* pRaiz){
        if(pRaiz == NULL)
            return 0;
        else
            return getHeight(pRaiz->Hizq) - getHeight(pRaiz->Hder);
    }

};
#endif // ARBOLAVLCURSOS_H
