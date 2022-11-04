#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char * argv[])
{
  int pid;
  char line[MAXLINE + 1];

  puts("digitar \"sair\" para finalizar.");
  do
  {
    fgets(line, MAXLINE, stdin);
    if (strchr(line, '\n') != NULL)      //se string contem uma mudanca de linha
       *(strchr(line, '\n')) = '\0';              //substituir por fim de string
    if (strcmp(line, "sair") != 0)
     {
      switch (pid = fork())
      {
        case -1:
          fprintf(stderr, "Nao foi possivel criar o processo filho\n");
          break;
        case 0:
          execvp(line, argv);
          fprintf(stderr, "Nao foi possivel executar o comando \"%s\"\n", line);
          exit(-1);
          break;
      }
     }
  } while (strcmp(line, "sair") != 0);

  return 0;
}
