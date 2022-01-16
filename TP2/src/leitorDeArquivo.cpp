#include "leitorDeArquivo.hpp"
#include "AplicacaoException.hpp"

LeitorDeArquivo::LeitorDeArquivo()
{

    this->nomeDoArquivo = "undefined";
    this->arquivo = new std::ifstream;
}

LeitorDeArquivo::LeitorDeArquivo(std::string nomeDoArquivo)
{

    this->nomeDoArquivo = nomeDoArquivo;
    this->arquivo = new std::ifstream;
    this->abrirArquivo();
}

bool LeitorDeArquivo::getConteudoDaLinha(std ::string &conteudo)
{

    if (!this->arquivo->good())
    {
        this->arquivo->close();
        return false;
    }

    *this->arquivo >> conteudo;

    return true;
}

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

    arquivo->open(this->nomeDoArquivo);

    if (!arquivo->good())
    {
        throw new AplicacaoException("Arquivo não encontrado!");
    }
}

void LeitorDeArquivo::abrirArquivo(std::string nomeDoArquivo)
{
    this->nomeDoArquivo = nomeDoArquivo;

    if (arquivo->is_open())
    {
        arquivo->close();
    }

    this->abrirArquivo();
}

LeitorDeArquivo::~LeitorDeArquivo()
{

    if (this->arquivo->is_open())
    {
        this->arquivo->close();
    }

    delete this->arquivo;
}
