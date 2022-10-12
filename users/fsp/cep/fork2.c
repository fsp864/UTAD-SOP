#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int pid;

  switch (pid = fork())
  {
    case -1:
      fprintf(stderr, "Nao foi possivel criar o processo filho\n");
      break;
    case 0:
      printf("%d: Sou o filho\n", getpid());
      break;
    default:
      printf("%d: Sou o pai e criei o processo %d\n", getpid(), pid);
  }
  
  return(0);
}