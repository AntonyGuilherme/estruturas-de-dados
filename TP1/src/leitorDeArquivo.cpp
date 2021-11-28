#include "leitorDeArquivo.hpp"

LeitorDeArquivo::LeitorDeArquivo(std::string nomeDoArquivo)
{

    this->nomeDoArquivo = nomeDoArquivo;
    this->abrirArquivo();
}

bool LeitorDeArquivo::getConteudoDaLinha(std :: string & conteudo)
{

    if (!this->arquivo.good())
    {
        this->arquivo.close();
        return false;
    }

    this->arquivo >> conteudo;

    return true;
}

void LeitorDeArquivo::abrirArquivo()
{

    arquivo.open(this->nomeDoArquivo);

    if (!arquivo.good())
    {
        throw "Arquivo nao encontrado!";
    }
}
