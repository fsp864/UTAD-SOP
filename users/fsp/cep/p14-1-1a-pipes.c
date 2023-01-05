#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define PIPE_OUT 0
#define PIPE_IN 1

int main()
{
  int i, valor, soma = 0;
  int f2p[2], p2f[2];

  if ((pipe(f2p) != -1) && (pipe(p2f) != -1))
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
          write(f2p[PIPE_IN], &valor, sizeof(int));
        } while (valor != 0);
        read(p2f[PIPE_OUT], &soma, sizeof(int));
        printf("[%d] Calculador: soma = %d\n", getpid(), soma);
        break;
      default:                                                /* processo pai */
        do
        {
          read(f2p[PIPE_OUT], &valor, sizeof(int));
          soma += valor;
        } while (valor != 0);
        write(p2f[PIPE_IN], &soma, sizeof(int));
        break;
    }
   }
   else
   {
    perror("Erro na criacao da pipe");
    return -1;
   }

  close(f2p[PIPE_IN]);
  close(f2p[PIPE_OUT]);
  close(p2f[PIPE_IN]);
  close(p2f[PIPE_OUT]);

  return 0;
}