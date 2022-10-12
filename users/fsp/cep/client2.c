#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockets.h"

#define MAXLINE 128
#define MAXHOSTNAME	255

int main(int argc,char *argv[])
{
  int i = 0, size, mysocket, port;
  char ch, buffer[MAXLINE + 1], * host;

  if (argc < 3)
   {
    fprintf(stderr, "uso: %s maquina porta\n", argv[0]);
    return(1);
   }

  host = argv[1];
  port = atoi(argv[2]);
  if ((mysocket = ClientCreateConnection(port, host)) < 0)
   {
    close(mysocket);
    perror("ClientCreateConnection: ");
    return(1);
   }

  printf("Ligacao ao servidor %s:%d (socket %d)\n", host, port, mysocket);
  do
  {
    fgets(buffer, MAXLINE, stdin);                        //inclui o caracter \n
    if (strchr(buffer, '\n') != NULL)                      //se string contem \n
      *(strchr(buffer, '\n')) = '\0';             //substituir por fim de string

    size = strlen(buffer) + 1;
    write(mysocket, &size, sizeof(int));
    write(mysocket, &buffer, size);
    read(mysocket, &buffer, size);

    puts(buffer);
  } while (strcasecmp(buffer, "sair") != 0);

  close(mysocket);
  
  return(0);
}
