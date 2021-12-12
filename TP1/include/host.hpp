#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>
#include "lista.hpp"
#include "url.hpp"

class Host
{

private:
    Lista<URL> urls;
    std ::string nome;

public:
    Host(std::string nome);
    void adicionarURL(std ::string url);
    void imprimirURLs();
    void escalonarURLs();
    std::string getNome();
};

#endif