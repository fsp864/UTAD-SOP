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

typedef int Semaphore;

#define MYKEY 12345
#define MAXLINE 80
#define P_n(semID, nsem) semaphore(semID, nsem, -1, 0)
#define U_n(semID, nsem) semaphore(semID, nsem, 1, 0)
#define Init_n(semID, nsem) semaphore(semID, nsem, 1, 0)
#define Down_n(semID, nsem) semaphore(semID, nsem, -1, 0)
#define Up_n(semID, nsem) semaphore(semID, nsem, 1, 0)
#define Lock_n(semID, nsem) semaphore(semID, nsem, -1, 0)
#define Unlock_n(semID, nsem) semaphore(semID, nsem, 1, 0)

void semaphore(Semaphore semID, unsigned sem_num, unsigned sem_op, unsigned short sem_flg)
{
  struct sembuf op;
  op.sem_num = sem_num;
  op.sem_op = sem_op;
  op.sem_flg = sem_flg;
  semop(semID, &op, 1);
}

#define LEITOR		0
#define CONVERSOR	1
#define ESCRITOR	2

int main()
{
  int i, semID, memID;
  char * buffer;
  struct shmid_ds shmbuf;

  memID = shmget(IPC_PRIVATE, MAXLINE + 1, 0600 | IPC_CREAT);
  semID = semget(IPC_PRIVATE, 3, 0600 | IPC_CREAT);

  if ((memID != -1) && (semID != -1))
   {
    Init_n(semID, LEITOR);                     //Iniciar no LEITOR, semaforo a 1

    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        break;
      case 0:                                                   //processo filho
		printf("Leitor (%d)\n", getpid());
        buffer = shmat(memID, 0, 0);
        do
        {
          Lock_n(semID, LEITOR);

          fgets(buffer, MAXLINE, stdin);                  //inclui o caracter \n
          if (strchr(buffer, '\n') != NULL)                //se string contem \n
            *(strchr(buffer, '\n')) = '\0';       //substituir por fim de string

          Unlock_n(semID, CONVERSOR);                     //dar vez ao CONVERSOR
        } while (strlen(buffer) != 0);
        break;
      default:                                                    //processo pai
        switch (fork())
        {
          case -1:                                              //erro no fork()
            perror("Erro fork: ");
            break;
          case 0:                                           //processo CONVERSOR
   		    printf("Conversor (%d)\n", getpid());
            buffer = shmat(memID, 0, 0);
            do
            {
              Lock_n(semID, CONVERSOR);

              for( i = 0 ; i < strlen(buffer) ; i++)
                buffer[i] = toupper(buffer[i]);

              Unlock_n(semID, ESCRITOR);                   //dar vez ao ESCRITOR
            } while (strlen(buffer) != 0);
            break;
          default:                                           //processo ESCRITOR
            buffer = shmat(memID, 0, 0);
            do
            {
              Lock_n(semID, ESCRITOR);

              printf("Esctritor (%d)=%s\n", getpid(), buffer);

              Unlock_n(semID, LEITOR);                       //dar vez ao LEITOR
            } while (strlen(buffer) != 0);
            break;            
        }
    }
	shmdt(buffer);                                         //desligar da memoria
    shmctl(memID, IPC_RMID, &shmbuf);                 //remover bloco de memoria
    semctl(semID, 0, IPC_RMID);                              //remover semaforos
   }
   else
   {
    perror("Erro bloco de memoria: ");
    return 1;
   }

  return 0;
}
