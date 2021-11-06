
/**
 * Ordena o vetor A em ordem ascendente
 * \FuncaoDeComplexadidade
 * Função de complexidade para o número de comparações : f(n) = n(n-1) <br>
 * Função de complexidade para o número de trocas : f(n) = (n-1)
 * \OrdemDeComplexidade = O(n^2)
 * @param A Vetor númerico
 * @param n Número de elementos do vetor
 */

void ordenar(int* A, int n){

    int  i,j,min,x;

    for(i = 0; i < n - 1; i++){

        min = i;

        for(j = i + 1; j < n; j++){

            if(A[j] < A[min]) { // somatório(k) => k = 1 -> n - 1  = n(n-1)/2
                min = j;
            }
        }

        // troca A[min] e A[i]
        // ( n - 1 )
        x = A[min];
        A[min] = A[i];
        A[i] = x;

    }

}
