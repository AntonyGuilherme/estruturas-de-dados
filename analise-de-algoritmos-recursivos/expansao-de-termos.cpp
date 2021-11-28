#include "iostream"

/*
  
    ?Expansão de Termos
    - A partir da recorrência, expanda os termos 
    obtendo termos com entradas menores.
    - Repita o processo até chegar no caso base.
    - Substitua os valores com os termos de entradas
    menores já computadas.
    - Some os custos de todos os termos
    - Calcule a fórmula fechada do somatório.
  
 */

int FatRecursivo(int n){

    if(n == 0){ // condição de parada
        return 1;
    }

    else { // chamada recursiva
        return n * FatRecursivo(n-1);
    }

    /*
    ? Equção de recorrência 
    T(n) =  1 + T(n-1); para n > 0
    T(n) = 0; para n <= 0; 

    T(n) = T(n-1) + c
    T(n-1) = T(n-2) + c
    . . . 
    T(1) =  T(0) + c
    T(0) = d;

    Realizando as substituições temos : 
    T(n) = c + c + c + .... c + d
    temos n c's e um d
    T(n) = c.n + d

    */

}

/*

    Exemplo :
    T(n) = n-1 + T(n-1)
    T(n - 1) = n - 2 + T( n-2 )
    T( n - 2 ) = n - 3 + T( n - 3)
    .   .   .
    T(2) =  1 + T(1)
    T(1) = 0 
    T(0) = 0

    0 1 2 3 .. n-1
    
    O(n) =  n(n-1)/2
    

*/






int main()
{

    return 0;
}
