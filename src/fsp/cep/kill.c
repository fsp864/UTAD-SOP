#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
  int signal, pid;

  if (argc >= 2)
   {
    signal = atoi(argv[1]);
    pid = atoi(argv[2]);

    printf("%s: Enviando o sinal %d ao processo %d\n", argv[0], signal, pid);
    kill(pid, signal);
   }
   else
    perror("Falta indicar o PID e/ou o sinal");
}
