#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

enum _BOOLEAN {FALSE = 0, TRUE = 1};
typedef enum _BOOLEAN BOOLEAN;

int nsair = TRUE;

void (*handler(int signal))(int sinal)
{
  switch (signal)
  {
    case SIGHUP: 
      puts("Programa recebeu um SIGHUP");
      break;
    case SIGINT: 
      puts("Programa recebeu um SIGINT");
      break;
    case SIGQUIT: 
      puts("Programa recebeu um SIGQUIT");
      nsair = FALSE;
      break;
  }
}

int main()
{
  signal(SIGHUP, (void (*)(int))handler);      //associar função ao sinal SIGHUP
  signal(SIGINT, (void (*)(int))handler);      //associar função ao sinal SIGHUP
  signal(SIGQUIT, (void (*)(int))handler);    //associar função ao sinal SIGQUIT
  
  printf("Programa (processo %d) recebe os sinais SIGHUP, SIGINT e SIGQUIT\n", getpid());

  while (nsair)
    sleep(1000000);

  puts("Abandonado programa devido a um SIGQUIT");
}
