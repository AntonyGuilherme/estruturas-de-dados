#include "escritorDeArquivos.hpp"
#include "arquivoException.hpp"

EscritorDeArquivos::EscritorDeArquivos(std::string nomeArquivos) : EscritorDeArquivos()
{
    // preparando o arquivo para escrita
    this->prepararArquivo(nomeArquivos);
}

EscritorDeArquivos::EscritorDeArquivos()
{
    // instanciando o item para realizar as escritas futuras
    this->arquivo = new std::ofstream();
}

void EscritorDeArquivos::prepararArquivo(std::string nomeDoArquivo)
{

    // se houver arquivo aberto ele é fechado
    if (this->arquivo->is_open())
        this->fechar();

    // abrindo o arquivo com o nome informado
    this->arquivo->open(nomeDoArquivo, std::ios_base::out);

    //se o arquivo não for aberto uma excessão é lançada
    if (!this->arquivo->is_open())
    {
        throw new ArquivoException("O Arquivo nao pode ser aberto!");
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
        throw new ArquivoException("O Arquivo nao pode ser aberto 5!");
    }
}

void EscritorDeArquivos::escrever(std::string conteudo)
{
    // adicionando o conteúdo no arquivo
    this->arquivo->write(conteudo.data(), conteudo.size());

    if (this->arquivo->fail())
    { // verificando se há erros na escrita do arquivo
        throw new ArquivoException("O Arquivo nao pode ser aberto 5!");
    }
}

void EscritorDeArquivos::fechar()
{
    // fechando o arquivo
    this->arquivo->close();
}

EscritorDeArquivos::~EscritorDeArquivos()
{
    // fechando o arquivo caso ele esteja aberto
    if (this->arquivo->is_open())
    {
        this->arquivo->close();
    }

    // liberando a memória do item de escrita
    delete this->arquivo;
}
