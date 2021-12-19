#include "escalonador.hpp"

Escalonador::Escalonador(std::string& nomeDoArquivo)
{
    this->hosts = new Fila<Host>();
    this->escritorDeArquivos = new EscritorDeArquivos(nomeDoArquivo);
}

void Escalonador::adicionarURLs(std::string url)
{
    // O(n^2)
    // a complexidade é resultado da soma de cada execução
    // então seria algo como 1 + 2 + 3 ... n
    // assim temos f(n) = n*(n+1)/2, O(n^2)

    //verificando se a url tem como o protocolo o http
    if (std::string::npos == url.find("http"))
    {
        return;
    }

    SplitString splitString;

    //retirando o nome do host da url
    std::string nomeHost = splitString.getPedacoDaStringQuebrada(&url, '/', 1);
    bool isEncontrado = false;

    Item<Host> *auxiliar = this->hosts->getPrimeiroItem();
    Host *hostArmazenado;

    //iterando pelo hosts
    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();

        // procurando pelo host
        if (hostArmazenado->getNome()->compare(nomeHost) == 0)
        {   
            // O(n^2)
            hostArmazenado->adicionarURL(url); 
            isEncontrado = true;
            break;
        }

        auxiliar = auxiliar->getProximoItem();
    }

    // se o host não for encontrado ele será inserido na lista junto com a sua URL
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

    // pesquisando o Host e escrevendo as URL's no arquivo
    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();

        if (hostArmazenado->getNome()->compare(nomeHost) == 0)
        {
            // escrevendo as URL's do host no arquivo
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

    // acessando e imprimindo o endereco de todos os os Hosts
    while (auxiliar != nullptr)
    {
        hostArmazenado = auxiliar->getValorDoObjetoArmazenado();
        this->escritorDeArquivos->escreverLinha(*hostArmazenado->getNome());
        auxiliar = auxiliar->getProximoItem();
    }
}

void Escalonador::escalanoarTodasAsURLs()
{
    // escalonando os Hosts

    //pegando o primeiro o host para realizar a iteração
    Item<Host> *itemHost = this->hosts->getPrimeiroItem();
    Host *host;

    // O(n)
    // n sendo o equivalente ao número de URL's adicionadas
    // isso ocorreo porque o número de hosts depende do número de URL's
    // e o somatório de suas URL's são as URL's adicionadas

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


    // encontrando e escalonando a URL do Host
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

    // encontrando o host e limpando as URL's do host
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