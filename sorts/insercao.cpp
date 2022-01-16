#include <iostream>

// estável
// melhor caso : vetor ordenado
// pior caso : ordem inversa
// comparações :
//     melhor caso : O(n)
//     pior caso : O(n^2)
// movimentações :
//     melhor caso : O(n)
//     pior caso : O(n^2)
// Vantagens : ótimo para quase ordenado , 
// quando se quer adicionar novos elementos em um vetor ordenado e estável
// Desvantagens : alto custo de movimentação de elementos no vetor



void insercao(int *v, int n)
{

    int aux, j;

    for (int i = 1; i < n; i++)
    {
        aux = v[i];
        j = i - 1;

        while ((j >= 0) && (aux < v[j]))
        {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = aux;
    }
}