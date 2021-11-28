#include "iostream"

/*
    ? Teorema Mestre
    ? T(n) = aT(n/b) + f(n)
    ? onde a >= 1, b > 1 e f(n) positiva
    * Este tipo de recorrencia é típico de algoritmos "dividir para conquistar"
    * Cada subproblema tem tamanho n/b 
    * Cada chamada realiza um trabalho de custo f(n)
    * O caso base, normalmente omitido, tem um custo constante para um valor de n pequeno T(n) = c, n < k
    * Compara-se a função f(n) com o termo ( n ^ log[ a (base b) ] = X )
    * * Caso 1 : se f(n) = O(X) => T(n) = 0(X)
    * * Caso 2 : se f(n) = 0(X) => T(n) = 0(X.log(n))
    * * Caso 3 : se f(n) = ômega(X) => T(n) = 0(f(n))
    * * * Também de ve satisfazer no caso 3 a condição de regularidade af(n/b) <= cf(n), c < 1 , n >n0

    Exemplo

    T(n) = 2 T(n/2) + 1 , n > 1
    T(n) = 0 , n <= 1

    a = 2 , b = 2 f(n) = 1

    X = n ^ 1

    f(n) = O(n ^( 1 - k)) , k definido como 1
    f(n) = 1 = O(1)

    Caso 1 
    T(n) = 0(n ^ X)
    T(n) = 0(n)

    T(n) = 9T(n/3) + n
    a = 9 , b = 3 , f (n) = n
    X = n ^2
    f(n) < n ^2
    f(n) = O(n) , k = 1
    T(n) = O(n^2)

    T(n) = 3T(n/4) + n log n
    a = 3 , b = 4, f(n) = nlog(n)
    f(n) = omega(X) = omega(n) , k = 0.207
    T(n) = 0(f(n)) = 0(n.log(n))

    T(n) = 2T(n/2) + n - 1
    a = 2 , b = 2 , f(n) = n - 1
    X = n 
    f(n) = 0(n)
    Caso 2:
    T(n) = 0(n . log(n))

    T(n) = 3T(n/3) + n.log(n)
    a = 3, b = 3 , X = n
    f(n) = n log n, não se pode usar o teorema mestre pois a equação é logariticamente maior. 


*/




int main(){

    return 0;
}