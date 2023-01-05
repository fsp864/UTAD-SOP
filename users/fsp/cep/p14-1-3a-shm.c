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

#define LEITOR 0
#define CALCULADOR 1
#define VALOR 0
#define POSITIVOS 1
#define NEGATIVOS 2

int main()
{
  int i, *shm, semID, memID;
  struct shmid_ds shmbuf;

  memID = shmget(IPC_PRIVATE, 2 * sizeof(int), 0600|IPC_CREAT);
  semID = semget(IPC_PRIVATE, 2, 0600|IPC_CREAT);

  if ((memID != -1) && (semID != -1))
   {
    Init_n(semID, LEITOR);
    switch (fork())
    {
      case -1:                                              /* erro no fork() */
        perror("Erro na criacao do processo filho");
        return -1;
        break;
      case 0:                                               /* processo filho */
        shm = shmat(memID, 0, 0);
        shm[POSITIVOS] = shm[NEGATIVOS] = 0;
        do
        {
          Lock_n(semID, LEITOR);
          printf("[%d] Leitor: ", getpid());
          scanf("%d", &shm[VALOR]);
          Unlock_n(semID, CALCULADOR); 
        } while (shm[VALOR] != 0);
        Lock_n(semID, LEITOR);
        printf("[%d] Calculador: %d valores positivos e %d valores negativos\n", getpid(), shm[POSITIVOS],  shm[NEGATIVOS]);
        break;
      default:                                                /* processo pai */
        shm = shmat(memID, 0, 0);
        do
        {
          Lock_n(semID, CALCULADOR);
          if (shm[VALOR] > 0)
            shm[POSITIVOS]++;
          if (shm[VALOR] < 0)
            shm[NEGATIVOS]++;
          Unlock_n(semID, LEITOR); 
        } while (shm[VALOR] != 0);
        break;
    }
    shmdt(shm);
    shmctl(memID, IPC_RMID, &shmbuf);
    semctl(semID, 0, IPC_RMID);   }
   else
   {
    perror("Erro na criacao da SHM");
    return -1;
   }

  return 0;
}