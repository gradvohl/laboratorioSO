/**
 * Programa desenvolvido para ilustrar o compartilhamento de
 * memoria principal entre processos.
 *
 * Baseado no programa shm_server.c disponivel em
 * http://www.cs.cf.ac.uk/Dave/C de David Marshall.
 *
 * Ultima atualizacao
 *   12/12/2024
 *
 * Para compilar:
 *   gcc shm_serv.c -o shm_serv
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>  // Cabecalho para comunicacao interprocessos
#include <sys/shm.h>  // Cabecalho para compatilhamento e memoria

// Definicao do Tamanho do segmento compartilhado
#define TamSegCompart  27

// Definicao do identificador do segmento compartilhado.
#define IDSegCompart 5678

int main(void)
{
 char c;
 int shmid;
 key_t key;
 char *shm, *s;

 // Criando/Atribuindo o ID do Segmento Compartilhado
 key = IDSegCompart;

 /* Criando o segmento. 
  * 0666 -> Permissao para leitura e escrita, 
  * para usuario, grupo e outros
  */
 shmid = shmget(key, TamSegCompart, IPC_CREAT | 0666);

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

 s = shm;

 // Inserindo alguns dados no segmento compartilhado.
 for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = 0; // NULL

 /* Aguarda ate que o outro processo coloque um "*" 
  * primeira posicao do segmento de memoria 
  * compartilhado */
 while (*shm != '*')
    sleep(1);

 /* Desvincula o segmento compartilhado */
 if (shmdt(shm))
 {
   perror("Erro na shmdt");
   return 1;
 }

 return 0;
}
