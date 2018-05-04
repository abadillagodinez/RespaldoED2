

#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>

#include "StringParser.h"

using namespace std;

class NodoGrupo{
public:
    char color;
    bool rojo;
    int codigoCarrera;
    int codigoCurso;
    int codigoGrupo;
    int codigoProfesor;
    int cupoTotal;
    int cupoMatriculado;
    int cupoCongelado;
    NodoGrupo *hijoIzquierdo;
    NodoGrupo *hijoDerecho;
    NodoGrupo *padre;
    
    NodoGrupo(int pCodigoCarrera, int pCodigoCurso, int pCodigoGrupo, int pCodigoProfesor, int pCupoTotal, int pCupoMatriculado, int pCupoCongelado)
{
    codigoCarrera = pCodigoCarrera;
    codigoCurso = pCodigoCurso;
    codigoGrupo = pCodigoGrupo;
    codigoProfesor = pCodigoProfesor;
    cupoTotal = pCupoTotal;
    cupoMatriculado = pCupoMatriculado;
    cupoCongelado = pCupoCongelado;
    hijoIzquierdo = NULL;
    hijoDerecho = NULL;
    padre = NULL;
    rojo = true;
}
    
    friend class arbolRN;

};

class arbolRN{
public:
    NodoGrupo* raiz;
    
    arbolRN(){raiz = NULL;}

    bool arbolVacio(){return raiz == NULL;}

