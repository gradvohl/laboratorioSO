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
 *   gcc pai.c -o pai.o
 *
 * Observacao: precisa que o programa filho.c esteja compilado.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void) 
{
  pid_t  filho;      // Identificador do procesos filho. 
  int    statusFilho;// Status de saida do filho. 
  pid_t  c;          // Identificador do filho que sera retornado pelo wait.
  char *args[3];     // Lista de argumentos para o processo filho. 

  // Define os argumentos para o programa filho.
  args[0] = "./filho.o"; // Nome do programa filho.
  args[1] = "2";         // Argumentos para o programa filho.
  args[2] = NULL;        // Indica o fim dos argumentos para o programa.

  filho = fork(); // Cria o processo filho atraves da primitiva fork().

  if (filho == 0) // Se o processo filho foi criado, este if sera verdadeiro
  { 
    printf("PID do filho = %ld\n", (long) getpid());

    /**
     * Substitui a imagem do filho pela imagem do programa 
     * "filho.o", com os respectivos argumentos.
     */
    execvp(args[0], args);

    /**
     * Se o processo filho alcanca este ponto, 
     *    entao a primitiva execvp falhou.
     */
    fprintf(stderr, "O processo filho nao pode executar a primitiva execvp.\n");
    exit(1);
  } 
  else // O processo pai entrara neste else.
  { 
    if (filho == (pid_t)(-1)) 
    {
      fprintf(stderr, "Fork falhou.\n"); 
      exit(1);
    } 
    else 
    {
      printf("Esperando o filho terminar!\n");
      c = wait(&statusFilho); //Esperando o filho terminar. 
      printf("Pai: filho (%ld) terminou com status = %d\n", (long) c, statusFilho);
    }
  }
  return  0;
}
