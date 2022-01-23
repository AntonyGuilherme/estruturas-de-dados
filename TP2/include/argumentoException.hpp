#ifndef ARGUMENTO_EXCEPTION_H
#define ARGUMENTO_EXCEPTION_H

#include "aplicacaoException.hpp"

// Excessão que demonstra um erro encontrado em um dos argumentos
// fornecidos ao programa
class ArgumentoException : public AplicacaoException
{

public:
    // recebe somente a mensagem do erro no argumento
    ArgumentoException(std::string mensagem)
        : ArgumentoException(mensagem, "Sem informacões adicionais!") {}

    // recebe não só a mensagem, mas também o valor que gerou o erro
    ArgumentoException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro nos argumentos informados!", informacoes) {}
};

#endif