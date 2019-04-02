/**
 * Programa para ilustrar a criacao de um processo filho
 * a partir do processo pai.
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   26/11/2003
 *
 * Para compilar:
 *   gcc PaiFilho.c -o PaiFilho
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
  int pid;
  int paiPid;
  int ret;
  int i=0;

  pid = getpid();
  printf("Pronto para o fork. Meu id e:%d\n",pid);

  sleep(1);

  ret = fork();

  if (ret < 0) // Problemas no fork
  {
   perror("Impossivel fazer o fork!\n");
   return 1;
  } 

  if (ret == 0) // Se verdade, sou o processo filho
  {
   pid = getpid();
   paiPid = getppid();
   printf("Sou o processo filho!\n");
   printf("\tMeu id e: %d.\n",pid);
   printf("\tO id do meu Pai e: %d\n", paiPid);
   return 0;
  } 
  else // Senao sou o processo pai
  {
   pid = getpid();
   printf("Sou o processo Pai!\n");
   printf("\tMeu id e: %d. \n",pid);
   printf("\tO id do meu filho e: %d\n", ret);
   return 0;
  }
}
