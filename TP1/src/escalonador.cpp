#include "escalonador.hpp"

void Escalonador::adicionarURLs(std::string url)
{

    if (std::string::npos != url.find("ftp."))
        return;

    SplitString splitString;

    std::string nomeHost = splitString.getPedacoDaStringQuebrada(&url, '/', 1);
    bool isEncontrado = false;

    for (auto &hostArmazenado : this->hosts)
    {

        if (hostArmazenado.getNome().compare(nomeHost) == 0)
        {
            hostArmazenado.adicionarURL(url);
            isEncontrado = true;
            break;
        }
    }

    if (!isEncontrado)
    {
        Host hostEncontrado(nomeHost);
        hostEncontrado.adicionarURL(url);
        hosts.push_back(hostEncontrado);
    }
}

void Escalonador::escalanoarTodasAsURLs()
{

    for (auto &host : this->hosts)
    {

        std::cout << host.getNome() << std::endl;

        for (auto &url : host.getUrlsDisponiveis())
        {

            std::cout << " [ " << url << " ] " << std::endl;
        }
    }
}

void Escalonador::escalonarURLsDoHost(std::string nomeHost)
{

    for (auto &host : this->hosts)
    {

        if (nomeHost.compare(nomeHost) == 0)
        {

            for (auto &url : host.getUrlsDisponiveis())
            {

                std::cout << " [ " << url << " ] " << std::endl;
            }

            break;
        }
    }
}

void Escalonador::visualizarURLsDoHost(std::string nomeHost)
{

    for (auto &host : this->hosts)
    {

        if (host.getNome().compare(nomeHost) == 0)
        {

            for (auto &url : host.getUrlsDisponiveis())
            {

                std::cout << " [ " << url << " ] " << std::endl;
            }

            break;
        }
    }
}

void Escalonador::visualizarHosts()
{

    for (auto &host : this->hosts)
    {

        std::cout << host.getNome() << std::endl;
    }
}
