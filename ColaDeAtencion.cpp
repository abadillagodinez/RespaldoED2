#include "ColaDeAtencion.h"

ColaDeAtencion::ColaDeAtencion()
{
    frente = 0;
    fondo = -1;
    disponibles = 10;
    indiceArchivo = 0;
    for(int i =0;i<9;i++){
        arreglo[i] = NULL;
    }
}

ColaDeAtencion::~ColaDeAtencion(){
    //dtor
}


void ColaDeAtencion:: pushElement (NodoDAtencion* newElement){
    if(fondo < 9){
        fondo++;
        disponibles--;
        arreglo[fondo]= newElement;
    }else{
        //cout<<"La cola esta llena";
    }
}

NodoDAtencion *ColaDeAtencion:: popElement(){
    if(!colaVacia()){
        NodoDAtencion *temp = arreglo[0];
        for(int i = 0; i < fondo+1; i++){
            arreglo[i] = arreglo[i+1];
        }
        fondo--;
        disponibles++;
        return temp;
    }
    else{
        cout << "La cola esta vacia" << endl;
        return NULL;
    }

}

void ColaDeAtencion:: imprimir(){
    for(int i = frente;i<fondo+1;i++){
        cout<< arreglo[i]->idEstudiante << ", " << arreglo[i]->codCurso << ", " << arreglo[i]->codGrupo << ", " << arreglo[i]->accion <<endl;
    }
}

//metodo de carga de datos
void ColaDeAtencion::cargarDatos(){
    string archivoAbrir = "Atencion.txt";
    fstream archivo(archivoAbrir.c_str());
    string linea;
    if (!archivo.is_open()){
        cout << "abrio el archivo" << endl;
        archivo.open(archivoAbrir.c_str(), ios::in);
    }
    for(int i = 0; i < disponibles; i++){
        int j = 0;
        while(getline(archivo, linea)){
            if(j == indiceArchivo){
                int id = getIdEstudiante(linea);
                string curso = getCodCurso(linea);
                string grupo = getCodGrupo(linea);
                int accion = getAccion(linea);
                NodoDAtencion *nuevo = new NodoDAtencion(id, curso, grupo, accion);
                indiceArchivo++;
                pushElement(nuevo);
                if(fondo == 9){
                    break;
                }
            }
            j++;
        }
    }
}


//metodo de recuperacion del id
int ColaDeAtencion::getIdEstudiante(string linea){
    stringstream ss;
    int cont = 0;
    char frase[1024];
    strcpy(frase, linea.c_str());
    string result1 = "";
    int result2 = 0;
    for(int i = 0; i < strlen(linea.c_str()); i++){
        if(cont > 0){
            break;
        }
        else if (frase[i] == ';'){
            cont++;
        }
        else if (cont == 0){
            result1.push_back(frase[i]);
        }
    }
    ss << result1;
    ss >> result2;
    return result2;
}


//metodo de recuperacion del codCurso
string ColaDeAtencion::getCodCurso(string linea){
    int cont = 0;
    char frase[1024];
    strcpy(frase, linea.c_str());
    string result = "";
    for(int i = 0; i < strlen(linea.c_str()); i++){
        if(cont > 1){
            break;
        }
        else if (frase[i] == ';'){
            cont++;
        }
        else if (cont == 1){
            result.push_back(frase[i]);
        }
    }
    return result;
}

//metodo de recuperacion del codGrupo
string ColaDeAtencion::getCodGrupo(string linea){
    int cont = 0;
    char frase[1024];
    strcpy(frase, linea.c_str());
    string result = "";
    for(int i = 0; i < strlen(linea.c_str()); i++){
        if(cont > 2){
            break;
        }
        else if (frase[i] == ';'){
            cont++;
        }
        else if (cont == 2){
            result.push_back(frase[i]);
        }
    }
    return result;
}

//metodo de recuperacion de la accion
int ColaDeAtencion::getAccion(string linea){
    stringstream ss;
    int cont = 0;
    char frase[1024];
    strcpy(frase, linea.c_str());
    string result1 = "";
    int result2 = 0;
    for(int i = 0; i < strlen(linea.c_str()); i++){
        if(cont > 3){
            break;
        }
        else if (frase[i] == ';'){
            cont++;
        }
        else if (cont == 3){
            result1.push_back(frase[i]);
        }
    }
    ss << result1;
    ss >> result2;
    return result2;
}
