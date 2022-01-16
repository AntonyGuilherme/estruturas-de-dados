#ifndef HEAP_EXCEPTION_H
#define HEAP_EXCEPTION_H

#include "AplicacaoException.hpp"

class HeapException : public AplicacaoException
{

public:
    HeapException(std::string mensagem) : AplicacaoException(mensagem) {}
};

#endif