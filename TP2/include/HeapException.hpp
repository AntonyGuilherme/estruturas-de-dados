#ifndef HEAP_EXCEPTION_H
#define HEAP_EXCEPTION_H

#include "aplicacaoException.hpp"

class HeapException : public AplicacaoException
{

public:
    HeapException(std::string mensagem)
        : AplicacaoException(mensagem, "Sem informacões adicionais!") {}

    HeapException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro no Heap", informacoes) {}
};

#endif