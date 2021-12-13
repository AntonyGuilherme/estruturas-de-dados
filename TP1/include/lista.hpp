#ifndef LISTA_H
#define LISTA_H

// https://www.programiz.com/cpp-programming/library-function/cstdlib/realloc

#include <cstdlib>
#include <iostream>
#include "item.hpp"
#include <stdexcept>

template <typename T>
class Lista
{

private:
    int tamanho = 0;
    Item<T> * primeiro = nullptr;
    Item<T> * ultimo = nullptr;

public:
    Lista(){};
    Lista(T* objeto);
    ~Lista();
    int size();
    void inserir(int index, T *);
    void inserir(T *);
    void inserir(Item<T> *,T *);
    T *get(int index);
    Item<T> * getItem(int index);
    Item<T> * getPrimeiroItem();
    Item<T> * getUltimoItem();
    void inserirPrimeiro(Item<T> *);
    void remover(int index, int elementos = 1);
};

template <class T>
Lista<T>::Lista(T* objeto)
{   
    this->tamanho = 0;
    this->inserir(objeto);
}

template <class T>
int Lista<T>::size()
{

    return this->tamanho;
}


template <class T>
T * Lista<T>::get(int index)
{

    Item<T> * auxiliar = this->getItem(index);
    
    if(auxiliar != nullptr) return auxiliar->getValorDoObjetoArmazenado();

    return nullptr;
}

template <class T>
Item<T> * Lista<T>::getItem(int index)
{

    if (index >= this->size())
    {
        return nullptr;
    }

    Item<T> * auxiliar = this->primeiro;
    int indexAuxiliar = 0;

    while(auxiliar != nullptr){

        if(indexAuxiliar == index) return auxiliar;

        auxiliar = auxiliar->getProximoItem();
        indexAuxiliar++;
    }


    return nullptr;
}

template<class T>
void Lista<T>::inserir(Item<T> * baseInsercao , T *objeto){

    if(objeto == nullptr){
        throw std::invalid_argument("Objeto de insercao e invalido.");
    }

    if(baseInsercao == nullptr){
        return this->inserir(objeto);
    }

    Item<T> * novoItem = new Item<T>(objeto,baseInsercao->getAnteriorItem(),baseInsercao);
    
    if(baseInsercao->getAnteriorItem() != nullptr){
        baseInsercao->getAnteriorItem()->inserirProximo(novoItem);
    }
    else{ // caso nao haja nenhum item anterior o item em questao eh o primeiro
        this->primeiro = novoItem;
    }

    baseInsercao->inserirAnterior(novoItem);

    this->tamanho++;

}

template <class T>
void Lista<T>::inserir(int index, T *objeto)
{   
    if(index  > this->tamanho){
        
        throw std::invalid_argument("Index invalido");
    }
    else if(index == 0){

        if(this->primeiro == nullptr) {
            this->inserir(objeto);
            return;
        }    
        
        Item<T> * novoItem = new Item<T>(objeto,nullptr,this->primeiro);
        this->primeiro->inserirAnterior(novoItem);
        this->primeiro = novoItem;

        if(this->ultimo == nullptr){
            this->ultimo = this->primeiro->getProximoItem();
        }

        this->tamanho++;
        return;
        
    }else if(index == this->tamanho){
        this->inserir(objeto);
        return;
    }

    Item<T> * auxiliar = this->getItem(index);   

    if(auxiliar == nullptr)
        throw std::invalid_argument("Index nao localizado");

    Item<T> * novoItem = new Item<T>(objeto,auxiliar->getAnteriorItem(),auxiliar);
    auxiliar->getAnteriorItem()->inserirProximo(novoItem);
    auxiliar->inserirAnterior(novoItem);

    this->tamanho++;
  
}

template <class T>
void Lista<T>::inserir(T *objeto)
{
    if (this->primeiro == nullptr)
    {
        this->primeiro = new Item<T>(objeto);
    }
    else if (this->ultimo == nullptr)
    {

        this->ultimo = new Item<T>(objeto, this->primeiro);
        this->primeiro->inserirProximo(this->ultimo);
    }
    else
    {
        Item<T> *item = new Item<T>(objeto, this->ultimo);
        this->ultimo->inserirProximo(item);
        this->ultimo = item;
    }

    this->tamanho++;

}

template <class T>
void Lista<T>::remover(int inicio, int elementos)
{   
    if(inicio < 0 ){
        throw "remocao indevida";
    }

    Item<T> *auxiliar = this->getItem(inicio);
    Item<T> *auxiliarAnterior = nullptr;

    if(auxiliar != nullptr) auxiliarAnterior = auxiliar->getAnteriorItem();
        
    Item<T> *auxiliarProximo;
    int elementosRemovidos = 0;

    while (auxiliar != nullptr && elementosRemovidos < elementos)
    {

        auxiliarProximo = auxiliar->getProximoItem();
        delete auxiliar;

        auxiliar = auxiliarProximo;
        elementosRemovidos++;
    }

    if(auxiliarAnterior != nullptr)
        auxiliarAnterior->inserirProximo(auxiliar);
    else{
        this->primeiro = auxiliar;
    }

    if(auxiliar != nullptr){
        auxiliar->inserirAnterior(auxiliarAnterior);
    }else{
        this->ultimo = auxiliarAnterior;
    }

}

template<class T>
Item<T> * Lista<T>::getPrimeiroItem(){
    return this->primeiro;
}

template<class T>
Item<T> * Lista<T>::getUltimoItem(){
    return this->ultimo;
}

template <class T>
Lista<T>::~Lista()
{

    Item<T> *auxiliar = this->primeiro;
    Item<T> *auxiliarProximo;

    while (auxiliar != nullptr)
    {

        auxiliarProximo = auxiliar->getProximoItem();
        delete auxiliar;
        auxiliar = auxiliarProximo;
    }

}


template<class T>
void Lista<T>::inserirPrimeiro(Item<T> * item){
    this->primeiro = item;
    item->inserirAnterior(nullptr);
}

#endif