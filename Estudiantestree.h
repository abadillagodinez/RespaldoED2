
#include <iostream>
#include <sstream>
#include <fstream>
#include "StringParser.h"

using namespace std;
//orden 5, implicito

class estudiante{
public:
    long idEstudiante;
    long codCarrera;
    string nombre;
    string direccion;
    string telefono;
    
    estudiante(){
        idEstudiante=-1;
    }
    
    estudiante(long nidEstudiante, long ncodCarrera, string nnombre, string ndireccion, string ntelefono){
        idEstudiante=nidEstudiante;
        codCarrera=ncodCarrera;
        nombre=nnombre;
        direccion=ndireccion;
        telefono=ntelefono;
    }
    
    void imprimir(){
        cout<<"ID:"<<idEstudiante<<endl;
        cout<<"Carrera:"<<codCarrera<<endl;
        cout<<"Nombre:"<<nombre<<endl;
        cout<<"Direccion:"<<direccion<<endl;
        cout<<"Telefono:"<<telefono<<endl;
    }
    
    string to_string(){
        string s="";
        s+="ID:"+std::to_string(idEstudiante)+"\n";
        s+="Carrera"+std::to_string(codCarrera)+"\n";
        s+="Nombre:"+nombre+"\n";
        s+="Direccion:"+direccion+"\n";
        s+="Telefono:"+telefono+"\n";
        return s;
    }
    
    friend class pagina;
};

class Pagina{
public:
    estudiante* claves[5];
    Pagina* ramas[5];
    int cuenta;
        
    Pagina(){
    this->cuenta = 0;
    for (unsigned int i = 0; i <= 4; ++i)
    {
        this->claves[i] = NULL;
        this->ramas[i] = NULL;
    }
    }

    string toString(){
        string out = "[";
        for(int i = 1; i <= cuenta; ++i)
            out += claves[i]->to_string()+"|";
        out.erase(out.end()-1, out.end());
        out += "]";
        return out;
    }

    bool isEmpty() { return cuenta == 0; }

    bool hayRamas(){
    bool out = false;
    for (int i = 0; i <= cuenta; ++i)
    {
        if (ramas[i] != NULL && !ramas[i]->isEmpty()) {
            out = true;
            break;
        }
    }return out;
    }

    void buscarEnPag(long num, bool &found, int &pos){
        cout << "> Buscando " << num << endl;
        if (num < claves[1]->idEstudiante){
        found = false;
        pos = 0;
        }else{
        pos = cuenta;
        while(num < claves[pos]->codCarrera && pos > 1)
            pos--;
        found = (num == claves[pos]->codCarrera);
        }
    }

    void meterEnPag(long newClave, Pagina *Xder, int pos,long cCarrera, string nombre,
    string direccion, string telefono){
        cout << ":: insertando " << newClave << " en pagina.";
        for (int i = cuenta; i > pos; --i){
            claves[i+1] = claves[i];
            ramas[i+1] = ramas[i];
            cout << '.';
        }
        claves[pos+1] = new estudiante(newClave,cCarrera,nombre,direccion,telefono);
        ramas[pos+1] = Xder;
        cuenta++;
        cout << "Listo! Ahora soy " + toString() << endl;
    }

    void divide(long newClave, int pos, estudiante* &Mda, Pagina *&Xder,long cCarrera, 
    string nombre, string direccion, string telefono){
        cout << ":: iniciando division de pagina "+toString() << endl;
        int posMda;
        if (pos <= 2)
            posMda = 2;
        else
            posMda = 3;

        Pagina* Mder = new Pagina();
        for (int i = (posMda+1); i <= 4; ++i){
            Mder->claves[i-posMda] = claves[i];
            Mder->ramas[i-posMda] = ramas[i];
        }
        Mder->cuenta = 4 - posMda;
        cuenta = posMda;
        
        if (pos <= 2)
            meterEnPag(newClave, Xder, pos,cCarrera,nombre,direccion,telefono);
        else
            Mder->meterEnPag(newClave, Xder, pos-posMda,cCarrera,nombre,direccion,telefono);

        Mda = claves[cuenta];
        Mder->ramas[0] = ramas[cuenta];
        cuenta--;
        Xder = Mder;
    }


