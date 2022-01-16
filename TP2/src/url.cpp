#include "url.hpp"

URL::URL(std::string url, int numeroDeVisualizacoes)
{

    this->url = url;
    this->numeroDeVisualizacoes = numeroDeVisualizacoes;
}

URL::URL(std::string url, int numeroDeVisualizacoes, int fitaDeOrigem) : URL(url,numeroDeVisualizacoes)
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

std::string URL::toString(){

    std::string textoURL = this->getEnderecoURL();
    return textoURL.append(" ").append(std::to_string(this->getNumeroDeVisualizacoes()));
}


int URL::getFitaDeOrigem(){

    return this->fitaDeOrigem;
}