#include <iostream>

/*
 * Problema: encontrar o maior e o menor elemento de um vetor de inteiros A[n]; n > 1
 */


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


// melhor caso == médio == pior == f(n) = 2 * (n-1);

void maxMin1(int *A , int n, int * Max, int *Min){

    int i;

    *Max = A[0]; *Min = A[0];

    for(i = 1; i < n ; i++){
        if(A[i] > *Max) *Max = A[i];
        if(A[i] < *Min) *Min = A[i];
    }



    std::cout << "Maximo " << *Max << " Minimo " << *Min;
}


// melhor caso elementos em ordem crescente f(n) = n -1
// pior caso Quando o maior elemento é o primeiro elemento do vetor f(n) = 2 * ( n - 1 );
// no caso médio, considerando que A[i] é maior do que Max a metade das vezes => f(n) = (3/2) * (n - 1)

void maxMin2(int *A , int n, int * Max, int *Min){

    int i;

    *Max = A[0]; *Min = A[0];

    for(i = 1; i < n ; i++){
        if(A[i] > *Max) *Max = A[i];
        else if(A[i] < *Min) *Min = A[i];
    }

    std::cout << "Maximo " << *Max << " Minimo " << *Min;
}






