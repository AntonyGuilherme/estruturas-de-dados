#ifndef ITEM_ESTRUTURA_H
#define ITEM_ESTRUTURA_H

template <class T>
class Item
{

private:
    T * objeto;
    Item<T> * proximo;
    Item<T> * anterior;

public:
    Item(T* objeto, Item<T> * anterior = nullptr, Item<T> * proximo = nullptr);
    void inserirProximo(Item<T> * proximo);
    void inserirAnterior(Item<T> * proximo);
    Item<T> * getProximoItem();
    Item<T> * getAnteriorItem();
    T * getValorDoObjetoArmazenado();
    ~Item();

};

template<class T>
Item<T>::Item(T * objeto, Item<T> * anterior, Item<T> * proximo){

    this->objeto = objeto;
    this->proximo = proximo;
    this->anterior = anterior;
}

template<class T>
Item<T> * Item<T> ::getProximoItem(){

    return this->proximo;
}

template<class T>
Item<T> * Item<T> ::getAnteriorItem(){

    return this->anterior;
}

template<class T>
T * Item<T>::getValorDoObjetoArmazenado(){
    
    return this->objeto;
}

template<class T>
void Item<T>::inserirProximo(Item<T> * proximo){

    this->proximo = proximo;
}

template<class T>
void Item<T>::inserirAnterior(Item<T> * anterior){
    
    this->anterior = anterior;
}

template<class T>
Item<T>::~Item(){

    delete this->objeto;
}



#endif