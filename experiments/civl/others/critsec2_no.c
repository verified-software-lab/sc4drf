#include <stdio.h>

int cap = 10, size = 0;
unsigned r = 0;

int main() {
#pragma omp parallel sections shared(size,cap) firstprivate(r) num_threads(2)
  {
#pragma omp section
    while (1) {
#pragma omp critical
      {
	if (size < cap) {
	  size++; // produce
	  printf("Produced! size=%d\n", size);
	  fflush(stdout);
	}
      }
      for (int i=0; i<1000; i++) r=(r+1)%10;
    }
#pragma omp section
    while (1) {
#pragma omp critical
      {
	if (size > 0) {
	  size--; // consume
	  printf("Consumed! size=%d\n", size);
	  fflush(stdout);
	}
      }
      for (int i=0; i<1000; i++) r=(r+1)%10;
    }
  }
}
