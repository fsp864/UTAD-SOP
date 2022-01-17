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

void waitfunc(void)
{
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

void (*handler(int signal))(int sinal)
{
  puts("Servidor recebeu um SIGHUP");
  exit(0);
}


int main(int argc, char * argv[])
{
  int mysocket, com, port, i, size;
  char * host, buffer[MAXMESSAGE + 1];

  if (argc > 2)
   {
    host = argv[1];
    port = atoi(argv[2]); 
    if ((mysocket = ServerCreateConnection(port, host, MAXCONNECTIONS)) < 0)
     {
      perror("ServerCreateConnection: ");
      return(-1);
     }

    signal(SIGCHLD, (void (*)()) waitfunc);
    signal(SIGHUP, (void (*)()) handler);

    fclose(stdin);
    printf("[%d]: Servidor em %s:%d\nEsperando comunicacoes (%d max) / SIGHUP termina\n", getpid(), host, port, MAXCONNECTIONS);
    do
    {
      if ((com = accept(mysocket, NULL, NULL)) < 0)
       {
        perror("accept: ");
        return(-1);
       }

      printf("[%d]: Comunicacao establecida\n", getpid());
      do
      {
        read(com, &size, sizeof(int));
        read(com, buffer, size);

        for( i = 0 ; i < size - 1 ; i++)
          buffer[i] = toupper(buffer[i]);

        write(com, buffer, size);
        printf("[%d]: %s\n", getpid(), buffer); 
     } while (strcasecmp(buffer, "sair") != 0);
     close(com);
    } while (1 == 1);
   }
   else
   {
    fprintf(stderr,"uso: %s interface porta\n", argv[0]);
    return(1);
   }

   return(0);
}
