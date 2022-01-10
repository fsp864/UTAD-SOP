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

void (*handlerUSR1(int signal))(int sinal)
{
}

int main()
{
  int i, memID;
  int pid, leitor = 0, conversor = 0, escritor = 0; 
  char * buffer;  
  struct shmid_ds shmbuf;
 
  signal(SIGUSR1, (void (*)(int))handlerUSR1);   //associar função ao sinal SIGUSR1
  
  if ((memID = shmget(IPC_PRIVATE, MAXLINE + 1, 0600|IPC_CREAT)) != -1)
   {
    leitor = getpid();
    if ((conversor = fork()) == 0)
	 {
	  conversor = getpid();		
//    if ((escritor = fork()) == 0)
//		escritor = getpid();
      escritor = fork();
	 }

    pid = getpid();
	
    if (leitor == pid)                                   /* processo LEITOR */
	 {
 	  printf("Leitor (%d)\n", leitor);
      buffer = shmat(memID, 0, 0);
      do
      {
        fgets(buffer, MAXLINE, stdin);              /* inclui o caracter \n */
        if (strchr(buffer, '\n') != NULL)            /* se string contem \n */
          *(strchr(buffer, '\n')) = '\0';   /* substituir por fim de string */
			
	    kill(conversor, SIGUSR1);
	    pause();

      } while (strcasecmp(buffer, "sair") != 0);
	 }

	 kill(conversor, SIGUSR1);
	   
    if (conversor == pid)                             /* processo CONVERSOR */
	 {
	  printf("Conversor (%d)\n", conversor);
      buffer = shmat(memID, 0, 0);
      do
      {
	    pause();
        for( i = 0 ; i < strlen(buffer) ; i++)
          buffer[i] = toupper(buffer[i]);

        kill(escritor, SIGUSR1);
      } while (strcasecmp(buffer, "sair") != 0);
     }
	   
    if (escritor = pid)                                /* processo ESCRITOR */
	 {
      buffer = shmat(memID, 0, 0);
      do
      {
        pause();

        printf("Esctritor (%d)=%s\n", getpid(), buffer);

        kill(leitor, SIGUSR1);
      } while (strcasecmp(buffer, "sair") != 0);
     }

	shmdt(buffer);
    shmctl(memID, IPC_RMID, &shmbuf);
   }
   else
    perror("Erro bloco de memoria: ");
  return(0);
}

