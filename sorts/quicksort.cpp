
// QuickSort não é estável
// Pior caso : se o pivô excolhido for maior ou menor elemento do vetor, a partição será 1 e n-1.
// análise do pior caso : T(n) = n + T(n-1) => C(n) = O(n^2)
// Melhor caso : As duas partes divididas são iguais
// Caso médio : C(n) = O(nlog n)
/*
?Vantagens:

* É extremamente eficiente para ordenar arquivos de dados.
* Necessita de apenas uma pequena pilha como memória auxiliar.
* Requer cerca de n log n comparações em média para ordenar n itens.

?Desvantagens:

* Tem um pior caso O(n2) comparações.
* Sua implementação é muito delicada e difícil:
* Um pequeno engano pode levar a efeitos inesperados para algumas entradas de dados.
* O método não é estável.
*/

struct Item
{
    int Chave;
};

void Particao(int Esq, int Dir, int *i, int *j, Item *A)
{
    Item x, w;
    *i = Esq;
    *j = Dir;
    x = A[(*i + *j) / 2]; /* obtem o pivo x */
    do
    {
        while (x.Chave > A[*i].Chave)
            (*i)++;
        while (x.Chave < A[*j].Chave)
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

void Ordena(int Esq, int Dir, Item *A)
{
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j)
        Ordena(Esq, j, A);
    if (i < Dir)
        Ordena(i, Dir, A);
}
void QuickSort(Item *A, int n)
{
    Ordena(0, n - 1, A);
}
