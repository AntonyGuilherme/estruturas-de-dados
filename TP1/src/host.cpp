#include "host.hpp"
#include <string>
#include <vector>

Host::Host(std::string nome){

    this->nome = nome;
}

std::string Host::getNome(){
    
    return this->nome;
}

void Host::adicionarURL(std::string url){

    this->urls.push_back(url);
}

std::vector<std::string> Host::getUrlsDisponiveis(){
    
    return this->urls;
}