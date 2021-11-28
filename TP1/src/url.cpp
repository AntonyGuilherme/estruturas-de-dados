#include "url.hpp"


URL::URL(std::string url){

    this->url = url;

    this->calcularNivelDeProfundidade();
}

void URL::calcularNivelDeProfundidade(){

    SplitString split;
    std::vector<std::string>* pedacos = split.quebrarStringBaseadoEm(&this->url,'/');
    
    this->nivelDeProfundidade = -2;

    for(auto& _ : *pedacos){
        this->nivelDeProfundidade++;
    }

    delete pedacos;
}

int URL::getProfundidade(){

    return this->nivelDeProfundidade;
}

std::string URL::getUrl(){

    return this->url;
}