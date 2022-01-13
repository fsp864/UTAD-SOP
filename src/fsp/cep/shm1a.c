#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#define MYKEY 0x12345
#define MAXLINE 80
#define PIPEOUT 0
#define PIPEIN 1

int main()
{
  int i, memID, flag = 0;
  int p2f[2], f2p[2];
  char * buffer;
  struct shmid_ds shmbuf;

  pipe(f2p);
  pipe(p2f);

  if ((memID = shmget(MYKEY, MAXLINE + 1, 0666 | IPC_CREAT)) != -1)
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro fork: ");
        break;
      case 0:                                                   //processo filho
        buffer = shmat(memID, NULL, 0);

        do
        {
          fgets(buffer, MAXLINE, stdin);                  //inclui o caracter \n
          if (strchr(buffer, '\n') != NULL)                //se string contem \n
            *(strchr(buffer, '\n')) = '\0';       //substituir por fim de string

          write(f2p[PIPEIN], &flag, sizeof(int));               //dar vez ao PAI
          read(p2f[PIPEOUT], &flag, sizeof(int));             //esperar pelo PAI

          printf("Filho (%d)=%s\n", getpid(), buffer);
        } while (strcasecmp(buffer, "sair") != 0);
        break;
      default:                                                    //processo pai
		printf("Pai (%d)\n", getpid());
        buffer = shmat(memID, NULL, 0);

        do
        {
          read(f2p[PIPEOUT], &flag, sizeof(int));           //esperar pelo FILHO

          for( i = 0 ; i < strlen(buffer) ; i++)
            buffer[i] = toupper(buffer[i]);

          write(p2f[PIPEIN], &flag, sizeof(int));             //dar vez ao FILHO
        } while (strcasecmp(buffer, "sair") != 0);
        break;
    }
    shmdt(buffer);
    shmctl(memID, IPC_RMID, &shmbuf);
   }
   else
    perror("Erro bloco de memoria: ");
  return 0;
}