#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>
#include "lista.hpp"
#include "url.hpp"

class Host
{

private:
    Lista<URL> * urls;
    std ::string nome;

public:
    Host(std::string nome);
    ~Host();
    void adicionarURL(std ::string url);
    void imprimirURLs();
    int escalonarURLs(int quantidadeMaxima);
    int escalonarURLs();
    void limparURLs();
    std::string * getNome();

};

#endif