#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include <string>
#include "splitString.hpp"
#include "host.hpp"
#include "fila.hpp"
#include "escritorDeArquivos.hpp"
/**
    * ADD_URLS <quantidade>: adiciona ao escalonador as URLs informadas nas linhas seguintes.
    * O parâmetro <quantidade> indica quantas linhas serão lidas antes do próximo comando.
    * ESCALONA_TUDO: escalona todas as URLs seguindo as regras estabelecidas previamente.
    * Quando escalonadas, as URLs são exibidas e removidas da lista.
    * ESCALONA <quantidade>: limita a quantidade de URLs escalonadas.
    * ESCALONA_HOST <host> <quantidade>: são escalonadas apenas URLs deste host.
    * VER_HOST <host>: exibe todas as URLs do host, na ordem de prioridade.
    * LISTA_HOSTS: exibe todos os hosts, seguindo a ordem em que foram conhecidos.
    * LIMPA_HOST <host>: limpa a lista de URLs do host.
 */

class Escalonador
{

public:
    Escalonador(std::string& nomeDoArquivoDeSaida);
    ~Escalonador();
    void adicionarURLs(std::string url);
    void escalanoarTodasAsURLs();
    void escalonarURLs(int quantidadeDeURLs);
    void escalonarURLsDoHost(std::string host,int quantidade);
    void visualizarURLsDoHost(std::string host);
    void visualizarHosts();
    void limparHost(std::string host);
    void limparTudo();

private:
    Fila<Host> * hosts;
    EscritorDeArquivos * escritorDeArquivos;
};

#endif