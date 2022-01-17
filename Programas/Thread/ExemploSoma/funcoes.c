/**
 * Codigo com as implementacao da funcao (thread) soma.
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   04/04/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "funcoes.h" // Cabecalho que contem o prototipo dessas funcoes

/* Especificacao da thread que realizara a soma parcial. */
void *soma(void *args)
{
  register float soma=0;
  register int i;
  parametros *param;
  float *resultado = NULL;
  
  /* Obtem os parâmetros passados para o thread */
  param = (parametros *) args;

  /* Calcula a soma parcial dos elementos do vetor */
  for (i = param->idxInicio; i <= param->idxFim; i++)
     soma += param->vetor[i];

  /* Aloca memoria para a variavel resultado poder
   * retornar da thread
   */
  if ((resultado = (float *) malloc(sizeof(float))) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao de memoria para o resultado\n");
    exit(EXIT_FAILURE);
  }

  *resultado = soma;

  /* Desaloca os parametros, ja que nao sao mais necessarios */
  free(param);

  /* Termina o thread e retorna o ponteiro resultado */
  pthread_exit(resultado);
}

/* Funcao para alocar na memoria os parametros na que serao
 * enviados ao thread
 */
parametros *alocaParametros(unsigned int idxInicio, unsigned int idxFim, float *vetor)
{
 parametros *param;

 /* Aloca memoria para armazenar os parametros */
  if ((param = (parametros *) malloc(sizeof(parametros))) == NULL)
  {
    fprintf(stderr,"Problemas na alocacao de memoria para o resultado\n");
    exit(EXIT_FAILURE);
  }

 param->idxInicio = idxInicio;
 param->idxFim = idxFim;
 param->vetor = vetor;

 return param;
} 