    void insertar(NodoGrupo* &pRaiz, int pCodigoCarrera, int pCodigoCurso, int pCodigoGrupo, 
    int pCodigoProfesor, int pCupoTotal, int pCupoMatriculado, int pCupoCongelado){
    int cont = 0;
    NodoGrupo* nuevo = NULL;
    NodoGrupo* otro = pRaiz;
    NodoGrupo* aux = NULL;

    while(pRaiz != NULL){
        aux = pRaiz;
        if(pCodigoGrupo < pRaiz -> codigoGrupo){
            pRaiz = pRaiz -> hijoIzquierdo;
        }else if(pCodigoGrupo > pRaiz -> codigoGrupo){
            pRaiz = pRaiz -> hijoDerecho;
        }else{
            //validar aca, si pongo cont  = 0; pega más grupos pero no imprime los ultimos
            cont = 1;
            break;
        }
    }
    if(cont == 0){
        nuevo = new NodoGrupo(pCodigoCarrera,pCodigoCurso,pCodigoGrupo,pCodigoProfesor,
                pCupoTotal,pCupoMatriculado,pCupoCongelado);
        nuevo -> padre = aux;
        nuevo -> color = 'r';
        if(aux == NULL){
            nuevo -> color = 'b';
            raiz = nuevo;
            return;
        }else if(pCodigoGrupo < aux -> codigoGrupo){
            aux -> hijoIzquierdo = nuevo;
        }
        else{
            aux -> hijoDerecho = nuevo;
        }
        insertarArreglado(nuevo,otro);
    }
}

void insertarArreglado(NodoGrupo* &nuevo, NodoGrupo* &pRaiz){
    raiz = pRaiz;
    while((nuevo -> padre != NULL) && (nuevo -> padre -> color == 'r'))    {
        if(nuevo -> padre == nuevo -> padre -> padre -> hijoIzquierdo)        {
            NodoGrupo* aux = nuevo -> padre -> padre -> hijoDerecho;
            if((aux != NULL) && (aux -> color == 'r'))            {
                nuevo -> padre -> color = 'b';
                aux -> color = 'b';
                nuevo -> padre -> padre -> color = 'r';
                nuevo = nuevo -> padre -> padre;
            }
            else{
                if(nuevo == nuevo -> padre -> hijoDerecho){
                    nuevo = nuevo -> padre;
                    rotarIzquierda(nuevo);
                }
                nuevo -> padre -> color = 'b';
                nuevo -> padre -> padre -> color = 'r';
                rotarDerecha(nuevo -> padre -> padre);
            }
        }
        else{
            NodoGrupo* aux = nuevo -> padre -> padre -> hijoIzquierdo;
            if((aux != NULL) && (aux -> color == 'r')){
                nuevo -> padre -> color = 'b';
                aux -> color = 'b';
                nuevo -> padre -> padre -> color = 'r';
                nuevo = nuevo -> padre -> padre;
            }
            else{
                if(nuevo == nuevo -> padre -> hijoIzquierdo){
                    nuevo = nuevo -> padre;
                    rotarDerecha(nuevo);
                }
                nuevo -> padre -> color = 'b';
                nuevo -> padre -> padre -> color = 'r';
                rotarIzquierda(nuevo -> padre -> padre);
            }
        }
    }
    raiz -> color = 'b';
}

void rotarIzquierda(NodoGrupo* subRaiz){
    NodoGrupo* temp = subRaiz -> hijoDerecho;
    subRaiz -> hijoDerecho = temp -> hijoIzquierdo;
    if(temp -> hijoIzquierdo != NULL){
        temp -> hijoIzquierdo -> padre = raiz;
    }
    temp -> padre = subRaiz -> padre;
    if(subRaiz -> padre == NULL){
        raiz = temp;
    }else if(subRaiz == subRaiz -> padre -> hijoIzquierdo){
        subRaiz -> padre -> hijoIzquierdo = temp;
    }else{
        subRaiz -> padre -> hijoDerecho = temp;
    }
    temp -> hijoIzquierdo = subRaiz;
    subRaiz -> padre = temp;
}

void rotarDerecha(NodoGrupo* subRaiz){
    NodoGrupo* temp = subRaiz -> hijoIzquierdo;
    subRaiz -> hijoIzquierdo = temp -> hijoDerecho;
    if(temp -> hijoDerecho != NULL){
        temp -> hijoDerecho -> padre = raiz;
    }
    temp -> padre = subRaiz -> padre;
    if(subRaiz -> padre == NULL){
        raiz = temp;
    }else if(subRaiz == subRaiz -> padre -> hijoDerecho){
        subRaiz -> padre -> hijoDerecho = temp;
    }else{
        subRaiz -> padre -> hijoIzquierdo = temp;
    }
    temp -> hijoDerecho = subRaiz;
    subRaiz -> padre = temp;
}

void mostrarArbol(NodoGrupo* actual){
    if(actual == NULL){
        return;
    }else{
        mostrarArbol(actual -> hijoIzquierdo);
        cout << "Carrera: " << actual -> codigoCarrera << "\tCurso: " << actual -> codigoCurso << "\tGrupo: " <<
                actual -> codigoGrupo << "\tProfesor: " << actual -> codigoProfesor << "\tCupo total: " <<
                actual -> cupoTotal << "\tCupo matriculado: " << actual -> cupoMatriculado <<
                "\tCupo congelado: " << actual -> cupoCongelado << endl;
        mostrarArbol(actual -> hijoDerecho);
    }
}

NodoGrupo* getRaiz(){return raiz;}

int stint(string s){
    stringstream k;
    k<<s;
    int i;
    k>>i;
    return i;
}
/*void ArbolGrupo::lecturaArchivo()
{
    string linea, word1, word2,word3,word4,word5,word6,word7;
    size_t pos = 0;
    string token;
    int cont = 0;
    string delimitador = ";";

    ifstream archivo("Grupos.txt");
    if(archivo.is_open())
    {
        while(getline(archivo,linea))
        {
            while((pos = linea.find(delimitador)) != string::npos)
            {
                token = linea.substr(0,pos);
                if(cont == 0)
                {
                    word1 = token;
                }
                else if(cont == 1)
                {
                    word2 = token;
                }
                else if(cont == 2)
                {
                    word3 = token;
                }
                else if(cont == 3)
                {
                    word4 = token;
                }
                else if(cont == 4)
                {
                    word5 = token;
                }
                else if(cont == 5)
                {
                    word6 = token;
                }
                linea.erase(0,pos+delimitador.length());
                cont++;
            }
            word7 = linea;
            cont = 0;
            int codCarrera = atoi(word1.c_str());
            int codCurso = atoi(word2.c_str());
            int codGrupo = atoi(word3.c_str());
            int codProfesor = atoi(word4.c_str());
            int cupoT = atoi(word5.c_str());
            int cupoM = atoi(word6.c_str());
            int cupoC = atoi(word7.c_str());
            insertar(getRaiz(),codCarrera,codCurso,codGrupo,codProfesor,cupoT,cupoM,cupoC);
        }
        archivo.close();
    }
    else
    {
        cout << "ERROR: No se pudo abrir el archivo 'Carreras.txt'" << endl;
    }
}*/

void cargarArbol(int carrera,int curso){
    ifstream file;
    file.open("Grupos.txt");
    string fromfile;
    String *data=new String();
    while(getline(file,fromfile)){
        data->fromSplit(fromfile,';');
        cout<<data->getPos(1)<<"!="<<carrera<<" & "<<data->getPos(2)<<"!="<<curso<<endl;
        if(std::to_string(carrera)==data->getPos(1)&&std::to_string(curso)==data->getPos(2)){
            cout<<"Insertar"<<endl;
            insertar(raiz,stint(data->getPos(1)),stint(data->getPos(2)),stint(data->getPos(3)),
                    stint(data->getPos(4)),stint(data->getPos(5)),stint(data->getPos(6)),stint(data->getPos(7)));
        }
        data->borrarFrase();
        fromfile.clear();
        if(file.eof()){
            file.close();
        }
        //addStudents();
    }
}
    /*void addStudents(){
        if(siguiente==NULL){
            miembros->armarEstudiantesCurso(codCurso,codGrupo);
        }else{
            nodoGrupo * aux=this;
        do{
            aux->miembros->armarEstudiantesCurso(aux->codCurso,aux->codGrupo);
            aux=aux->siguiente;
        }while(aux!=this);
        }
    }
    */
};


#endif /* GRUPO_H */

