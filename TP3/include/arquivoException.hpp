#ifndef ARQUIVO_EXCEPTION_H
#define ARQUIVO_EXCEPTION_H

#include "aplicacaoException.hpp"

// Excessão que demonstra um erro encontrado na leitura ou escrita de um arquivo
class ArquivoException : public AplicacaoException
{

public:
    // recebe somente a mensagem do erro no Arquivo
    ArquivoException(std::string mensagem)
        : ArquivoException(mensagem, "Sem informacões adicionais!") {}

    // recebe não só a mensagem, mas também o valor que gerou o erro
    ArquivoException(std::string mensagem, std::string informacoes)
        : AplicacaoException(mensagem, "Erro no Arquivo!", informacoes) {}
};

#endif