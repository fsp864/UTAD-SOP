#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sockets.h"

#define MAXLINE 128
#define MAXHOSTNAME	255

int main(int argc,char *argv[])
{
  int i = 0, com, port, sentido, valor;
  char * host;

  if (argc < 3)
   {
    fprintf(stderr, "uso: %s maquina porta\n", argv[0]);
    return(1);
   }

  host = argv[1];
  port = atoi(argv[2]);
  if ((com = ClientCreateConnection(port, host)) < 0)
   {
    perror("ClientCreateConnection: ");
    return 1;
   }

  printf("Ligacao ao servidor %s:%d (socket %d)\n", host, port, com);

  do
  {
    printf("Valor a enviar: ");
    scanf("%d", &valor);

    write(com, &valor, sizeof(int));
    read(com, &sentido, sizeof(int));

    if (sentido == 0)
      puts("Acertou!!!");
     else
      if (sentido > 0)
        puts("O numero e' para cima");
       else       
        puts("O numero e' para baixo");

  } while (sentido != 0);
  close(com);
  
  return 0;
}