#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define MAXBUFFER       80

#define PIPE_OUT         0
#define PIPE_IN          1

int main()
{
  int i, size;
  int p2f[2], f2p[2];
  char buffer[MAXBUFFER + 1];

  if ((pipe(f2p)!= -1) && (pipe(p2f) != -1))
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro na criacao do processo filho");
        break;
      case 0:                                                   //processo filho
        do
        {
          printf("[%d]: ", getpid());
		  fgets(buffer, MAXBUFFER, stdin);                 //inclui o carater \n

          size = strlen(buffer);
          buffer[size - 1] = '\0';                              //subs \n por \0

          write(f2p[PIPE_IN], &size, sizeof(int));                //enviar texto
          write(f2p[PIPE_IN], buffer, size);

          read(p2f[PIPE_OUT], &size, sizeof(int));    //receber texto convertido
          read(p2f[PIPE_OUT], buffer, size);

          printf("[%d]: texto=%s\n", getpid(), buffer);

        } while (strcasecmp(buffer, "SaIr") != 0);

        close(f2p[PIPE_IN]);
        close(f2p[PIPE_OUT]);

        break;
      default:                                                    //processo pai
        do
        {
          read(f2p[PIPE_OUT], &size, sizeof(int));            //receber mensagem
          read(f2p[PIPE_OUT], buffer, size);

          for( i = 0 ; i < size ; i++)                      //converter mensagem
            buffer[i] = toupper(buffer[i]);
          printf("[%d]: Texto convertido\n", getpid());

          write(p2f[PIPE_IN], &size, sizeof(int));             //enviar mensagem
          write(p2f[PIPE_IN], buffer, size);

        } while (strcasecmp(buffer, "SAir") != 0);

        close(p2f[PIPE_IN]);
        close(p2f[PIPE_OUT]);

        break;
    }
   }
   else
    perror("Erro na criacao das pipes");

  return 0;
}
