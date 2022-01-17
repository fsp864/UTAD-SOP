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

#define MAXMESSAGE	128
#define MAXCONNECTIONS  3

void waitfunc(void)
{
  while (waitpid(-1, NULL, WNOHANG) > 0);
}

void (*handler(int signal))(int sinal)
{
  puts("Servidor recebeu um SIGHUP");
  exit(0);
}

int GetMessage(int com)
{
  char ch, buffer[MAXMESSAGE] = "Servidor SOP 0v1b2\n";
  int i = 0;

  write(com, buffer, strlen(buffer) + 1); 
  do
  {
   read(com, &ch, sizeof(char));
   buffer[i++] = toupper(ch);
  } while (ch != '\n');
  buffer[i] = '\0';
  write(com ,buffer ,strlen(buffer) + 1);
  close(com);
  printf("%s", buffer);
  return(strcmp(buffer, "SAIR"));
}

int main(int argc, char * argv[])
{
  int mysocket, com, port;
  char * host;

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
      switch(fork())
      {
        case -1 :
          perror("fork: ");
          close(mysocket);
          close(com);
          return(1);
        case 0 :
          printf("[%d]: Comunicacao establecida: ", getpid());
          close(mysocket);
          if (GetMessage(com) == 0)
            kill(getppid(), SIGHUP);
          return(0);
        default :
          close(com);
      } 
    } while (1 == 1);
   }
   else
   {
    fprintf(stderr,"uso: %s interface porta\n", argv[0]);
    return(1);
   }

   return(0);
}
