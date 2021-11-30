#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

template <typename T>
class ArrayList
{

private:
    int tamanho;
    T** array;


public :
    ArrayList(int tamanho);
    int size();
    void inserir(int index , T*);
    T* operator[](int index);
    void remover(int index, int elementos = 1);
};


template<class T>
ArrayList<T>::ArrayList(int tamanho){
    
    this->tamanho = tamanho;
    this->array = new T*[tamanho];
}

template<class T>
int ArrayList<T>::size(){

    return this->tamanho;
}

template<class T>
T* ArrayList<T>::operator[](int index){

    if(index  >= this->size()){
        return nullptr;
    }

    return this->array[index];
}

template<class T>
void ArrayList<T>::inserir(int index,T * objeto){

    if(index < 0 || index >= this->size()){
        throw "Erro na inserção do elemento";
    }

    this->array[index] = objeto;
}

template<class T>
void ArrayList<T>::remover(int inicio , int elementos = 1){

    for(int index = 0 ; index < elementos ; index++){

        this->array[inicio+index] = this->array[(inicio+elementos)+index];

    }

}


#endif