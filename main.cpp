#include <iostream>

template<class T>
class SocioClub;

class Socio{
private:
    int numeroSocio;
    int anioIngreso;
    std::string nombre;
    std::string domicilio;
public:
    Socio():numeroSocio(0), anioIngreso(0), nombre(""), domicilio(""){};

    friend std::ostream & operator<<(std::ostream &os, Socio &x){
        os<<"Nombre del Socio: "<<x.nombre<<std::endl;
        os<<"Domicilio de Socio: "<<x.domicilio<<std::endl;
        os<<"Numero de Socio: "<<x.numeroSocio<<std::endl;
        os<<"Anio de ingreso: "<<x.anioIngreso<<std::endl;
        return os;
    }
    friend std::istream & operator>>(std::istream &is, Socio &x){
        std::cout<<"  Nombre del Socio: ";
        is>>x.nombre;
        std::cout<<"  Domicilio de Socio: ";
        is>>x.domicilio;
        std::cout<<"  Numero de Socio: ";
        is>>x.numeroSocio;
        std::cout<<"  Anio de ingreso: ";
        is>>x.anioIngreso;
        return is;
    }
    bool operator == (Socio &a){
            return nombre == a.nombre && domicilio == a.domicilio && numeroSocio == a.numeroSocio && anioIngreso == a.anioIngreso;
    }
    bool operator != (Socio &a){
            return nombre != a.nombre || domicilio != a.domicilio;
    }

    int getNumeroSocio(){
        return numeroSocio;
    }
    void setNombre(std::string n){
        nombre = n;
    }
    void setDomicilio(std::string d){
        domicilio = d;
    }

    friend class SocioClub<Socio>;
};

template<class T>
class node{
private:
    T data;
    node<T>* sig;
public:
    node():sig(nullptr){};
    friend class SocioClub<T>;
    T getData(){
    return data;
    }
    node<T>* getSig(){
    return sig;
    }
};

template<class T>
class SocioClub{
private:
    node<T>* lista;
public:
    SocioClub():lista(nullptr){};
    bool vacia()const;
    node<T>* ultimo()const;
    node<T>* primero()const;
    node<T>* anterior(node<T>* pos)const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir()const;
    node<T>* buscar(T elem)const;
    int total();
};
template<class T>
int SocioClub<T>::total(){
    node<T>* aux=lista;
    int i;
    for(i = 0; aux; i++){
        aux = aux->sig;
    }
    return i;
}

template<class T>
node<T>* SocioClub<T>::buscar(T elem)const{
    node<T>* aux=lista;
    while(aux && aux->data != elem){
        aux = aux->sig;
    }
    return aux;
}

template<class T>
void SocioClub<T>::imprimir()const{
    node<T>* aux=lista;
    while(aux!=nullptr){
        std::cout<<"\n-> "<<aux->data;
        aux=aux->sig;
    }
}

template<class T>
bool SocioClub<T>::eliminar(node<T>* pos){
    if(vacia() || pos==nullptr){
        return false;
    }
    if(pos==lista){
        lista=lista->sig;
    }
    else{
        anterior(pos)->sig=pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void SocioClub<T>::insertar(node<T>* pos, T elem){
    node<T>* aux= new node<T>;
    aux->data=elem;
    if(pos==nullptr){
        aux->sig=lista;
        lista=aux;
    }
    else{
        aux->sig=pos->sig;
        pos->sig=aux;
    }
}

template<class T>
node<T>* SocioClub<T>::anterior(node<T>* pos)const{
    if(vacia() || pos==nullptr){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux!=nullptr && aux->sig!=pos){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
node<T>* SocioClub<T>::primero()const{
    if(vacia()){
        return nullptr;
    }
    return lista;
}


template<class T>
node<T>* SocioClub<T>::ultimo()const{
    if(vacia()){
        return nullptr;
    }
    node<T>* aux=lista;
    while(aux->sig!=nullptr){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
bool SocioClub<T>::vacia()const{
    if(lista==nullptr)
        return true;
    return false;
}

int main()
{
    SocioClub<Socio> milista;
    Socio elem;
    node<Socio>* pos = nullptr;
    bool flag = true;
    int opc;
    std::string aux;

    do
    {
        system("cls");
        std::cout<<"Elija una opcion\n"<<std::endl;
        std::cout<<"1. Registrar un nuevo Socio"<<std::endl;
        std::cout<<"2. Dar de baja a un Socio"<<std::endl;
        std::cout<<"3. Reporte de todos los Socios"<<std::endl;
        std::cout<<"4. Buscar a un Socio"<<std::endl;
        std::cout<<"5. Numero total de Socios"<<std::endl;
        std::cout<<"6. Salir"<<std::endl<<"  : ";
        std::cin>>opc;

        switch (opc)
        {
            case 1:
                system("cls");
                std::cout<<"Registrar un nuevo Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cin>>elem;
                pos = milista.primero();
                while(pos && flag){
                    if(pos->getData().getNumeroSocio() == elem.getNumeroSocio())
                        flag = false;
                    pos = pos->getSig();
                }
                if(flag){
                    milista.insertar(pos, elem);
                    std::cout<<"\nEl socio se ha registrado"<<std::endl;
                }
                else
                    std::cout<<"\nYa hay un socio con el mismo numero de Socio"<<std::endl;
                system("pause");
            break;
            case 2:
                system("cls");
                std::cout<<"Dar de baja a un Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cin>>elem;
                if (milista.eliminar(milista.buscar(elem)))
                    std::cout<<"El socio ha sido dado de baja"<<std::endl;
                else
                    std::cout<<"El socio no se ha encontrado o borrado"<<std::endl;
                system("pause");
            break;
            case 3:
                system("cls");
                std::cout<<"Reporte de todos los Socios\n"<<std::endl;
                milista.imprimir();
                system("pause");
            break;
            case 4:
                system("cls");
                std::cout<<"Buscar a un Socio\n"<<std::endl;
                std::cout<<"Ingrese los datos del Socio:"<<std::endl;
                std::cout<<"  Nombre: ";
                std::cin>>aux; elem.setNombre(aux);
                std::cout<<"  Domicilio: ";
                std::cin>>aux; elem.setDomicilio(aux);
                if(milista.buscar(elem)){
                    elem = milista.buscar(elem)->getData();
                    std::cout<<"\n\nLos datos del socio son:"<<std::endl<<elem;
                }
                else
                    std::cout<<"No se encontro el socio"<<std::endl;
                system("pause");
            break;
            case 5:
                system("cls");
                std::cout<<"Numero total de Socios\n"<<std::endl;
                std::cout<<"Hay un total de "<<milista.total()<<" Socios"<<std::endl;
                system("pause");
            break;
        }
    } while (opc != 6);


    return 0;
}
