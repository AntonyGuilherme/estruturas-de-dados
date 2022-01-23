#include "leitorDeArquivo.hpp"
#include "arquivoException.hpp"

LeitorDeArquivo::LeitorDeArquivo()
{
    // atribuindo o nome do arquivo como não declarado
    this->nomeDoArquivo = "undefined";

    // craindo o item para acesso ao arquivo futuramente
    this->arquivo = new std::ifstream;
}

LeitorDeArquivo::LeitorDeArquivo(std::string nomeDoArquivo)
{
    // atribuindo o nome do arquivo para leitura
    this->nomeDoArquivo = nomeDoArquivo;
    
    // craindo o item para acesso ao arquivo futuramente
    this->arquivo = new std::ifstream;

    // abrindo o arquivo para leitura
    this->abrirArquivo();
}

bool LeitorDeArquivo::getConteudoDaLinha(std ::string &conteudo)
{

    // se o arquivo não estiver aberto de maneira correta
    // a leitura não é concluída
    if (!this->arquivo->good())
    {
        this->arquivo->close();
        return false;
    }

    // inserindo o valor lido do arquivo na variável fornecida
    *this->arquivo >> conteudo;

    // retornado que a leitura foi bem sucedida
    return true;
}

// lendo o conteudo da linha para um inteiro
// utilizando as mesmas regras de um conteúdo em formato de string
bool LeitorDeArquivo::getConteudoDaLinha(int &conteudo)
{

    if (!this->arquivo->good())
    {
        this->arquivo->close();
        return false;
    }

    *this->arquivo >> conteudo;

    return true;
}

void LeitorDeArquivo::abrirArquivo()
{
    // abrindo o arquivo com o nome informado
    arquivo->open(this->nomeDoArquivo);

    // se o arquivo não for aberto uma excessão é jogada
    if (!arquivo->good())
    {
        throw new ArquivoException("Arquivo não encontrado!",this->nomeDoArquivo);
    }
}

void LeitorDeArquivo::abrirArquivo(std::string nomeDoArquivo)
{
    // atribuindo o nome do arquivo informado
    this->nomeDoArquivo = nomeDoArquivo;

    // fechando o arquivo anterior caso ele esteja aberto
    if (arquivo->is_open())
    {
        arquivo->close();
    }

    // abrindo o arquivo
    this->abrirArquivo();
}

LeitorDeArquivo::~LeitorDeArquivo()
{
    // se o arquivo estiver aberto ele é fechado
    if (this->arquivo->is_open())
    {
        this->arquivo->close();
    }

    // liberando a memória do acesso aos arquivos
    delete this->arquivo;
}
