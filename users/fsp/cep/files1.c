#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAXLINE 80

int main()
{
  int comfile, size, i, file;
  char buffer[MAXLINE + 1];
  char com[] = "comfileXXXXXX";

  if ((comfile = mkstemp(com)) != -1)                //criar ficheiro temporario
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        break;
      case 0:                                                   //processo filho
        fgets(buffer, MAXLINE, stdin);                     //inclui o carater \n
        if (strchr(buffer, '\n') != NULL)                  //se string contem \n
          *(strchr(buffer, '\n')) = '\0';         //substituir por fim de string

        size = strlen(buffer);
        write(comfile , &size, sizeof(int));
        write(comfile , buffer, size);
        
        close(comfile);
        unlink(com);
        break;
      default:                                                    //processo pai
      	file = open(com, O_RDONLY);
      	while (read(file, &size, sizeof(int)) != sizeof(int))
          usleep(10000);
        read(file, buffer, size);

        close(file);
        unlink(com);
        
        for( i = 0 ; i < size ; i++)
          buffer[i] = toupper(buffer[i]);

	    buffer[size] = '\0';
        puts(buffer);
        break;
    }
   }
   else
    perror("Erro ficheiro temporario: ");
}