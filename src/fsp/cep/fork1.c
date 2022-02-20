#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  pid_t childpid;

  if ((childpid = fork()) == -1)
    perror(strerror(errno));
   else
     if (childpid == 0)
      printf("%d: Sou o filho\n", getpid());
     else
      printf("%d: Sou o pai e criei o processo %d\n", getpid(), childpid);

  return(0);
}