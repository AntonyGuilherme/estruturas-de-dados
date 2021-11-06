#include "iostream"
#include "teste.h"

// g++ -c main.cpp
// g++ -c teste.cpp
// g++ -o programa.out main.o teste.o
// mingw32-make

/* 
? estrutura das pastas que devem ser seguidas 
 ./bin - smpre vazia para o envio
 ./include - arquivos .h
 ./src - arquivos .cpp ou .c
 ./obj - deve ser enviada vazia

 Não usar bibliotecas específicas para windows

*/

int main(int argc , char** argv){
    
    Teste * teste = new Teste();

    for(int i = 1; i < argc ; i++){
        std::cout << "ARG " << argv[i] << std :: endl;    
    }

    std::cout << "TESTE" << std :: endl;

    delete teste;

    return 0;
}