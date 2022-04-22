#ifndef HASH_EXCEPTION_H
#define HASH_EXCEPTION_H

#include "aplicacaoException.hpp"

// classe que gerencia erros gerados pela HASH
class HashException : public AplicacaoException
{

public:
        // construtor que somente recebe a mensagem do error ocorrido
    HashException(std::string mensagem)
        : AplicacaoException(mensagem, "Sem informacões adicionais!") {}

    // construtor que recebe a mensagem e o valor que gerou o erro
    HashException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro no HASH", informacoes) {}
};

#endif