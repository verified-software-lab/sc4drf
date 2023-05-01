#include <stdio.h>
int main() {
  int a[2], i=0, j=1;
#pragma omp parallel sections shared(a,i,j) num_threads(2)
  {
#pragma omp section
    a[i] = 1;
#pragma omp section
    a[j] = 2;
  }
  printf("%d %d\n", a[i], a[j]);
}
