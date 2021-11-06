
#include "iostream"

/*

 * Análise do Tempo de Execução
 * * Coando de atribuição, de leitura ou de escrita : O(1)
 * * Comando de decisão
 * * * Tempo dos comandos dentro do condicional, mais tempo para avaliar a condição que
 * * * em geral é O(1)
 * * Comando Laço
 * * * Inicialização + número de iterações * (
 * * * tempo de avaliar a condição de parada +
 * * * tempo de execução do corpo do laço +
 * * * tempo para incrementar o contador )
 * * Sequência de comandos
 * * * Determinado pelo maior tempo de execução de quaquer comando da sequencia

 */

// Exemplo

void FazAlgo(int n){

    // Melhor caso O(1)
    // Pior Caso O(n^2)

    int x, i, j;

    std::scanf("%d",&x); // O(1)

    if(x < 10) // O(1)
        return; // O(1)
    else{
        // O(n ^2)
        for (i =0; i < n; i++){ // executado n vezes
            j = 0;
            while(j < n){ // O(n)
                x++;
                j++;
            }
        }
    }
}


int Exemplo1(int n){

    // Pior Caso : O(n^2)
    // Melhor Caso : O(n)

    int i , a;
    a =0 ; // O(1)

    for(i =0 ; i < n; i++){ // O(n)
       a += i; // O(1)
    }

    FazAlgo(n); // O(n^2)

    return a; // O(1)
}




int main(){
    return 0;
}

