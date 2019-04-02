/**
 * Programa desenvolvido para ilustrar o compartilhamento de
 * memoria principal entre processos.
 *
 * Baseado no programa shm_client.c disponivel em 
 * http://www.cs.cf.ac.uk/Dave/C de David Marshall.
 * 
 * Atualizado em: 15/12/2003
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

// Definicao do Tamanho do segmento compartilhado
#define TamSegCompart  27

// Definicao do identificador do segmento compartilhado.
#define IDSegCompart 5678

int main(void)
{
    int shmid;
    key_t key;
    char *shm, *s;

 // Criando/Atribuindo o ID do Segmento Compartilhado
 key = IDSegCompart;
    
 // Localizando o segmento.
 shmid = shmget(key, TamSegCompart, 0666);
 if (shmid  < 0) 
 {
  perror("Erro no shmget");
  return 1;
 }

 /* Vinculando o segmento ao espaco de enderecamento
  * Note que o segundo parametro e NULL. Isso significa
  * que a primitiva shmat vai encontrar um endereco nao
  * usado para vincular o segmento. Essa e a melhor forma.
  */
 shm = shmat(shmid, NULL, 0);

 if (shm  == (char *) -1)
 {
  perror("Erro no shmat");
  return 1;
 }

 // Lendo o que o outro processo deixou na memoria
 for (s = shm; *s != 0 /*NULL*/; s++)
     putchar(*s);
 putchar('\n');

 /* Escrevendo '*' na primeira posicao de memoria
  * para notificar que ja leu o segmento.
  */
 *shm = '*';

/* Desvincula o segmento compartilhado */
 if (shmdt(shm))
 {
   perror("Erro na shmdt");
   return 1;
 }
 return 0;
}
