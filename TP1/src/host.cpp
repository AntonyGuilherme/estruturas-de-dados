#include "host.hpp"
#include <string>
#include <vector>

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

void Host::imprimirURLs()
{
    Item<URL> * auxiliar = this->urls->getPrimeiroItem();
    URL * url;
    while (auxiliar != nullptr)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        std::cout << url->getUrl() << " " << url->getProfundidade() << std::endl;

        auxiliar = auxiliar->getProximoItem();
    }
}

int Host::escalonarURLs(int quantidadeMaxima){

    Item<URL> * auxiliar = this->urls->getPrimeiroItem();
    URL * url;
    int index = 0;

    while (auxiliar != nullptr && quantidadeMaxima > index)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        std::cout << "[ " << url->getUrl() << " ]" << std::endl;
        auxiliar = auxiliar->getProximoItem();
        index++;
    }

    if(auxiliar != nullptr){
       this->urls->inserirPrimeiro(auxiliar);
    }

    this->urls->remover(0,index);

    return index;
}

int Host::escalonarURLs(){

    return this->escalonarURLs(this->urls->size());
}

void Host::limparURLs(){

    delete this->urls;
    this->urls = new Lista<URL>();
}

Host::~Host(){

    delete this->urls;
}
