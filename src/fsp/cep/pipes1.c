#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define PIPE_OUT 0
#define PIPE_IN 1
#define MAXBUFFER 80

int main()
{
  int i, size;
  int p[2];
  char buffer[MAXBUFFER + 1];

  if (pipe(p) != -1)                                            /* criar pipe */
   {
    switch (fork())
    {
      case -1:                                              /* erro no fork() */
        perror("Erro na criacao do processo filho");
        break;
      case 0:                                               /* processo filho */
	    printf("[%d]: ", getpid());
        fgets(buffer, MAXBUFFER, stdin);               /* inclui o carater \n */
        size = strlen(buffer);
        write(p[PIPE_IN], &size, sizeof(int));
        write(p[PIPE_IN], buffer, size);
        break;
      default:                                                /* processo pai */
        read(p[PIPE_OUT], &size, sizeof(int));
        read(p[PIPE_OUT], buffer, size);
        buffer[size] = '\0';  /*colocar explicitamente o \0 no final da string*/
        for( i = 0 ; i < strlen(buffer) ; i++)   /* converter para maiusculas */
          buffer[i] = toupper(buffer[i]);
        printf("[%d]: texto=%s", getpid(), buffer);
        break;
    }
   }
   else
    perror("Erro na criacao da pipe");
}
