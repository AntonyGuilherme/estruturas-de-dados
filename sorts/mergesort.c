/* Merge Sort
    Método dividir para conquistar baseado em merging(ou intercalação)
    * dividir => ordenar os pares => combona ordenando

    ? Estável : permite estabilidade if (valuesL[i] <= valuesR[j])
    ? Adptável : Não, ele executa o mesmo número de comparações, independentemente da entrada.

    ? Análise de Complexidade : T(n) = 2T(n/2) + n = O(n log n )

    Vantagens :
        Deve ser considerado quando alto custo de pior caso não pode ser tolerado.
    Desvantagens :
        Requer espaço extra proporcional a .
            

*/

int *merge(int *valuesL, int *valuesR, int nl, int nr)
{
    int *result = (int *)malloc((nl + nr) * sizeof(int));
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < nl && j < nr)
    {
        if (valuesL[i] <= valuesR[j])
        {
            result[k] = valuesL[i];
            i++;
        }
        else
        {
            result[k] = valuesR[j];
            j++;
        }
        k++;
    }

    if (k < nl + nr)
    {
        for (; i < nl; i++)
        {
            result[k] = valuesL[i];
            k++;
        }
        for (; j < nr; j++)
        {
            result[k] = valuesR[j];
            k++;
        }
    }

    return result;
}