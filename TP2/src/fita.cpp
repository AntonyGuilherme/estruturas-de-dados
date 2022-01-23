#include "fita.hpp"

Fita::Fita(std::string nomeDoArquivo, int numeroDeFita)
{
    // instanciando o leitor de arquivos
    this->leitor = new LeitorDeArquivo(nomeDoArquivo);
    
    // atribuindo o número da fita
    this->numeroDeFita = numeroDeFita;
}

bool Fita::lerURL(std::string &endereco, int &numeroDeAcessos)
{
    // lendo o endereco e o número de acessos da url
    return this->leitor->getConteudoDaLinha(endereco) && this->leitor->getConteudoDaLinha(numeroDeAcessos);
}

bool Fita::read(URL *&url)
{

    std::string endereco;
    int numeroDeAcessos;

    // lendo a próxima URL do arquivo
    // caso não seja possível ler o arquivo
    // ele é fechado automaticamente
    if (this->lerURL(endereco, numeroDeAcessos))
    {
        // criando a url com o endereco e o numero de acessos
        // lidos no arquivo
        url = new URL(endereco, numeroDeAcessos, this->numeroDeFita);

        return true;
    }

    return false;
}