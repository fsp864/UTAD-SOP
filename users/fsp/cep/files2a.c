#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 80

int main()
{
  int comfile, size;
  char buffer[MAXLINE + 1];
  char com[] = "comfile";

  if ((comfile = creat(com, S_IRWXU)) != -1)                //criar ficheiro
   {
    fgets(buffer, MAXLINE, stdin);                     //inclui o carater \n
    if (strchr(buffer, '\n') != NULL)                  //se string contem \n
      *(strchr(buffer, '\n')) = '\0';         //substituir por fim de string

    size = strlen(buffer);
    write(comfile , &size, sizeof(int));            //enviar nº de carateres
    write(comfile , buffer, size);                        //enviar carateres
       
    close(comfile);
    unlink(com);                               //pedir para remover ficheiro
   }
   else
    perror("Erro no ficheiro temporario");

  return 0;
}
