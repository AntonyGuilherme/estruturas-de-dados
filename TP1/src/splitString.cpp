#include "splitString.hpp"
#include <iostream>
// https://www.javatpoint.com/how-to-split-strings-in-cpp

std::vector<std::string> SplitString::quebrarStringBaseadoEm(std::string *conteudo, char token)
{

    // pedaco encontrado no conteudo da string buscada
    std::string pedaco;

    //craindo um stream de dados a partir da string informada
    std::stringstream streamData(*conteudo);

    // lista que contém os pedaços encontrados na string
    std::vector<std::string> pedacosEncontrados;

    // navegando pelos padaços encontrados no conteudo da string informada
    while (std::getline(streamData, pedaco, '/'))
    {
        if (pedaco.size())
            pedacosEncontrados.push_back(pedaco);
    }

    streamData.clear();

    return pedacosEncontrados;
}

std::string SplitString::getPedacoDaStringQuebrada(std::string *conteudo, char token, int posicao)
{
    // posicao
    int index = 0;

    // pedaco encontrado no conteudo da string buscada
    std::string pedaco;

    //craindo um stream de dados a partir da string informada
    std::stringstream streamData(*conteudo);

    // navegando pelos padaços encontrados no conteudo da string informada
    while (std::getline(streamData, pedaco, '/'))
    {
        if (pedaco.size())
        {
            if (posicao == index)
                return pedaco;

            index++;
        }
    }

    streamData.clear();

    std::cout << *conteudo << std::endl;

    throw "Posicao nao encontrada";
}

std::string SplitString::removerPedacoDaString(std::string fonte, std::string conteudoParaRemocao)
{
    //buscando a pela posicao
    size_t posicaoInicial = fonte.find(conteudoParaRemocao);

    if(posicaoInicial != std::string::npos) // se for encontrado o item para remocao remova
        fonte.erase(posicaoInicial, conteudoParaRemocao.length());

    //caso não encontre retorna a mesma string
    return fonte;
}