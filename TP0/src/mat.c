//---------------------------------------------------------------------
// Arquivo	: mat.c
// Conteudo	: implementacao do TAD MAT
// Autor	: Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico	: 2021-10-18 - arquivo criado
//		: 2021-10-21 - estrutura de diretorios
//---------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// limite superior da inicializacao aleatoria
#define INITRANDOMRANGE 10
// Macro que realiza swap sem variavel auxiliar
#define ELEMSWAP(x, y) (x += y, y = x - y, x -= y)

mat_tipo *criarMatrizDeUmArquivo(char *nomeDoArquivo)
{

  // ler arquivo

  FILE *referenciaAoArquivo = fopen(nomeDoArquivo, "r");
  erroAssert(referenciaAoArquivo != NULL, "Arquivo não encontrado!");

  mat_tipo *matriz = malloc(sizeof(mat_tipo));

  fscanf(referenciaAoArquivo, "%d", &matriz->tamx);
  fscanf(referenciaAoArquivo, "%d", &matriz->tamy);

  criaMatriz(matriz, matriz->tamx, matriz->tamy);

  int resultadoDaLeitura = 0;

  for (int i = 0; i < matriz->tamx; i++)
  {

    for (int j = 0; j < matriz->tamy; j++)
    {

      resultadoDaLeitura = fscanf(referenciaAoArquivo, "%lf", &matriz->m[i][j]);

      erroAssert(
          resultadoDaLeitura != -1,
          "\nVerifique a(s) matrizes informadas! Elemento(s) Ausente(s).\n"
          );

      escreveMemLog((long int)(&(matriz->m[i][j])), sizeof(double));
    }
  }

  fclose(referenciaAoArquivo);

  return matriz;
};

void criaMatriz(mat_tipo *mat, int tx, int ty)
// Descricao: cria matriz com dimensoes tx X ty
// Entrada: mat, tx, ty
// Saida: mat
{
  // verifica se os valores de tx e ty são validos
  erroAssert(tx > 0, "Dimensao nula");
  erroAssert(ty > 0, "Dimensao nula");

  // inicializa as dimensoes da matriz
  mat->tamx = tx;
  mat->tamy = ty;

  // alocando a memória para o uso da matriz
  alocarDinamicamenteAMatriz(mat);
}

void alocarDinamicamenteAMatriz(mat_tipo *matriz)
{

  // alocando os vetores que irão receber as linhas da matriz
  // no formato
  /*
      # ... vetor a ser preenchido
      # ... vetor a ser preenchido
      # ... vetor a ser preenchido
    */
  matriz->m = malloc(matriz->tamx * sizeof(double *));

  // nesse as linhas são alocadas e assim temos:
  /*
      ####
      ####
      ####
    */
  for (int i = 0; i < matriz->tamx; i++)
  {
    matriz->m[i] = malloc(matriz->tamy * sizeof(double));
  }
}

void inicializaMatrizNula(mat_tipo *mat)
// Descricao: inicializa mat com valores nulos
// Entrada: mat
// Saida: mat
{
  int i, j;
  // inicializa todos os elementos da matriz com 0, por seguranca
  for (i = 0; i < mat->tamx; i++)
  {
    for (j = 0; j < mat->tamy; j++)
    {
      mat->m[i][j] = 0;
      escreveMemLog((long int)(&(mat->m[i][j])), sizeof(double));
    }
  }
}

void inicializaMatrizAleatoria(mat_tipo *mat)
// Descricao: inicializa mat com valores aleatorios
// Entrada: mat
// Saida: mat
{
  int i, j;
  // inicializa matriz com valores aletorios entre 0 e INITRANDOMRANGE
  for (i = 0; i < mat->tamx; i++)
  {
    for (j = 0; j < mat->tamy; j++)
    {
      mat->m[i][j] = drand48() * INITRANDOMRANGE;
      escreveMemLog((long int)(&(mat->m[i][j])), sizeof(double));
    }
  }
}

void imprimeMatriz(mat_tipo *mat)
// Descricao: imprime a matriz com a identificacao de linhas e colunas
// Entrada: mat
// Saida: impressao na saida padrao (stdout)
{
  int i, j;

  // imprime os identificadores de coluna
  printf("%9s", " ");
  for (j = 0; j < mat->tamy; j++)
    printf("%8d ", j);
  printf("\n");

  // imprime as linhas
  for (i = 0; i < mat->tamx; i++)
  {
    printf("%8d ", i);
    for (j = 0; j < mat->tamy; j++)
    {
      printf("%8.2f ", mat->m[i][j]);
      leMemLog((long int)(&(mat->m[i][j])), sizeof(double));
    }
    printf("\n");
  }
}

void criarArquivoDaMatriz(mat_tipo *mat, char *nomeDoArquvo)
{

  FILE *arquivo = fopen(nomeDoArquvo, "w");

  // insere a quantidade de linhas e colunas no arquivo
  fprintf(arquivo, "%d %d", mat->tamx, mat->tamy);

  // insere as linhas no arquivo
  for (int i = 0; i < mat->tamx; i++)
  {
    // quebrando a linha
    fprintf(arquivo, "\n");

    for (int j = 0; j < mat->tamy; j++)
    {
      fprintf(arquivo, "%.2f ", mat->m[i][j]);
      leMemLog((long int)(&(mat->m[i][j])), sizeof(double));
    }
  }

  fclose(arquivo);
}

