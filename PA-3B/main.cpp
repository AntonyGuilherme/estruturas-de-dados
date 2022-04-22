#include <iostream>
#include <string>

struct Camisa
{
    std::string nome;
    std::string cor;
    char tamanho;
};

/**
branco P Cezar Torres Mo
branco P Maria Jose
branco M JuJu Mentina
branco G Adabi Finho
branco G Severina Rigudinha
vermelho P Amaro Dinha
vermelho P Baka Lhau
vermelho P Carlos Chade Losna
vermelho P Mangojata Mancuda
 */

int comparar(Camisa &camisa1, Camisa &camisa2)
{
    int comp;

    if ((comp = camisa1.cor.compare(camisa2.cor)) != 0)
        return comp;
    else if (camisa1.tamanho < camisa2.tamanho)
        return 1;
    else if (camisa1.tamanho > camisa2.tamanho)
        return -1;
    else if ((comp = camisa1.nome.compare(camisa2.nome)) != 0)
        return comp;
    else
        return 0;
}

int mediana(int index1, int index2, int index3, Camisa *camisas)
{

    if (comparar(camisas[index1], camisas[index2]) >= 0)
    {
        if (comparar(camisas[index1], camisas[index3]) <= 0)
            return index1;
    }
    else if (comparar(camisas[index2], camisas[index3]) <= 0)
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
void particionar(int Esq, int Dir, int *i, int *j, Camisa *itens)
{
    Camisa x, w;
    // inicializa os índices que vão percorrer o vetor
    *i = Esq;
    *j = Dir;

    int indiceDoPivo = (Esq + Dir) / 2;

    // inicializa o pivô com elemento central
    x = itens[indiceDoPivo];
    do
    {
        // procura elemento maior que o pivô
        while (comparar(x, itens[*i]) > 0)
            (*i)++;
        // procura elemento menor que o pivô
        while (comparar(x, itens[*j]) < 0)
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
void realizarOrdenacao(int Esq, int Dir, Camisa *itens)
{

    // índices i e j que vão percorrer o vetor
    int i, j;

    // Particiona com os índices i e j
    particionar(Esq, Dir, &i, &j, itens);

    // se os elementos são <= pivô
    if (Esq < j)
        realizarOrdenacao(Esq, j, itens);

    // se os elementos são maiores ou iguais aos do pivô
    if (i < Dir)
        realizarOrdenacao(i, Dir, itens);
}

void ordenar(Camisa *itens, int tamanho)
{
    // não é necessário ordenar um vetor de um item
    if (tamanho <= 1)
        return;

    // realizando a ordenação
    realizarOrdenacao(0, tamanho - 1, itens);
}

void criarCamisa(Camisa &camisa)
{
    std::getline(std::cin, camisa.nome);
    std::cin >> camisa.cor;
    std::cin >> camisa.tamanho;
}

void processarCaso(int n)
{
    Camisa *camisas = new Camisa[n];

    for (int i = 0; i < n; i++)
    {
        criarCamisa(camisas[i]);
        std::cin.ignore();
    }

    ordenar(camisas, n);

    for (int i = 0; i < n; i++)
    {
        printf("%s %c %s", camisas[i].cor.c_str(), camisas[i].tamanho, camisas[i].nome.c_str());

        if ((i + 1) <= n)
            printf("\n");
    }
}

int main()
{
    int tamanho = 0;
    std::cin >> tamanho;
    while (tamanho != 0)
    {
        std::cin.ignore();
        processarCaso(tamanho);

        std::cin >> tamanho;

        if (tamanho >= 1)
            printf("\n");
    }

    return 0;
}