#ifndef FREQUENCIA
#define FREQUENCIA

#include <string>
#include <math.h>

class Frequencia
{

public:
    Frequencia(int idDoDocumento, int quantidadeDeVezes)
    {

        this->idDocumento = idDoDocumento;
        this->quantidadeDeVezes = quantidadeDeVezes;
    };

    int GetFrequencia()
    {

        return this->quantidadeDeVezes;
    };

    int GetIdDoDocumento()
    {

        return this->idDocumento;
    };

    std::string ToString()
    {

        return "( " + std::to_string(this->idDocumento) + " , " + std::to_string(this->quantidadeDeVezes) + " )";
    };

    void IncrementarFrequencia()
    {
        this->quantidadeDeVezes += 1;
    }

    void CalcularPeso(int numeroTotalDeDocumentos,int numeroDeDocumentosEmQueOTermoAparece){

        peso = this->quantidadeDeVezes * std::log(double (numeroTotalDeDocumentos/numeroDeDocumentosEmQueOTermoAparece));
    };

    double GetPeso(){

        return this->peso;
    };

private:
    int quantidadeDeVezes = 0;
    int idDocumento = 0;
    double peso = 0.0;
};

#endif