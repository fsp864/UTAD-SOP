#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int value, pai, filhos = 5;

  pai = getpid();
  while (filhos--)
  {
    if (!fork())
      break;
  }

  scanf("%d", &value);
  printf("%d: li da entrada %d\n", getpid(), value);
//  if (getpid() == pai) 
    wait(NULL);

  return 0;
}