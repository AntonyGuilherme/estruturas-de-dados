#include <iostream>

struct No
{
    int valor;
    int profundidade;
    bool cortado;
    int pai;
};

int comparar(No &no1, No &no2, int *temFilhos)
{

    if (no1.cortado && !no2.cortado)
        return 1;
    else if (!no1.cortado && no2.cortado)
        return -1;
    else if (no1.cortado && no2.cortado)
        return 0;

    if (temFilhos[no1.valor] < temFilhos[no2.valor])
        return 1;
    else if (temFilhos[no1.valor] > temFilhos[no2.valor])
        return -1;
    else if (no1.valor > no2.valor)
        return -1;
    else if (no1.valor < no2.valor)
        return 1;
    else
        return 0;
}

int mediana(int index1, int index2, int index3, No *itens, int *temFilhos)
{

    if (comparar(itens[index1], itens[index2], temFilhos) >= 0)
    {
        if (comparar(itens[index1], itens[index3], temFilhos) <= 0)
            return index1;
    }
    else if (comparar(itens[index2], itens[index3], temFilhos) <= 0)
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
void particionar(int Esq, int Dir, int *i, int *j, No *itens, int *temFilhos)
{
    No x, w;
    // inicializa os índices que vão percorrer o vetor
    *i = Esq;
    *j = Dir;

    int indiceDoPivo = mediana(Esq, Dir, (Esq + Dir) / 2, itens, temFilhos);

    // inicializa o pivô com elemento central
    x = itens[indiceDoPivo];
    do
    {
        // procura elemento maior que o pivô
        while (comparar(x, itens[*i], temFilhos) > 0)
            (*i)++;
        // procura elemento menor que o pivô
        while (comparar(x, itens[*j], temFilhos) < 0)
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
void realizarOrdenacao(int Esq, int Dir, No *itens, int *temFilhos)
{

    // índices i e j que vão percorrer o vetor
    int i, j;

    // Particiona com os índices i e j
    particionar(Esq, Dir, &i, &j, itens, temFilhos);

    // se os elementos são <= pivô
    if (Esq < j)
        realizarOrdenacao(Esq, j, itens, temFilhos);

    // se os elementos são maiores ou iguais aos do pivô
    if (i < Dir)
        realizarOrdenacao(i, Dir, itens, temFilhos);
}

void ordenar(No *itens, int tamanho, int *temFilhos)
{
    // não é necessário ordenar um vetor de um item
    if (tamanho <= 1)
        return;

    // realizando a ordenação
    realizarOrdenacao(0, tamanho - 1, itens, temFilhos);
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

void printarItens(No * itens , int quantidade){

    for(int i = 0; i < quantidade ; i++){
        printf("%d pai %d",itens[i].valor, itens[i].pai);
    }

}

bool criarArvore(std::string &linha, int tamanho)
{

    bool continuarLeitura = false;
    int quantidade = 0;
    int numeroLido = 0;
    char parenteses = ' ';
    int profundidadeAtual = 0;
    No itens[50];
    int matriz[50][50] = {{0}};
    int graus[50] = {0};
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
            if ((i + 1) < linha.length() && isNumber(linha[i + 1])){

                i++;
            }

            itens[quantidade].valor = numero;
            itens[quantidade].profundidade = profundidadeAtual;
            itens[quantidade].cortado = false;
            quantidade++;

            
        }
    }

    definirPais(itens, quantidade, temFilhos);

    for(int i = 1; i < quantidade; i++){

        matriz[itens[i].valor][itens[i].pai] = 1;
        matriz[itens[i].pai][itens[i].valor] = 1;

    }

    for(int i = 0; i < 50; i++){
        //printf("\n");
        for (int j = 0; j < 50; j++){
            graus[i] += matriz[i][j];
        }
    }


    for(int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){

            if(matriz[i][j]){

                if(graus[i] == 1){
                    printf(" %d",j);
                    matriz[j][i] = 0;
                    graus[j]--;
                }

            }
        
        }
    }

    


    return true;
}

int main()
{
    std::string linha;
    while (std::getline(std::cin,linha))
    {
        criarArvore(linha,linha.length());
        printf("\n");
    };

    return 0;
}