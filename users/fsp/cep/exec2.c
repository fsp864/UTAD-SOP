#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  int pid;

  if (argc > 1)
   {
    switch (pid = fork())
    {
      case -1:
        fprintf(stderr, "Nao foi possivel criar o processo filho\n");
        break;
      case 0:
        printf("%d: Sou o filho e vou executar \"%s\"\n", getpid(), argv[1]);
        execlp(argv[1], argv[1], (char *)NULL);
        fprintf(stderr, "Nao foi possivel obter o programa \"%s\"\n", argv[1]);
        break;
      default:
        printf("%d: Sou o pai e criei o processo %d\n", getpid(), pid);
        break;
    }
   }
   else
    printf("%d: Falta argumento\n", getpid());

  return 0;
}
