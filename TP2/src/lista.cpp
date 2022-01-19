#include "Lista.hpp"
#include <iostream>
#include "listaException.hpp"

bool Lista::pop(URL *&url)
{

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

    // atribuindo o tamanho da lista e allocando a memória necessária
    this->tamanhoTotal = tamanhoTotalDoHeap;
    this->tamanhoUsado = 0;
    this->lista = new URL *[this->tamanhoTotal];
}

void Lista::ordenar(Ordenador *ordenador)
{
    ordenador->ordenar(this->lista, this->tamanhoUsado);
}

int Lista::getTamanhoUsado()
{

    return this->tamanhoUsado;
}

Lista::~Lista(){

    delete lista;
}