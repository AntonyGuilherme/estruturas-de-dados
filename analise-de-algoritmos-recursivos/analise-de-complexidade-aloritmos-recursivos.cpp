#include "iostream"


/*

        Na análise de complexidade, para cada procedimento é 
    associada uma função de complexidade f(n) desconhecida, onde n
    normalmente é relacionado com o tamanho da entrada do procedimento.
        Por se tratar de um algoritmo recursivo, f(n)
    vai ser obtida através de uma equação de recorrência.

    ? Equação de recorrência
            Maneira de definir um função por uma expressão envolvendo
        a mesma função com entradas menores.
            Uma equação de recorrência tem duas partes
             ** Caso base : no qual a equação tem uma solução para
            um determinado valor de entrada.
            ** Recorrência: no qual a solução da equação para uma entrada n é
            expressa em função da solução para valores menores




*/


int Fat(int n){

    if(n == 0){ // condição de parada
        return 1;
    }

    else { // chamada recursiva
        return n * Fat(n-1);
    }

    /*
    ? Equção de recorrência 
    T(n) =  1 + T(n-1); para n > 0
    T(n) = 0; para n <= 0; 
    */

}


int Fib(int n){

    if(n <= 2){
        return 1;
    }
    else{
        return Fib(n-1) + Fib(n-2);
    }

    /*
    
    T(n) = d , para n <= 2;
    T(n) = T(n-1) + T(n-2) + c; para n > 2
    
    */

}


int main(){


    return 0;
}