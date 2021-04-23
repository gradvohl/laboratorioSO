/** 
 * Este e um programa simples para exemplificar a utilizacao 
 * de Threads. 
 * O programa visa realizar a soma dos elementos
 * de um vetor com 20 posicoes. Para isso, vai dividir o 
 * vetor entre duas threads. Cada thread calcula sua soma
 * parcial e a thread principal calcula a soma final.
 *
 * Desenvolvido por: 
 *   Prof. Andre Leon S. Gradvohl, Dr.
 * 
 * Outros arquivos necessarios para a execucao desse 
 * programa sao:
 * - funcoes.h
 * - funcoes.c
 *
 * Ultima atualizacao:
 *   23/04/2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Cabecalho para a funcao sleep
#include <pthread.h> // Cabecalho especifico para threads POSIX
#include "funcoes.h" // Cabecalho para a funcoes que serao os threads.

int main( void )
{
 pthread_t meutid;        /* Variavel que armazena o id do thread principal */
 pthread_t idPrimeiroThread; /* Vetor que armazena o id do primeiro thread */
 pthread_t idSegundoThread;  /* Vetor que armazena o id do segundo thread */
 parametros *param; /* Ponteiro para a estrutura que armazenara 
                     * os parametros para os threads */
 
 float vetor[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  // Soma: 45
                 10,11,12,13,14,15,16,17,18,19}; // Soma: 145
 float *primeiroResultParcial = NULL;
 float *segundoResultParcial = NULL;

 /* Funcao que captura o id do thread (nesse caso o thread principal) */
 meutid = pthread_self(); 
 printf("Meu Thread ID  = %ld\n",meutid);

 /* Preenchimento dos parametros para o primeiro thread. */
 param = alocaParametros(0, 9, vetor);

 printf("Disparando o primeiro Thread para somar");
/**
 * A funcao a seguir cria um thread (linha de execucao) para a funcao "sub_a".
 * O prototipo da funcao e:
 *   int pthread_create(pthread_t *thread,  const  pthread_attr_t *attr, 
 *                      void *(*start_routine, void*), void *arg);
 * Onde:
 *   "thread" e o identificador do thread que se quer criar.
 *   "attr" sao os atributos do Thread (Geralmente NULL).
 *   "start_routine" e a funcao onde estao os threads.
 *   "arg" sao os parametros da "start_routine".
 * A funcao retorna
 */
 pthread_create(&idPrimeiroThread, NULL, soma, param); 
 printf("(id = %ld)\n", idPrimeiroThread);

 /* Preenchimento dos parametros para o segundo thread. */
 param = alocaParametros(10, 19, vetor);

 printf("Disparando o segundo Thread para somar");
 pthread_create(&idSegundoThread, NULL, soma, param);
 printf("(id = %ld)\n", idSegundoThread);

 printf("Aguardando finalizacao dos Threads id=%ld e id=%ld\n", 
        idPrimeiroThread, idSegundoThread);
/**
 * A funcao a seguir bloqueia o processo ate que o thread indicado termine.
 * O prototipo da funcao e:
 *   int pthread_join(pthread_t thread, void **value_ptr);
 * Onde:
 *   "thread" e o identificador do thread que se espera terminar.
 *   "value_ptr" e o valor de retorno da funcao
 * A funcao retorna 0 se funcionou corretamente e um valor 
 * diferente de 0 para indicar erro.
 */
 pthread_join(idPrimeiroThread, (void **) &primeiroResultParcial);
 pthread_join(idSegundoThread, (void **) &segundoResultParcial);
 
 /* Impressao dos valores finais. */
 printf("Threads id=%ld e id=%ld finalizados\n", idPrimeiroThread, idSegundoThread);
 printf("Soma parcial do primeiro thread: %.2f\n", *primeiroResultParcial);
 printf("Soma parcial do segundo thread: %.2f\n", *segundoResultParcial);
 printf("Soma total: %.2f\n", *primeiroResultParcial + *segundoResultParcial);

 /* Desalocando variaveis com soma parcial*/
 free(primeiroResultParcial);
 free(segundoResultParcial);
 
 return 0;
}
