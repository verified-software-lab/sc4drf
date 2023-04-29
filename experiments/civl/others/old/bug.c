#include <stdio.h>
int main() {
  int s=0, done=0;
#pragma omp parallel sections shared(done,s) num_threads(2)
  {
#pragma omp section
    {
#pragma omp critical (A)
      {
	s=1;
      }
    }
#pragma omp section
    {
#pragma omp critical (B)
      {
	int tmp = s;
	if (tmp) done = 1;
      }
    }
  }
  printf("%d\n", done);
}
