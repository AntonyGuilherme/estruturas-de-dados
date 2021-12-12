#ifndef FILA_H
#define FILA_H

// Listas :
// inserção em qualquer posição
// remoção em qualquer posição

// FIlas
// Inserção: Trás ( última posição)
// remoção Início

#include "itemFila.hpp"
#include "url.hpp"

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
    ~Fila();
    void inserir(T *item);
    T remover();
    ItemFila<T> *getPrimeiroItem();
    ItemFila<T> *getUltimoItem();
    bool isFilaVazia();
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
        ItemFila<T> *item = new ItemFila<T>(objeto, this->ultimo);
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
    ItemFila<T> *auxiliarParaRemocao = this->ultimo;

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
ItemFila<T> *Fila<T>::getPrimeiroItem()
{

    return this->primeiro;
}

template <class T>
ItemFila<T> *Fila<T>::getUltimoItem()
{

    return this->ultimo;
}

template <class T>
Fila<T>::~Fila()
{

    ItemFila<T> *auxiliar = this->primeiro;
    ItemFila<T> *auxiliarProximo;

    while (auxiliar != nullptr)
    {

        auxiliarProximo = auxiliar->getProximoItem();
        std::cout << "Apagando " << auxiliar->getValorDoObjetoArmazenado() << std::endl;
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