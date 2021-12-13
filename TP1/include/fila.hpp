#ifndef FILA_H
#define FILA_H

// Listas :
// inserção em qualquer posição
// remoção em qualquer posição

// FIlas
// Inserção: Trás ( última posição)
// remoção Início

#include "item.hpp"
#include "url.hpp"

template <typename T>
class Fila
{

private:
    int tamanho;
    Item<T> *primeiro = nullptr;
    Item<T> *ultimo = nullptr;

public:
    Fila(){};
    Fila(T *objeto);
    ~Fila();
    void inserir(T *item);
    T remover();
    Item<T> *getPrimeiroItem();
    Item<T> *getUltimoItem();
    bool isFilaVazia();
};

template <class T>
Fila<T>::Fila(T *objeto)
{

    this->primeiro = new Item<T>(objeto);
}

template <class T>
void Fila<T>::inserir(T *objeto)
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
}

template <class T>
T Fila<T>::remover()
{

    if (this->ultimo == nullptr)
    {
        throw "Removendo um item nulo";
    }

    T auxiliarParaRetorno = *this->ultimo->getValorDoObjetoArmazenado();
    Item<T> *auxiliarParaRemocao = this->ultimo;

    //reajustando a ultima posicao
    this->ultimo = this->ultimo->getAnteriorItem();

    if (this->ultimo != nullptr)
        this->ultimo->inserirProximo(nullptr);
    else    
        this->primeiro = nullptr;
    
    delete auxiliarParaRemocao;

    return auxiliarParaRetorno;
}

template <class T>
Item<T> *Fila<T>::getPrimeiroItem()
{

    return this->primeiro;
}

template <class T>
Item<T> *Fila<T>::getUltimoItem()
{

    return this->ultimo;
}

template <class T>
Fila<T>::~Fila()
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

template <class T>
bool Fila<T>::isFilaVazia()
{

    return this->ultimo == nullptr;
}

#endif