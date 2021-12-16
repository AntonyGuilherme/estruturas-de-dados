#ifndef HOST_H
#define HOST_H

#include <string>
#include "lista.hpp"
#include "url.hpp"
#include "splitString.hpp"
#include "escritorDeArquivos.hpp"

class Host
{

private:
    Lista<URL> * urls;
    std ::string nome;

public:
    Host(std::string nome);
    ~Host();
    void adicionarURL(std ::string url);
    void imprimirURLs(EscritorDeArquivos * escritor);
    int escalonarURLs(int quantidadeMaxima,EscritorDeArquivos * escritor);
    int escalonarURLs(EscritorDeArquivos * escritor);
    void limparURLs();
    std::string * getNome();

};

#endif