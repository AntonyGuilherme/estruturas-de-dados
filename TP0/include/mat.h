//---------------------------------------------------------------------
// Arquivo	: mat.h
// Conteudo	: definicoes do TAD MAT
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//---------------------------------------------------------------------

#ifndef MATH
#define MATH

#include "memlog.h"

// todo remover o tamanho fixo double **m;
#define MAXTAM 10

typedef struct mat
{
	double **m;
	int tamx, tamy;
} mat_tipo;

void criaMatriz(mat_tipo *mat, int tx, int ty);
void inicializaMatrizNula(mat_tipo *mat);
void inicializaMatrizAleatoria(mat_tipo *mat);
void alocarDinamicamenteAMatriz(mat_tipo *matriz);
void imprimeMatriz(mat_tipo *mat);
void criarArquivoDaMatriz(mat_tipo *mat, char * nomeDoArquivo);
void escreveElemento(mat_tipo *mat, int x, int y, double v);
double leElemento(mat_tipo *mat, int x, int y);
void copiaMatriz(mat_tipo *src, mat_tipo *dst);
void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c);
void transpoeMatriz(mat_tipo *a);
void destroiMatrizes(mat_tipo ** matrizes, int numeroDeMatrizes);
void destroiMatriz(mat_tipo *a);
void desalocarAMatriz(double **matriz, int tamy);

// ler arquivos
mat_tipo * criarMatrizDeUmArquivo(char *nomeDoArquivo);

#endif
