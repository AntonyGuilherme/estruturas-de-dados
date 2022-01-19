#ifndef URL_H
#define URL_H

#include <string>

class URL
{

private:
    int numeroDeVisualizacoes;
    std::string url;
    int fitaDeOrigem;
    int getDiferencaDeVisualizacoes(URL* url);
    int comparaEmNumeroDeVisualizacoes(URL * url);
    int compararAlfabeticamente(URL * url);

public:
    URL(std::string url, int numeroDeVisualizacoes);
    URL(std::string url, int numeroDeVisualizacoes, int fitaDeOrigerem);
    std::string getEnderecoURL();
    int getNumeroDeVisualizacoes();
    std::string toString();
    int getFitaDeOrigem();
    int isSuperiorComparadaCom(URL * url);
};

#endif