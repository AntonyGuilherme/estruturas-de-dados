#ifndef HASHWD
#define HASHWD

#include <string>
#include "Wd.hpp"
#include "HashException.hpp"

class HashWD
{

public:
    HashWD()
    {
        // alocando o espaço para os itens do hash
        Tabela = new ItemWD *[tamanhoTotal];
        vazio = new bool[tamanhoTotal];
        retirado = new bool[tamanhoTotal];

        // colocando os valores iniciais no hash
        for (int i = 0; i < tamanhoTotal; i++)
        {
            vazio[i] = true;
            retirado[i] = false;
        }
    };

    bool Pesquisa(int chave, ItemWD *&wd)
    {

        if(chave < 0){
            throw new HashException("A chave deve ser maior que zero");
        }

        // se não houver nenhum item no hash
        if (tamanhoUtilizado <= 0)
            return false;

        // calculando o hash fixo
        int posicaoEsperada = generateHash(chave, tamanhoTotal);
        int i = 0;
        int hashCalculado = 0;

        // buscando a posicao da lista de frequencias
        while ((i < tamanhoTotal) && calcularHash(hashCalculado, posicaoEsperada, i, tamanhoTotal) && !vazio[hashCalculado] &&
               (Tabela[hashCalculado]->GetChave() != chave))
        {
            i++;
        }

        // se a chave estiver de fato no hash
        if (!vazio[hashCalculado] && (Tabela[hashCalculado]->GetChave() == chave) && !retirado[hashCalculado])
        {
            wd = Tabela[hashCalculado];

            return true;
        }

        return false;
    };

    void Insere(ItemWD *wd)
    {
        if(wd == nullptr){
            throw new HashException("O valor inserido não pode ser nulo");
        }

        // verificando se 75% do tamanho disponível
        bool isTamanhoDeSegurancaUtilizado = ((double)tamanhoUtilizado / tamanhoTotal) >= 0.75;

        // caso já esteja ocupado o hash é regerado
        if (isTamanhoDeSegurancaUtilizado)
            regerarHash();

        ItemWD *aux;
        int posicaoEsperada, i;

        // buscando pelo item no hash
        if (Pesquisa(wd->GetChave(), aux)){

            aux->Insere(wd);
            return;
        }

        // calculando o hash fixo
        posicaoEsperada = generateHash(wd->GetChave(), tamanhoTotal);
        i = 0;
        int hashCalculado = 0;

        // encontrando a posicao real do item
        while ((i < tamanhoTotal) &&
               calcularHash(hashCalculado, posicaoEsperada, i, tamanhoTotal) &&
               !vazio[hashCalculado] && !retirado[hashCalculado])
        {
            i++;
        }

        //inserindo o item no hash
        Tabela[(posicaoEsperada + i) % tamanhoTotal] = wd;
        vazio[(posicaoEsperada + i) % tamanhoTotal] = false;
        retirado[(posicaoEsperada + i) % tamanhoTotal] = false;

        // incrementando o tamanho utilizado 
        tamanhoUtilizado++;
    };

private:
    int generateHash(int chave, int tamanho)
    {

        return chave % tamanho;
    };

    bool calcularHash(int &hashCalculado, int hashFixo, int posicao, int tamanho)
    {
        // calculando o hash de maneira dinamica
        return (hashCalculado = (hashFixo + posicao) % tamanho) >= 0;
    }

    void regerarHash()
    {

        // redimensionando o tamanho do hash
        // para o dobro do anterior
        int novoTamanho = tamanhoTotal * 2;

        // realocando os novos itens do hash para o tamanho especificado
        ItemWD **novaListaFrequencia = new ItemWD *[novoTamanho];
        bool *novoVazio = new bool[novoTamanho];
        bool *novoRetirado = new bool[novoTamanho];

        // inicializando os valores do vazio e do retirado
        for (int i = 0; i < novoTamanho; i++)
        {
            novoVazio[i] = true;
            novoRetirado[i] = false;
        }

        int posicaoEsperada;
        int hashCalculado = 0;

        for (int i = 0; i < tamanhoTotal; i++)
        {

            // se a posicao nao estiver vazia ela deve ser reposicionada
            if (!vazio[i])
            {
                // refazendo o calculo do hash para o novo tamanho
                posicaoEsperada = generateHash(Tabela[i]->GetChave(), novoTamanho);

                // encontrando a nova posicao relativa da lista de frequencias
                int j = 0;
                while (
                    (j < tamanhoTotal) &&
                    calcularHash(hashCalculado, posicaoEsperada, j, novoTamanho) &&
                    !novoVazio[hashCalculado] &&
                    !novoRetirado[hashCalculado])
                {
                    j++;
                }

                // reposicionado a lista de frequencias de acordo como o novo tamanho do hash
                novaListaFrequencia[hashCalculado] = Tabela[i];
                novoVazio[hashCalculado] = false;
                novoRetirado[hashCalculado] = false;
            }
        }

        // liberando o espaço do tamnho anterior
        delete Tabela;
        delete vazio;
        delete retirado;

        // alocando o tamanho do hash
        tamanhoTotal = novoTamanho;
        vazio = novoVazio;
        Tabela = novaListaFrequencia;
        retirado = novoRetirado;
    };

    int tamanhoTotal = 120;

    ItemWD **Tabela;
    bool *vazio;
    bool *retirado;
    int tamanhoUtilizado = 0;
};

#endif