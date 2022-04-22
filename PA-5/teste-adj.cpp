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
    int paisPorProfundidade[51];
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

int buscarProximoItemDoCodigo(int folha, vector<vector<int>> &matriz_adjacencia, bool *removidos)
{

    for (int item : matriz_adjacencia[folha])
        if (!removidos[item])
            return item;

    return 0;
}

int limpandoFolha(set<int> &folhas, bool *removidos)
{
    int folha = *folhas.begin();
    removidos[folha] = true;
    folhas.erase(folha);
    return folha;
}

void insererirNovaFolha(int *graus, int item, set<int> &folhas)
{
    graus[item]--;
    if (graus[item] != 1)
        return;
    folhas.insert(item);
}

void inicializandoAsFolhas(int *graus, set<int> &folhas, int tamannho)
{

    for (int i = 0; i < tamannho; i++)
    {
        if (graus[i] != 1)
            continue;
        folhas.insert(i);
    }
}

void codigo_prufer(int matriz[51][51], int quantidade, int *graus)
{

    vector<vector<int>> matriz_adjacencia;
    set<int> folhas;
    int tamanho = quantidade + 1;

    for (int i = 0; i < 51; i++)
    {
        matriz_adjacencia.push_back(vector<int>());

        for (int j = 0; j < 51; j++)
        {
            if (matriz[i][j] == 1)
                matriz_adjacencia[i].push_back(j);
        }
    }

    bool removidos[tamanho] = {0};

    inicializandoAsFolhas(graus, folhas, tamanho);
    string codigo;
    for (int i = 0; i < tamanho - 2; i++)
    {
        int folha = limpandoFolha(folhas, removidos);
        int item = buscarProximoItemDoCodigo(folha, matriz_adjacencia, removidos);
        codigo = codigo.append(to_string(item) + " ");
        insererirNovaFolha(graus, item, folhas);
    }

    codigo[codigo.size()-1] = '\0';

    printf(codigo.c_str());

}

bool criarArvore(std::string &linha, int tamanho)
{

    bool continuarLeitura = false;
    int quantidade = 0;
    int numeroLido = 0;
    char parenteses = ' ';
    int profundidadeAtual = 0;
    No itens[51];
    int matriz[51][51] = {{0}};
    int graus[51] = {0};
    int pais[51];
    int temFilhos[51] = {0};

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

    for (int i = 0; i < 51; i++)
    {
        for (int j = 0; j < 51; j++)
        {
            graus[i] += matriz[i][j];
        }
    }

    codigo_prufer(matriz, quantidade, graus);

    return true;
}

int main()
{
    std::string linha;
    while (std::getline(std::cin, linha))
    {
        criarArvore(linha, linha.length());
        std::cout << std::endl;
    };

    return 0;
}