    friend class ArbolB;
};

class ArbolB{
public:
    Pagina* root;
    
    ArbolB() { root = new Pagina(); }
    ArbolB(Pagina* newRoot) { root = newRoot; }

    Pagina* getRoot() { return root; }
    
    bool sEmpty() { return root == NULL; }

    void insertar(long clave,long cCarrera, string nombre, string direccion, string telefono){
        Pagina *r = root;
        Pagina *Xr = NULL;
        bool empujarArriba = false;
        estudiante* Mdna = new estudiante();
        try {
            cout << ":: Iniciando insercion de " << clave << " ::" << endl;
            empujar(clave, r, empujarArriba, Mdna, Xr,cCarrera,nombre,direccion,telefono);
            if (empujarArriba)
            {
                Pagina* p = new Pagina();
                p->cuenta++;
                p->claves[1] = Mdna;
                p->ramas[0] = root;
                p->ramas[1] = Xr;
                root = p;
                cout << " Nueva raiz: "+root->toString() << endl;
            }
        cout << "Terminando insercion " << endl;
        }
        catch(string exc) {
            cout << "ERROR :: "+exc << endl;
        }
    }

void empujar(long newClave, Pagina* &p, bool &empujarArriba, estudiante* &Mdna, Pagina* &Xr,long cCarrera, string nombre, string direccion, string telefono)
    {
    if (p->isEmpty())
    {
        cout << "> Pagina vacia... empujando arriba" << endl;
        empujarArriba = true;
        Mdna = new estudiante(newClave,cCarrera,nombre,direccion,telefono);
        Xr = new Pagina();
    }
    else
    {
        cout << "> Pagina actual: "+p->toString() << endl;
        bool found = false;
        int pos = -1;
        p->buscarEnPag(newClave, found, pos);
        if (found) {
            string error = "item repetido";
            throw error;
        }
        cout << "> Bajando a rama " << pos << endl;
        empujar(newClave, p->ramas[pos], empujarArriba, Mdna, Xr,cCarrera,nombre,direccion,telefono);
        if (empujarArriba){
            if (p->cuenta < 4){
                cout << "> Pagina tiene espacio :: ";
                empujarArriba = false;
                p->meterEnPag(newClave, Xr, pos,cCarrera,nombre,direccion,telefono);
            }else{
                cout << "> !-Pagina llena-! ";
                empujarArriba = true;
                p->divide(newClave, pos, Mdna, Xr,cCarrera,nombre,direccion,telefono);
                cout << "> P.izq: "+p->toString()+" ~ P.der: "+Xr->toString() << endl;
            }
        }
    }
}

bool buscar(int num) { return buscar(num, root, 0); }

bool buscar(int num, Pagina *p, int pos)
{
    bool found = false;
    if (!p->isEmpty())
    {
        p->buscarEnPag(num, found, pos);
        if (!found)
            found = buscar(num, p->ramas[pos], pos);
    }
    return found;
}

void imprimir()
{
    cout << "PREORDEN :: ";
    preorden(root);
    cout << endl;
}
    void preorden(Pagina* actual){
        if (actual == NULL || actual->isEmpty())
            return;
        else    {
            cout << actual->toString() << "->";
            if (actual->hayRamas()) {
                for (int i = 0; i <= actual->cuenta; ++i)
                 preorden(actual->ramas[i]);
            }
        }
    }
    
    long Stringtolong(string s){
        stringstream p;
        p<<s;
        long i;
        p>>i;
        return i;
    }
    
    void cargarEstudiantes(){
        ifstream file;
        file.open("Estudiantes.txt");
        string fromfile;
        String *data=new String();
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            cout<<"ü ok bro?"<<endl;
            insertar(Stringtolong(data->getPos(1)),Stringtolong(data->getPos(2)),data->getPos(3),data->getPos(4),data->getPos(5));
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
            cout<<"Estudiante agregado"<<endl;
            //root->imprimir();
        }
    }

};

