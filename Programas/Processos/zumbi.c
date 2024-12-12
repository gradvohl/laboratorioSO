/**
 * Programa exemplo para criar processos zumbis.
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   12/12/2024
 *
 * Para compilar:
 *   gcc zumbi.c -o zumbi
 */  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main ()
{
  pid_t pidFilho;

  // Executa um fork() para criar um processo filho.
  pidFilho = fork ();

  if (pidFilho > 0) {
    // Processo Pai vai dormir por 30 segundos e 
    // sair, sem uma chamada para o wait.
    fprintf(stderr,"Processo Pai. PID: %d dormindo 30 segundos\n", getpid());    
    fprintf(stderr,"Em outra janela, execute o comando a seguir:\n\t");
    fprintf(stderr,"top -p %d -p %d\n", getpid(), pidFilho);
    sleep(30); 
    exit(0);
  }
  else if (pidFilho == 0) {
    // Processo Filho vai sair imediatamente
    fprintf(stderr,"Processo Filho. PID: %d\n", getpid());
    exit(0);    
  }
  else if (pidFilho == -1) 
  { // Erro no fork() 
    perror("Falha no fork().");
    exit(1);
  }
  else // Isso nao deve acontecer.
  {
    fprintf(stderr, "Valor de retorno %d da chamada ao fork() desconhecido.", pidFilho);
    exit(2);
  }
  return 0;
}
