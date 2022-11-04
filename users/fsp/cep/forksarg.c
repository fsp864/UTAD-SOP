#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  int i = 0, procs, pid;


  if (argc > 1)
   {
    procs = atoi(argv[1]);

    while (i++ < procs)
    {
      switch (pid = fork())
      {
        case -1:
          fprintf(stderr, "Nao foi possivel criar o processo filho\n");
          exit(-1);
          break;
        case 0:
          printf("%d: Sou o filho de %d\n", getpid(), getppid());
          exit(-1);
          break;
        default:
          printf("%d: Sou o pai e criei o processo %d\n", getpid(), pid);
      }
    }
   }  
   else
   {
    fprintf(stderr,"uso: %s numero_de_procesoos_a_criar\n", argv[0]);
    return 1;
   }

   return 0;
}
