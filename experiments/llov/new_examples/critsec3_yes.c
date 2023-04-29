#include <stdio.h>
int main() {
  int x=0, s=0;
#pragma omp parallel sections shared(x,s) num_threads(2)
  {
#pragma omp section
    {
      x=1;
#pragma omp critical (A)
      {
	s=1;
      }
    }
#pragma omp section
    {
      int done = 0;
      while (!done) {
#pragma omp critical (B)
	{
	  if (s) done = 1;
	}
      }
      x=2;
    }
  }
  printf("%d\n", x);
}
