#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "host.hpp"
#include "splitString.hpp"
#include "url.hpp"
#include "leitorDeArquivo.hpp"
#include "escalonador.hpp"
#include "arraylist.hpp"
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
    ArrayList<URL> vetorTeste(1);
    vetorTeste.inserir(0,new URL("http://globoesporte.com/spfc/index.html"));
    //vetorTeste.inserir(1,new URL("http://globoesporte.com/spfc/index.html"));
    vetorTeste.remover(0,1);
    if( vetorTeste[0] == nullptr){
        std::cout << "Remocao"  << std::endl;
    }

    for(int i =0; i < vetorTeste.size() ; i++){
        std::cout << vetorTeste[i]->getUrl() << std::endl;
    }


    /*
    std::cout << url.getProfundidade() << " " << url.getUrl() << std::endl;
    
    SplitString splitString;
    LeitorDeArquivo leitorDoArquivo("teste.txt");
    std::string conteudo;
    std::vector<Host> hosts;

    Escalonador escalonador;

    while(leitorDoArquivo.getConteudoDaLinha(conteudo)){
        
        escalonador.adicionarURLs(conteudo);
    }

    escalonador.escalanoarTodasAsURLs();

    escalonador.escalonarURLsDoHost("www.globoesporte.com");
    escalonador.visualizarHosts();
    */
    

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