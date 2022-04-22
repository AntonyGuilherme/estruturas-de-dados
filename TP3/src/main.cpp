#include <iostream>
#include <filesystem>
#include <string>
#include "Hash.hpp"
#include "lista.hpp"
#include "Frequencia.hpp"
#include "leitorDeArquivo.hpp"
#include "HashWD.hpp"
#include "ordenador.hpp"
#include "escritorDeArquivos.hpp"
#include "argumentoException.hpp"

namespace fs = std::filesystem;
using std::filesystem::recursive_directory_iterator;

void removerCaracteresIndesejados(std::string &palavra)
{

    std::string palavraSemCaracteresIndesejados = "";

    bool encontrado;

    for (int i = 0; i < palavra.length(); i++)
    {

        encontrado = false;

        for (char c = 'a'; c <= 'z'; c++)
        {

            if (palavra[i] == c)
            {
                encontrado = true;
                palavraSemCaracteresIndesejados = palavraSemCaracteresIndesejados.append(1, palavra[i]);
                break;
            }
        }

        if (encontrado)
            continue;

        for (char c = '0'; c <= '9'; c++)
        {

            if (palavra[i] == c)
            {
                palavraSemCaracteresIndesejados = palavraSemCaracteresIndesejados.append(1, palavra[i]);
                break;
            }
        }
    }

    palavra = palavraSemCaracteresIndesejados;
}

void TransformarPalavraParaMinusculo(std::string& palavra){

    for(int i =0; i < palavra.length(); i++){
        palavra[i] = std::tolower(palavra[i]);
    }

}

void lerPalavrasDoArquivo(LeitorDeArquivo *leitor, Hash *hash, int idDoDocumento, Hash *stopWords)
{

    std::string palavra;
    ListaFrequencia *lista, *auxiliarDePesquisa;

    while (leitor->getConteudoDaLinha(palavra))
    {
        TransformarPalavraParaMinusculo(palavra);
        removerCaracteresIndesejados(palavra);

        if (palavra.length() <= 0)
            continue;

        if (stopWords->Pesquisa(palavra, auxiliarDePesquisa))
            continue;

        if (!hash->Pesquisa(palavra, lista))
        {
            lista = new ListaFrequencia(palavra);
            hash->Insere(lista);
        }

        lista->InserirFrequencia(idDoDocumento);
    }
}

void LerStopWords(Hash *stopWords, LeitorDeArquivo *leitor)
{

    std::string stopWord;

    while (leitor->getConteudoDaLinha(stopWord)){

        TransformarPalavraParaMinusculo(stopWord);
        stopWords->Insere(new ListaFrequencia(stopWord));
    }
};

void LerConsulta(Lista<std::string> *lista, LeitorDeArquivo *leitor)
{

    std::string palavraDaConsulta;
    while (leitor->getConteudoDaLinha(palavraDaConsulta)){
        TransformarPalavraParaMinusculo(palavraDaConsulta);
        lista->inserir(new std::string(palavraDaConsulta));
    }
};

int main(int numeroDeArgumentos, char **argumentos)
{

    try
    {

        if (numeroDeArgumentos < 5)
        {
            throw new ArgumentoException("Deve haver 4 argumentos : <consulta>.txt <ranking>.txt <corpus> <stopwords>.txt");
        }

        std::string nomeDoArquivoDeConsulta = std::string(argumentos[1]);
        std::string nomeDoArquivoDeSaida = std::string(argumentos[2]);
        std::string diretorioCorpus = std::string(argumentos[3]);
        std::string nomeDoArquivoDasStopWords = std::string(argumentos[4]);

        LeitorDeArquivo *leitor = new LeitorDeArquivo();
        Hash *stopWords = new Hash();

        leitor->abrirArquivo(nomeDoArquivoDasStopWords);
        LerStopWords(stopWords, leitor);

        Hash *hashPesquisa = new Hash();

        std::string path = std::filesystem::current_path();
        path = path.append("/").append(diretorioCorpus);
        std::string nomeDoArquivo;
        std::string numero = "";
        int quantidadeDocumentos = 0;

        for (const auto &entry : fs::directory_iterator(path))
        {
            nomeDoArquivo = entry.path().filename();

            numero = "";
            for (int i = 0; i < nomeDoArquivo.length() - 4; i++)
            {
                numero = numero.append(1, nomeDoArquivo[i]);
            }

            int idDoDocumento = std::stoi(numero);
            leitor->abrirArquivo(entry.path());
            lerPalavrasDoArquivo(leitor, hashPesquisa, idDoDocumento, stopWords);
            quantidadeDocumentos++;
        }

        // Termos Pesquisa
        Lista<std::string> *listaTermos = new Lista<std::string>();

        leitor->abrirArquivo(nomeDoArquivoDeConsulta);
        LerConsulta(listaTermos, leitor);

        int tamanho = 0;

        // Cálculo
        HashWD *hash = new HashWD();

        hashPesquisa->CalcularPesos(quantidadeDocumentos, hash);

        ListaFrequencia *listaFrequenciaTermos;

        Item<std::string> *item = listaTermos->getPrimeiroItem();
        std::string termo;

        while (item != nullptr)
        {

            termo = std::string(item->getValorDoObjetoArmazenado()->c_str());

            if (hashPesquisa->Pesquisa(termo, listaFrequenciaTermos))
            {
                tamanho += listaFrequenciaTermos->GetSize();
            }

            item = item->getProximoItem();
        }

        int tamanhoOcupado = 0;
        int *idsDocumentos = new int[tamanho];

        item = listaTermos->getPrimeiroItem();

        while (item != nullptr)
        {

            termo = std::string(item->getValorDoObjetoArmazenado()->c_str());

            if (hashPesquisa->Pesquisa(termo, listaFrequenciaTermos))
            {
                listaFrequenciaTermos->CalcularSimilaridades(hash, idsDocumentos, tamanhoOcupado);
            }

            item = item->getProximoItem();
        }

        Ordenador *ordenador = new Ordenador();
        ordenador->ordenar(idsDocumentos, tamanhoOcupado, hash);
        ItemWD *wd;
        int quantidade = 0;

        EscritorDeArquivos *escritor = new EscritorDeArquivos(nomeDoArquivoDeSaida);

        for (int i = 0; i < tamanhoOcupado; i++)
        {
            if (quantidade >= 10)
                break;
            quantidade++;

            if ((i - 1) >= 0 && idsDocumentos[i] == idsDocumentos[i - 1])
            {
                continue;
            }

            hash->Pesquisa(idsDocumentos[i], wd);

            escritor->escrever(std::to_string(idsDocumentos[i]).append(" "));
        };

        delete escritor;
        delete ordenador;
        delete idsDocumentos;
        delete hash;
        delete hashPesquisa;
        delete listaTermos;
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