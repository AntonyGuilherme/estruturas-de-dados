#ifndef LISTA_H
#define LISTA_H

#include "url.hpp"
#include "ordenador.hpp"

class Lista
{

private:
    URL ** lista;
    int tamanhoTotal;
    int tamanhoUsado;

public:
    Lista(int tamanhoDoHeap);
    bool pop(URL*&url);
    void inserir(URL * url);
    void ordenar(Ordenador * ordenador);
    int getTamanhoUsado();
    ~Lista();

};

#endif