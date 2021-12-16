#include "escritorDeArquivos.hpp"

//https://www.delftstack.com/howto/cpp/cpp-write-to-file/

EscritorDeArquivos::EscritorDeArquivos(std::string &nomeArquivos)
{
    this->arquivo.open(nomeArquivos, std::ios_base::out);

    if (!this->arquivo.is_open())
    {
        throw std::invalid_argument("O Arquivo nao pode ser aberto!");
    }
}

void EscritorDeArquivos::escreverLinha(std::string &conteudo)
{
    // adicionando o conteúdo da linha ao arquivo
    this->arquivo.write(conteudo.data(), conteudo.size());

    // quebrando a linha do arquivo
    this->arquivo << std::endl;

    if(this->arquivo.fail()){ // verificando se há erros na escrita do arquivo
        throw std::invalid_argument("O Arquivo nao pode ser aberto!");
    }
}

void EscritorDeArquivos::fechar()
{
    this->arquivo.close();
}