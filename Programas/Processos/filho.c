/**
 * Programa exemplo para ilustrar a criacao de processos filhos
 * a partir de processos pais. Alem da criacao, os processos filhos
 * assumirao processos diferentes dos processos pais.
 *
 * Desenvolvido por:
 *   Prof. Andre Leon S. Gradvohl, Dr.
 *
 * Ultima atualizacao:
 *   02/04/2019
 *
 * Para compilar:
 *   gcc filho.c -o filho.o
 *
 * Observacao: precisa que o programa pai.c esteja compilado.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
   unsigned int tempo=0;
   printf("Sou o novo processo filho.\n");
   printf("\tMeu id: %d. Id do processo pai: %d\n", 
           getpid(), getppid());

   if (argc == 2) // Se a quantidade de argumentos na linha de comando for 2.
   {
        tempo = atoi(argv[1]);
        printf("Colocando este processo (filho) para dormir %d segundos\n", tempo);
        sleep(tempo);
   }
   return 0;
}
