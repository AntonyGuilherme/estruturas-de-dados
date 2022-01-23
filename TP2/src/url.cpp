#include "url.hpp"

URL::URL(std::string url, int numeroDeVisualizacoes)
{

    // atribuindo o nome da url e o número de urls
    this->url = url;
    this->numeroDeVisualizacoes = numeroDeVisualizacoes;
}

URL::URL(std::string url, int numeroDeVisualizacoes, int fitaDeOrigem) : URL(url, numeroDeVisualizacoes)
{
    // atribuindo a fita de origem, 
    // caso a url seja lida de uma fita
    this->fitaDeOrigem = fitaDeOrigem;
}

int URL::getNumeroDeVisualizacoes()
{
    // recuperando o número de visualizações
    return this->numeroDeVisualizacoes;
}

std::string URL::getEnderecoURL()
{
    // retorna o endereco da url : www.url.com
    return this->url;
}

std::string URL::toString()
{
    // criando uma visualização da url com seu endereço 
    // e com seu número de visualizações
    std::string textoURL = this->getEnderecoURL();
    return textoURL.append(" ").append(std::to_string(this->getNumeroDeVisualizacoes()));
}

int URL::getFitaDeOrigem()
{
    // retornando a fita de origem
    return this->fitaDeOrigem;
}

int URL::isSuperiorComparadaCom(URL *url)
{
    // verificando a diferença do número de visualizações
    int diferencaDeVisualizacoes = this->comparaEmNumeroDeVisualizacoes(url);

    // se a url informada for melhor um número negativo é informado
    // caso a url atual seja melhor um número positivo é retornado
    // caso as urls possuam o mesmo número de visualizações 
    // elas são comparadas alfabeticamente 
    if (diferencaDeVisualizacoes != 0)
    {
        return diferencaDeVisualizacoes;
    }

    // comparando a ordem alfabetica das urls
    return this->compararAlfabeticamente(url);
}

int URL::comparaEmNumeroDeVisualizacoes(URL *url)
{
    // calculando a diferença do número de visualizações das duas urls
    return this->getNumeroDeVisualizacoes() - url->getNumeroDeVisualizacoes();
}

int URL::compararAlfabeticamente(URL *url)
{   
    // comparando as urls alfabeticamente
    return url->getEnderecoURL().compare(this->getEnderecoURL());
}