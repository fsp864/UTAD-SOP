#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAXLINE 80

int main()
{
  int comfile, size, i;
  char buffer[MAXLINE + 1];
  char com[] = "comfile";

  while ((comfile = open(com, O_RDONLY)) == -1);
    //sleep(5);
  puts("Ficheiro aberto");
  
  while (read(comfile, &size, sizeof(int)) != sizeof(int));
    //sleep(5);
  read(comfile, buffer, size);
  close(comfile);
  unlink(com);
      
  for( i = 0 ; i < size ; i++)
    buffer[i] = toupper(buffer[i]);

  buffer[size] = '\0';  
  puts(buffer);
}