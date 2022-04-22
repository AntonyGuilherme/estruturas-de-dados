#ifndef ESCRITOR_DE_ARQUIVOS_H
#define ESCRITOR_DE_ARQUIVOS_H

#include <iostream>
#include <fstream>
#include <stdexcept>

class EscritorDeArquivos
{

private:
    std::ofstream * arquivo;

public:
    EscritorDeArquivos();
    EscritorDeArquivos(std::string nomeArquivo);
    void prepararArquivo(std::string nomeArquivo);
    void escreverLinha(std::string conteudo);
    void escrever(std::string conteudo);
    void fechar();
    ~EscritorDeArquivos();

};

#endif