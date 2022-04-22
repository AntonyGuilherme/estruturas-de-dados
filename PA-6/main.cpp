#include <iostream>
#include <string>

/*
1
2
CBA
DDD
*/

int calcularPosicaoNoAlfabeto(char letra)
{

    char _letra = 'A';
    int posicao = 0;
    while (_letra != letra)
    {
        _letra++;
        posicao++;
    }

    return posicao;
}

int calcularValor(char letra, int elemento, int posicao)
{

    printf("letra %c valor : %d , elemento %d , posicao : %d\n",letra,calcularPosicaoNoAlfabeto(letra),elemento, posicao);

    return calcularPosicaoNoAlfabeto(letra) + elemento + posicao;
}

int processarLinha(int elemento, std::string &linha)
{
    std::cout << linha << std::endl;
    int acumuladoDaLinha = 0;
    for (int i = 0; i < linha.size(); i++)
    {
        acumuladoDaLinha += calcularValor(linha.c_str()[i], elemento, i);
    }

    return acumuladoDaLinha;
}

void processarElementos()
{

    int numeroMaximoDeElementos = 0;
    std::string linha;

    scanf("%d", &numeroMaximoDeElementos);

    int acumuladoDosElementos = 0;

    for (int elemento = 0; elemento < numeroMaximoDeElementos; elemento++)
    {

        std::getline(std::cin, linha);
        acumuladoDosElementos += processarLinha(elemento, linha);
    }

    printf("%d\n", acumuladoDosElementos);
}

int main()
{

    int leituras = 0;

    scanf("%d", &leituras);

    while ((--leituras) >= 0)
        processarElementos();

    return 0;
}