#ifndef FITA_H
#define FITA_H

#include <string>
#include "leitorDeArquivo.hpp"
#include "url.hpp"
class Fita
{

private:
    LeitorDeArquivo *leitor;
    bool lerURL(std::string &endereco, int &numeroDeAcessos);
    int numeroDeFita;

public:
    Fita(std::string nomeDoArquivo, int numeroDaFita);
    bool read(URL *&url);
};

#endif