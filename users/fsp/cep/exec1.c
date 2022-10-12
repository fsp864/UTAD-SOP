#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  if (argc > 1)
   {
    printf("%d: Vou executar \"%s\"\n", getpid(), argv[1]);
    execlp(argv[1], argv[1], (char *)NULL);
    fprintf(stderr, "Nao foi possivel obter o programa \"%s\"\n", argv[1]);
   }
   else
    printf("%d: Falta argumento\n", getpid());

  return(0);
}