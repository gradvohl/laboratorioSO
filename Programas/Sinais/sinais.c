/**
 * Programa para exemplificar o tratamento de sinais.
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   12/12/2024
 *
 * Para compilar:
 *   gcc sinais.c -o sinais
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// Funcao que tratara os sinais
void trataSinal(int numSinal)
{
  switch(numSinal)
  {
    case SIGINT:
        fprintf(stderr,"Tentou usar o Ctrl-C\n");
        break;
    case SIGHUP:
      fprintf(stderr, "Recebi um sinal HUP\n");
      fprintf(stderr, "Agora ignorando o SIGHUP\n");
      /* SIG_IGN e usado para ignorar signais.  SIGKILL e SIGSTOP
       * nao podem ser ignorados.
       */
      signal(SIGHUP, SIG_IGN);
    case SIGQUIT:
      fprintf(stderr, "Recebi um sinal de termino!\n Adeus!\n");
      exit(0);
  }
}

int main()
{
  // Registrando as funcoes para tratamento dos sinais.
  signal(SIGINT, trataSinal);
  signal(SIGHUP, trataSinal);
  signal(SIGQUIT, trataSinal);

  fprintf(stderr, "use o comando 'kill -HUP %d' ou \n", getpid());
  fprintf(stderr, "'kill -QUIT %d' para encerrar o processo\n", getpid());

  while(1)
  {
    puts(".");
    sleep(2);
  }
  return 0;
}
