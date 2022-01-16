#ifndef URL_H
#define URL_H

#include <string>

class URL
{

private:
    int numeroDeVisualizacoes;
    std::string url;
    int fitaDeOrigem;

public:
    URL(std::string url, int numeroDeVisualizacoes);
    URL(std::string url, int numeroDeVisualizacoes, int fitaDeOrigerem);
    std::string getEnderecoURL();
    int getNumeroDeVisualizacoes();
    std::string toString();
    int getFitaDeOrigem();
};

#endif