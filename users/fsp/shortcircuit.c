#include <stdio.h>

int main()
{
  int a=0, b=0;

  if ((a++ == 1) && (b++ == 0))
    a++; 

  printf("a=%d b=%d\n", a, b);

  return 0;
}
