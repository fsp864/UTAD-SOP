#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <time.h>

#include "sockets.h"

#define MAXCONNECTIONS  3
#define MAXVALUE 1000

void waitfunc(void)
{
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

void (*handlerHUP(int signal))(int sinal)
{
  puts("Servidor recebeu um SIGHUP");
  exit(0);
}

int main(int argc, char * argv[])
{
  int port, mysocket, com, valor, cliente, sentido;
  time_t tloc;
  char * host;

  if (argc > 2)
   {
    host = argv[1];
    port = atoi(argv[2]); 
    if ((mysocket = ServerCreateConnection(port, host, MAXCONNECTIONS)) < 0)
     {
      perror("ServerCreateConnection: ");
      return -1;
     }

    signal(SIGCHLD, (void (*)()) waitfunc);
    signal(SIGHUP, (void (*)()) handlerHUP);

    fclose(stdin);
    printf("[%d]: Servidor em %s:%d\nEsperando comunicacoes (pelo menos %d clientes) / SIGHUP termina\n", getpid(), host, port, MAXCONNECTIONS);

    do
    {
      if ((com = accept(mysocket, NULL, NULL)) < 0)
       {
        perror("accept: ");
        return -1;
       }
      switch(fork())
      {
        case -1:
          perror("fork: ");
          close(mysocket);
          close(com);
          return -1;
        case 0:
          close(mysocket);
          srand(time(&tloc));
		  valor = (int)((float)rand() / RAND_MAX * MAXVALUE);
          printf("[%d]: Comunicacao establecida, valor a adevinhar e': %d\n", getpid(), valor);

          do 
          {
            read(com, &cliente, sizeof(int));
            if (cliente == valor)
              sentido = 0;
             else
              if (cliente > valor)
                sentido = -1;
               else
                sentido = 1;
            write(com, &sentido, sizeof(int));

            printf("[%d]: Valor cliente %d, sentido %d, valor %d.\n", getpid(), cliente, sentido, valor);
          } while (sentido != 0);
          puts("Valor correto. Canal fechado.");
          return 0;
          close(com);
          break;
        default:
          close(com);
          break;
      } 
    } while (1 == 1);
   }
   else
   {
    fprintf(stderr,"uso: %s interface porta\n", argv[0]);
    return 1;
   }

   return 0;
}