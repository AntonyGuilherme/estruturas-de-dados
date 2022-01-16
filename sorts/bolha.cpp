#include <iostream>

// Estável
// Não troca as posições relativas dos itens : 5 da posição dois e o cinco
// da posição 3 permanecem em suas repectivas posições relativas
// O(n^2)
// pior caso : vetor inversamente ordenado
// melhor caso : vetor ordenado
// Vantagens : Algoritmo simples e estável
// Desvantagem : não adaptável em termos de comparações
// Muitas trocas de itens

void bolha(int *v, int n)
{

    bool isOrdenado = true;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n - i; j++)
        {

            if (v[j] < v[j - 1])
            {
                // 3 movimentações
                int c = v[j];
                v[j] = v[j - 1];
                v[j - 1] = c;

                // melhoria
                isOrdenado = false;
            }
        }

        // melhoria
        if (isOrdenado)
            break;
    }
}

int main()
{

    int v[5]{1, 2, 6, 7, 5};

    bolha(v, 5);

    for (int i = 0; i < 5; i++)
    {
        std::cout << v[i] << " ";
    }

    return 0;
}