#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  fork();
  fork();
  fork();
  fork();
  
  printf("%d: O meu pai e' %d\n", getpid(), getppid());
}