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
  int coml2c_f, comc2e_f, size, i, l2c_f, c2e_f, pai, leitor, escritor;
  char buffer[MAXLINE + 1];
  char l2c[] = "comfileXXXXXX", c2e[] = "comfileXXXXXX";

  signal(SIGUSR1, (void (*)(int))handlerUSR1);//associar função ao sinal SIGUSR1

  if (((coml2c_f = mkstemp(l2c)) != -1) && ((comc2e_f = mkstemp(c2e)) != -1))
   {
    switch (leitor = fork())                    //guardar PDI do filho para o Pai
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        return -1;
        break;
      case 0:                                                   //processo filho
        pai = getppid();							          //obter PID do Pai
        do 
        {
          printf("[%d] Leitor: ", getpid());
          fgets(buffer, MAXLINE, stdin);                   //inclui o carater \n
          if (strchr(buffer, '\n') != NULL)                //se string contem \n
            *(strchr(buffer, '\n')) = '\0';       //substituir por fim de string

          size = strlen(buffer) + 1;
          write(coml2c_f , &size, sizeof(int));
          write(coml2c_f , buffer, size);

          kill(pai, SIGUSR1);					               	   //acordar Pai

          pause();                                              //Filho adormece
        } while (strcasecmp(buffer, "sair") != 0);
//        } while (strlen(buffer) != 0);
        
        break;
      default:                                                    //processo Pai
        switch (escritor = fork())                    //guardar PDI do filho para o Pai
        {
          case -1:                                                  //erro no fork()
            perror("Erro fork: ");
            return -1;
            break;
          case 0:                                                   //processo filho
        	c2e_f = open(c2e, O_RDONLY|O_NONBLOCK);
            do
            {
              pause();			 //esperar pelo acordar do filho (dodos disponiveis)

       	      read(c2e_f, &size, sizeof(int)) != sizeof(int);
              read(c2e_f, buffer, size);

              printf("[%d] Escritor: %s\n", getpid(), buffer);

              kill(leitor, SIGUSR1);	       	    //acordar leitor
            } while (strcasecmp(buffer, "sair") != 0);
//            } while (strlen(buffer) != 0);
            close(c2e_f);

            break;
          default:
        	l2c_f = open(l2c, O_RDONLY|O_NONBLOCK);
            do
            {
              pause();			 //esperar pelo acordar do filho (dodos disponiveis)

       	      read(l2c_f, &size, sizeof(int)) != sizeof(int);
              read(l2c_f, buffer, size);
          
              printf("[%d] Conversor: %s -> ", getpid(), buffer);
              for( i = 0 ; i < size ; i++)
                buffer[i] = toupper(buffer[i]);
              printf("%s\n", buffer);

              write(comc2e_f , &size, sizeof(int));
              write(comc2e_f , buffer, size);

              kill(escritor, SIGUSR1);	       	    //acordar escritor
            } while (strcasecmp(buffer, "sair") != 0);
//            } while (strlen(buffer) != 0);

            close(l2c_f);
        }
    }
   }
   else
   {
    perror("Erro ficheiro temporario: ");
    return -1;
   }

  close(coml2c_f);
  close(comc2e_f);
  unlink(l2c);
  unlink(c2e);
 
  return 0;
}