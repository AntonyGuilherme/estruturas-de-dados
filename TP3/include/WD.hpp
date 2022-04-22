#ifndef WD
#define WD

#include <math.h>
#include "Frequencia.hpp"
#include <iostream>
class ItemWD
{

public:
    ItemWD(Frequencia * frequencia)
    {
        this->chave = frequencia->GetIdDoDocumento();
        this->wd = std::pow(frequencia->GetPeso(),2);
    };

    int GetChave()
    {
        return this->chave;
    };

    void Insere(ItemWD * wd){

        this->wd += wd->Get();
    };

    double Get()
    {
        return this->wd;
    };

    double GetRaiz(){

        return std::sqrt(this->wd);
    };

    void CalcularSimilaridade(Frequencia * frequencia){

        this->similaridade += (double) (frequencia->GetPeso() / this->GetRaiz());
       
    };

    double GetSimilaridade(){

        return this->similaridade;
    };

private:
    double similaridade = 0.0;
    double wd;
    int chave;
};

#endif
