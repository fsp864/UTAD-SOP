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
  char ch, line[MAXLINE + 1], * host;

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
    read(mysocket, &line[i], sizeof(char));
  } while (line[i++] != '\n');
  line[--i] = '\0';
  puts(line);

  fgets(line, MAXLINE, stdin);

  write(mysocket, line, strlen(line));
  read(mysocket, line, strlen(line));

  close(mysocket);
  puts(line);
  
  return(0);
}
