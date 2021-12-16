#include "escalonador.hpp"

Escalonador::Escalonador(std::string& nomeDoArquivo)
{
    this->hosts = new Fila<Host>();
    this->escritorDeArquivos = new EscritorDeArquivos(nomeDoArquivo);
}

void Escalonador::adicionarURLs(std::string url)
{

    if (std::string::npos == url.find("http"))
    {
        return;
    }

    SplitString splitString;

    std::string nomeHost = splitString.getPedacoDaStringQuebrada(&url, '/', 1);
    bool isEncontrado = false;

    Item<Host> *auxiliar = this->hosts->getPrimeiroItem();
    Host *hostArmazenado;

    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();

        if (hostArmazenado->getNome()->compare(nomeHost) == 0)
        {
            hostArmazenado->adicionarURL(url);
            isEncontrado = true;
            break;
        }

        auxiliar = auxiliar->getProximoItem();
    }

    if (!isEncontrado)
    {
        Host *hostEncontrado = new Host(nomeHost);
        hostEncontrado->adicionarURL(url);
        this->hosts->inserir(hostEncontrado);
    }
}

void Escalonador::visualizarURLsDoHost(std::string nomeHost)
{

    Item<Host> *auxiliar = this->hosts->getPrimeiroItem();
    Host *hostArmazenado;

    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();

        if (hostArmazenado->getNome()->compare(nomeHost) == 0)
        {

            hostArmazenado->imprimirURLs(this->escritorDeArquivos);

            break;
        }

        auxiliar = auxiliar->getProximoItem();
    }
}

void Escalonador::visualizarHosts()
{

    Item<Host> *auxiliar = this->hosts->getPrimeiroItem();
    Host *hostArmazenado;

    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();
        this->escritorDeArquivos->escreverLinha(*hostArmazenado->getNome());
        auxiliar = auxiliar->getProximoItem();
    }
}

void Escalonador::escalanoarTodasAsURLs()
{
    Item<Host> *itemHost = this->hosts->getPrimeiroItem();
    Host *host;

    while (itemHost != nullptr)
    {
        host = itemHost->getValorDoObjetoArmazenado();
        host->escalonarURLs(this->escritorDeArquivos);
        itemHost = itemHost->getProximoItem();
    }
}

void Escalonador::escalonarURLsDoHost(std::string nomeHost,int quantidade)
{
    Item<Host> *itemHost = this->hosts->getPrimeiroItem();
    Host *host;

    while (itemHost != nullptr)
    {
        host = itemHost->getValorDoObjetoArmazenado();
        if (nomeHost.compare(*host->getNome()) == 0)
        {
            host->escalonarURLs(quantidade,this->escritorDeArquivos);
            break;
        }

        itemHost = itemHost->getProximoItem();
    }
}

void Escalonador::escalonarURLs(int quantidade)
{

    Item<Host> *auxiliar = this->hosts->getPrimeiroItem();
    Host *host;
    int quantidadeEscalonada = 0;
    int quantidadeParaProcessar = quantidade;

    while (auxiliar != nullptr && quantidade > quantidadeEscalonada)
    {

        host = auxiliar->getValorDoObjetoArmazenado();
        quantidadeParaProcessar -= host->escalonarURLs(quantidadeParaProcessar,this->escritorDeArquivos);

        auxiliar = auxiliar->getProximoItem();
    }
}

void Escalonador::limparHost(std::string nomeHost)
{

    Item<Host> *itemHost = this->hosts->getPrimeiroItem();
    Host *host;

    while (itemHost != nullptr)
    {
        host = itemHost->getValorDoObjetoArmazenado();
        if (nomeHost.compare(*host->getNome()) == 0)
        {
            host->limparURLs();
            break;
        }

        itemHost = itemHost->getProximoItem();
    }
}

void Escalonador::limparTudo()
{
    delete this->hosts;
    this->hosts = new Fila<Host>();
}

Escalonador::~Escalonador()
{   
    this->escritorDeArquivos->fechar();
    delete this->escritorDeArquivos;
    delete this->hosts;
}