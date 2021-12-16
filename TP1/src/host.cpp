#include "host.hpp"

Host::Host(std::string nome)
{

    this->nome = nome;
    this->urls = new Lista<URL>();
}

std::string *Host::getNome()
{

    return &this->nome;
}

void Host::adicionarURL(std::string url)
{

    URL *novaUrl = new URL(url);
    Item<URL> * auxiliar = this->urls->getPrimeiroItem();
    URL * urlAdicionada;
    int index = 0;

    while (auxiliar != nullptr)
    {
        urlAdicionada = auxiliar->getValorDoObjetoArmazenado();

        if (urlAdicionada->getProfundidade() > novaUrl->getProfundidade())
        {   
            this->urls->inserir(index, novaUrl);
            return;
        }

        auxiliar = auxiliar->getProximoItem();

        index++;
    }

    this->urls->inserir(novaUrl);

}

void Host::imprimirURLs(EscritorDeArquivos * escritor)
{
    Item<URL> * auxiliar = this->urls->getPrimeiroItem();
    URL * url;
    std::string valorURL;
    while (auxiliar != nullptr)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        valorURL = url->getUrl();
        escritor->escreverLinha(valorURL);
        auxiliar = auxiliar->getProximoItem();
    }
}

int Host::escalonarURLs(int quantidadeMaxima, EscritorDeArquivos * escritor){

    Item<URL> * auxiliar = this->urls->getPrimeiroItem();
    URL * url;
    int index = 0;
    std::string valorURL;

    while (auxiliar != nullptr && quantidadeMaxima > index)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        valorURL = url->getUrl();
        escritor->escreverLinha(valorURL);
        auxiliar = auxiliar->getProximoItem();
        index++;
    }


    this->urls->remover(0,index);

    return index;
}

int Host::escalonarURLs(EscritorDeArquivos * escritor){

    return this->escalonarURLs(this->urls->size(),escritor);
}

void Host::limparURLs(){

    delete this->urls;
    this->urls = new Lista<URL>();
}

Host::~Host(){

    delete this->urls;
}
