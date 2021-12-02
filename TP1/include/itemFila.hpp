#ifndef ITEM_FILA_H
#define ITEM_FILA_H

template <class T>
class ItemFila
{

private:
    T * objeto;
    ItemFila<T> * proximo;
    ItemFila<T> * anterior;

public:
    ItemFila(T* objeto, ItemFila<T> * anterior = nullptr, ItemFila<T> * proximo = nullptr);
    void inserirProximo(ItemFila<T> * proximo);
    void inserirAnterior(ItemFila<T> * proximo);
    ItemFila<T> * getProximoItem();
    ItemFila<T> * getAnteriorItem();
    T * getValorDoObjetoArmazenado();
    ~ItemFila();

};

template<class T>
ItemFila<T>::ItemFila(T * objeto, ItemFila<T> * anterior, ItemFila<T> * proximo){

    this->objeto = objeto;
    this->proximo = proximo;
    this->anterior = anterior;
}

template<class T>
ItemFila<T> * ItemFila<T> ::getProximoItem(){

    return this->proximo;
}

template<class T>
ItemFila<T> * ItemFila<T> ::getAnteriorItem(){

    return this->anterior;
}

template<class T>
T * ItemFila<T>::getValorDoObjetoArmazenado(){
    
    return this->objeto;
}

template<class T>
void ItemFila<T>::inserirProximo(ItemFila<T> * proximo){

    this->proximo = proximo;
}

template<class T>
void ItemFila<T>::inserirAnterior(ItemFila<T> * anterior){
    
    this->anterior = anterior;
}

template<class T>
ItemFila<T>::~ItemFila(){

    delete this->objeto;
}



#endif