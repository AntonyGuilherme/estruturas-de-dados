//
// Created by word2 on 28/10/2021.
//


/*
    A função de complexidade e definidade como uma função de n
     * para n 's pequenos não faz tanta diferença , f(n) = n; f(n) = n^2 ; f(n) = log (n)
     * è importante estudar o custo do algoritmo para valores grandes de n(n->infinito)
     * isso é chamado de comportamento assintótico das funções de custo

    Complexidade Assintótica
        * analisa-se o algoritmo quando o valor de n tende a infinito
        * não ´necessário se proucupar com as constantes e termos de menor crescimento

    Dominação Assintótica
        * f(n) = n^2 domina g(n) = n
        * As duas funções são assintoticamente equivalentes se
        * as duas se dominarem  ex : f(n) = n^2 e g(n) = (n+1)^2

    Notação Assintótica

    * Notação O (letra O)
        * especifica um limite superiror para g(n)
        * g(n) = O(f(n)) se f(n) domina assintoticamente g(n)

    Notação Ω
        * Especifica um limite inferior para g(n)
        * Definição : Uma função g(n) é Ω(f(n)) se existirem duas contanstes
        * c e m tais que : g(n) >= cf(n), para tod0 n >= m

    Notação Θ
        * Definição: Uma função g(n) é Θ(f(n)) se existirem constantes positivas
        * c1, c2 e m tais que : 0 <= c1f(n) <= g(n) <= c2f(n)
        * Para tod0 n>=m, a função g(n)  é igual a f(n) a menos de uma constante
        * Para o caso da função g(n) ser Θ(f(n)), f(n) é um limite assintótico firme

    Classes de Comportamento Assintótico
        * Quando dos algoritmos fazem parte da mesma classe
        * de comportamento assintótico eles são ditos equivalentes

    Principais Classes de Algoritmos
        * f(n) = O(1) : complexidade constante
            * Uso do algoritmo independe de n
            * As instruções do algoritmo são executadas um
            * número fixo de vezes
        * f(n) = O(log n) : COmplexidade logarítmica
            * Típic em algoritmos que transformam um problema em outros menores
        * f(n) = O(n) Complexidade linear
            * Em geral, um pequeno trabalho é realizzado sobre
            * cada elemento de entrada
            * Cada vez que n dobra de tamanho, o tempo de execução dobra
        * f(n) = O(nlog(n))
            * Típico em algoritmos que quebram um problema em outros menores,
            * resolvem cada um deles independentemente e juntando as soluções depois;
        * f(n) = O(n^2) : COmplexidade quandrática
           * Ocorrem quando os itens de dados são processados aos pares, muitas
           * vezes um anel dentro do outro
        * f(n) = O(n^3): Complexidade cúbica
            * Úteis apenas para resolver problemas pequenos.
        * f(n) = O(2^n) : Complexidade exponencial
            * Geralmente não são úteis sob o ponto de vista prático (força bruta)
        * f(n) = O(n!)
            * Um algoritmode complexidade O(n!) é dito ter complexidade
            * exponencial, apesar de O(n!) ter comportamento muito pior do que O(2^n)

        * Algoritmo exponencial no tempo de execução tem ordem de complexidade
        * maior que O(c^n); c > 1
            * são geralmente simples variações de pesquisa exaustiva.

        * Algoritmo polinomial no tempo de execução tem ordem de complexidade
        * O(p(n)), onde p(n) é um polinômio
            *  são geralmente obtidos mediante entendimento mais profundo da
            *  estrutura do problema

        * Limite Inferior
            * Dado um modelo de computação que expresse o comportamento do algoritmo,
            * o oráculo informa o resultado de cada passo possível
            * O oráculo procura sempre fazer com que o algoritmo trabalhe o máximo,
            * escolhendo como resultado da próxima comparação aquele que cause o
            * maior trabalho possível necessário para determinar a resposta final.
 */


void func(int *v, int n){

    int i, j, sum = 0;

    for(i = 0; i < n ;i++){ // n = O(n)
        sum += v[i];
    }

    for(i = 1; i < n; i++){ // n - 1 = O(n)
        for(j = 1; j < n; j++){ // n -1 = O(n)
            sum += v[i];
        }
    }

     // f(n) =  n + (n-1)^2
     // f(n) = O(n) + O(n^2) = O(n^2)


}


