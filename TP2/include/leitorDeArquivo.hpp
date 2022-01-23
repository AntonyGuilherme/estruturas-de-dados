#ifndef LEITOR_DE_ARQUIVO_H
#define LEITOR_DE_ARQUIVO_H

#include <string>
#include <fstream>

class LeitorDeArquivo
{

private:
    std::ifstream * arquivo;
    std::string nomeDoArquivo;
    void abrirArquivo();

public:
    void abrirArquivo(std::string novoNomeDoArquivo);
    LeitorDeArquivo(std::string nomeDoArquivo);
    LeitorDeArquivo();
    bool getConteudoDaLinha(std::string &conteudo);
    bool getConteudoDaLinha(int &conteudo);
    void fechar();
    ~LeitorDeArquivo();
};

#endif