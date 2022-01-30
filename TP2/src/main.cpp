#include <iostream>
#include "heap.hpp"
#include "aplicacaoException.hpp"
#include "leitorDeArquivo.hpp"
#include "escritorDeArquivos.hpp"
#include "fita.hpp"
#include "lista.hpp"
#include "argumentoException.hpp"

// ler a url a partir de um arquivo de entrada ou uma rodada
// considerando que ela esteja no formato <url> <número de acessos>
bool lerURL(LeitorDeArquivo *leitor, std::string &endereco, int &numeroDeAcessos)
{
    return leitor->getConteudoDaLinha(endereco) && leitor->getConteudoDaLinha(numeroDeAcessos);
}

// gerando o nome do arquivo de acordo com o numero da rodada
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

bool lerEntidades(int numeroDeURLASeremLidas, Lista *lista, LeitorDeArquivo *leitorDeArquivo)
{
    // aramazena o endereco da url : www.ufmg.br
    std::string enderecoDaURL;

    // aramazena o número de acessos do site em questao
    int numeroDeAcessos;

    // armazerna o número de URLs lidas até o momento
    int numeroDeURLsLidas = 0;

    // realiza n leitruas, sendo n o número limitado pelo usuário
    // realiza n inserções e n comparações
    // assim temos O(n = numeroDeURLASeremLidas)
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

// retornada true caso ainda haja leituras a serem feitas
bool GerarRodada(
    int numeroDaRodada,
    int numeroDeItensPorRodada,
    Lista *lista,
    EscritorDeArquivos *escritor,
    LeitorDeArquivo *leitorDeArquivo,
    Ordenador *ordenador)
{
    // se houver entidades a serem lidas faça :
    // O(n)
    if (lerEntidades(numeroDeItensPorRodada, lista, leitorDeArquivo))
    {
        // ordenando o heap
        // O(nlog(n))
        lista->ordenar(ordenador);

        // escrevendo o arquivo da rodada com as urls lidas e ordenadas
        // O(n)
        escreverArquivoDaRodada(numeroDaRodada, lista, escritor, leitorDeArquivo);
        return true;
    }

    return false;
}

// gera as rodadas e seus respectivos arquivos
// posteriormente, retorna o número de fitas geradas
int GerarRodadas(
    int numeroDeItensPorRodada,
    Lista *lista,
    LeitorDeArquivo *leitor,
    EscritorDeArquivos *escritor)
{
    // gerando um ordenador que utilize o QuickSort
    Ordenador ordenador;

    int rodada = 0;

    // enquanto for necessário gerar rodadas faça :
    // Cada rodada - O(n.log(n))
    // Mas lembremos que isso será executado : M (número de urls) / N (Limite estipulado pelo usuário)
    // Assim temos O(nlog(n) * m/n) = O(mlog(n))
    while (GerarRodada(rodada, numeroDeItensPorRodada, lista, escritor, leitor, &ordenador))
    {
        // incrementando número de rodadas geradas
        rodada++;
    }

    return rodada;
}

// gerando o acesso as fitas (rodada-n.txt) salvas
void gerarFitas(int numeroDeRodadasGeradas, Fita **fitas)
{
    for (int numeroDaRodada = 0; numeroDaRodada < numeroDeRodadasGeradas; numeroDaRodada++)
    {
        // gerando as fitas e marcando o seu respectivo número
        // para que possa ser usado, posteriormente, na leitura das respectivas urls da fita
        fitas[numeroDaRodada] = new Fita(gerarNomeDoArquivoDaRodada(numeroDaRodada), numeroDaRodada);
    }
}

// liberando a memória utilizada no armazenamento das fitas
void removerFitasGeradas(int numeroDeRodadasGeradas, Fita **fitas)
{
    for (int numeroDaRodada = 0; numeroDaRodada < numeroDeRodadasGeradas; numeroDaRodada++)
    {
        // removendo a fita da memória
        delete fitas[numeroDaRodada];
    }
}

// O(mlog(n))
void Intercalar(int numeroDeRodadasGeradas, EscritorDeArquivos *escritor, std::string &arquivo)
{
    // abrindo o arquivo no qual a fita deverá ser escrita
    escritor->prepararArquivo(arquivo);

    // criando o heap para a intercalação das urls
    Heap heap(numeroDeRodadasGeradas);

    // criando o acesso para as fitas
    Fita **fitas = new Fita *[numeroDeRodadasGeradas];

    // gerando as fitas para o acesso as arquivos gerados nas rodadas
    // O(m/n)
    gerarFitas(numeroDeRodadasGeradas, fitas);

    // ponteiro de url que será usado na leitura
    // para receber o a url lida de um arquivo de rodada
    URL *url;

    // pegando a primeira url de cada arquivo
    // O(nlog(n))
    for (int rodada = 0; rodada < numeroDeRodadasGeradas; rodada++)
    {
        // caso não seja possível ler a url é retornado "false"
        // e assim ela não é inserida no heap
        // O(1)
        if (fitas[rodada]->read(url))
            heap.inserir(url); // inserindo a url no heap / O(log(rodada))
    }

    int fitaDeOrigemDaURL = 0;

    // retirando a url do heap até que chegue ao fim
    // O(log(m^2/n)*m^2) 
    while (heap.pop(url)) 
    {

        // escrevendo a url no arquivo de saída
        escritor->escreverLinha(url->toString());

        // atribuindo o número da fita de origem da url
        // para a próxima leitura
        fitaDeOrigemDaURL = url->getFitaDeOrigem();

        // removendo a url da memória
        delete url;

        // lendo mais urls da fita de origem da url lida anteriormente
        if (fitas[fitaDeOrigemDaURL]->read(url))
            heap.inserir(url); // inserindo a url no heap O(log(m/n))
    }

    // fechando o arquivo de saída
    escritor->fechar();

    // liberando a memória utlizada para cada fita
    // O(n)
    removerFitasGeradas(numeroDeRodadasGeradas, fitas);

    // removendo as fitas da memória
    delete fitas;
}

void lerArgumentos(
    int numeroDeArgumentos, char **argumentos,
    std::string &arquivoDeEntrada,
    std::string &arquivoDeSaida,
    int &numeroDeItensPorRodada)
{
    if (numeroDeArgumentos < 4)
    {
        throw new ArgumentoException(
            "Eram esperados 3 argumentos, <arquivo-de-entrada> <arquivo-de-saida> <número-de-entidades>",
            std::to_string(numeroDeArgumentos));
    }

    try
    {

        // recuperando o nome do arquivo de saída e origem
        arquivoDeEntrada = std::string(argumentos[1]);
        arquivoDeSaida = std::string(argumentos[2]);

        // recuperando a quantidade de itens que devem ser lidos por rodada
        numeroDeItensPorRodada = std::stoi(argumentos[3]);
    }
    catch (std::exception erro)
    {
        throw new ArgumentoException("Erro no formato dos agumentos.");
    }
}

// <arquivo-de-entrada> <arquivo-de-saida> <número-de-entidades>
int main(int numeroDeArgumentos, char **argumentos)
{
    try
    {

        // recuperando os argumentos
        std::string arquivoDeEntrada, arquivoDeSaida;
        int numeroDeItensPorRodada;
        lerArgumentos(numeroDeArgumentos,argumentos,
        arquivoDeEntrada,arquivoDeSaida,numeroDeItensPorRodada);

        // instanciando a lista para a leitura das URLs
        Lista lista(numeroDeItensPorRodada);

        // criando o leitor de arquivo para ler o arquivo passado pelo usuário
        LeitorDeArquivo *leitor = new LeitorDeArquivo(arquivoDeEntrada);

        // criando o escritor para escrever os arquivos gerados pelas rodadas
        EscritorDeArquivos *escritor = new EscritorDeArquivos();

        // gerando as rodadas e recuperando o número de rodadas geradas
        // O(mlog(n))
        int numeroDeRodadasGeradas = GerarRodadas(numeroDeItensPorRodada, &lista, leitor, escritor);

        //intercalando e por consequência escrevendo no arquivo de saída
        // O(mlog(n))
        Intercalar(numeroDeRodadasGeradas, escritor, arquivoDeSaida);

        // liberando a memória do escritor de arquivos e do leitor
        // caso hajam arquivos abertos, eles são fechados automaticamente
        delete leitor, escritor;
    }
    catch (AplicacaoException *ex) // captura erros gerados pela aplicação
    {
        // gera a visualização do erro considerando :
        // o código, ou seja, pelo que o erro foi gerado
        // a mesagem que descreve o erro que foi gerado
        // e as informações, ou seja, o valor que gerou o erro, caso exista
        std::cout << std::endl;
        std::cout << "ERRO NA APLICAÇÃO " << std::endl;
        std::cout << ex->getCodigo() << std::endl;
        std::cout << ex->getMensagem() << std::endl;
        std::cout << "INFORMAÇÕES ADICIONAIS DO ERRO" << std::endl;
        std::cout << ex->getInformacoes() << std::endl;
    }

    return 0;
}