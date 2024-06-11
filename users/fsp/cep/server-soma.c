#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "sockets.h"

#define MAXMESSAGE	  128
#define MAXCONNECTIONS  1

void (*handlerHUP(int signal))(int sinal)
{
  puts("Servidor recebeu um SIGHUP");
  exit(0);
}

int main(int argc, char * argv[])
{
  int com, port, i, size, mysocket, valor, soma = 0;
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

    signal(SIGHUP, (void (*)()) handlerHUP);

    fclose(stdin);
    printf("[%d]: Servidor de somas em %s:%d\nEsperando comunicacoes (%d max) / SIGHUP termina\n", \
           getpid(), host, port, MAXCONNECTIONS);    //msg do servidor no stdout

    if ((com = accept(mysocket, NULL, NULL)) < 0)     //esperar pela comunicacao
     {
      perror("accept: ");
      return -1;
     }

    printf("[%d]: Comunicacao establecida\n", getpid());
    do
    {
      read(com, &valor	, sizeof(int));
      soma += valor;
      printf("%d (%d)\n",valor, soma);
    } while (valor != 0);
    write(com, &soma, sizeof(int));
    close(com);          
   }
   else
   {
    fprintf(stderr,"uso: %s interface porta\n", argv[0]);
    return -1;
   }

   return 0;
}
