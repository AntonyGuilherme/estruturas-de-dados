#include <iostream>
#include "leitorDeArquivo.hpp"
#include "escalonador.hpp"
#include "lista.hpp"
#include <stdexcept>
#include "item.hpp"

void adicionarURLs(
    Escalonador *escalonador,
    LeitorDeArquivo *leitor,
    SplitString &split,
    Lista<std::string> &extensoesNaoConsideradas,
    std::string &conteudoLido)
{
    //pegando a quantidade de urls que devem ser adicionadas
    leitor->getConteudoDaLinha(conteudoLido);
    int quantidade = std::stoi(conteudoLido);
    int index = 0;

    while (quantidade > index)
    {

        leitor->getConteudoDaLinha(conteudoLido);
        // removendo o www. da url informada
        conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");

        bool pularURL = false;

        // O(1)-- custo constante 
        for (int i = 0; i < extensoesNaoConsideradas.size(); i++)
        {
            if (conteudoLido.find(*extensoesNaoConsideradas.get(i)) != std::string::npos)
            {
                // pulando a url caso ela de acesso a um arquivo inadequado
                pularURL = true;
            }
        }

        // removendo a barra no final da url se houver
        if (conteudoLido[conteudoLido.size() - 1] == '/')
        {
            conteudoLido.erase(conteudoLido.size() - 1, 1);
        }

        if (!pularURL)
            escalonador->adicionarURLs(conteudoLido); // O(n^2)

        index++;
    }
}

void escalonadorTodasAsURLs(Escalonador *escalonador)
{
    escalonador->escalanoarTodasAsURLs();
}

void escalonarURLsPorQuantidade(LeitorDeArquivo *leitor, Escalonador *escalonador, std::string &conteudoLido)
{

    leitor->getConteudoDaLinha(conteudoLido);
    int quantidade = std::stoi(conteudoLido);
    escalonador->escalonarURLs(quantidade);
}

void escalonarURLsPorHost(
    LeitorDeArquivo *leitor,
    Escalonador *escalonador,
    std::string &conteudoLido,
    SplitString &split)
{

    std::string host;
    leitor->getConteudoDaLinha(host);
    leitor->getConteudoDaLinha(conteudoLido);
    int quantidade = std::stoi(conteudoLido);
    host = split.removerPedacoDaString(host, "www.");
    escalonador->escalonarURLsDoHost(host, quantidade);
}

void visualizarURLsDoHost(
    LeitorDeArquivo *leitor,
    Escalonador *escalonador,
    std::string &conteudoLido,
    SplitString &split)
{
    leitor->getConteudoDaLinha(conteudoLido);
    conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");
    escalonador->visualizarURLsDoHost(conteudoLido);
}

void limparHost(
    LeitorDeArquivo *leitor,
    Escalonador *escalonador,
    std::string &conteudoLido,
    SplitString &split)
{
    leitor->getConteudoDaLinha(conteudoLido);
    conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");
    escalonador->limparHost(conteudoLido);
}

void visualizarHosts(Escalonador * escalonador){
    escalonador->visualizarHosts();
}

void limparTudo(Escalonador * escalonador){
    escalonador->limparTudo();
}

int main(int numeroDeArgumentos, char **argumentos)
{
    Lista<std::string> extensoesNaoConsideradas;
    extensoesNaoConsideradas.inserir(new std::string(".pdf"));
    extensoesNaoConsideradas.inserir(new std::string(".doc"));
    extensoesNaoConsideradas.inserir(new std::string(".avi"));
    extensoesNaoConsideradas.inserir(new std::string(".mp3"));
    extensoesNaoConsideradas.inserir(new std::string(".gif"));
    extensoesNaoConsideradas.inserir(new std::string(".jpg"));

    // verificando se o arquivo foi informado
    if (numeroDeArgumentos < 1)
    {
        throw std::invalid_argument("O nome do arquivo nao foi encontrado");
    }

    std::string nomeArquivo(argumentos[1]);

    // verificando a extensão do arquivo
    if (nomeArquivo.find_last_of(".txt") == std::string::npos)
    {
        throw std::invalid_argument("O arquivo deve possuir a extensao txt");
    }

    SplitString split;
    std::string nomeSemExtensao = split.removerPedacoDaString(nomeArquivo, ".txt");
    std::string nomeArquivoDeSaida = nomeSemExtensao.append("-out").append(".txt");

    Escalonador *escalonador = new Escalonador(nomeArquivoDeSaida);
    LeitorDeArquivo *leitor = new LeitorDeArquivo(nomeArquivo);
    std::string conteudoLido;

    while (leitor->getConteudoDaLinha(conteudoLido))
    {

        if (conteudoLido.compare("ADD_URLS") == 0)
        {
            adicionarURLs(escalonador, leitor, split, extensoesNaoConsideradas, conteudoLido);
        }
        else if (conteudoLido.compare("ESCALONA_TUDO") == 0)
        {
            escalonadorTodasAsURLs(escalonador);
        }
        else if (conteudoLido.compare("ESCALONA") == 0)
        {
            escalonarURLsPorQuantidade(leitor, escalonador, conteudoLido);
        }
        else if (conteudoLido.compare("ESCALONA_HOST") == 0)
        {
            escalonarURLsPorHost(leitor, escalonador, conteudoLido, split);
        }
        else if (conteudoLido.compare("VER_HOST") == 0)
        {
            visualizarURLsDoHost(leitor, escalonador, conteudoLido, split);
        }
        else if (conteudoLido.compare("LISTA_HOSTS") == 0)
        {
            visualizarHosts(escalonador);   
        }
        else if (conteudoLido.compare("LIMPA_HOST") == 0)
        {
            limparHost(leitor,escalonador,conteudoLido,split);
        }
        else if (conteudoLido.compare("LIMPA_TUDO") == 0)
        {
            limparTudo(escalonador);
        }
        else
        {
            throw std::invalid_argument("Opção não encontrada!");
        }
    }

    return 0;
}