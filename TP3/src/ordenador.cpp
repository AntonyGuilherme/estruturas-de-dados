#include "ordenador.hpp"
#include <iostream>

void Ordenador::ordenar(int * urls, int tamanho,HashWD * hash)
{
    // não é necessário ordenar um vetor de um item
    if (tamanho <= 1)
        return;

    // realizando a ordenação
    realizarOrdenacao(0, tamanho - 1, urls, hash);
}

int Ordenador::comparar( int documento1, int documento2, HashWD * hash)
{

    ItemWD * item;
    hash->Pesquisa(documento1,item);
    double similaridadeDocumento1 = item->GetSimilaridade();

    hash->Pesquisa(documento2,item);
    double similaridadeDocumento2 = item->GetSimilaridade();
    
    if(similaridadeDocumento1 > similaridadeDocumento2) return -1;
    else if (similaridadeDocumento2 > similaridadeDocumento1) return 1;
    else if(documento1 > documento2) return 1;
    else if(documento2 > documento1) return -1;
    
    return 0;
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param i índice de maiores
 * @param j índice de menores
 * @param urls - vetor
 */
void Ordenador::particionar(int Esq, int Dir, int *i, int *j, int *idsDocumentos,HashWD * hash)
{
    int x, w;
    // inicializa os índices que vão percorrer o vetor
    *i = Esq;
    *j = Dir;

    int indiceDoPivo = (Esq+Dir)/2 ;

    // inicializa o pivô com elemento central
    x = idsDocumentos[indiceDoPivo];
    do
    {
        // procura elemento maior que o pivô
        while (this->comparar(x, idsDocumentos[*i],hash) > 0)
            (*i)++;
        // procura elemento menor que o pivô
        while (this->comparar(x, idsDocumentos[*j],hash) < 0)
            (*j)--;

        // se os índices não se cruzaram
        if (*i <= *j)
        {
            // então troca-se os elementos de índice i e j de lugar
            w = idsDocumentos[*i];
            idsDocumentos[*i] = idsDocumentos[*j];
            idsDocumentos[*j] = w;

            // i e j passam para a próxima posição
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j); // é executado até que os índices se cruzem
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param urls vetor
 */
void Ordenador::realizarOrdenacao(int Esq, int Dir, int * idsDocumentos, HashWD * hash)
{

    // índices i e j que vão percorrer o vetor
    int i, j;

    // Particiona com os índices i e j
    particionar(Esq, Dir, &i, &j, idsDocumentos,hash);

    // se os elementos são <= pivô
    if (Esq < j)
        realizarOrdenacao(Esq, j, idsDocumentos,hash);

    // se os elementos são maiores ou iguais aos do pivô
    if (i < Dir)
        realizarOrdenacao(i, Dir, idsDocumentos,hash);
}