#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>

class Host
{

private:
    std::vector<std::string> urls;
    std ::string nome;

public:
    Host(std::string nome);
    void adicionarURL(std ::string url);
    std::vector<std::string> getUrlsDisponiveis();
    std::string getNome();
};

#endif