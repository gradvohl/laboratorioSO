#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "auxFuncs.h"

/**
 * Funcao para alocar dinamicamente um vetor de inteiros.
 * @param tamanho Numero de posicoes do vetor.
 * @return Vetor alocado.
 */
int *alocaVetor(unsigned int tamanho)
{
  int *vetor;

  if (tamanho<=0)
    return NULL;

  if ((vetor = (int *) malloc(sizeof(int)*tamanho)) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao do vetor\n");
    exit(EXIT_FAILURE);
  }

  return vetor;
}

/**
 * Funcao para alocar dinamicamente um vetor do tipo parametrosThreads.
 * @param tamanho Numero de posicoes do vetor.
 * @return Vetor alocado.
 */
parametrosThread *alocaVetorParametrosThreads(unsigned int tamanho)
{
  parametrosThread *vetor;

  if (tamanho<=0)
    return NULL;

  if ((vetor = (parametrosThread *) malloc(sizeof(parametrosThread)*tamanho)) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao do vetor\n");
    exit(EXIT_FAILURE);
  }

  return vetor;
}

/**
 * Funcao para alocar dinamicamente um vetor de identificadores de threads.
 * @param tamanho Numero de posicoes do vetor.
 * @return Vetor alocado.
 */
pthread_t *alocaIdsThreads(unsigned int tamanho)
{
  pthread_t *vetor;

  if (tamanho<=0)
    return NULL;

  if ((vetor = (pthread_t *) malloc(sizeof(pthread_t)*tamanho)) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao do vetor\n");
    exit(EXIT_FAILURE);
  }

  return vetor;
}

/**
 * Procedimento para preencher as posicoes de um vetor com valores.
 * @param vetor Vetor a ser preenchido.
 * @param tamanho Quantidade de elementos do vetor.
 */
void preencheSequencial(int *vetor, unsigned int tamanho)
{
  register unsigned int i;

  if (vetor == NULL)
  {
    fprintf(stderr,"Vetor nao alocado\n");
    exit(EXIT_FAILURE);
  }

  for (i=0; i<tamanho; i++)
    vetor[i] = i;
}