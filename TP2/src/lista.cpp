#include "Lista.hpp"
#include <iostream>
#include "listaException.hpp"

bool Lista::pop(URL *&url)
{

    // caso não haja mais leituras a serem feitas é retornado false
    if (this->tamanhoUsado <= 0)
        return false;

    // atribuindo a maior url com os atributos especificados
    // e reajustando o tamanho do heap
    this->tamanhoUsado -= 1;
    url = this->lista[(this->tamanhoUsado)];
    this->lista[(this->tamanhoUsado)] = nullptr;

    return true;
}

void Lista::inserir(URL *url)
{

    // se houver uma tentaiva de ultrapassar o tamanho máximo
    // permitido o programa é parado
    if (tamanhoTotal <= tamanhoUsado)
    {
        throw new ListaException("Tamanho máximo do Heap atingido!", url->toString());
    }

    // atribuindo a url e incrementando o tamanho utilizado
    this->lista[this->tamanhoUsado] = url;
    this->tamanhoUsado++;
}

Lista::Lista(int tamanhoTotalDoHeap)
{
    // caso o tamanho da lista não seja válido o programa é parado
    if (tamanhoTotalDoHeap <= 0)
    {
        throw new ListaException(
            "Tamanho de Heap Inválido! É esperado um valor maior do que zero.", std::to_string(tamanhoTotalDoHeap));
    }

    // atribuindo o tamanho da lista e alocando a memória necessária
    this->tamanhoTotal = tamanhoTotalDoHeap;
    this->tamanhoUsado = 0;
    this->lista = new URL *[this->tamanhoTotal];
}

void Lista::ordenar(Ordenador *ordenador)
{
    // ordenando o arquivo de acordo com a regra estipulada pelo ordenador
    ordenador->ordenar(this->lista, this->tamanhoUsado);
}

int Lista::getTamanhoUsado()
{
    // retorna o tamnho utilizado até o momento pela lista
    return this->tamanhoUsado;
}

Lista::~Lista(){

    // liberando o ponteiro que guarda o ponteiro para
    // os ponteiros das urls
    // as urls em si, devem ter sua memória liberada pelo utilizador
    delete lista;
}