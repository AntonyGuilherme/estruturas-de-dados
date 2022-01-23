#ifndef HEAP_EXCEPTION_H
#define HEAP_EXCEPTION_H

#include "aplicacaoException.hpp"

// classe que gerencia erros encontrados no heap
class HeapException : public AplicacaoException
{

public:
    
    // construtor que recebe somente uma mensagem de erro
    HeapException(std::string mensagem)
        : HeapException(mensagem, "Sem informacões adicionais!") {}

    // construtor que recebe a mensagem e o valor gerador do erro
    HeapException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro no Heap", informacoes) {}
};

#endif