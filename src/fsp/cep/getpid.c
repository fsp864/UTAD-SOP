#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  printf("O meu PID e' %d\n", getpid());
  printf("O PID do processo (pai) que me criou e' %d\n", getppid());

  return(0);
}