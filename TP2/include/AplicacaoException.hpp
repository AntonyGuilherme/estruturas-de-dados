#ifndef APLICACAO_EXCEPTION_H
#define APLICACAO_EXCEPTION_H

#include <string>

// classe que gerencia excessões lançadas pela aplicação
class AplicacaoException
{

private:
    std::string mensagem; // mensagem informada
    std::string codigo; // onde a excessão foi lançada
    std::string informacoes; // valor que possivelmente gerou o erro

public:
    // construtor mais descritivo, ou seja, que recebe e atribui todos os itens acima
    AplicacaoException(std::string mensagem, std::string codigo, std::string informacoes)
    {
        this->mensagem = mensagem;
        this->codigo = codigo;
        this->informacoes = informacoes;
    };

    // construtor que somente utiliza a mensagem e o código
    AplicacaoException(std::string mensagem, std::string codigo) : AplicacaoException(mensagem, codigo, "Sem informação aidcional") {}

    // construtor que só tuliza a mensagem
    AplicacaoException(std::string mensagem) : AplicacaoException(mensagem, "Sem Descricao")
    {
        this->mensagem = mensagem;
    };

    // retornando a mensagem do erro
    std::string getMensagem()
    {
        return this->mensagem;
    }

    // retornando o código(local onde o erro foi gerado)
    std::string getCodigo()
    {
        return this->codigo;
    }

    // retornando o possível valor que gerou o erro
    std::string getInformacoes()
    {
        return this->informacoes;
    }
};

#endif