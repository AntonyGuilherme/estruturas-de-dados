#include <iostream>
#include "heap.hpp"
#include "aplicacaoException.hpp"
#include "leitorDeArquivo.hpp"
#include "escritorDeArquivos.hpp"
#include "fita.hpp"
#include "lista.hpp"

//GERA_RODADA(n):
//1) entidades = le_entidades(NUM_ENTIDADES)
//2) ordena(entidades)
//3) escreve(entidades, “rodada-”+n+”.txt”)

bool lerURL(LeitorDeArquivo *leitor, std::string &endereco, int &numeroDeAcessos)
{

    return leitor->getConteudoDaLinha(endereco) && leitor->getConteudoDaLinha(numeroDeAcessos);
}

std::string gerarNomeDoArquivoDaRodada(int numeroDaRodada)
{
    return "rodada-" + std::to_string(numeroDaRodada) + ".txt";
}

void escreverArquivoDaRodada(
    int numeroDaRodada,
    Lista *lista,
    EscritorDeArquivos *escritor,
    LeitorDeArquivo *leitor)
{
    // criando o nome do arquivo da rodada
    std::string nomeDoArquivoDaRodada = gerarNomeDoArquivoDaRodada(numeroDaRodada);

    // abrindo / criando o arquivo para ser escrito
    escritor->prepararArquivo(nomeDoArquivoDaRodada);

    // url lida do heap
    URL *url;

    // enquanto houver urls no heap faça
    while (lista->pop(url))
    {
        // escrevendo a url no arquivo
        escritor->escreverLinha(url->toString());

        delete url;
    }

    // fechando o arquivo para leituras futuras
    escritor->fechar();
}

void ordenar(Ordenador *ordenador, Lista *lista)
{
    lista->ordenar(ordenador);
}

bool lerEntidades(int numeroDeURLASeremLidas, Lista *lista, LeitorDeArquivo *leitorDeArquivo)
{
    // aramazena o endereco da url : www.ufmg.br
    std::string enderecoDaURL;

    // aramazena o número de acessos do site em questao
    int numeroDeAcessos;

    // armazerna o número de URLs lidas até o momento
    int numeroDeURLsLidas = 0;

    while (lerURL(leitorDeArquivo, enderecoDaURL, numeroDeAcessos))
    {
        // incrementando número de URLs lidas até o momento
        numeroDeURLsLidas += 1;

        // inserindo a nova URL no Heap
        lista->inserir(new URL(enderecoDaURL, numeroDeAcessos));

        // se o número máximo de URL's lidas chegar ao limite estipulado
        // o loop é parado
        if (numeroDeURLsLidas >= numeroDeURLASeremLidas)
            return true;
    }

    // caso não seja feito nenhuma leitura de url é retornado false
    // caso contrário é retornado true
    return numeroDeURLsLidas > 0;
}

bool GerarRodada(
    int numeroDaRodada,
    int numeroDeItensPorRodada,
    Lista *lista,
    EscritorDeArquivos *escritor,
    LeitorDeArquivo *leitorDeArquivo,
    Ordenador *ordenador)
{
    // se houver entidades a serem lidas faça :
    if (lerEntidades(numeroDeItensPorRodada, lista, leitorDeArquivo))
    {
        // ordenando o heap
        ordenar(ordenador, lista);

        // escrevendo o arquivo da rodada com as urls lidas e ordenadas
        escreverArquivoDaRodada(numeroDaRodada, lista, escritor, leitorDeArquivo);
        return true;
    }

    return false;
}

// o arquivo de entrada deve ser lido enquanto as entidades couberem na memória principal.
int GerarRodadas(
    int numeroDeItensPorRodada,
    Lista *lista,
    LeitorDeArquivo *leitor,
    EscritorDeArquivos *escritor)
{
    Ordenador ordenador;

    int rodada = 0;
    // enquanto for necessário gerar rodadas faça :
    while (GerarRodada(rodada, numeroDeItensPorRodada, lista, escritor, leitor, &ordenador))
    {
        // incrementando número de rodadas geradas
        rodada++;
    }

    return rodada;
}

void gerarFitas(int numeroDeRodadasGeradas, Fita **fitas)
{

    for (int numeroDaRodada = 0; numeroDaRodada < numeroDeRodadasGeradas; numeroDaRodada++)
    {
        fitas[numeroDaRodada] = new Fita(gerarNomeDoArquivoDaRodada(numeroDaRodada), numeroDaRodada);
    }
}

void Intercalar(int numeroDeRodadasGeradas, EscritorDeArquivos *escritor, std::string& arquivo)
{
    escritor->prepararArquivo(arquivo);
    Heap heap(numeroDeRodadasGeradas);
    Fita **fitas = new Fita *[numeroDeRodadasGeradas];

    gerarFitas(numeroDeRodadasGeradas, fitas);

    URL *url;

    for (int rodada = 0; rodada < numeroDeRodadasGeradas; rodada++)
    {

        if (fitas[rodada]->read(url))
            heap.inserir(url);
    }

    while (heap.pop(url))
    {

        escritor->escreverLinha(url->toString());
        delete url;    

        if (fitas[url->getFitaDeOrigem()]->read(url))
            heap.inserir(url);

    }

    escritor->fechar();

    delete fitas;
}

// <arquivo-de-entrada> <arquivo-de-saida> <número-de-entidades>
int main(int numeroDeArgumentos, char ** argumentos)
{
    try
    {
        
        std::string arquivoDeEntrada(argumentos[1]), arquivoDeSaida(argumentos[2]);
        
        // instanciando o heap para a leitura das URLs
        int numeroDeItensPorRodada = std::stoi(argumentos[3]);

        Lista lista(numeroDeItensPorRodada);

        // criando o leitor de arquivo para ler o arquivo passado pelo usuário
        LeitorDeArquivo *leitor = new LeitorDeArquivo(arquivoDeEntrada);

        // criando o escritor para escrever os arquivos gerados pelas rodadas
        EscritorDeArquivos *escritor = new EscritorDeArquivos();

        // gerando as rodadas e recuperando o número de rodadas geradas
        int numeroDeRodadasGeradas = GerarRodadas(numeroDeItensPorRodada, &lista, leitor, escritor);

        Intercalar(numeroDeRodadasGeradas, escritor, arquivoDeSaida);

        delete leitor, escritor;
    }
    catch (AplicacaoException *ex)
    {
        std::cout << std::endl;
        std::cout << "ERRO NA APLICAÇÃO " << std::endl;
        std::cout << ex->getCodigo() << std::endl;
        std::cout << ex->getMensagem() << std::endl;
        std::cout << "INFORMAÇÕES ADICIONAIS DO ERRO" << std::endl;
        std::cout << ex->getInformacoes() << std::endl;
    }

    return 0;
}