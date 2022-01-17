/* Definicao da estrutura que armazenara os parametros
 * para envio a thread.
 */
typedef struct {
  unsigned int idxInicio;
  unsigned int idxFim;
  float *vetor;
} parametros;

/* Especificacao da thread que realizara a soma parcial. */
void *soma(void *);

/* Funcao para alocar na memoria os parametros na que serao 
 * enviados ao thread 
 */
parametros *alocaParametros(unsigned int idxInicio, unsigned int idxFim, float *vetor);
