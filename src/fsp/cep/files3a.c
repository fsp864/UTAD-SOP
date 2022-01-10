#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAXLINE 80

ssize_t bread(int fd, void * buf, size_t count)
{
  ssize_t bytes = 0;
  while (bytes != count)
    bytes += read(fd, buf + bytes, count - bytes);
  return bytes;
}
ssize_t bwrite(int fd, void * buf, size_t count)
{
  ssize_t bytes = 0;
  while (bytes != count)
    bytes += write(fd, buf + bytes, count - bytes);
  return bytes;
}
ssize_t wbread(int fd, void * buf, size_t count, useconds_t micros)
{
  ssize_t bytes = 0;
  while (bytes != count)
  {
    bytes += read(fd, buf + bytes, count - bytes);
    usleep(micros);
  }
  return bytes;
}
ssize_t wbwrite(int fd, void * buf, size_t count, useconds_t micros)
{
  ssize_t bytes = 0;
  while (bytes != count)
  {
    bytes += write(fd, buf + bytes, count - bytes);
    usleep(micros);
  }
  return bytes;
}

int main()
{
  int comfile1, comfile2, size, i, file1, file2;
  char buffer[MAXLINE + 1];
  char com1[] = "comfileXXXXXX", com2[] = "comfileXXXXXX";
  comfile1 = mkstemp(com1);                     /* criar ficheiros temporario */
  comfile2 = mkstemp(com2);
  
  if ((comfile1 != -1) && (comfile2 != -1))
   {
    switch (fork())
    {
      case -1:                                              /* erro no fork() */
        perror("Erro fork: ");
        break;
      case 0:                                               /* processo filho */
	    printf("Leitor [%d]\n", getpid());
        fgets(buffer, MAXLINE, stdin);                /* inclui o caracter \n */
        if (strchr(buffer, '\n') != NULL)              /* se string contem \n */
          *(strchr(buffer, '\n')) = '\0';     /* substituir por fim de string */
        size = strlen(buffer);
        bwrite(comfile1 , &size, sizeof(int));
        bwrite(comfile1 , buffer, size);
        
        while ((file2 = open(com2, O_RDONLY)) == -1)
          sleep(1);
      	wbread(file2, &size, sizeof(int),10000);
        bread(file2, buffer, size);
        
		buffer[size] = '\0';                   
        printf("Escritor [%d]: %s\n", getpid(), buffer);
        
        close(comfile1);
        unlink(com1);
        close(comfile2);
        unlink(com2);
        break;
      default:                                                /* processo pai */
	    printf("Conversor [%d]\n", getpid());
        file1 = open(com1, O_RDONLY);
      	wbread(file1, &size, sizeof(int), 10000);
        bread(file1, buffer, size);
		
		
        for( i = 0 ; i < size ; i++)
          buffer[i] = toupper(buffer[i]);
		  
        bwrite(comfile2 , &size, sizeof(int));
        bwrite(comfile2 , buffer, size);

        close(comfile1);
        unlink(com1);
        close(comfile2);
        unlink(com2);
        break;
    }
   }
   else
    perror("Erro ficheiros temporarios: ");
}