#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char** argv)
{
  int length;
  if (argc > 1) {
      length = atoi(argv[1]);
  }
  int i;
  srandom((int) time(0));
  for (i = 0; i < length; i++) {
    printf ("%d\n", (rand() % 1000));
  }
  return 0;
}



