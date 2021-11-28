#include "iostream"


/*

    * Recursividade
        ?Definição : 
            Um procedimento que chama a si mesmo é dito recursivo.
        ?Vantagem: 
            Recursividade permite descrever algortmos de forma mais clara e concisa,
        especialmente problemas recursivos por natureza ou que utilizam estruturas recursivas.

    * Execução de Algoritmos Recursivos
        Internamente, quando qualquer chamada de função é feita dentro
     de um programa, é criado um registro de ativação na Pilha de Execução
     do programa.
        O registro de ativação armazena os parâmetros e variáveis locais da função bem
     como o "ponto de retorno" no programa ou subprograma que chamou essa função.
        Quando vale a pena usar recursividade ?      
            Algoritmos complexos, cuja a implmentação iterativa é complexa e 
        normalmente requer o uso explícito de uma pilha;
*/



// exemplos
// A condição de parada é fundamental para evitar a execução de loops infinitos
int Fat(int n){

    if(n == 0){ // condição de parada
        return 1;
    }

    else { // chamada recursiva
        return n * Fat(n-1);
    }

}


int main(){

    int fatorialDe5 = Fat(5);

    std :: cout << " Fatorial " << fatorialDe5;

    return 0;

}





