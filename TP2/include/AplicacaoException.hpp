#ifndef APLICACAO_EXCEPTION_H
#define APLICACAO_EXCEPTION_H

#include <string>

class AplicacaoException
{

private:
    std::string mensagem;
    std::string codigo;
    std::string informacoes;

public:
    AplicacaoException(std::string mensagem, std::string codigo, std::string informacoes)
    {
        this->mensagem = mensagem;
        this->codigo = codigo;
        this->informacoes = informacoes;
    };

    AplicacaoException(std::string mensagem, std::string codigo) : AplicacaoException(mensagem, codigo, "Sem informação aidcional") {}

    AplicacaoException(std::string mensagem) : AplicacaoException(mensagem, "Sem Descricao")
    {
        this->mensagem = mensagem;
    };

    std::string getMensagem()
    {
        return this->mensagem;
    }

    std::string getCodigo()
    {
        return this->codigo;
    }

    std::string getInformacoes()
    {
        return this->informacoes;
    }
};

#endif