#include <iostream>
#include "leitorDeArquivo.hpp"
#include "escalonador.hpp"
#include "lista.hpp"
#include <stdexcept>
#include "item.hpp"

/*
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
*/

int main(int numeroDeArgumentos, char **argumentos)
{
    Lista<std::string> extensoesNaoConsideradas;
    extensoesNaoConsideradas.inserir(new std::string(".pdf"));
    extensoesNaoConsideradas.inserir(new std::string(".doc"));
    extensoesNaoConsideradas.inserir(new std::string(".avi"));
    extensoesNaoConsideradas.inserir(new std::string(".mp3"));
    extensoesNaoConsideradas.inserir(new std::string(".gif"));
    extensoesNaoConsideradas.inserir(new std::string(".jpg"));

    if (numeroDeArgumentos < 1)
    {
        throw std::invalid_argument("O nome do arquivo nao foi encontrado");
    }

    std::string nomeArquivo(argumentos[1]);

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
            leitor->getConteudoDaLinha(conteudoLido);
            int quantidade = std::stoi(conteudoLido);
            int index = 0;

            while (quantidade > index)
            {

                leitor->getConteudoDaLinha(conteudoLido);
                conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");

                bool pularURL = false;
                for (int i = 0; i < extensoesNaoConsideradas.size(); i++)
                {
                    if (conteudoLido.find(*extensoesNaoConsideradas.get(i)) != std::string::npos)
                    {
                        // pulando a url caso ela de acesso a um arquivo inadequado
                        pularURL = true;
                    }
                }

                if(!pularURL)
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
            host = split.removerPedacoDaString(host, "www.");
            escalonador->escalonarURLsDoHost(host, quantidade);
        }
        else if (conteudoLido.compare("VER_HOST") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");
            escalonador->visualizarURLsDoHost(conteudoLido);
        }
        else if (conteudoLido.compare("LISTA_HOSTS") == 0)
        {
            escalonador->visualizarHosts();
        }
        else if (conteudoLido.compare("LIMPA_HOST") == 0)
        {
            leitor->getConteudoDaLinha(conteudoLido);
            conteudoLido = split.removerPedacoDaString(conteudoLido, "www.");
            escalonador->limparHost(conteudoLido);
        }
        else if (conteudoLido.compare("LIMPA_TUDO") == 0)
        {
            escalonador->limparTudo();
        }
        else
        {
            std::cout << conteudoLido << std::endl;
            break;
        }
    }

    return 0;
}