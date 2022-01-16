#include <iostream>
#include "heap.hpp"
#include "HeapException.hpp"
#include "leitorDeArquivo.hpp"
#include "escritorDeArquivos.hpp"
#include "fita.hpp"

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
    Heap *heap,
    EscritorDeArquivos *escritor,
    LeitorDeArquivo *leitor,
    bool isUltimaRodada)
{
    // criando o nome do arquivo da rodada
    std::string nomeDoArquivoDaRodada = gerarNomeDoArquivoDaRodada(numeroDaRodada);

    // abrindo / criando o arquivo para ser escrito
    escritor->prepararArquivo(nomeDoArquivoDaRodada);

    // url lida do heap
    URL *url, *urlArquivo;

    std::string endereco;
    int numeroDeVisualizacoes;

    // enquanto houver urls no heap faça
    while (heap->pop(url))
    {
        if (isUltimaRodada && lerURL(leitor, endereco, numeroDeVisualizacoes))
        {

            urlArquivo = new URL(endereco, numeroDeVisualizacoes);

            if (url->getNumeroDeVisualizacoes() > urlArquivo->getNumeroDeVisualizacoes())
            {
                heap->inserir(urlArquivo);
            }
            else
            {
                heap->inserir(url);
                url = urlArquivo;
            }
        }

        // escrevendo a url no arquivo
        escritor->escreverLinha(url->toString());
    }

    // fechando o arquivo para leituras futuras
    escritor->fechar();
}

void ordenar(Heap *heap, int tamanho)
{
}

bool lerEntidades(int numeroDeURLASeremLidas, Heap *heap, LeitorDeArquivo *leitorDeArquivo)
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
        numeroDeURLsLidas++;

        // inserindo a nova URL no Heap
        heap->inserir(new URL(enderecoDaURL, numeroDeAcessos));

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
    Heap *heap,
    EscritorDeArquivos *escritor,
    LeitorDeArquivo *leitorDeArquivo,
    bool isUltimaFita)
{
    // se houver entidades a serem lidas faça :
    if (lerEntidades(numeroDeItensPorRodada, heap, leitorDeArquivo))
    {
        // ordenando o heap
        ordenar(heap, numeroDeItensPorRodada);

        // escrevendo o arquivo da rodada com as urls lidas e ordenadas
        escreverArquivoDaRodada(numeroDaRodada, heap, escritor, leitorDeArquivo, isUltimaFita);
        return true;
    }

    return false;
}

// o arquivo de entrada deve ser lido enquanto as entidades couberem na memória principal.
int GerarRodadas(
    int numeroDeItensPorRodada,
    Heap *heap,
    LeitorDeArquivo *leitor,
    EscritorDeArquivos *escritor,
    int numeroDeFitas)
{

    int rodada = 0;
    bool isUltimaFita = numeroDeFitas <= (rodada + 1);
    // enquanto for necessário gerar rodadas faça :
    while (GerarRodada(rodada, numeroDeItensPorRodada, heap, escritor, leitor, isUltimaFita))
    {
        // incrementando número de rodadas geradas
        rodada++;

        isUltimaFita = numeroDeFitas <= (rodada + 1);
    }

    return rodada;
}

void Intercalar()
{
}

void gerarFitas(int numeroDeRodadasGeradas, Fita **fitas)
{

    for (int numeroDaRodada = 0; numeroDaRodada < numeroDeRodadasGeradas; numeroDaRodada++)
    {
        fitas[numeroDaRodada] = new Fita(gerarNomeDoArquivoDaRodada(numeroDaRodada), numeroDaRodada);
    }
}

int main()
{
    // numero de fitas disponiveis
    int numeroDeFitas = 1;
    // instanciando o heap para a leitura das URLs
    int numeroDeItensPorRodada = 5;
    Heap *heap = new Heap(numeroDeItensPorRodada);

    // criando o leitor de arquivo para ler o arquivo passado pelo usuário
    LeitorDeArquivo *leitor = new LeitorDeArquivo("teste.txt");

    // criando o escritor para escrever os arquivos gerados pelas rodadas
    EscritorDeArquivos *escritor = new EscritorDeArquivos();

    // gerando as rodadas e recuperando o número de rodadas geradas
    int numeroDeRodadasGeradas = GerarRodadas(numeroDeItensPorRodada, heap, leitor, escritor, numeroDeFitas);
    escritor->prepararArquivo("arquivo-saida.txt");

    Fita **fitas = new Fita *[numeroDeRodadasGeradas];
    gerarFitas(numeroDeRodadasGeradas, fitas);
    URL *url;

    for (int rodada = 0; rodada < numeroDeRodadasGeradas; rodada++)
    {

        if (fitas[rodada]->read(url))
            heap->inserir(url);
    }

    while (heap->pop(url))
    {

        escritor->escreverLinha(url->toString());

        if (fitas[url->getFitaDeOrigem()]->read(url))
            heap->inserir(url);
    }

    std::cout << "Numero de rodadas geradas " << numeroDeRodadasGeradas << std::endl;

    return 0;
}