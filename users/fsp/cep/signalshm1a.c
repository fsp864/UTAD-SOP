#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>

#define MYKEY 12345
#define MAXLINE 80

char * buffer;  

void (*handlerUSR1leitor(int signal))(int sinal)
{
  printf("[%d] Leitor: ", getpid());
  fgets(buffer, MAXLINE, stdin);                    //inclui o caracter \n
  if (strchr(buffer, '\n') != NULL)                  //se string contem \n
    *(strchr(buffer, '\n')) = '\0';         //substituir por fim de string
}

void (*handlerUSR1conversor(int signal))(int sinal)
{
  int i;

  printf("[%d] Converor convertendo...\n", getpid());
  for( i = 0 ; i < strlen(buffer) ; i++)
    buffer[i] = toupper(buffer[i]);
}

void (*handlerUSR1escritor(int signal))(int sinal)
{
   printf("[%d] Escritor: %s\n", getpid(), buffer);
}

int main()
{
  int i, memID;
  int pid, leitor = -1, conversor = -1, escritor = -1; 
  struct shmid_ds shmbuf;
 
  if ((memID = shmget(IPC_PRIVATE, MAXLINE + 1, 0600|IPC_CREAT)) != -1)
   {
    leitor = getpid();                            //zona de criacão de processos
                                                  //pai leitor
    if ((conversor = fork()) == 0)                //cria filho 1
     {
      conversor = getpid();		                  //filho 1 conversor
      if ((escritor = fork()) == 0)               //filho 1 cria filho 2 
        escritor = getpid();                      //filho 2 escrito
     }

    pid = getpid();	
    printf("[%d] leitor = %d, conversor = %d e escritor %d\n", pid, leitor, conversor, escritor);

    if (pid == leitor)                                         //processo LEITOR
     {
      buffer = shmat(memID, 0, 0);
      signal(SIGUSR1, (void (*)(int))handlerUSR1leitor);//associar função ao sinal SIGUSR1

      usleep(1000); //adormecer por 1000 usegundo para os outros processos apresentar info do printf anterior
      kill(leitor, SIGUSR1);
      do
      {
        kill(conversor, SIGUSR1);
        pause();
//      } while (strcasecmp(buffer, "sair") != 0);
      } while (strlen(buffer) != 0);
     }
	   
    if (pid == conversor)                                   //processo CONVERSOR
     {
      buffer = shmat(memID, 0, 0);
      signal(SIGUSR1, (void (*)(int))handlerUSR1conversor);//associar função ao sinal SIGUSR1

      do
      {
        pause();
        kill(escritor, SIGUSR1);
//      } while (strcasecmp(buffer, "sair") != 0);
      } while (strlen(buffer) != 0);
     }
	   
    if (pid == escritor)                                     //processo ESCRITOR
     {
      buffer = shmat(memID, 0, 0);
      signal(SIGUSR1, (void (*)(int))handlerUSR1escritor);//associar função ao sinal SIGUSR1

      do
      {
        pause();
        kill(leitor, SIGUSR1);
//      } while (strcasecmp(buffer, "sair") != 0);
      } while (strlen(buffer) != 0);
     }

    shmdt(buffer);							//todos detach
    shmctl(memID, IPC_RMID, &shmbuf);       //todos pedem para remover
   }
   else
   {
    perror("Erro bloco de memoria: ");
    return -1;
   }

  return 0;
}