#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  printf("%d: Sou o programa 2\n", getpid());

  return 0;
}
