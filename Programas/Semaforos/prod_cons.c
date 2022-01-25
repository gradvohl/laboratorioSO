/**
 * Programa desenvolvido para ilustrar a solucao do problema do 
 * produtor/consumidor com o uso de threads e semaforos.
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   04/04/2019
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 20
#define VEZES 60

sem_t vazio; // Semaforo para controlar as posicoes vazias no buffer
sem_t cheio; // Semaforo para controlar as posicoes preenchidas no buffer
sem_t mutex; // Semaforo binario para garantir exclusao mutua na regiao critica

int buffer[N]; // Armazena os dados produzidos ou consumidos
int proxPosCheia; // Proxima posicao cheia
int proxPosVazia; // Proxima posicao vazia
int cont;         // Controla a quantidade de dados presentes no buffer

// Prototipos das funcoes para o produtor e consumidor
void *produtor(void *);
void *consumidor(void *);

int main(void)
{
    //Define a semente da funcao geradora de numeros aleatorios
    srand(time(NULL));

    cont = 0;
    proxPosCheia = 0;
    proxPosVazia = 0;

    /**
     * Inicializa os semaforos
     * 1o parametro: variavel semaforo
     * 2o parametro: indica se um semaforo sera compartilhado entre as threads 
     *               de um processo ou entre processos o valor 0 indica que o 
     *               semaforo sera compartilhado entre as threads de um processo 
     *               (digit o comando "man sem_init" no shell do linux p/ ver os 
     *               detalhes)
     * 3o parametro: valor inicial do semaforo
     */
     sem_init(&mutex, 0 , 1);
     sem_init(&vazio, 0, N);
     sem_init(&cheio, 0, 0);

     pthread_t thd0, thd1;
     /**
      * Incializa as threads
      * 1o parametro: variavel thread
      * 2o parametro: indica se uma thread e "joinable", ou seja, se a thread 
      *               nao sera finalizada ate chegar a uma chamada de funcao
      *               pthread_join().
      * 3o parametro: indica o nome do metodo que ira compor o trecho de codigo 
      *               q/ sera executado pela thread
      * 4o parametro: utilizado qdo se necessita passar algum paramentro a thread. 
      *               Pode se passar quaisquer tipos de dados, inclusive uma 
      *               estrutura de dados qdo houver a necessidade de passar mais 
      *               de um parametroi (dentro do metodo chamado realiza-se um 
      *               "cast" p/ recuperar os dados)
      */
      pthread_create(&thd0, 0, (void *) produtor, NULL);
      pthread_create(&thd1, 0, (void *) consumidor, NULL);

      /* Bloqueiam a thread principal ate que as threads indicadas por 
       * thd0 e thd1 terminem.
       */ 
      pthread_join(thd0,0);
      pthread_join(thd1,0);

      printf("\n");
      exit(0);
}

// Metodo que produz os itens q/ serao inseridos no buffer (numeros aleatorios)
int produz_item()
{
    int val;
    val = rand() % 100;
    printf("\nProduzindo item: %d", val);
    return val;
}

/* Metodo utilizado p/ mostra o valor q foi consumido 
 * (meramente implementado p/ fins didaticos)
 */
void consome_item(int item)
{
        printf("\nCosumindo item: %d", item);
}

//Metodo que a realiza a insercao do dado no buffer
void insere_item(int val)
{
    if(cont < N)
    {
        buffer[proxPosVazia] = val;
        /* A utilizacao da divisao em modulo implementa um comportamento 
         * circular da utilizacao do buffer, ou seja, quando o contador 
         * chegar no valor de N (N % N = 0) o valor da variavel voltara 
         * ao inicio do buffer.
         */ 
         proxPosVazia = (proxPosVazia + 1) % N;
         cont = cont + 1;
         if(cont == N)
             printf("\n############## Buffer completo ##############");
     }
}

// Metodo que realiza a retirada do dado do buffer
int remove_item()
{
    int val;
    if(cont > 0)
    {
        val = buffer[proxPosCheia];
        proxPosCheia = (proxPosCheia + 1) % N;
        cont = cont - 1;
    }
    return val;
}

void *produtor(void *p_arg)
{
    int item;
    register int i=0;

    while(i++<VEZES)
    {
        item = produz_item(); 
        // sem_wait (realiza o down no semaforo)
        sem_wait(&vazio);
        sem_wait(&mutex);

        insere_item(item);

        // sem_post (realiza o up no semaforo)
        sem_post(&mutex);
        sem_post(&cheio);

        sleep(item%2);
    }
    pthread_exit(NULL);
}

void *consumidor(void *p_arg)
{
    int item;
    register int i=0;

    while(i++<VEZES)
    {
        sem_wait(&cheio);
        sem_wait(&mutex);

        item = remove_item();

        sem_post(&mutex);
        sem_post(&vazio);

        consome_item(item);

        sleep(item%3);
    }

    pthread_exit(NULL);
}
