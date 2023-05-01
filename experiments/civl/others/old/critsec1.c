#include <stdio.h>

int cap = 10, size = 0;

int main() {
#pragma omp parallel sections shared(size,cap)
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
    }
  }
}
