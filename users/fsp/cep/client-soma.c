#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockets.h"

#define MAXLINE 128
#define MAXHOSTNAME	255

int main(int argc,char *argv[])
{
  int i = 0, size, mysocket, port, valor, soma;
  char ch, * host;

  if (argc < 2)
   {
    fprintf(stderr, "uso: %s maquina porta\n", argv[0]);
    return -1;
   }

  host = argv[1];
  port = atoi(argv[2]);
  if ((mysocket = ClientCreateConnection(port, host)) < 0)
   {
    close(mysocket);
    perror("ClientCreateConnection: ");
    return -1;
   }

  printf("Ligacao ao servidor %s:%d (socket %d)\n", host, port, mysocket);
  do
  {
    scanf("%d", &valor);
    write(mysocket, &valor, sizeof(int));  
  } while (valor != 0);
  read(mysocket, &soma, sizeof(int));       
  close(mysocket);
  printf("Soma = %d\n", soma);

  return 0;
}