void escreveElemento(mat_tipo *mat, int x, int y, double v)
// Descricao: atribui o valor v ao elemento (x,y) de mat
// Entrada: mat, x, y, v
// Saida: mat
{
  // verifica se x e y sao validos
  erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
  erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

  mat->m[x][y] = v;
  escreveMemLog((long int)(&(mat->m[x][y])), sizeof(double));
}

double leElemento(mat_tipo *mat, int x, int y)
// Descricao: retorna o elemento (x,y) de mat
// Entrada: mat, x, y
// Saida: mat[x][y]
{
  // verifica se x e y sao validos
  erroAssert((x < 0) || (x >= mat->tamx), "Indice invalido");
  erroAssert((y < 0) || (y >= mat->tamy), "Indice invalido");

  leMemLog((long int)(&(mat->m[x][y])), sizeof(double));
  return mat->m[x][y];
}

void copiaMatriz(mat_tipo *src, mat_tipo *dst)
// Descricao: faz uma copia de src em dst
// Entrada: src
// Saida: dst
{
  int i, j;

  // cria novamente a matriz dst para ajustar as suas dimensoes
  criaMatriz(dst, src->tamx, src->tamy);
  // inicializa a matriz dst como nula
  inicializaMatrizNula(dst);
  // copia os elementos da matriz src
  for (i = 0; i < src->tamx; i++)
  {
    for (j = 0; j < src->tamy; j++)
    {
      dst->m[i][j] = src->m[i][j];
      leMemLog((long int)(&(src->m[i][j])), sizeof(double));
      escreveMemLog((long int)(&(dst->m[i][j])), sizeof(double));
    }
  }
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: soma as matrizes a e b e armazena o resultado em c
// Entrada: a, b
// Saida: c
{
  int i, j;
  // verifica se as dimensoes das matrizes a e b sao as mesmas
  erroAssert(a->tamx == b->tamx, "Dimensoes incompativeis");
  erroAssert(a->tamy == b->tamy, "Dimensoes incompativeis");

  // inicializa a matriz c garantindo a compatibilidade das dimensoes
  criaMatriz(c, a->tamx, a->tamy);
  inicializaMatrizNula(c);

  // faz a soma elemento a elemento
  for (i = 0; i < a->tamx; i++)
  {
    for (j = 0; j < a->tamy; j++)
    {
      c->m[i][j] = a->m[i][j] + b->m[i][j];
      leMemLog((long int)(&(a->m[i][j])), sizeof(double));
      leMemLog((long int)(&(b->m[i][j])), sizeof(double));
      escreveMemLog((long int)(&(c->m[i][j])), sizeof(double));
    }
  }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c)
// Descricao: multiplica as matrizes a e b e armazena o resultado em c
// Entrada: a,b
// Saida: c
{
  int i, j, k;
  // verifica a compatibilidade das dimensoes
  erroAssert(a->tamy == b->tamx, "Dimensoes incompativeis");

  // cria e inicializa a matriz c
  criaMatriz(c, a->tamx, b->tamy);
  inicializaMatrizNula(c);

  // realiza a multiplicacao de matrizes
  for (i = 0; i < c->tamx; i++)
  {
    for (j = 0; j < c->tamy; j++)
    {
      for (k = 0; k < a->tamy; k++)
      {
        c->m[i][j] += a->m[i][k] * b->m[k][j];
        leMemLog((long int)(&(a->m[i][k])), sizeof(double));
        leMemLog((long int)(&(b->m[k][j])), sizeof(double));
        escreveMemLog((long int)(&(c->m[i][j])), sizeof(double));
      }
    }
  }
}

void transpoeMatriz(mat_tipo *a)
// Descricao: transpoe a matriz a
// Entrada: a
// Saida: a
{
  int i, j;

  // alocar a memória para a transposta da matriz

  mat_tipo transposta_de_a;
  transposta_de_a.tamx = a->tamy;
  transposta_de_a.tamy = a->tamy;

  alocarDinamicamenteAMatriz(&transposta_de_a);

  // faz a transposicao como se a matriz fosse quadrada
  for (i = 0; i < a->tamx; i++)
  {
    for (j = 0; j < a->tamy; j++)
    {

      transposta_de_a.m[j][i] = a->m[i][j];

      escreveMemLog((long int)(&(a->m[i][j])), sizeof(double));
      escreveMemLog((long int)(&(transposta_de_a.m[j][i])), sizeof(double));
    }
  }

  // desalocando a matriz para substitui-la pela transposta
  desalocarAMatriz(a->m, a->tamx);

  a->m = transposta_de_a.m;

  // ajustando as novas dimensoes
  ELEMSWAP(a->tamx, a->tamy);
}

void destroiMatrizes(mat_tipo **matrizes, int numeroDeMatrizes)
{

  for (int i = 0; i < numeroDeMatrizes; i++)
  {
    destroiMatriz(matrizes[i]);
  }
}

void destroiMatriz(mat_tipo *a)
// Descricao: destroi a matriz a, que se torna inacessível
// Entrada: a
// Saida: a
{
  //um erro é lançado se a matriz for destruida mais de uma vez
  erroAssert(a != NULL, "A Matriz já foi destruida");

  desalocarAMatriz(a->m, a->tamx);

  //liberando a matriz como um todo
  free(a);

  //desabilitando a matriz
  a = NULL;
}

void desalocarAMatriz(double **matriz, int tamx)
{

  //desalocando linha por linha da matriz
  for (int i = 0; i < tamx; i++)
  {
    free(matriz[i]);
  }

  // desalocando o vetor que continhas as linhas
  free(matriz);
}
