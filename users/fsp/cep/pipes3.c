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
  int l2c[2], c2e[2];
  char buffer[MAXBUFFER + 1];

  if ((pipe(l2c)!= -1) && (pipe(c2e) != -1))
   {
    switch (fork())
    {
      case -1:                                                  //erro no fork()
        perror("Erro na criacao do processo filho 1");
        break;
      case 0:                                                   //processo filho
        switch (fork())
        {
          case -1:                                              //erro no fork()
            perror("Erro na criacao do processo filho 2");
            break;
          case 0:
            printf("Leitor [%d]: Ativo\n", getpid());
            do
            {
		      fgets(buffer, MAXBUFFER, stdin);         

              size = strlen(buffer);
              buffer[size - 1] = '\0';                     //exclur o carater \n

              write(l2c[PIPE_IN], &size, sizeof(int));            //enviar texto
              write(l2c[PIPE_IN], buffer, size);

            } while (strcasecmp(buffer, "sair") != 0);

            close(l2c[PIPE_IN]);
            close(l2c[PIPE_OUT]);
            break;
		  default:	
            do
            {
              read(c2e[PIPE_OUT], &size, sizeof(int));
              read(c2e[PIPE_OUT], buffer, size);      //receber texto convertido

              printf("Escritor [%d]: texto=%s\n", getpid(), buffer);
            } while (strcasecmp(buffer, "sair") != 0);

            close(l2c[PIPE_IN]);
            close(l2c[PIPE_OUT]);
            break;
        }
        break;
      default:                                                    //processo pai
        printf("Conversor [%d]: Ativo\n", getpid());
        do
        {
          read(l2c[PIPE_OUT], &size, sizeof(int));            //receber mensagem
          read(l2c[PIPE_OUT], buffer, size);

          for( i = 0 ; i < size ; i++)                      //converter mensagem
            buffer[i] = toupper(buffer[i]);

          write(c2e[PIPE_IN], &size, sizeof(int));             //enviar mensagem
          write(c2e[PIPE_IN], buffer, size);
        } while (strcasecmp(buffer, "sair") != 0);

        close(c2e[PIPE_IN]);
        close(c2e[PIPE_OUT]);

        break;
    }
   }
   else
    perror("Erro na criacao das pipes");

   return 0;
}
