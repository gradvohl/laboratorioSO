#ifndef _AUXFUNCS
#define _AUXFUNCS
 /* Definicao da estrutura que contem os parametros para
  * uma thread.
  * Os parametros sao a posicao de inicio, a posicao do final
  * e o endereco do vetor.
  */
 typedef struct {
   unsigned int posInicio;
   unsigned int posFinal;
   int *vetor;
 } parametrosThread;

 int *alocaVetor(unsigned int);
 parametrosThread *alocaVetorParametrosThreads(unsigned int);
 pthread_t *alocaIdsThreads(unsigned int);
 void preencheSequencial(int *vetor, unsigned int);
#endif
