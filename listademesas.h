#ifndef LISTADEMESAS_H
#define LISTADEMESAS_H
#include <iostream>
#include <sstream>
#include "NodoDMesas.h"
#include "ListaDCarreras.h"
#include "ListaDEstCurs.h"
#include "ListaDEstudiante.h"
#include "ListaDProfesores.h"
#include "ColaDeAtencion.h"
#include <fstream>
#include <time.h>
#include <ctime>
#include <math.h>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

//template <typename E>
class ListaDMesas{
public:
    ListaDMesas(){
        head = NULL;
        length = 0;
    }

    virtual ~ListaDMesas(){
        NodoDMesas *aux;

       while(head) {
          aux = head;
          head = head->next;
          delete aux;
       }
    }

    bool isVoid(){
        return (head == NULL);
    }

    //metodo de insersion identado
        void insertAtHead(int pNewElement){
            NodoDMesas *newNode = new NodoDMesas(pNewElement);
            if (isVoid())
            {
                head = newNode;
                head->next = head;
                head->previous = head;
                length++;
            }
           else
            {
                 newNode->next = head;
                 newNode->previous = head->previous;
                 head->previous->next = newNode;
                 newNode->next->previous = newNode;
                 head = newNode;
                 length++;
            }
        }


        void insertAtPos(int pos, int pNewElement){
            if (isVoid() || pos <= 0){
                insertAtHead(pNewElement);
            }
            else if(pos > length-1){
                insertAtTail(pNewElement);
            }
            else{
                NodoDMesas *newNode = new NodoDMesas(pNewElement);
                NodoDMesas *aux = head;
                int i = 1;
                while((i != pos)&&(aux->next != head)){
                    i++;
                    aux = aux->next;
                }
                newNode->next = aux->next;
                aux->next = newNode;
                aux->next->previous = aux;
                newNode->next->previous = newNode;
                length++;
            }
        }


        void insertAtTail(int pNewElement){
            NodoDMesas *newNode = new NodoDMesas(pNewElement);
            if(isVoid()){
                head = newNode;
                head->next = head;
                head->previous = head;
                length++;
            }
            else{
                newNode->previous = head->previous;
                newNode->next = head->previous->next;
                head->previous->next = newNode;
                head->previous = newNode;
                length++;
            }
        }


        void deleteAtHead(){
            if(isVoid()){
                cout << "La lista ya está vacía" << endl;
            }
            else if(head->next == head){
                NodoDMesas *temp = head;
                head = NULL;
                delete temp;
                length--;
            }
            else{
                NodoDMesas *aux = head;
                NodoDMesas *temp = head;
                while (aux->next != head){
                    aux = aux->next;
                    }
                aux->next = head->next;
                head = head->next;
                head->previous = aux;
                temp->next = NULL;
                temp->previous = NULL;
                delete temp;
                length--;
            }
        }


        void deleteAtPos(int pos){
            if(isVoid()){
                cout << "La lista está vacía" << endl;
            }
            else if((pos > length-1) || (pos<0)){
                cout << "ERROR: posición no válida" << endl;
            }
            else if(pos == 0){
                deleteAtHead();
            }
            else{
                int i = 1;
                NodoDMesas *aux = head;
                while(i < pos){
                    aux = aux->next;
                    i++;
                }
                NodoDMesas *temp = aux->next;
                aux->next = aux->next->next;
                aux->next->previous = aux;
                delete temp;
                length--;
            }
        }

        void deleteAtTail(){
            if(isVoid()){
                cout << "La lista está vacía" << endl;
            }
            else if(head->next == head){
                NodoDMesas *temp = head;
                head = NULL;
                delete temp;
                length--;
            }
            else{
                NodoDMesas *aux = head;
                while (aux->next->next != head)
                    aux = aux->next;
                NodoDMesas *temp = aux->next;
                aux->next = head;
                head->previous = aux;
                delete temp;
                length--;
            }
        }


        void print(){
            if (isVoid()){
                 cout << "la lista esta vacia" << endl;
             }
             else{
                 NodoDMesas *aux = head;
                 do{
                     cout << aux->id<< endl;
                     aux = aux->next;
                 }while(aux != head);
             }
             cout << endl;
         }


        void cargaEstructura();
        void MenuReportes();
        int getCantidadDeAtenciones();
        void ejecutarAcciones();


    protected:

    private:
        // hay que cambiar todos los codigos de los reportes, ya que
        // todos los reportes cambian, respecto a la interfaz

        /**
         * por cierto:
         * hay que reescribir el metodo de cargaEstructura por completo
         */
        void reporteCarreras();
        void reporteCursosDeUnaCarrera();
        void reporteProfesores();
        void reporteProfesoresDeUnCurso();
        void reporteProfesoresDeUnCursoAux(NodoDCursos *curso, string nombreCarrera);
        void reporteEstudiantesDeUnGrupo();
        void reporteEstudiantesDeUnGrupoAux(NodoDCursos *curso, string nombreCarrera);
        void reporteEstudiantesDeUnaCarrera();
        void reporteEstudiantesDeUnaCarreraAux(NodoDCarreras *carrera);
        void reporteProfesoresServicio();
        void reporteProfesoresDeUnaCarrera();
        void reporteProfesoresDeUnaCarreraAux(NodoDCarreras *carrera);
        void reporteContador();

        NodoDMesas *head;
        int length;
        // cambiar codigo de la lista por los arboles
        ListaDCarreras *carreras = new ListaDCarreras();
        ListaDProfesores *profesores = new ListaDProfesores();
        ListaDEstudiante *estudiantes = new ListaDEstudiante();
        ColaDeAtencion *atencion = new ColaDeAtencion();
};
#endif // LISTADEMESAS_H
