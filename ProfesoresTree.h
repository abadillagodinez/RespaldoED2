#include <iostream>
#include <sstream>
#include <fstream>
#include "StringParser.h"

using namespace std;
//orden 5, implicito

class profesor{
public:
    long idprofesor;
    long codCarrera;
    string nombre;
    string categoria;
    
    profesor(){
        idprofesor=-1;
    }
    
    profesor(long nidprofesor, long ncodCarrera, string nnombre, string ncategoria){
        idprofesor=nidprofesor;
        codCarrera=ncodCarrera;
        nombre=nnombre;
        categoria=ncategoria;
    }
    
    void imprimir(){
        cout<<"ID:"<<idprofesor<<endl;
        cout<<"Carrera:"<<codCarrera<<endl;
        cout<<"Nombre:"<<nombre<<endl;
        cout<<"Categoria:"<<categoria<<endl;
    }
    
    string to_string(){
        string s="";
        s+="ID:"+std::to_string(idprofesor)+"\n";
        s+="Carrera"+std::to_string(codCarrera)+"\n";
        s+="Nombre:"+nombre+"\n";
        s+="Categoria:"+categoria+"\n";
        return s;
    }
    
    friend class Paginap;
};

class Paginap{
public:
    profesor* claves[5];
    Paginap* ramas[5];
    int cuenta;
        
    Paginap(){
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
        if (num < claves[1]->idprofesor){
        found = false;
        pos = 0;
        }else{
        pos = cuenta;
        while(num < claves[pos]->codCarrera && pos > 1)
            pos--;
        found = (num == claves[pos]->codCarrera);
        }
    }

    void meterEnPag(long newClave, Paginap *Xder, int pos,long cCarrera, string nombre,
    string direccion){
        cout << ":: insertando " << newClave << " en Paginap.";
        for (int i = cuenta; i > pos; --i){
            claves[i+1] = claves[i];
            ramas[i+1] = ramas[i];
            cout << '.';
        }
        claves[pos+1] = new profesor(newClave,cCarrera,nombre,direccion);
        ramas[pos+1] = Xder;
        cuenta++;
        cout << "Listo! Ahora soy " + toString() << endl;
    }

    void divide(long newClave, int pos, profesor* &Mda, Paginap *&Xder,long cCarrera, 
    string nombre, string direccion){
        cout << ":: iniciando division de Paginap "+toString() << endl;
        int posMda;
        if (pos <= 2)
            posMda = 2;
        else
            posMda = 3;

        Paginap* Mder = new Paginap();
        for (int i = (posMda+1); i <= 4; ++i){
            Mder->claves[i-posMda] = claves[i];
            Mder->ramas[i-posMda] = ramas[i];
        }
        Mder->cuenta = 4 - posMda;
        cuenta = posMda;
        
        if (pos <= 2)
            meterEnPag(newClave, Xder, pos,cCarrera,nombre,direccion);
        else
            Mder->meterEnPag(newClave, Xder, pos-posMda,cCarrera,nombre,direccion);

        Mda = claves[cuenta];
        Mder->ramas[0] = ramas[cuenta];
        cuenta--;
        Xder = Mder;
    }


    friend class ArbolB;
};

class ArbolBp{
public:
    Paginap* root;
    
    ArbolBp() { root = new Paginap(); }
    ArbolBp(Paginap* newRoot) { root = newRoot; }

    Paginap* getRoot() { return root; }
    
    bool sEmpty() { return root == NULL; }

    void insertar(long clave,long cCarrera, string nombre, string direccion){
        Paginap *r = root;
        Paginap *Xr = NULL;
        bool empujarArriba = false;
        profesor* Mdna = new profesor();
        try {
            cout << ":: Iniciando insercion de " << clave << " ::" << endl;
            empujar(clave, r, empujarArriba, Mdna, Xr,cCarrera,nombre,direccion);
            if (empujarArriba)
            {
                Paginap* p = new Paginap();
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

void empujar(long newClave, Paginap* &p, bool &empujarArriba, profesor* &Mdna, Paginap* &Xr,
long cCarrera, string nombre, string direccion)
    {
    if (p->isEmpty())
    {
        cout << "> Paginap vacia... empujando arriba" << endl;
        empujarArriba = true;
        Mdna = new profesor(newClave,cCarrera,nombre,direccion);
        Xr = new Paginap();
    }
    else
    {
        cout << "> Paginap actual: "+p->toString() << endl;
        bool found = false;
        int pos = -1;
        p->buscarEnPag(newClave, found, pos);
        if (found) {
            string error = "item repetido";
            throw error;
        }
        cout << "> Bajando a rama " << pos << endl;
        empujar(newClave, p->ramas[pos], empujarArriba, Mdna, Xr,cCarrera,nombre,direccion);
        if (empujarArriba){
            if (p->cuenta < 4){
                cout << "> Paginap tiene espacio :: ";
                empujarArriba = false;
                p->meterEnPag(newClave, Xr, pos,cCarrera,nombre,direccion);
            }else{
                cout << "> !-Paginap llena-! ";
                empujarArriba = true;
                p->divide(newClave, pos, Mdna, Xr,cCarrera,nombre,direccion);
                cout << "> P.izq: "+p->toString()+" ~ P.der: "+Xr->toString() << endl;
            }
        }
    }
}

bool buscar(int num) { return buscar(num, root, 0); }

bool buscar(int num, Paginap *p, int pos)
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
    void preorden(Paginap* actual){
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
    
    void cargarProfesores(){
        ifstream file;
        file.open("Profesores.txt");
        string fromfile;
        String *data=new String();
        while(getline(file,fromfile)){
            data->fromSplit(fromfile,';');
            cout<<"ü ok bro?"<<endl;
            insertar(Stringtolong(data->getPos(1)),Stringtolong(data->getPos(2)),data->getPos(4),data->getPos(3));
            data->borrarFrase();
            fromfile.clear();
            if(file.eof()){
                file.close();
            }
            cout<<"profesor agregado"<<endl;
            //root->imprimir();
        }
    }

};
