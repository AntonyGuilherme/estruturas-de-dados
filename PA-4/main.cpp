#include <iostream>


struct Tecla{
    int tecla;
    double oleosidade;
};

void ordenacaoBolha(Tecla *v, int n)
{

    bool isOrdenado = true;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n - i; j++)
        {

            if (v[j].oleosidade > v[j - 1].oleosidade)
            {
                // 3 movimentações
                Tecla c = v[j];
                v[j] = v[j - 1];
                v[j - 1] = c;

                isOrdenado = false;
            }

        }

        if (isOrdenado)
            break;
    }
}

void imprimirSenha(Tecla* teclas, int tamanhoDaSenha, int numeroDoCaso){

    std::cout << "Caso " << numeroDoCaso << ": ";

    for(int i = 0; i < tamanhoDaSenha; i++ ){
        std::cout << teclas[i].tecla;
    }

}


int main(){

    int numeroDoCaso = 1;
    Tecla teclas[10];
    int tamanhoDaSenha = 0;

    while(std::cin >> tamanhoDaSenha){

        for(int i =0; i < 10; i ++){
            teclas[i].tecla = i;
            std::cin >> teclas[i].oleosidade;
        }

        ordenacaoBolha(teclas,10);
        imprimirSenha(teclas,tamanhoDaSenha,numeroDoCaso); 
        numeroDoCaso++;   
    }
    


    return 0;
}


