#ifndef LISTA_EXCEPTION_H
#define LISTA_EXCEPTION_H

#include "aplicacaoException.hpp"

// classe que gerencia erros gerados pela lista
class ListaException : public AplicacaoException
{

public:
        // construtor que somente recebe a mensagem do error ocorrido
    ListaException(std::string mensagem)
        : AplicacaoException(mensagem, "Sem informacões adicionais!") {}

    // construtor que recebe a mensagem e o valor que gerou o erro
    ListaException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro na Lista", informacoes) {}
};

#endif