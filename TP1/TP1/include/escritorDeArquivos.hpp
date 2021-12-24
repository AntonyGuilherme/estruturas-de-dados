#ifndef ESCRITOR_DE_ARQUIVOS_H
#define ESCRITOR_DE_ARQUIVOS_H

#include <iostream>
#include <fstream>
#include <stdexcept>

class EscritorDeArquivos
{

public:
    EscritorDeArquivos(std::string& nomeArquivo);
    void escreverLinha(std::string& conteudo);
    void fechar();

private:
    std::ofstream arquivo;


};

#endif