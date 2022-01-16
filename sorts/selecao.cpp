
// estável : não estável
// comparações : O(n^2)
// movimentações : O(n)
// sem adaptabilidade
// Vantagens : custo linear na movimentação
// Desvantagens : Não adaptável e não estável

void selecao(int *v, int n)
{

    int i, j, Min;

    for (i = 0; i < n - 1; i++)
    {

        Min = i;

        for (j = i + 1; j < n; j++)
        {
            if (v[j] < v[Min])
            {
                Min = j;
            }
        }

        int c = v[i];
        v[i] = v[Min];
        v[Min] = c;
    }
}