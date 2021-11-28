#ifndef LEITOR_DE_ARQUIVO_H
#define LEITOR_DE_ARQUIVO_H

#include <string>
#include <fstream>

class LeitorDeArquivo
{

private:
    std::ifstream arquivo;
    std::string nomeDoArquivo;
    void abrirArquivo();


public:
    LeitorDeArquivo(std::string nomeDoArquivo);
    bool getConteudoDaLinha(std::string& conteudo);

};


#endif