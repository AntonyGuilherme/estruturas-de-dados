#include "heap.hpp"
#include <iostream>
#include "HeapException.hpp"

void Heap::Refaz(int Esq, int Dir, URL **A)
{

    int i, j;
    URL *x;
    i = Esq;
    j = i * 2;
    x = A[i];

    while (j <= Dir)
    {

        if (j < Dir)
        {
            if (A[j]->getNumeroDeVisualizacoes() < A[j + 1]->getNumeroDeVisualizacoes())
                j++;
        }

        if (x->getNumeroDeVisualizacoes() >= A[j]->getNumeroDeVisualizacoes())
            break;

        A[i] = A[j];

        i = j;
        j = i * 2;
    }

    A[i] = x;
}

bool Heap::RetiraMax(URL **A, int *n, URL *&url)
{

    if (*n < 1)
    {
        return false;
    }

    else
    {
        url = A[1];
        A[1] = A[*n];
        (*n)--;
        Refaz(1, *n, A);
    }

    return true;
}

void Heap::Constroi(URL **A, int *n)
{

    int esq = *n / 2 + 1; // verificando as folhas

    while (esq > 1)
    {
        esq--;
        Refaz(esq, *n, A);
    }
}

bool Heap::pop(URL *&url)
{

    return RetiraMax(this->heap, &this->tamanhoUsado, url);
}

void Heap::inserir(URL *url)
{

    if(tamanhoTotal == (tamanhoUsado+1)){
         throw new HeapException("Tamanho máximo do Heap atingido!");
    }

    this->tamanhoUsado++;
    this->heap[this->tamanhoUsado] = url;
    this->Constroi(this->heap, &this->tamanhoUsado);
}

Heap::Heap(int tamanhoTotalDoHeap)
{
    if (tamanhoTotalDoHeap <= 0)
    {
        throw new HeapException("Tamanho de Heap Inválido! É esperado um valor maior do que zero.");
    }

    this->tamanhoTotal = tamanhoTotalDoHeap + 1;
    this->tamanhoUsado = 0;
    this->heap = new URL *[this->tamanhoTotal];
}
