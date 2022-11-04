#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void (*handlerUSR1(int signal))(int sinal)
{
  puts("Programa recebeu um sinal USR1");
  exit(-1);
}

int main()
{
  signal(SIGUSR1, (void (*)(int))handlerUSR1);   //associar função ao sinal USR1

  printf("Programa (processo %d) vai adormecer\n", getpid());
  pause();
  puts("Programa acordado por um sinal.");

  return 0;
}
