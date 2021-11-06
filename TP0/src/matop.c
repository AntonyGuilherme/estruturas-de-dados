//---------------------------------------------------------------------
// Arquivo      : matop.c
// Conteudo     : programa de avaliacao do TAD MAT
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2021-10-18 - arquivo criado
//              : 2021-10-21 - estrutura de diretorios
//              : 2021-10-25 - opcoes de linha de comando
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "mat.h"
#include "memlog.h"
#include "msgassert.h"

// definicoes de operacoes a serem testadas
#define OPSOMAR 1
#define OPMULTIPLICAR 2
#define OPTRANSPOR 3

// variaveis globais para opcoes
static int opescolhida;
char lognome[100];
char arquivo_da_matriz_1[50], arquivo_da_matriz_2[50];
int optx, opty, regmem;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr, "matop\n");
  fprintf(stderr, "\t-s \t(somar matrizes) \n");
  fprintf(stderr, "\t-m \t(multiplicar matrizes) \n");
  fprintf(stderr, "\t-t \t(transpor matriz)\n");
  fprintf(stderr, "\t-p <arq>\t(arquivo de registro de acesso)\n");
  fprintf(stderr, "\t-l \t(registrar acessos a memoria)\n");
  fprintf(stderr, "\t-x <int>\t(primeira dimensao)\n");
  fprintf(stderr, "\t-y <int>\t(segunda dimensao)\n");
}

void parse_args(int argc, char **argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, lognome
{
  // variaveis externas do getopt
  extern char *optarg;
  extern int optind;

  // variavel auxiliar
  int c;

  // inicializacao variaveis globais para opcoes
  opescolhida = -1;
  optx = -1;
  opty = -1;
  regmem = 0;
  lognome[0] = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "smtp:1:2:lh")) != EOF)
    switch (c)
    {
    case 'm':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPMULTIPLICAR;
      break;
    case 's':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPSOMAR;
      break;
    case 't':
      avisoAssert(opescolhida == -1, "Mais de uma operacao escolhida");
      opescolhida = OPTRANSPOR;
      break;
    case 'p':
      strcpy(lognome, optarg);
      break;
    case '1':
      strcpy(arquivo_da_matriz_1, optarg);
      break;
    case '2':
      strcpy(arquivo_da_matriz_2, optarg);
      break;
    case 'l':
      regmem = 1;
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }
  // verificacao da consistencia das opcoes
  erroAssert(opescolhida > 0, "matop - necessario escolher operacao");
  erroAssert(strlen(lognome) > 0,"matop - nome de arquivo de registro de acesso tem que ser definido");

}

void opcaoDeSoma()
{

  // cria matrizes a e b a partir de arquivos, que sao somadas para a matriz c
  // matriz c é impressa e todas as matrizes sao destruidas

  // lendo e declarando as matrizes
  mat_tipo *a = criarMatrizDeUmArquivo(arquivo_da_matriz_1);
  mat_tipo *b = criarMatrizDeUmArquivo(arquivo_da_matriz_1);

  mat_tipo *c = malloc(sizeof(mat_tipo));
  criaMatriz(c, a->tamx,a->tamy);

  // criando vetor para desalocação de memória futura
  mat_tipo *matrizes[] = {a, b, c};

  somaMatrizes(a, b, c);
  imprimeMatriz(c);
  destroiMatrizes(matrizes,3);

}

void opcaoDeMultiplicacao(){

    // cria matrizes a e b aleatorias, que sao multiplicadas para matriz c
    // matriz c é impressa e todas as matrizes sao destruidas

    // lendo as matrizes
    mat_tipo *a = criarMatrizDeUmArquivo(arquivo_da_matriz_1);
    mat_tipo *b = criarMatrizDeUmArquivo(arquivo_da_matriz_1);

    mat_tipo *c = malloc(sizeof(mat_tipo));
    criaMatriz(c, a->tamx, b->tamy);
    
    mat_tipo *matrizes[] = {a, b, c};

    multiplicaMatrizes(a, b, c);
    imprimeMatriz(c);
    destroiMatrizes(matrizes,3);

}

void opcaoDeTransposicao(){

    // cria matriz a partir de um arquivo, que e transposta, impressa e destruida
    mat_tipo * a = criarMatrizDeUmArquivo(arquivo_da_matriz_1);

    transpoeMatriz(a);
    imprimeMatriz(a);
    destroiMatriz(a);

}

int main(int argc, char **argv)
// Descricao: programa principal para execucao de operacoes de matrizes
// Entrada: argc e argv
// Saida: depende da operacao escolhida
{

  // ate 3 matrizes sao utilizadas, dependendo da operacao
  //mat_tipo *a, *b, *c;

  // avaliar linha de comando
  parse_args(argc, argv);

  // iniciar registro de acesso
  iniciaMemLog(lognome);

  // ativar registro de acesso
  ativaMemLog();

  // execucao dependente da operacao escolhida
  switch (opescolhida)
  {

  case OPSOMAR:
    opcaoDeSoma();
    break;

  case OPMULTIPLICAR:
    opcaoDeMultiplicacao();
    break;
  
  case OPTRANSPOR:
    opcaoDeTransposicao();
    break;

  default:
    // nao deve ser executado, pois ha um erroAssert em parse_args
    uso();
    exit(1);
  }

  // conclui registro de acesso
  return finalizaMemLog();
}
