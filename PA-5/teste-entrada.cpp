#include <iostream>

struct No
{
    int valor;
    int profundidade;
    bool cortado;
    int pai;
};

int comparar(No &no1, No &no2, int *temFilhos, No *nos, int quantidade)
{

    if (no1.cortado && !no2.cortado)
        return 1;
    else if (!no1.cortado && no2.cortado)
        return -1;
    else if (no1.cortado && no2.cortado)
        return 0;

    bool umUnicoGalho = true;
    for (int i = quantidade; i >= 0; i++)
        if (temFilhos[nos[i].valor] > 1)
        {
            umUnicoGalho = false;
            break;
        }

    if ((temFilhos[no1.valor] < temFilhos[no2.valor]) && !umUnicoGalho)
        return 1;
    else if ((temFilhos[no1.valor] > temFilhos[no2.valor]) && !umUnicoGalho)
        return -1;
    else if (no1.valor > no2.valor)
        return -1;
    else if (no1.valor < no2.valor)
        return 1;
    else
        return 0;
}

int mediana(int index1, int index2, int index3, No *itens, int *temFilhos, int quantidade)
{

    if (comparar(itens[index1], itens[index2], temFilhos, itens, quantidade) >= 0)
    {
        if (comparar(itens[index1], itens[index3], temFilhos, itens, quantidade) <= 0)
            return index1;
    }
    else if (comparar(itens[index2], itens[index3], temFilhos, itens, quantidade) <= 0)
        return index2;

    return index3;
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param i índice de maiores
 * @param j índice de menores
 * @param itens - vetor
 */
void particionar(int Esq, int Dir, int *i, int *j, No *itens, int *temFilhos, int quantidade)
{
    No x, w;
    // inicializa os índices que vão percorrer o vetor
    *i = Esq;
    *j = Dir;

    int indiceDoPivo = mediana(Esq, Dir, (Esq + Dir) / 2, itens, temFilhos, quantidade);

    // inicializa o pivô com elemento central
    x = itens[indiceDoPivo];
    do
    {
        // procura elemento maior que o pivô
        while (comparar(x, itens[*i], temFilhos, itens, quantidade) > 0)
            (*i)++;
        // procura elemento menor que o pivô
        while (comparar(x, itens[*j], temFilhos, itens, quantidade) < 0)
            (*j)--;

        // se os índices não se cruzaram
        if (*i <= *j)
        {
            // então troca-se os elementos de índice i e j de lugar
            w = itens[*i];
            itens[*i] = itens[*j];
            itens[*j] = w;

            // i e j passam para a próxima posição
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j); // é executado até que os índices se cruzem
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param itens vetor
 */
void realizarOrdenacao(int Esq, int Dir, No *itens, int *temFilhos, int quantidade)
{

    // índices i e j que vão percorrer o vetor
    int i, j;

    // Particiona com os índices i e j
    particionar(Esq, Dir, &i, &j, itens, temFilhos, quantidade);

    // se os elementos são <= pivô
    if (Esq < j)
        realizarOrdenacao(Esq, j, itens, temFilhos, quantidade);

    // se os elementos são maiores ou iguais aos do pivô
    if (i < Dir)
        realizarOrdenacao(i, Dir, itens, temFilhos, quantidade);
}

void ordenar(No *itens, int tamanho, int *temFilhos)
{
    // não é necessário ordenar um vetor de um item
    if (tamanho <= 1)
        return;

    // realizando a ordenação
    realizarOrdenacao(0, tamanho - 1, itens, temFilhos, tamanho);
}

int leitura(char &parenteses)
{

    int numeroDeLeitura = EOF;
    while ((numeroDeLeitura = scanf("%c", &parenteses)) >= 1 && parenteses == ' ')
        ;

    return numeroDeLeitura;
}

void definirPais(No *itens, int quantidade, int *temFilho)
{

    int profundidade = 1;
    int paisPorProfundidade[50];
    paisPorProfundidade[0] = 0;
    int paiAtual = 0;

    for (int i = 0; i < quantidade; i++)
    {

        paisPorProfundidade[itens[i].profundidade] = itens[i].valor;
        itens[i].pai = paisPorProfundidade[itens[i].profundidade - 1];
        temFilho[paisPorProfundidade[itens[i].profundidade - 1]]++;
    }
}

bool isNumber(char c)
{

    return !(c == ' ' || c == '(' || c == ')');
}

bool criarArvore(std::string &linha, int tamanho)
{

    bool continuarLeitura = false;
    int quantidade = 0;
    int numeroLido = 0;
    char parenteses = ' ';
    int profundidadeAtual = 0;
    No itens[50];
    int pais[50];
    int temFilhos[50] = {0};

    for (int i = 0; i < linha.length(); i++)
    {

        if (linha[i] == ' ')
            continue;
        else if (linha[i] == '(')
            profundidadeAtual++;
        else if (linha[i] == ')')
            profundidadeAtual--;
        else
        {

            int numero = std::atoi(&linha[i]);
            if ((i + 1) < linha.length() && isNumber(linha[i + 1]))
            {

                i++;
            }

            itens[quantidade].valor = numero;
            itens[quantidade].profundidade = profundidadeAtual;
            itens[quantidade].cortado = false;
            quantidade++;
        }
    }

    definirPais(itens, quantidade, temFilhos);
    ordenar(itens, quantidade, temFilhos);

    for (int i = quantidade - 1; i > 1; i--)
    {
        printf(" %d", itens[i].pai);
        temFilhos[itens[i].pai]--;
        itens[i].cortado = true;
        ordenar(itens, i + 1, temFilhos);
    }

    if (quantidade > 1)
        printf(" %d", quantidade);

    return true;
}

int main()
{
    std::string linha;
    while (std::getline(std::cin, linha))
    {
        criarArvore(linha, linha.length());
        printf("\n");
    };

    return 0;
}