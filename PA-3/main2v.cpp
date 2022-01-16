#include <iostream>

struct NoArvore
{
    int beleza;
    int galho;
    int chave;
    int pai;
    bool podado;
};

struct ItemPai
{
    int comeco;
    int fim;
    bool isIniciado;
};

/*
5
0 0 2 2
1 1 2 -3
2 2 4 4
3 4 3 -10

15
0 194 331 -395
1 194 281 -662
2 333 161 -859
3 405 756 -947
4 405 970 464
5 405 310 690
6 405 463 -213
7 989 873 247
8 819 132 188
9 59 229 -464
10 59 710 -777
11 871 950 463
12 127 423 -579
13 682 25 749

*/

void Particao(int Esq, int Dir, int *i, int *j, NoArvore *A)
{
    NoArvore x, w;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j) / 2]; /* obtem o pivo x */
    do
    {
        while (x.pai > A[*i].pai)
            (*i)++;
        while (x.pai < A[*j].pai)
            (*j)--;
        if (*i <= *j)
        {
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void Ordena(int Esq, int Dir, NoArvore *A)
{
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j)
        Ordena(Esq, j, A);
    if (i < Dir)
        Ordena(i, Dir, A);
}

void QuickSort(NoArvore *A, int n)
{
    Ordena(0, n - 1, A);
}

void ParticaoInteiro(int Esq, int Dir, int *i, int *j, int *A)
{
    int x, w;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j) / 2]; /* obtem o pivo x */
    do
    {
        while (x > A[*i])
            (*i)++;
        while (x < A[*j])
            (*j)--;
        if (*i <= *j)
        {
            w = A[*i];
            A[*i] = A[*j];
            A[*j] = w;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void OrdenaInteiro(int Esq, int Dir, int *A)
{
    int i, j;
    ParticaoInteiro(Esq, Dir, &i, &j, A);
    if (Esq < j)
        OrdenaInteiro(Esq, j, A);
    if (i < Dir)
        OrdenaInteiro(i, Dir, A);
}

void QuickSortInteiro(int *A, int n)
{
    OrdenaInteiro(0, n - 1, A);
}

int calcularValorSemCortes(NoArvore *itens, int chave, ItemPai *pais)
{
    int total = 0;

    for (int j = pais[chave].comeco; j <= pais[chave].fim; j++)
    {
        total += itens[j].beleza;

        if (pais[chave].comeco < 0 && pais[chave].fim < 0)
            continue;

        total += calcularValorSemCortes(itens, chave, pais);
    }

    return total;
}

int Podar(NoArvore *itens, int chave, ItemPai *pais)
{

    if (pais[chave].comeco < 0 && pais[chave].fim < 0)
    {
        return 0;
    }

    int total = 0;

    for (int j = pais[chave].comeco; j <= pais[chave].fim; j++)
    {

        // somar o valor positivo da chave com o valor da beleza dela
        // de isso for menor que zero deve-se cortar
        int valorPodados = Podar(itens, itens[j].chave, pais);
        int valorCalculadoDeBelezaDoGalho = itens[j].beleza + valorPodados;

        if (valorCalculadoDeBelezaDoGalho <= 0)
        {
            itens[j].podado = true;
            continue;
        }

        total += valorCalculadoDeBelezaDoGalho;
    }

    return total;
}

void GerarGalhosPodados(NoArvore *itens, int chave, ItemPai *pais, int *galhosPodados, int &numeroDeGalhosPodados)
{

    if (pais[chave].comeco < 0 && pais[chave].fim < 0)
    {
        return;
    }

    int total = 0;

    for (int j = pais[chave].comeco; j <= pais[chave].fim; j++)
    {

        if (itens[j].podado)
        {
            galhosPodados[numeroDeGalhosPodados] = itens[j].galho;
            numeroDeGalhosPodados++;
            continue;
        }

        GerarGalhosPodados(itens, itens[j].chave, pais, galhosPodados, numeroDeGalhosPodados);
    }
}

void ImprimirGalhosPodados(int *itens, int numeroDeGalhos)
{

    for (int j = 0; j < numeroDeGalhos; j++)
    {
        std ::cout << itens[j] << " ";
    }
}

int main()
{

    int tamanhoDeFilhos, n;
    scanf("%d", &n);
    tamanhoDeFilhos = n - 1;

    NoArvore *arvore = new NoArvore[tamanhoDeFilhos];
    ItemPai *pais = new ItemPai[n];

    int *galhosPodados = new int[n];

    int numeroDeGalhosPodados = 0;

    int galho = 0, chaveAI = 0, chaveBI = 0, beleza = 0, pai = 0, chave = 0;

    pais[0] = {0, 0, 1};

    for (int i = 0; i < tamanhoDeFilhos; i++)
    {

        scanf("%d %d %d %d", &arvore[i].galho, &chaveAI, &chaveBI, &arvore[i].beleza);

        if (pais[chaveAI].isIniciado || (!pais[chaveAI].isIniciado && !pais[chaveBI].isIniciado))
        {
            pai = chaveAI;
            chave = chaveBI;
        }

        else if (pais[chaveBI].isIniciado)
        {
            pai = chaveBI;
            chave = chaveAI;
        }

        arvore[i].pai = pai;
        arvore[i].chave = chave;

        pais[chave].comeco = -1;
        pais[chave].fim = -1;
        pais[chave].isIniciado = true;
    }

    QuickSort(arvore, tamanhoDeFilhos);
    pai = 0;

    for (int i = 0; i < tamanhoDeFilhos; i++)
    {
        if (pai != arvore[i].pai)
        {

            if (i > tamanhoDeFilhos)
                break;

            pai = arvore[i].pai;

            pais[pai].comeco = i;
            pais[pai].fim = i;
        }
        else
        {
            pais[pai].fim = i;
        }
    }

    int valorTotal = Podar(arvore, 0, pais);
    GerarGalhosPodados(arvore, 0, pais, galhosPodados, numeroDeGalhosPodados);

    std::cout << valorTotal << " " << numeroDeGalhosPodados;

    if (numeroDeGalhosPodados > 0)
    {
        std::cout << std::endl;
        QuickSortInteiro(galhosPodados, numeroDeGalhosPodados);
        ImprimirGalhosPodados(galhosPodados, numeroDeGalhosPodados);
    }

    return 0;
}