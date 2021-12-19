#include "url.hpp"
#include <iostream>

URL::URL(std::string url)
{

    this->url = url;

    this->calcularNivelDeProfundidade();
}

void URL::calcularNivelDeProfundidade()
{
    // pegando os pedacos da URL
    Lista<std::string> pedacos = split.quebrarStringBaseadoEm(&this->url, '/');

    this->nivelDeProfundidade = -2;
    Item<std::string> *auxiliar = pedacos.getPrimeiroItem();

    // calculando o nível de profundida
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
