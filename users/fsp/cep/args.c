#include <stdio.h>

#define NORMAL    0

int main(int argc, char * argv[])
{
  int i;

  printf("Argumentos (%d):\n", argc);
  for( i = 0 ; i < argc ; i++ )
    printf("\targv[%d]=%s\n", i, argv[i]);

  return NORMAL;
}
