#ifndef SPLIT_STRING_H
#define SPLIT_STRING_H

#include <string>
#include <vector>
#include <sstream>

class SplitString
{

public:
    std::vector<std::string> quebrarStringBaseadoEm(std::string* conteudo, char token);
    std::string getPedacoDaStringQuebrada(std::string* conteudo, char token, int posicao);
    std::string removerPedacoDaString(std::string fonte,std::string conteudoParaRemocao);
};

#endif