#include "url.hpp"

URL::URL(std::string url, int numeroDeVisualizacoes)
{

    this->url = url;
    this->numeroDeVisualizacoes = numeroDeVisualizacoes;
}

URL::URL(std::string url, int numeroDeVisualizacoes, int fitaDeOrigem) : URL(url, numeroDeVisualizacoes)
{
    this->fitaDeOrigem = fitaDeOrigem;
}

int URL::getNumeroDeVisualizacoes()
{
    return this->numeroDeVisualizacoes;
}

std::string URL::getEnderecoURL()
{
    return this->url;
}

std::string URL::toString()
{

    std::string textoURL = this->getEnderecoURL();
    return textoURL.append(" ").append(std::to_string(this->getNumeroDeVisualizacoes()));
}

int URL::getFitaDeOrigem()
{

    return this->fitaDeOrigem;
}

int URL::isSuperiorComparadaCom(URL *url)
{
    int diferencaDeVisualizacoes = this->comparaEmNumeroDeVisualizacoes(url);

    if (diferencaDeVisualizacoes != 0)
    {
        return diferencaDeVisualizacoes;
    }

    return this->compararAlfabeticamente(url);
}

int URL::comparaEmNumeroDeVisualizacoes(URL *url)
{
    return this->getNumeroDeVisualizacoes() - url->getNumeroDeVisualizacoes();
}

int URL::compararAlfabeticamente(URL *url)
{
    return this->getEnderecoURL().compare(url->getEnderecoURL());
}