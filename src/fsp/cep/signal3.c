#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

enum _BOOLEAN {FALSE = 0, TRUE = 1};
typedef enum _BOOLEAN BOOLEAN;

int sair = FALSE;
int nusr1 = 0;
int nusr2 = 0;

void (*handlerUSR1(int signal))(int sinal)
{
  puts("Programa recebeu um USR!");
  nusr1++;
}

void (*handlerUSR2(int signal))(int sinal)
{
  puts("Programa recebeu um USR2");
  nusr2++;
}

void (*handlerQUIT(int signal))(int sinal)
{
  puts("Programa recebeu um SIGQUIT");
  sair = TRUE;
}

int main()
{
  signal(SIGUSR1, (void (*)(int))handlerUSR1);   //associar função ao sinal SIGUSR1
  signal(SIGUSR2, (void (*)(int))handlerUSR2);   //associar função ao sinal SIGUSR2
  signal(SIGQUIT, (void (*)(int))handlerQUIT);//associar função ao sinal SIGQUIT
  
  printf("Programa (processo %d) recebe os sinais USR1, USR2 e SIGQUIT\n", getpid());
  while (sair != TRUE)
  {
    printf("%d USR1 e %d USR2\n", nusr1, nusr2); 
    pause();
  }
  printf("Abandonado programa devido a um SIGQUIT com %d USR1 (%d) e %d USR2 (%d)\n", nusr1, SIGUSR1, nusr2, SIGUSR2);
}
