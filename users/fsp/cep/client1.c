#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockets.h"

#define MAXLINE 128
#define MAXHOSTNAME	255

int main(int argc,char *argv[])
{
  int i = 0, mysocket, port;
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
    perror("ClientCreateConnection: ");
    return(1);
   }

  printf("Ligacao ao servidor %s:%d (socket %d)\n", host, port, mysocket);

  do
  {
    read(mysocket, &buffer[i], sizeof(char));
  } while (buffer[i++] != '\n');
  buffer[i] = '\0';
  printf("%s", buffer);

  fgets(buffer, MAXLINE, stdin);                        //inclui o caracter \n

  write(mysocket, buffer, strlen(buffer));
  read(mysocket, buffer, strlen(buffer));

  close(mysocket);
  printf("%s", buffer);
  
  return 0;
}
