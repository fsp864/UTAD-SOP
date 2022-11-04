#include <stdio.h>
#include <stdlib.h>

#define NORMAL    0

int main(int argc, char * argv[])
{
  int i, soma = 0;

  for( i = 0 ; i < argc ; i++ )
    soma += atoi(argv[i]);

  printf("soma = %d\n", soma);

  return NORMAL;
}
