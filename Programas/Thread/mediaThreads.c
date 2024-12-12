/**
 * Programa para ilustrar a utilizacao de multiplos threads para trabalhar em um  
 * unico vetor compartilhado entre as threads. Cada thread calcula a soma parcial 
 * de um conjunto de elementos do vetor e, no final, a thread principal calcula 
 * a media.
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Outros arquivos necessarios para a execucao desse
 * programa sao:
 * - auxFuncs.h
 * - auxFuncs.c
 *
 * Ultima atualizacao:
 *   12/12/2024
 * 
 * Para compilar:
 *   gcc -pthread auxFuncs.c mediaThreads.c -o mediaThreads
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "auxFuncs.h"
#define NTHREADS 4
#define TAMANHO 100

/**
 * Funcao (thread) que calcula a soma de uma quantidade de elementos
 * informada como parametro.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 *             - A posicao inicial do vetor.
 *             - A posicao final do vetor.
 *             - O vetor.
 * @return Soma dos elementos
 */
void *thrdSomaParcial(void *args)
{
  register unsigned int i, inicio, final;
  int *soma;
  int *vetor;

  // Extracao dos parametros da estrutura args.
  inicio = ( (parametrosThread *) args)->posInicio;
  final  = ( (parametrosThread *) args)->posFinal;
  vetor  = ( (parametrosThread *) args)->vetor;


  if ((soma = (int *) malloc(sizeof(int))) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao para armazenamento da soma parcial\n");
    exit(EXIT_FAILURE);
  }

  *soma = 0;

  for (i=inicio; i<=final; i++)
     *soma += vetor[i];

  return ((void *) soma);
}

/**
 * Funcao que calcula a media dos elementos de um vetor. Essa funcao
 * dispara uma certa quantidade de threads que atua sobre uma particao
 * do vetor.
 *
 * @param vetor Vetor de numeros inteiros.
 * @param tamanho Tamanho do vetor.
 * @param nThreads Quantidade de threads para calcular a soma parcial.
 * @return Media dos elementos do vetor.
 */
float media(int *vetor, unsigned int tamanho, unsigned int nThreads)
{
  void *somaParcial=NULL;
  parametrosThread *parametros;
  pthread_t *idsThread;
  register unsigned int i, quantElementos;
  int soma=0;
  int err;

  parametros  = alocaVetorParametrosThreads(nThreads);
  idsThread   = alocaIdsThreads(nThreads);

  if (tamanho % nThreads != 0)
  {
    fprintf(stderr,"O tamanho nao e divisivel pelo numero de threads\n");
    exit(EXIT_FAILURE);
  }

  quantElementos = tamanho/nThreads;

  for (i=0; i<nThreads; i++)
  {
    parametros[i].posInicio = quantElementos * i;
    parametros[i].posFinal  = (quantElementos * (i+1)) - 1;
    parametros[i].vetor = vetor;

    /* Criacao de um thread passando os parametros especificos
     * na estrutura informada em parametros[i].
     */
    err = pthread_create(&idsThread[i],
                         NULL,
                         thrdSomaParcial,
                         (void *) &parametros[i]);

    if (err != 0)
    {
      fprintf(stderr,"Erro na criacao do thread %d\n",i);
      exit(EXIT_FAILURE);
    }
  }

  for (i=0; i<nThreads; i++)
  {
    /* Juncao dos threads com o retorno de cada thread
     * armazenado na variavel soma parcial.
     */
    err = pthread_join(idsThread[i], &somaParcial);

    if (err != 0)
    {
      fprintf(stderr,"Erro na juncao do thread %d\n",i);
      exit(EXIT_FAILURE);
    }

    printf("Soma parcial do thread %d: %d\n", i, *((int *) somaParcial));
    soma += *((int *) somaParcial);
    free(somaParcial);
  }

  free(parametros);

  return soma/tamanho;
}

int main(int argc, char *argv[])
{
 int *vetor;

 vetor = alocaVetor(TAMANHO);

 preencheSequencial(vetor, TAMANHO);

 printf("A media dos elementos do vetor e %.2f\n", media(vetor, TAMANHO, NTHREADS));

 free(vetor);

 return 0;
}
