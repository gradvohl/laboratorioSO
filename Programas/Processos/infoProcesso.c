/**
 * Programa para capturar informacoes sobre um processo.
 * Desenvolvido por: 
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   04/04/2019
 *
 * Para compilar:
 *   gcc infoProcesso.c -o infoProcesso 
 */
#include <stdlib.h>     // Cabecalho de Biblioteca padrao
#include <stdio.h>      // Cabecalho de Biblioteca de I/O padrao
#include <sched.h>      // Cabecalho de Biblioteca de escalonamento 
#include <sys/types.h>  // Cabecalho com definicao de tipos de dados
#include <sys/utsname.h>// Cabecalho com definicao da estrutura utsname
#include <unistd.h>     // Cabecalho com definicao de constantes padrao

#define Kbyte 1024.
#define Mbyte 1048576. //(1024 Kbytes)
#define Nelem 3

int main(void)
{
  pid_t idProcesso;
  pid_t idProcessoPai;
  uid_t idUsuario;
  gid_t idGrupo;

  long memTotal;
  long memDisp;
  int tamPagina;

  double carga[Nelem];

  char dirTrabalho[100];
  char str[30];

  int n;
  int politicaEscalonamento;

  struct utsname info;

  puts("Programa para captura de informacoes sobre o processo.");

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

  puts("Informacoes sobre o processo:");
  printf("\tO identificador do meu processo e: %d\n", idProcesso);
  printf("\tO identificador do meu processo pai e: %d\n", idProcessoPai);
  printf("\tO identificador de usuario desse processo e: %d\n", idUsuario);
  printf("\tO identificador de grupo desse processo e: %d\n", idGrupo);
  printf("\tO diretorio de trabalho eh: %s\n", dirTrabalho);

  // Captura o tamanho da pagina
  tamPagina = getpagesize();

  /* Captura a quantidade de paginas de memoria a multiplica pelo 
     tamanho da pagina */
  memTotal = sysconf(_SC_PHYS_PAGES) * tamPagina;

  /* Captura a quantidade de paginas de memoria disponiveis e
     a multiplica pelo  tamanho da pagina */
  memDisp = sysconf(_SC_AVPHYS_PAGES) * tamPagina;

  puts("Informacoes sobre a memoria:");
  printf("\tO tamanho da pagina e: %d (%.0f Kbytes)\n",
	 tamPagina, tamPagina/Kbyte);
  printf("\tO tamanho total da memoria: %ld (%f Mbytes)\n",
	 memTotal, memTotal/Mbyte);
  printf("\tO tamanho de memoria disponivel: %ld (%f Mbytes)\n",
	 memDisp, memDisp/Mbyte);

  // Captura a media de carga do sistema: numero de processos/tempo
  n = getloadavg(carga,Nelem);
  if (n > -1)
  {
    printf("Media de carga: \n");
    printf("\t no ultimo minuto: %f\n",carga[0]);
    printf("\t nos ultimos 5 minutos:%f\n",carga[1]);
    printf("\t nos ultimos 15 minutos:%f\n",carga[2]);
  }

  // Captura a politica de escalonamento utilizada pelo SO
  politicaEscalonamento = sched_getscheduler(idProcesso);

  puts("A politica de escalonamento:");
  switch(politicaEscalonamento)
  {
    case SCHED_FIFO: puts("\tPolitica FIFO");
      break;
    case SCHED_RR: puts("\tPolitica RoundRobin");
      break;
    case SCHED_OTHER: puts("\tPolitica default");
      break;
    default: puts("Erro!");
  }

  // Captura informacoes sobre o sistema
  uname(&info);

  printf("Informacoes do sistema:\n");
  printf("\tNome do S.O.: %s\n",info.sysname);
  printf("\tRelease do S.O.: %s\n",info.release);
  printf("\tVersao do S.O.: %s\n",info.version);
  printf("\tHardware: %s\n",info.machine);
  printf("\tNome do host:%s\n",info.nodename);

  puts("Digite algo e tecle <enter> para encerrar.");
  scanf("%s",str);
  return 1;
}
