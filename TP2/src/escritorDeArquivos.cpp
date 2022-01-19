#include "escritorDeArquivos.hpp"

EscritorDeArquivos::EscritorDeArquivos(std::string nomeArquivos) : EscritorDeArquivos()
{
    this->prepararArquivo(nomeArquivos);
}

EscritorDeArquivos::EscritorDeArquivos()
{
    this->arquivo = new std::ofstream();
}

void EscritorDeArquivos::prepararArquivo(std::string nomeDoArquivo)
{

    if (this->arquivo->is_open())
        this->fechar();

    this->arquivo->open(nomeDoArquivo, std::ios_base::out);

    if (!this->arquivo->is_open())
    {
        throw std::invalid_argument("O Arquivo nao pode ser aberto!");
    }
}

void EscritorDeArquivos::escreverLinha(std::string conteudo)
{
    // adicionando o conteúdo da linha ao arquivo
    this->arquivo->write(conteudo.data(), conteudo.size());

    // quebrando a linha do arquivo
    *this->arquivo << std::endl;

    if (this->arquivo->fail())
    { // verificando se há erros na escrita do arquivo
        throw std::invalid_argument("O Arquivo nao pode ser aberto 5!");
    }
}

void EscritorDeArquivos::fechar()
{
    this->arquivo->close();
}

EscritorDeArquivos::~EscritorDeArquivos()
{
    if (this->arquivo->is_open())
    {
        this->arquivo->close();
    }

    delete this->arquivo;
}
