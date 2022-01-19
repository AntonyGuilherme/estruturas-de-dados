#ifndef LISTA_EXCEPTION_H
#define LISTA_EXCEPTION_H

#include "aplicacaoException.hpp"

class ListaException : public AplicacaoException
{

public:
    ListaException(std::string mensagem)
        : AplicacaoException(mensagem, "Sem informacões adicionais!") {}

    ListaException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro na Lista", informacoes) {}
};

#endif