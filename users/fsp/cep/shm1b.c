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

typedef int Semaphore;

#define MYKEY 0x12345
#define MAXLINE 80
#define P(semID) semaphore(semID, 0, -1, 0)
#define U(semID) semaphore(semID, 0, 1, 0)
#define Init(semID) semaphore(semID, 0, 1, 0)
#define Down(semID) semaphore(semID, 0, -1, 0)
#define Up(semID) semaphore(semID, 0, 1, 0)

void semaphore(Semaphore semID, unsigned sem_num, unsigned sem_op, unsigned short sem_flg)
{
  struct sembuf op;
  op.sem_num = sem_num;
  op.sem_op = sem_op;
  op.sem_flg = sem_flg;
  semop(semID, &op, 1);
}

int main()
{
  int i, semID, memID;
  char * buffer;
  struct shmid_ds shmbuf;
  
  memID = shmget(IPC_PRIVATE, MAXLINE + 1, 0600|IPC_CREAT);        //Criar bloco
  semID = semget(IPC_PRIVATE, 1, 0600|IPC_CREAT);              //Criar semáforos

  if ((memID != -1) && (semID != -1))
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        break;
      case 0:                                                   //processo filho
        buffer = shmat(memID, 0, 0);                 //ligar ao bloco de memoria 

        do
        {
          fgets(buffer, MAXLINE, stdin);                      //inclui o carater
          if (strchr(buffer, '\n') != NULL)                //se string contem \n
            *(strchr(buffer, '\n')) = '\0';       //substituir por fim de string

          Up(semID);                                    //dar vez ao processo pai
//          usleep(1); //evitar entrada do filho de seguida (erro no Ubuntu para windows)
          Down(semID);                                         //esperar pelo pai 

          printf("Filho (%d)=%s\n", getpid(), buffer);
        } while (strcasecmp(buffer, "sair") != 0);
        break;
      default:                                                    //processo pai
		printf("Pai (%d)\n", getpid());
        buffer = shmat(memID, 0, 0);                 //ligar ao bloco de memoria 

        do
        {
          Down(semID);                                       //esperar pelo filho

          for( i = 0 ; i < strlen(buffer) ; i++)
            buffer[i] = toupper(buffer[i]);

          Up(semID);                                  //dar vez ao processo filho
        } while (strcasecmp(buffer, "sair") != 0);
        break;
    }
	shmdt(buffer);
    shmctl(memID, IPC_RMID, &shmbuf);                 //pedir para remover bloco
    semctl(semID, 0, IPC_RMID);                   //pedir para remover semaforos
   }
   else
    perror("Erro bloco de memoria: ");
  return 0;
}
