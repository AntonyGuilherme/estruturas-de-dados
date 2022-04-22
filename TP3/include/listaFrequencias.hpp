#ifndef LISTA_FREQUENCIA
#define LISTA_FREQUENCIA

#include <string>
#include <algorithm>
#include "Frequencia.hpp"
#include "lista.hpp"
#include "HashWD.hpp"

class ListaFrequencia
{

public:
    std::string GetChave()
    {

        return this->chave;
    };

    void InserirFrequencia(int idDoDocumento)
    {

        Frequencia *frequencia = GetFrequenciaByID(idDoDocumento);

        if (frequencia != nullptr)
        {

            frequencia->IncrementarFrequencia();
        }
        else
        {

            lista->inserir(new Frequencia(idDoDocumento, 1));
        };
    }

    Frequencia *GetFrequenciaByID(int idDoDocumento)
    {
        Item<Frequencia> *auxiliar = lista->getPrimeiroItem();
        while (auxiliar != nullptr && auxiliar->getValorDoObjetoArmazenado()->GetIdDoDocumento() != idDoDocumento)
        {
            auxiliar = auxiliar->getProximoItem();
        }

        if (auxiliar != nullptr)
            return auxiliar->getValorDoObjetoArmazenado();
        else
            return nullptr;
    };

    void PrintFrequencies(){

        Item<Frequencia> *auxiliar = lista->getPrimeiroItem();
        while (auxiliar != nullptr)
        {   
            std::cout << auxiliar->getValorDoObjetoArmazenado()->ToString() << std::endl;
            auxiliar = auxiliar->getProximoItem();
        }

    };

    void CalcularPesos(int numeroTotalDeDocumentos, HashWD * hash){

        Item<Frequencia> *auxiliar = lista->getPrimeiroItem();
        Frequencia * frequencia;
        while (auxiliar != nullptr)
        {   
            frequencia = auxiliar->getValorDoObjetoArmazenado();
            frequencia->CalcularPeso(numeroTotalDeDocumentos,lista->size());

            hash->Insere(new ItemWD(frequencia));
            auxiliar = auxiliar->getProximoItem();
        }

    };

    void CalcularSimilaridades(HashWD * hash, int *& idsDocumentos, int& tamanho){

        Item<Frequencia> *auxiliar = lista->getPrimeiroItem();
        Frequencia * frequencia;
        ItemWD * wd;

        while (auxiliar != nullptr)
        {   
            frequencia = auxiliar->getValorDoObjetoArmazenado();
            
            idsDocumentos[tamanho] = frequencia->GetIdDoDocumento();
            tamanho++;

            if(hash->Pesquisa(frequencia->GetIdDoDocumento(),wd)){
                wd->CalcularSimilaridade(frequencia);
            };

            auxiliar = auxiliar->getProximoItem();
        }
        
    };

    int GetSize(){

        return this->lista->size();
    };

    ListaFrequencia(std::string chave)
    {

        this->chave = chave;
        lista = new Lista<Frequencia>();
    };

private:
    Lista<Frequencia> *lista;
    std::string chave;
    int frequencia;
};

#endif