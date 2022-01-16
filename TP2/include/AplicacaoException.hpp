#ifndef APLICACAO_EXCEPTION_H
#define APLICACAO_EXCEPTION_H

#include <string>

class AplicacaoException
{

private:
    std::string mensagem;

public:
    AplicacaoException(std::string mensagem)
    {
        this->mensagem = mensagem;
    }

    std::string GetMensagem()
    {
        return this->mensagem;
    }
};

#endif