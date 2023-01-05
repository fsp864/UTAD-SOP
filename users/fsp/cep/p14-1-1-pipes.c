#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define PIPE_OUT 0
#define PIPE_IN 1

int main()
{
  int i, valor, soma = 0;
  int p[2];

  if (pipe(p) != -1)                                            /* criar pipe */
   {
    switch (fork())
    {
      case -1:                                              /* erro no fork() */
        perror("Erro na criacao do processo filho");
        return -1;
        break;
      case 0:                                               /* processo filho */
        do
        {
          printf("[%d] Leitor: ", getpid());
          scanf("%d", &valor);
          write(p[PIPE_IN], &valor, sizeof(int));
        } while (valor != 0);
        break;
      default:                                                /* processo pai */
        do
        {
          read(p[PIPE_OUT], &valor, sizeof(int));
          soma += valor;
        } while (valor != 0);
        printf("[%d] Calculador: soma = %d\n", getpid(), soma);
        break;
    }
   }
   else
   {
    perror("Erro na criacao da pipe");
    return -1;
   }

  close(p[0]);
  close(p[1]);

  return 0;
}