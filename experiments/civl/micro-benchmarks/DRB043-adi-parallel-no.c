/**
 * adi.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 * Alternating Direction Implicit solver: 
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 * License: /LICENSE.OSU.txt
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
/* Include polybench common header. */
// #include "polybench/polybench.h"
/* Include benchmark-specific header. */
/* Default data type is double, default size is 10x1024x1024. */
// #include "polybench/adi.h"
/* Array initialization. */

#ifdef _CIVL
#include <civlc.cvh>
#include <stdlib.h>
$input int N, BOUND = 4;
$assume(1 <= N && N <= BOUND);
int M = N-1;
int P = N-3;
#else
#define N (500)
#define M (N-1)
#define P (N-3)
#endif  // _CIVL 

static void init_array(int n,double X[N + 0][N + 0],double A[N + 0][N + 0],double B[N + 0][N + 0])
{
  //int i;
  //int j;
{
    int c1;
    int c2;
    if (n >= 1) {
#pragma omp parallel for private(c2)
      for (c1 = 0; c1 <= n + -1; c1++) {
        for (c2 = 0; c2 <= n + -1; c2++) {
          X[c1][c2] = (((double )c1) * (c2 + 1) + 1) / n;
          A[c1][c2] = (((double )c1) * (c2 + 2) + 2) / n;
          B[c1][c2] = (((double )c1) * (c2 + 3) + 3) / n;
        }
      }
    }
  }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int n,double X[N + 0][N + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      fprintf(stderr,"%0.2lf ",X[i][j]);
      if ((i * N + j) % 20 == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_adi(int tsteps,int n,double X[N + 0][N + 0],double A[N + 0][N + 0],double B[N + 0][N + 0])
{
  //int t;
  //int i1;
  //int i2;
  
  //#pragma scop
{
    int c0;
    int c2;
    int c8;
    for (c0 = 0; c0 <= 9; c0++) {
#pragma omp parallel for private(c8)
      for (c2 = 0; c2 <= M; c2++) {
        for (c8 = 1; c8 <= M; c8++) {
          B[c2][c8] = B[c2][c8] - A[c2][c8] * A[c2][c8] / B[c2][c8 - 1];
        }
        for (c8 = 1; c8 <= M; c8++) {
          X[c2][c8] = X[c2][c8] - X[c2][c8 - 1] * A[c2][c8] / B[c2][c8 - 1];
        }
        for (c8 = 0; c8 <= P; c8++) {
          X[c2][N - c8 - 2] = (X[c2][N - 2 - c8] - X[c2][N - 2 - c8 - 1] * A[c2][N - c8 - 3]) / B[c2][N - 3 - c8];
        }
      }
#pragma omp parallel for
      for (c2 = 0; c2 <= M; c2++) {
        X[c2][N - 1] = X[c2][N - 1] / B[c2][N - 1];
      }
#pragma omp parallel for private(c8)
      for (c2 = 0; c2 <= M; c2++) {
        for (c8 = 1; c8 <= M; c8++) {
          B[c8][c2] = B[c8][c2] - A[c8][c2] * A[c8][c2] / B[c8 - 1][c2];
        }
        for (c8 = 1; c8 <= M; c8++) {
          X[c8][c2] = X[c8][c2] - X[c8 - 1][c2] * A[c8][c2] / B[c8 - 1][c2];
        }
        for (c8 = 0; c8 <= P; c8++) {
          X[N - 2 - c8][c2] = (X[N - 2 - c8][c2] - X[N - c8 - 3][c2] * A[N - 3 - c8][c2]) / B[N - 2 - c8][c2];
        }
      }
#pragma omp parallel for
      for (c2 = 0; c2 <= M; c2++) {
        X[N - 1][c2] = X[N - 1][c2] / B[N - 1][c2];
      }
    }
  }
  
//#pragma endscop
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = N;
  int tsteps = 10;
/* Variable declaration/allocation. */
  double (*X)[N + 0][N + 0];
  X = ((double (*)[N + 0][N + 0])(malloc(((N + 0) * (N + 0))*(sizeof(double )))));
  ;
  double (*A)[N + 0][N + 0];
  A = ((double (*)[N + 0][N + 0])(malloc(((N + 0) * (N + 0))*(sizeof(double )))));
  ;
  double (*B)[N + 0][N + 0];
  B = ((double (*)[N + 0][N + 0])(malloc(((N + 0) * (N + 0))*(sizeof(double )))));
  ;
/* Initialize array(s). */
  init_array(n, *X, *A, *B);
/* Start timer. */
  // polybench_timer_start();
  // ;
/* Run kernel. */
  kernel_adi(tsteps,n, *X, *A, *B);
/* Stop and print timer. */
  // polybench_timer_stop();
  // ;
  // polybench_timer_print();
  // ;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  // if (argc > 42 && !strcmp(argv[0],"")) 
  //  print_array(n, *X);
/* Be clean. */
  free(((void *)X));
  ;
  free(((void *)A));
  ;
  free(((void *)B));
  ;
  return 0;
}
