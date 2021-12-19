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
    // O(n^2)

    // criando a URL
    URL *novaUrl = new URL(url);
    // acessando o primeiro item para iteração
    Item<URL> *auxiliar = this->urls->getPrimeiroItem();
    URL *urlAdicionada;
    int index = 0;

    while (auxiliar != nullptr)
    {   
        // pegando a URL de fato
        urlAdicionada = auxiliar->getValorDoObjetoArmazenado();
        
        // verificando se a URL já foi informado
        if (urlAdicionada->getUrl().compare(novaUrl->getUrl()) == 0)
        {
            return;
        }

        // comparando a profundidade e inserindo a URL na posicao correta
        if (urlAdicionada->getProfundidade() > novaUrl->getProfundidade())
        {

            this->urls->inserir(index, novaUrl); // O(n)
            return;
        }

        auxiliar = auxiliar->getProximoItem();

        index++;
    }

    this->urls->inserir(novaUrl);
}

void Host::imprimirURLs(EscritorDeArquivos *escritor)
{
    Item<URL> *auxiliar = this->urls->getPrimeiroItem();
    URL *url;
    std::string valorURL;

    // escrevendo as URL's no arquivo
    while (auxiliar != nullptr)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        valorURL = url->getUrl();
        escritor->escreverLinha(valorURL);
        auxiliar = auxiliar->getProximoItem();
    }
}

int Host::escalonarURLs(int quantidadeMaxima, EscritorDeArquivos *escritor)
{
    // O(n)
    Item<URL> *auxiliar = this->urls->getPrimeiroItem();
    URL *url;
    int index = 0;
    std::string valorURL;
    
    //escalonando e escrvendo o resultado direto no arquivo
    while (auxiliar != nullptr && quantidadeMaxima > index)
    {
        url = auxiliar->getValorDoObjetoArmazenado();
        valorURL = url->getUrl();
        escritor->escreverLinha(valorURL);
        auxiliar = auxiliar->getProximoItem();
        index++;
    }

    this->urls->remover(0, index);

    return index;
}

int Host::escalonarURLs(EscritorDeArquivos *escritor)
{

    return this->escalonarURLs(this->urls->size(), escritor);
}

void Host::limparURLs()
{

    delete this->urls;
    this->urls = new Lista<URL>();
}

Host::~Host()
{

    delete this->urls;
}
