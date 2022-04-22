#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct No
{
    int valor;
    int profundidade;
    bool cortado;
    int pai;
};

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

void printarItens(No *itens, int quantidade)
{

    for (int i = 0; i < quantidade; i++)
    {
        printf("%d pai %d", itens[i].valor, itens[i].pai);
    }
}

vector<int> pruefer_code(int matriz[50][50], int quantidade, int * graus)
{

    vector<vector<int>> matriz_adjacencia;

    for (int i = 0; i < 50; i++)
    {
        matriz_adjacencia.push_back(vector<int>());

        for (int j = 0; j < 50; j++)
        {
            if (matriz[i][j] == 1)
                matriz_adjacencia[i].push_back(j);
        }
    }

    int n = matriz_adjacencia.size();
    set<int> folhas;
    vector<bool> removidos(n, false);

    for (int i = 0; i < n; i++)
    {
        if (graus[i] == 1)
            folhas.insert(i);
    }

    vector<int> code(n - 2);
    for (int i = 0; i < n - 2; i++)
    {
        int leaf = *folhas.begin();
        folhas.erase(leaf);
        removidos[leaf] = true;
    
        int v;
        for (int u : matriz_adjacencia[leaf])
        {
            if (!removidos[u])
                v = u;
        }

        code[i] = v;
        if (--graus[v] == 1)
            folhas.insert(v);
    }

    return code;
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

    for (int i = 1; i < quantidade; i++)
    {

        matriz[itens[i].valor][itens[i].pai] = 1;
        matriz[itens[i].pai][itens[i].valor] = 1;
    }

    for (int i = 0; i < 50; i++)
    {
        //printf("\n");
        for (int j = 0; j < 50; j++)
        {
            graus[i] += matriz[i][j];
        }
    }

    vector<int> pruffer_code = pruefer_code(matriz,quantidade,graus);
    
    for(int n = 0 ; n < quantidade -1; n++ ){
        std:: cout << " " << pruffer_code[n];
    }

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