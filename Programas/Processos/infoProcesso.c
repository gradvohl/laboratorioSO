/**
 * Programa para capturar informacoes sobre um processo.
 *
 * Desenvolvido por: 
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   21/11/2024
 *
 * Para compilar:
 *   gcc infoProcesso.c -o infoProcesso 
 */
#include <stdlib.h>     // Cabecalho de Biblioteca padrao
#include <stdio.h>      // Cabecalho de Biblioteca de I/O padrao
#include <sched.h>      // Cabecalho de Biblioteca de escalonamento 
#include <unistd.h>     // Cabecalho com definicao de constantes padrao

int main(void)
{
  pid_t idProcesso;    // Variavel para armazenar o id do processo.
  pid_t idProcessoPai; // Variavel para armazenar o id do processo pai.
  uid_t idUsuario;     // Variavel para armazenar o id do usuario
  gid_t idGrupo;       // Variavel para armazenar o id do grupo do usuario.

  char dirTrabalho[100]; // String para armazenar o diretorio de trabalho.

  int politEscal; // Variavel para armazenar informacoes sobre o escalonamento.

  printf("Programa para captura de informacoes sobre o processo:\n");

  // Captura o id desse processo.
  idProcesso = getpid();
  
  // Captura o id do processo pai.
  idProcessoPai = getppid(); 

  // Captura o id do usuario
  idUsuario = getuid(); 

  // Captura o id do grupo
  idGrupo = getgid();
  
  // Captura o diretorio de trabalho desse processo
  getcwd(dirTrabalho, 99); 

  printf("Informacoes sobre o processo:\n");
  printf("\tO identificador do meu processo e: %d\n", idProcesso);
  printf("\tO identificador do meu processo pai e: %d\n", idProcessoPai);
  printf("\tO identificador de usuario desse processo e: %d\n", idUsuario);
  printf("\tO identificador de grupo desse processo e: %d\n", idGrupo);
  printf("\tO diretorio de trabalho eh: %s\n", dirTrabalho);

  // Captura a politica de escalonamento utilizada pelo SO
  politEscal = sched_getscheduler(idProcesso);

  printf("A politica de escalonamento: ");
  switch(politEscal)
  {
    case SCHED_FIFO: printf("Politica FIFO.\n");
      break;
    case SCHED_RR: printf("Politica RoundRobin.\n");
      break;
    case SCHED_OTHER: printf("Politica default.\n");
      break;
    default: fprintf(stderr,"Erro!\n");
  }

  printf("Pressione <enter> para sair do programa.\n");
  getchar();
  return 0;
}
