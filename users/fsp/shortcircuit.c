#include <stdio.h>

int main()
{
  int a = 0, b = 0;

  if ((a++ == 1) && (b++ == 0))       // b++ not executed due to && shor circuit
    a++; 

  printf("a=%d b=%d\n", a, b);

  return 0;
}
