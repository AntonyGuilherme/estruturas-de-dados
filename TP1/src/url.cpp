#include "url.hpp"
#include <iostream>
//https://www.delftstack.com/pt/howto/cpp/split-string-in-cpp/

URL::URL(std::string url)
{

    this->url = url;

    this->calcularNivelDeProfundidade();
}

void URL::calcularNivelDeProfundidade()
{

    Lista<std::string> pedacos = split.quebrarStringBaseadoEm(&this->url, '/');

    this->nivelDeProfundidade = -2;
    Item<std::string> *auxiliar = pedacos.getPrimeiroItem();

    while (auxiliar != nullptr)
    {
        this->nivelDeProfundidade++;
        auxiliar = auxiliar->getProximoItem();
    }
}

int URL::getProfundidade()
{

    return this->nivelDeProfundidade;
}

std::string URL::getUrl()
{

    return this->url;
}
