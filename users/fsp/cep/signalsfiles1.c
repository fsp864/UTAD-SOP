#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#define MAXLINE 80

void (*handlerUSR1(int signal))(int sinal)
{
}

int main()
{
  int comfile, size, i, file, pai, filho;
  char buffer[MAXLINE + 1];
  char com[] = "comfileXXXXXX";

  signal(SIGUSR1, (void (*)(int))handlerUSR1);//associar função ao sinal SIGUSR1

  if ((comfile = mkstemp(com)) != -1)                //criar ficheiro temporario
   {
    switch (filho = fork())                    //guardar PDI do filho para o Pai
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        return -1;
        break;
      case 0:                                                   //processo filho
        pai = getppid();							          //obter PID do Pai
        do 
        {
          fgets(buffer, MAXLINE, stdin);                   //inclui o carater \n
          if (strchr(buffer, '\n') != NULL)                //se string contem \n
            *(strchr(buffer, '\n')) = '\0';       //substituir por fim de string

          size = strlen(buffer);
          write(comfile , &size, sizeof(int));
          write(comfile , buffer, size);
          kill(pai, SIGUSR1);					               	   //acordar Pai
	      pause();                                              //Filho adormece
        } while (strcasecmp(buffer, "sair") != 0);
//        } while (strlen(buffer) != 0);
        
        close(comfile);
        unlink(com);
        break;
      default:                                                    //processo Pai
      	file = open(com, O_RDONLY|O_NONBLOCK);
        do
        {
          pause();			 //esperar pelo acordar do filho (dodos disponiveis)
       	  read(file, &size, sizeof(int)) != sizeof(int);
          read(file, buffer, size);
          
          kill(filho, SIGUSR1);	       	    //acordar filho dados ja forma lidos

          for( i = 0 ; i < size ; i++)
            buffer[i] = toupper(buffer[i]);

	      buffer[size] = '\0';
          puts(buffer);

        } while (strcasecmp(buffer, "sair") != 0);
//        } while (strlen(buffer) != 0);

        close(file);
        unlink(com);
        break;
    }
   }
   else
   {
    perror("Erro ficheiro temporario: ");
    return -1;
   }

  return 0;
}
