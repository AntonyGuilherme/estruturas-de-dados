#ifndef LISTA_H
#define LISTA_H

// https://www.programiz.com/cpp-programming/library-function/cstdlib/realloc

#include <cstdlib>
#include <iostream>

template <typename T>
class Lista
{

private:
    int tamanho;
    int tamanhoOcupado;
    T** lista;


public :
    Lista(int tamanho);
    ~Lista();
    int size();
    void inserir(int index , T*);
    void inserir(T*);
    T* operator[](int index);
    T* get(int index);
    void remover(int index, int elementos = 1);
    void incrementarTamanho(int complemento);
};


template<class T>
Lista<T>::Lista(int tamanho){
    
    this->tamanho = tamanho;
    this->lista = (T**) malloc(sizeof(T**)*tamanho);
    this->tamanhoOcupado = 0;
}

template<class T>
int Lista<T>::size(){

    return this->tamanhoOcupado;
}

template<class T>
T* Lista<T>::operator[](int index){

    return this->get(index);
}

template<class T>
T* Lista<T>::get(int index){

    if(index  >= this->size()){
        return nullptr;
    }

    return this->lista[index];
}

template<class T>
void Lista<T>::inserir(int index,T * objeto){

    if(index < 0 || index >= this->tamanho || (this->tamanhoOcupado + 1) >= this->tamanho){
        throw "Erro na inserção do elemento";
    }

    for(int i = (this->tamanhoOcupado + 1); i > index; i--)
        this->lista[i] = this->lista[i-1];
    
    this->lista[index] = objeto;

    this->tamanhoOcupado++;
}

template<class T>
void Lista<T>::inserir(T * objeto){

    int index = this->tamanhoOcupado;

    std::cout << index << " " << this->tamanho << std::endl;

     if(index < 0 || index >= this->tamanho){
       throw "Erro na inserção do elemento";
    }

    if(this->lista[index] != nullptr){
        delete this->lista[index];
    }

    this->lista[index] = objeto;

    this->tamanhoOcupado++;
}

template<class T>
void Lista<T>::remover(int inicio , int elementos){

    for(int index = inicio ; index <= elementos ; index++){
        
        delete this->lista[index];

        if( (elementos+index) < this->size() ){
            
            this->lista[index] = this->lista[elementos+index];
            this->lista[elementos+index] = nullptr;
        }
        else{
            this->lista[index] = nullptr;
        }
    }

    this->tamanho -= elementos;

}

template<class T>
void Lista<T>::incrementarTamanho(int complemento){

    int novoTamanho = complemento + this->tamanho;

    if( novoTamanho <= this->tamanho){  
        return;
    }

   this->lista = (T**) realloc(this->lista,sizeof(T**)*novoTamanho);

   this->tamanho = novoTamanho;

    std::cout << novoTamanho << std::endl;

    if(this->lista == nullptr){
        throw "Erro na realocacao!";
    }
}

template<class T>
Lista<T>::~Lista(){

    for(int i = 0; i < this->tamanho; i++){

        if(this->lista[i] != nullptr)
            delete this->lista[i];
    }

    delete this->lista;

}


#endif