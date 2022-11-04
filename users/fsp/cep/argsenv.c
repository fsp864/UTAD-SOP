#include <stdio.h>

#define NORMAL    0

int main(int argc, char * argv[], char * env[])
{
  int i;
  
  printf("Argumentos (%d):\n", argc);
  for( i = 0 ; i < argc ; i++ )
    printf("\targv[%d]=%s\n", i, argv[i]);

  puts("Variaveis de ambiente:");
//  i = 0;
//  while (env[i] != NULL)
  for( i = 0; env[i] != NULL; i++)
    printf("\t env[%d] %s\n", i, env[i]);
  
  return NORMAL;
}
