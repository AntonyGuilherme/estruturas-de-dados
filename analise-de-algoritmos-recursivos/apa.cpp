#include <iostream>
#include <math.h>

using namespace std;

const std::string GRITO_DO_CORVO = "caw caw";
const char PISCADA_DO_CORVO = '*';
const char OLHO_FECHADO_DO_CORVO = '-';

bool isGritoDoCorvo(char * conteudoDaLinha);
bool isAcaoDoOlhoDoCorvo(char acao);
int converAcaoDoOlhoDoCorvo(char acao);
int converterValorDosOlhos(char *acoes);

int main()
{

    char conteudoDaLinha[50];
    int numeroDaLoteria = 0;
    int numerosInformadosPeloCorvo = 1;

    while (cin.getline(conteudoDaLinha, 20))
    {
        

        if (isAcaoDoOlhoDoCorvo(conteudoDaLinha[0]))
        {
            numeroDaLoteria += converterValorDosOlhos(conteudoDaLinha);
            continue;
        }

        else if (!GRITO_DO_CORVO.compare(conteudoDaLinha))
        {

            cout << numeroDaLoteria << endl;
            numeroDaLoteria = 0;
            numerosInformadosPeloCorvo++;

            if(numerosInformadosPeloCorvo > 3)
                break;

            continue;
        }

        break;
    }

    return 0;
}



bool isAcaoDoOlhoDoCorvo(char acao)
{
    return OLHO_FECHADO_DO_CORVO == acao || PISCADA_DO_CORVO == acao;
}

int converterValorDosOlhos(char *acoes)
{

    int valorDosOlhos = 0;

    for (int i = 2; i >= 0; i--)
    {
        if (converAcaoDoOlhoDoCorvo(acoes[i]) == 1)
            valorDosOlhos += (int)std::pow(2, 2 - i);
    }

    return valorDosOlhos;
}

int converAcaoDoOlhoDoCorvo(char acao)
{

    if (acao == PISCADA_DO_CORVO)
        return 1;

    return 0;
}

bool isGritoDoCorvo(char * conteudoDaLinha){

    return !GRITO_DO_CORVO.compare(conteudoDaLinha);
}