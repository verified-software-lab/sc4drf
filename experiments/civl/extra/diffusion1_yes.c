// this one has a race because u1 and u2 become aliased
#include <stdlib.h>
#include <stdio.h>

double *u1, *u2, c = 0.2;
int n = 10, nsteps = 10;

int main() {
  u1 = malloc(n*sizeof(double));
  u2 = malloc(n*sizeof(double));
  for (int i=1; i<n-1; i++)
    u2[i] = u1[i] = 1.0*rand()/RAND_MAX;
  u1[0] = u1[n-1] = u2[0] = u2[n-1] = 0.5;
  for (int t=0; t<nsteps; t++) {
#pragma omp parallel for
    for (int i=1; i<n-1; i++) {
      u2[i] = u1[i] + c*(u1[i-1]+u1[i+1]-2*u1[i]);
    }
    double * tmp = u1; u1 = u2; // u2 = tmp;
  }
  for (int i=0; i<n; i++)
    printf("%1.2lf ", u1[i]);
  printf("\n");
  free(u1);
  free(u2);
}

