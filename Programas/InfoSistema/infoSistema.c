/**
 * Programa para capturar informacoes sobre o  hardware (CPU e memoria).
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   20/11/2024
 *
 * Para compilar:
 *   gcc infoSistema.c -o infoSistema
 */
#include <stdio.h>       // Cabecalho de Biblioteca de I/O padrao
#include <stdlib.h>      // Cabecalho de Biblioteca padrao
#include <unistd.h>      // Cabecalho com definicao de constantes padrao
#include <sys/sysinfo.h> // Cabecalho de Biblioteca para informacoes sobre o hw
#include <sys/utsname.h> // Cabecalho com definicao da estrutura utsname

#define Kbytes 1024.0    // Valor no tipo float para permitir a divisao real.
#define Mbytes 1048576.0 // Valor no tipo float para permitir a divisao real.

int main(void)
{
  struct sysinfo infoMemoria; /* Variavel (estrutura) para obter informacoes
			       * sobre a memoria.
			       */
  struct utsname infoSistema; /* Variavel (estrutura) para obter informacoes
                               * sobre o sistema.
                               */
  double cargaProcess[3]; /* Vetor para armazenar a carga de processamento.*/

  printf("=== Informacoes sobre a CPU: ===\n");	
  printf("- Esse sistema tem %d processadores configurados", get_nprocs_conf());
  printf(" e %d processadores disponiveis.\n", get_nprocs());

  /* Obtencao de dados sobre a memoria e 
   * armazenamento na estrutura infoMemoria.
   */
  if (sysinfo(&infoMemoria) != 0)
  {
    fprintf(stderr, "Problemas na utilizacao da primitiva sysinfo.\n");
    exit(EXIT_FAILURE);
  }


  printf("\n=== Informacoes sobre a memoria: ===\n");
  printf("- Total de memoria: %.0f Kilobytes ou %.3f Megabytes\n", 
	  (infoMemoria.totalram/Kbytes), (infoMemoria.totalram/Mbytes));

  printf("- Total de memoria livre: %.0f Kilobytes ou %.3f Megabytes\n",
          (infoMemoria.freeram/Kbytes), (infoMemoria.freeram/Mbytes));

  printf("- Total de memoria compartilhada: %.0f Kilobytes ou %.3f Megabytes\n",
          (infoMemoria.sharedram/Kbytes), (infoMemoria.sharedram/Mbytes));

  printf("\n=== Informacoes sobre o sistema: ===\n");
  printf("- Tempo desde a inicializacao do sistema: %lu segundos ou %.2f minutos\n", 
		  infoMemoria.uptime, infoMemoria.uptime/60.0);

  // Captura informacoes sobre o sistema
  if (uname(&infoSistema) == -1)
  {
    fprintf(stderr, "Problemas na utilizacao da primitiva uname.\n");
    exit(EXIT_FAILURE);
  }
  
  printf("- Nome do kernel: %s\n",infoSistema.sysname);
  printf("- Release do kernel: %s\n",infoSistema.release);
  printf("- Versao do kernel: %s\n",infoSistema.version);
  printf("- Arquitetura do hardware: %s\n",infoSistema.machine);
  printf("- Nome do host: %s\n",infoSistema.nodename);

  printf("\n=== Informacoes sobre os processos: ===\n"); 
  printf("- Numero de processos em andamento: %d\n",infoMemoria.procs);

  // Captura informacoes sobre a carga dos processos
  if (getloadavg(cargaProcess,3) != 3)
  {
    fprintf(stderr, "Problemas na utilizacao da primitiva getloadavg.\n");
    exit(EXIT_FAILURE);
  }
  
  printf("- Carga media de processamento:\n");
  printf("\t-- no ultimo minuto: %f\n", cargaProcess[0]);
  printf("\t-- nos ultimos 5 minutos: %f\n", cargaProcess[1]);
  printf("\t-- nos ultimos 15 minutos: %f\n",cargaProcess[2]);

  return 0;
}
