#include <iostream>

struct Pai
{
    int inicio;
    int fim;
    int item;
};

struct No {
    int item;
    int pai;
};

int leitura(char &parenteses)
{

    int numeroDeLeitura = EOF;
    while ((numeroDeLeitura = scanf("%c", &parenteses)) >= 1 && parenteses == ' ')
        ;

    return numeroDeLeitura;
}

void adicionarFilhos(No *itens, Pai &pai, Pai *pais, int &quantidade, No& abertura)
{
    int numeroLido = 0;
    char parenteses;

    if (scanf("%d", &numeroLido) >= 1)
    {
        itens[quantidade].item = numeroLido;
        pais[numeroLido].fim = -1;
        pais[numeroLido].inicio = -1;
        pais[numeroLido].item = numeroLido;

        pai.fim = quantidade;

        quantidade++;
        
        adicionarFilhos(itens, pai, pais, quantidade, abertura);
    }

    else if (leitura(parenteses) >= 1)
    {

        if (parenteses == '(')
        {

            int index = itens[quantidade - 1].item;
            pais[index].inicio = quantidade;
            pais[index].fim = quantidade;

            adicionarFilhos(itens, pais[index], pais, quantidade,abertura);
        }
        
        else{

           // adicionarFilhos(itens, pais[index], pais, quantidade,abertura);

        }


    
        // parentes == ")"
        return;
    }
}



void adicionarFilhosLoop(No *itens, Pai &pai, Pai *pais, int &quantidade)
{
    bool fazerLeitura = true;
    int numeroLido = 0;
    char parenteses = ' ' ;

        while(fazerLeitura){

            if(scanf("%d", &numeroLido) >= 1){

                itens[quantidade].item = numeroLido;

            }


            


        }

}

int main()
{

    No itens[50];
    Pai pais[50];

    int numeroLido = 0;
    char parenteses;
    bool isNotFimDoArquivo = true;

    itens[0].item = 0;
    pais[0].inicio = 0;
    pais[0].fim = 0;
    int quantidade = 1;

   // adicionarFilhos(itens, pais[0], pais, quantidade);
    
    for(int i = 0; i < quantidade ; i++){
        printf("%d filhos %d a %d\n",itens[i], pais[itens[i].item].inicio, pais[itens[i].item].fim);
    }

    return 0;
}