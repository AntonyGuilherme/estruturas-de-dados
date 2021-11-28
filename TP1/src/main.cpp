#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "host.hpp"
#include "splitString.hpp"
#include "url.hpp"
#include "leitorDeArquivo.hpp"

void splitString(std::string *source, std::vector<std::string> *vetor)
{

    std::string conteudo;
    //Construct a stream from the string
    std::stringstream streamData(*source);

    while (std::getline(streamData, conteudo, '/'))
    {
        vetor->push_back(conteudo);
    }
}

void adicionarLinhas(std::ifstream *arquivo, std::vector<std::string> *vetor, int numeroDeURLs)
{
    int linhasAdicionadas = 0;
    std::string urlLida;
    while (linhasAdicionadas < numeroDeURLs)
    {

        *arquivo >> urlLida;
        if (std::string::npos != urlLida.find("http"))
        {
            vetor->push_back(urlLida);
        };
        linhasAdicionadas++;
    }

}

void isHostAdicionado(std::vector<Host>& hosts, std::string url){
    
    SplitString splitString;

    std::string host = splitString.getPedacoDaStringQuebrada(&url,'/',1);
    bool isEncontrado =  false;

    for(auto& hostArmazenado : hosts){

        if(hostArmazenado.getNome().compare(host) == 0){
            hostArmazenado.adicionarURL(url);
            isEncontrado = true;
            break;
        }
        
    }

    if(!isEncontrado){
        Host hostEncontrado(host);
        hostEncontrado.adicionarURL(url);
        hosts.push_back(hostEncontrado);
    }


}


int main()
{
    URL url("http://globoesporte.com/spfc/index.html");

    std::cout << url.getProfundidade() << " " << url.getUrl() << std::endl;
    
    SplitString splitString;
    LeitorDeArquivo leitorDoArquivo("teste.txt");
    std::string conteudo;
    std::vector<Host> hosts;

    while(leitorDoArquivo.getConteudoDaLinha(conteudo)){
        if(std::string::npos == conteudo.find("ftp."))
            isHostAdicionado(hosts,conteudo);
    }

     for(auto& hostArmazenado : hosts){
        std::cout << hostArmazenado.getNome() << std::endl;

        for(auto &url : hostArmazenado.getUrlsDisponiveis()){
            std::cout << "  " << url << std::endl;
        }


     }

    /*
   // std::cout << host.getNome();

    std::string conteudoLido;
    std::string ADICIONAR_URL = "ADD_URLS";
    std::ifstream arquivo;
    std::vector<std::string> listaDeTestes;

    arquivo.open("file.txt");

    while (arquivo.good())
    {

        arquivo >> conteudoLido;

        if (conteudoLido.compare(ADICIONAR_URL) == 0)
        {
            arquivo >> conteudoLido;
            adicionarLinhas(&arquivo, &listaDeTestes, stoi(conteudoLido));
        }

        std::cout << conteudoLido << std::endl;
    }

    std::cout << "URLS ENCONTRADAS" << std::endl
              << std::endl;

    for (auto &line : listaDeTestes)
    {

        std ::cout << line << std::endl;
    }

    std::vector<std::string> teste;
    splitString(&listaDeTestes[0], &teste);

    for (auto &t : teste)
    {
        std ::cout << t << std::endl;
    }

    arquivo.close();
    */
}