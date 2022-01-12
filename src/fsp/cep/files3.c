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
  int comfile1, comfile2, size, i, file1, file2;
  char buffer[MAXLINE + 1];
  char com1[] = "comfileXXXXXX", com2[] = "comfileXXXXXX";
  
  if (((comfile1 = mkstemp(com1)) != -1)            //criar ficheiros temporario
     && ((comfile2 = mkstemp(com2)) != -1))
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        break;
      case 0:                                                   //processo filho
	    printf("Leitor [%d]\n", getpid());
        fgets(buffer, MAXLINE, stdin);                    //inclui o caracter \n
        if (strchr(buffer, '\n') != NULL)                  //se string contem \n
          *(strchr(buffer, '\n')) = '\0';         //substituir por fim de string

        size = strlen(buffer);
        write(comfile1 , &size, sizeof(int));
        write(comfile1 , buffer, size);
        
        file2 = open(com2, O_RDONLY);
        //  sleep(1);
      	while (read(file2, &size, sizeof(int)) != sizeof(int));
        //  sleep(1);
        read(file2, buffer, size);
        
		buffer[size] = '\0';
        printf("Escritor [%d]: %s\n", getpid(), buffer);
        
        close(comfile1);
        close(comfile2);
//        unlink(com1);
//        unlink(com2);
        break;
      default:                                                    //processo pai
	    printf("Conversor [%d]\n", getpid());
        file1 = open(com1, O_RDONLY);
      	while (read(file1, &size, sizeof(int)) != sizeof(int));
        //  sleep(1);
        read(file1, buffer, size);
				
        for( i = 0 ; i < size ; i++)
          buffer[i] = toupper(buffer[i]);

        write(comfile2 , &size, sizeof(int));
        write(comfile2 , buffer, size);

        close(comfile1);
        close(comfile2);
//        unlink(com1);
//        unlink(com2);
        break;
    }
   }
   else
    perror("Erro ficheiros temporarios: ");
}