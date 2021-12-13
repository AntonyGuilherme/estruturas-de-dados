#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "host.hpp"
#include "splitString.hpp"
#include "url.hpp"
#include "leitorDeArquivo.hpp"
#include "escalonador.hpp"
#include "lista.hpp"
#include "item.hpp"
#include "fila.hpp"
#include <stdexcept>

/*
void splitString(std::string *source, std::vector<std::string> *vetor)
{

    std::string conteudo;
    //Construct a stream from the string
    std::stringstream streamData(*source);

    while (std::getline(streamData, conteudo, '/'))
    {
        vetor->push_back(conteudo);
    }
}

void adicionarLinhas(std::ifstream *arquivo, std::vector<std::string> *vetor, int numeroDeURLs)
{
    int linhasAdicionadas = 0;
    std::string urlLida;
    while (linhasAdicionadas < numeroDeURLs)
    {

        *arquivo >> urlLida;
        if (std::string::npos != urlLida.find("http"))
        {
            vetor->push_back(urlLida);
        };
        linhasAdicionadas++;
    }

}

void isHostAdicionado(std::vector<Host>& hosts, std::string url){
    
    SplitString splitString;

    std::string host = splitString.getPedacoDaStringQuebrada(&url,'/',1);
    bool isEncontrado =  false;

    for(auto& hostArmazenado : hosts){

        if(hostArmazenado.getNome().compare(host) == 0){
            hostArmazenado.adicionarURL(url);
            isEncontrado = true;
            break;
        }
        
    }

    if(!isEncontrado){
        Host hostEncontrado(host);
        hostEncontrado.adicionarURL(url);
        hosts.push_back(hostEncontrado);
    }


}
*/

void testesLista()
{

    Lista<URL> *urls = new Lista<URL>();
    urls->inserir(0, new URL("http://www.globo.com/2"));
    urls->inserir(0, new URL("http://www.globo.com/1"));
    urls->inserir(0, new URL("http://www.globo.com/0"));
    urls->inserir(3, new URL("http://www.globo.com/84"));
    //urls->inserir(3, new URL("http://www.globo.com/84"));
    urls->inserir(2, new URL("http://www.globo.com/42"));
    urls->inserir(0, new URL("http://www.globo.com/42"));
    urls->inserir(urls->getPrimeiroItem(), new URL("http://www.globo.com/4256"));
    //urls->inserir(urls->getItem(7),new URL("http://www.globo.com/42562"));

    Item<URL> *auxiliar = urls->getPrimeiroItem();

    while (auxiliar != nullptr)
    {

        std::cout << auxiliar->getValorDoObjetoArmazenado()->getUrl() << std::endl;

        auxiliar = auxiliar->getProximoItem();
    }
}

int main()
{

    Escalonador *escalonador = new Escalonador();
    LeitorDeArquivo *leitor = new LeitorDeArquivo("file.txt");
    std::string conteudoLido;

    while (leitor->getConteudoDaLinha(conteudoLido))
    {   
        

        if (conteudoLido.compare("ADD_URLS") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            int quantidade = std::stoi(conteudoLido);
            int index = 0;

            while (quantidade > index)
            {

                leitor->getConteudoDaLinha(conteudoLido);
                escalonador->adicionarURLs(conteudoLido);
                index++;
            }
        }
        else if (conteudoLido.compare("ESCALONA_TUDO") == 0)
        {
            escalonador->escalanoarTodasAsURLs();
        }
        else if (conteudoLido.compare("ESCALONA") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            int quantidade = std::stoi(conteudoLido);
            escalonador->escalonarURLs(quantidade);
        }
        else if (conteudoLido.compare("ESCALONA_HOST") == 0)
        {   
            std::string host;
            leitor->getConteudoDaLinha(host);
            leitor->getConteudoDaLinha(conteudoLido);
            int quantidade = std::stoi(conteudoLido);
            escalonador->escalonarURLsDoHost(host,quantidade);
        }
        else if (conteudoLido.compare("VER_HOST") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            escalonador->visualizarURLsDoHost(conteudoLido);
        }
        else if (conteudoLido.compare("LISTA_HOSTS") == 0)
        {
            escalonador->visualizarHosts();
        }
        else if (conteudoLido.compare("LIMPA_HOST") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            escalonador->limparHost(conteudoLido);
        }
        else if (conteudoLido.compare("LIMPA_TUDO") == 0)
        {
            escalonador->limparTudo();
        }
        else
        {
            std::cout<< conteudoLido << std::endl;
            break;
        }
    }

    return 0;
}