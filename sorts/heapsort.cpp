#include <iostream>

/*
? Heap => fila de prioridade 
 Definição :
    Estrutura de dados composta de itens, cuja chave reflete 
    a prioridade com que se deve tratar aquele item.
    Suporta duas operações principais : inserção de um novo item e 
    remoção do item com a maior chave
 Heap : Lista de prioridade utilizando uma árvore binária
 Representação vetorial para a árvore do Heap
 Nós são numerados de 1 a n
 * O primeiro é chamado raiz
 * Os nós 2k e (2k+1) são filhos da esquerda e direita do nó k, para 1 <= k <= n/2
 * O nó k/2 é o pai do nó k, 1 < k <= n 
 * Representação por mkeio de vetores é compacta
 * Permite caminhar pelos nós da árvore facilmente
 ! Filhos de um nó i estão nas posições 2i e 2i +1 
 ! O pai de um nó i está na posição i/2
 ! A maior chave está na posição 1
    ? Condição para ser heap : Nó pai deve ser maior que seus filhos 
*/

struct Item
{
    int Chave;
};

void Refaz(int Esq, int Dir, Item *A)
{

    int i, j;
    Item x;
    i = Esq;
    j = i * 2;
    x = A[i];

    while (j <= Dir)
    {

        if (j < Dir)
        {
            if (A[j].Chave < A[j + 1].Chave)
                j++;
        }

        if (x.Chave >= A[j].Chave) break;
        
        A[i] = A[j];

        i = j;
        j = i * 2;
    }

    A[i] = x;
}

Item RetiraMax(Item *A, int *n)
{
    Item Maximo;

    if (*n < 1)
    {
        std::cout << "Erro: heap vazio";
    }

    else
    {
        Maximo = A[1];
        A[1] = A[*n];
        (*n)--;
        Refaz(1, *n, A);
    }

    return Maximo;
}

void Constroi(Item *A, int n)
{

    int esq = n / 2 + 1; // verificando as folhas

    while (esq > 1)
    {
        esq--;
        Refaz(esq, n, A);
    }
}

void Heapsort(Item *A, int *n)
{

    int Esq, Dir;
    Item x;
    Constroi(A, *n);
    Esq = 1;
    Dir = *n;

    while (Dir > 1)
    {
        x = A[1];
        A[1] = A[Dir];
        A[Dir] = x;
        Dir--;
        Refaz(Esq, Dir, A);
    }
}

// método não estável
/*

    Refaz : C(n) = O(log n) - uma altura da árvore
    Constroi : C(n) = O(n log n)
    Heapsort : C(n) = O(n log n)

*/

int main()
{

    Item vetor[4] = {{},{1}, {2}, {3}};
    Constroi(vetor,3);
    int n = 3;
    for(int i = 0; i < 3 ; i++){
        n = 3 -i;
        std::cout << RetiraMax(vetor, &n).Chave << std::endl;
    }
    return 0;
}