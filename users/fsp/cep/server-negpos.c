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
  int com, port, i, valor, positivos = 0, negativos = 0,mysocket;
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
    printf("[%d]: Servidor em %s:%d\nEsperando comunicacoes (%d max) / SIGHUP termina\n", \
           getpid(), host, port, MAXCONNECTIONS);    //msg do servidor no stdout

    if ((com = accept(mysocket, NULL, NULL)) < 0)     //esperar pela comunicacao
     {
      perror("accept: ");
      return -1;
     }

    printf("[%d]: Comunicacao establecida\n", getpid());
    do
    {
      read(com, &valor, sizeof(int));
      if (valor > 0)
        positivos++;
      if (valor < 0)
        negativos++;

      printf("[%d]: recebido valor %d (positivos = %d, negativos = %d)\n", getpid(), valor, positivos, negativos); //info no stdout 
    } while (valor != 0);
    write(com, &positivos, sizeof(int));
    write(com, &negativos, sizeof(int));
    close(com);                                             //fechar comunicacao
   }
   else
   {
    fprintf(stderr,"uso: %s interface porta\n", argv[0]);
    return -1;
   }

   return 0;
}
