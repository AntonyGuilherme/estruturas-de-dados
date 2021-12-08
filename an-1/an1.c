#include <stdio.h>

int diamantesEncontradas(int aberturas, int fechamentos){

    if(aberturas > fechamentos) return fechamentos;
    
    return aberturas;
}


int main()
{

    int quantidadeDeAnalise = 0, iteracoes = 0, aberturas = 0, fechamentos = 0;
    char mineracao[1000];
    int i = 0;
    
    scanf("%d", &quantidadeDeAnalise);

    while (iteracoes < quantidadeDeAnalise)
    {

        scanf("%s", mineracao);

        for (i = 0; mineracao[i] != '\0'; i++)
        {
            if (mineracao[i] == '>' && aberturas > 0) fechamentos++;
            else if (mineracao[i] == '<') aberturas++;
        }

        printf("%d\n",diamantesEncontradas(aberturas,fechamentos));
        
        aberturas = 0;
        fechamentos = 0;

        iteracoes++;
    }

    return 0;
}