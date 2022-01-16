#include <iostream>

struct Item
{
    bool isCortado;
    int beleza;
    int chave;
    bool isIniciado;
    int pai;
};

struct ItemPai{
    int comeco;
    int fim;
};

int calcularValorSemCortes(Item *itens, int n, int chave, int comeco = 0)
{
    int total = 0;

    for (int j = comeco; j < n; j++)
    {
        if (itens[j].pai == chave)
        {
            total += itens[j].beleza;
            total += calcularValorSemCortes(itens, n, itens[j].chave, j);
        }
    }

    return total;
}

int calcularValor(Item *itens, int n, int chave, int comeco = 0)
{
    int total = 0;

    for (int j = comeco; j < n; j++)
    {
        if (itens[j].pai == chave && !itens[j].isCortado)
        {
            total += itens[j].beleza;
            total += calcularValor(itens, n, itens[j].chave, j);
        }
    }

    return total;
}

int podarArvore(Item *itens, int n)
{
    int quantidadeCortes = 0;

    for (int j = (n - 1); j >= 0; j--)
    {

        int beleza = itens[j].beleza + calcularValorSemCortes(itens, n, itens[j].chave, j);

        if (beleza < 0)
        {
            itens[j].isCortado = true;
            quantidadeCortes++;
            continue;
        }
    }

    return quantidadeCortes;
}

int ValorTotal(Item *itens, int n)
{
    return calcularValor(itens, n, itens[0].pai);
}

int calcularNumeroDeCortes(Item *itens, int n)
{
    int galhosCortados = 0;

    for (int i = 0; i < n; i++)
    {
        if (itens[i].isCortado)
        {
            galhosCortados++;
        }
    }

    return galhosCortados;
}

void printarGalhosParaPodar(Item *itens, int n)
{
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        if (itens[i].isCortado)
        {
            printf("%d ", i);
        }
    }
}

int main()
{

    int tamanhoVetor;

    //lendo a quantidade
    scanf("%d", &tamanhoVetor);

    Item *itens = new Item[tamanhoVetor - 1];
    Item *pais = new Item[tamanhoVetor - 1];

    // 0 0 1 2
    int galho, ai, bi, wi;

    for (int i = 0; i < (tamanhoVetor - 1); i++)
    {
        scanf("%d %d %d %d", &galho, &ai, &bi, &wi);

        itens[galho].beleza = wi;
        itens[galho].chave = bi;
        itens[galho].pai = ai;
        itens[galho].isIniciado = true;

        if (ai > bi)
        {
            itens[galho].chave = ai;
            itens[galho].pai = bi;
        }
    }

    int quantidadeDeCortes = podarArvore(itens, tamanhoVetor - 1);
    int valorDaArvore = ValorTotal(itens, tamanhoVetor - 1);

    printf("%d %d", valorDaArvore, quantidadeDeCortes);

    if (quantidadeDeCortes > 0)
    {
        printarGalhosParaPodar(itens, tamanhoVetor);
    }

    delete itens;

    return 0;
}