#ifndef FILA_H
#define FILA_H

// Listas :
// inserção em qualquer posição
// remoção em qualquer posição

// FIlas
// Inserção: Trás ( última posição)
// remoção Início

#include "itemFila.hpp"

template <typename T>
class Fila
{

private:
    int tamanho;
    ItemFila<T> *primeiro = nullptr;
    ItemFila<T> *ultimo = nullptr;

public:
    Fila(){};
    Fila(T *objeto);
    void inserir(T *item);
    void remover();
    ItemFila<T> * getPrimeiro();
};

template <class T>
Fila<T>::Fila(T *objeto)
{

    this->primeiro = new ItemFila<T>(objeto);
}

template <class T>
void Fila<T>::inserir(T *objeto)
{

    if (this->primeiro == nullptr)
    {

        this->primeiro = new ItemFila<T>(objeto);
    }
    else if (this->ultimo == nullptr)
    {

        this->ultimo = new ItemFila<T>(objeto, this->primeiro);
        this->primeiro->inserirProximo(this->ultimo);
    }
    else
    {
       ItemFila<T> * item = new ItemFila<T>(objeto, this->ultimo);
       this->ultimo->inserirProximo(item);
        this->ultimo = item;
    }
}

template <class T>
void Fila<T>::remover() {}

template <class T>
ItemFila<T> * Fila<T>::getPrimeiro()
{

    return this->primeiro;
}

#endif