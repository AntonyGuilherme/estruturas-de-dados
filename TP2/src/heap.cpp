#include "heap.hpp"
#include <iostream>
#include "heapException.hpp"

/**
 * @brief 
 * 
 * @param Esq recebe o primeiro elemento considerado na consturção
 * @param Dir último elemento do vetor
 * @param A vetor
 */
void Heap::Refaz(int Esq, int Dir, URL **A)
{

    int i, j;
    URL *x;
    i = Esq; // primeiro item considerado
    j = i * 2; // filho da esquerda
    x = A[i]; // chave do nó

    while (j <= Dir) // enquanto j for um index de um filho 
    {

        if (j < Dir) // se existe um filho da direita
        {
            // verifica o maior entre os filhos, para ser comparado com o pai
            if (A[j + 1]->isSuperiorComparadaCom(A[j]) > 0)  
                j++;
        }

        // se o pai for maior que os filhos, o loop é encerrado 
        if (x->isSuperiorComparadaCom(A[j]) >= 0) 
            break;

        // chave do filho passo para o pai
        A[i] = A[j]; 
        // atualiza o índice do pai e filhos, para percorrer a subárvore
        i = j;
        j = i * 2;
    }
    // coloca a chave do pai, na posição descendentes
    A[i] = x;
}

bool Heap::RetiraMax(URL **A, int *n, URL *&url)
{

    if (*n < 1) // testa se o heap está vazio
    {
        return false;
    }

    else
    {
        // recebe o valor máximo
        url = A[1];
        // passa o último elemento para a priemeira posição 
        A[1] = A[*n];
        A[*n] = nullptr;

        // decrementando o tamanho do heap
        (*n)--;
        
        // reconstruindo o heap
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
        Refaz(esq, *n, A); // refazendo todas as folhas
    }
}

bool Heap::pop(URL *&url)
{
    // retirando o elemento máximo
    return RetiraMax(this->heap, &this->tamanhoUsado, url);
}

void Heap::inserir(URL *url)
{

    // verificando se o heap já foi completamente inserido
    if (tamanhoTotal == (tamanhoUsado + 1))
    {
        throw new HeapException("Tamanho máximo do Heap atingido!");
    }

    // incrementando o tamanho utilizado
    this->tamanhoUsado++;
    // adicionando o a url no heap
    this->heap[this->tamanhoUsado] = url;
    // reconstruindo o heap com o elemento adicionado
    this->Constroi(this->heap, &this->tamanhoUsado);
}

Heap::Heap(int tamanhoTotalDoHeap)
{
    // verificando o tamanho do heap gerado
    if (tamanhoTotalDoHeap <= 0)
    {
        throw new HeapException(
            "Tamanho de Heap Inválido! É esperado um valor maior do que zero.",
            std::to_string(tamanhoTotalDoHeap));
    }

    // incrementando o tamanho do heap
    this->tamanhoTotal = tamanhoTotalDoHeap + 1;
    
    // inicializando o tamanho utilizado
    this->tamanhoUsado = 0;

    // alocando o espaço para as url
    this->heap = new URL *[this->tamanhoTotal];
}

Heap::~Heap()
{
    // removendo o ponteiro que armazena os ponteiros das urls
    // os poteiros das urls devem ser removidos pelos utilizadores
    delete heap;
}