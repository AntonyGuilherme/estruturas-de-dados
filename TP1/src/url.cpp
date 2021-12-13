#include "url.hpp"
#include <iostream>
//https://www.delftstack.com/pt/howto/cpp/split-string-in-cpp/

URL::URL(std::string url){

    this->url = split.removerPedacoDaString(url,"www.");

    this->calcularNivelDeProfundidade();
}

void URL::calcularNivelDeProfundidade(){

    std::vector<std::string> pedacos = split.quebrarStringBaseadoEm(&this->url,'/');
    
    this->nivelDeProfundidade = -2;

    for(auto& _ : pedacos){
        this->nivelDeProfundidade++;
    }

}

int URL::getProfundidade(){

    return this->nivelDeProfundidade;
}

std::string URL::getUrl(){

    return this->url;
}
