#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#$(EXE) -s -p /tmp/somalog.out -l -x 4 -y 5
#	$(EXE) -m -p /tmp/multlog.out -l -x 5 -y 5
# $(EXE) -t -p /tmp/transplog.out -l -x 5 -y 4
# $(EXE) -t -p transplog.out -1 matriz_100.txt -o response.txt
#	$(EXE) -s -p somalog.out -1 matriz_100.txt -2 matriz_100.txt -o response.txt
#---------------------------------------------------------------------

CC = gcc
CFLAGS = -Wall -c
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/matop

all: $(EXE)
	$(EXE) -t -p transplog.out -1 matriz.txt -o response-t.txt
	$(EXE) -m -p multlog.out -1 matriz.txt -2 matriz.txt -o response-m.txt
	$(EXE) -s -p somalog.out -1 matriz.txt -2 matriz.txt -o response-s.txt

	
$(BIN)/matop: $(OBJS)
	$(CC) -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm $(EXE) $(OBJS) 
