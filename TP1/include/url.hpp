#ifndef URL_H
#define URL_H

#include <string>
#include "splitString.hpp"

class URL
{
private:
    std::string url;
    int nivelDeProfundidade;
    void calcularNivelDeProfundidade();
    std::string processarURL(std::string url);
    SplitString split;

public:
    URL(std::string url);
    int getProfundidade();
    std::string getUrl();
};

#endif