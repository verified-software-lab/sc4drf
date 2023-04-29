/**
 * jacobi-2d-imper.c: This file is part of the PolyBench/C 3.2 test suite.
 * Jacobi with array copying, no reduction. 
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 * License: /LICENSE.OSU.txt
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
// #include "polybench/polybench.h"
/* Include benchmark-specific header. */
/* Default data type is double, default size is 20x1000. */
// #include "polybench/jacobi-2d-imper.h"
/* Array initialization. */

#ifdef _CIVL
#include <civlc.cvh>
$input int N, BOUND = 500;
$assume(1 <= N && N <= BOUND);
int M = N-2;
int P = N-3;
#else
#define N (500)
#define M (N-2)
#define P (N-3)
#endif  // _CIVL 

static void init_array(int n,double A[N + 0][N + 0],double B[N + 0][N + 0])
{
  //int i;
  //int j;
{
    int c2;
    int c1;
    if (n >= 1) {
#pragma omp parallel for private(c2)
      for (c1 = 0; c1 <= n + -1; c1++) {
        for (c2 = 0; c2 <= n + -1; c2++) {
          A[c1][c2] = (((double )c1) * (c2 + 2) + 2) / n;
          B[c1][c2] = (((double )c1) * (c2 + 3) + 3) / n;
        }
      }
    }
  }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int n,double A[N + 0][N + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      fprintf(stderr,"%0.2lf ",A[i][j]);
      if ((i * n + j) % 20 == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_jacobi_2d_imper(int tsteps,int n,double A[N + 0][N + 0],double B[N + 0][N + 0])
{
  //int t;
  //int i;
  //int j;
  
  //#pragma scop
{
    int c2;
    int c1;
    int c0;
    for (c2 = 1; c2 <= M; c2++) {
      B[1][c2] = 0.2 * (A[1][c2] + A[1][c2 - 1] + A[1][1 + c2] + A[2][c2] + A[0][c2]);
    }
    for (c0 = 2; c0 <= M+27; c0++) {
      if (c0 <= 27+1) {
        if ((2 * c0 + 1) % 3 == 0) {
          for (c2 = 1; c2 <= M; c2++) {
            B[1][c2] = 0.2 * (A[1][c2] + A[1][c2 - 1] + A[1][1 + c2] + A[2][c2] + A[0][c2]);
          }
        }
      }
      int c1s = ((((2 * c0 + 2) * 3 < 0?-(-(2 * c0 + 2) / 3) : ((3 < 0?(-(2 * c0 + 2) + - 3 - 1) / - 3 : (2 * c0 + 2 + 3 - 1) / 3)))) > c0 + -9?(((2 * c0 + 2) * 3 < 0?-(-(2 * c0 + 2) / 3) : ((3 < 0?(-(2 * c0 + 2) + - 3 - 1) / - 3 : (2 * c0 + 2 + 3 - 1) / 3)))) : c0 + -9);
      int c1e = (((((2 * c0 + M) * 3 < 0?((3 < 0?-((-(2 * c0 + M) + 3 + 1) / 3) : -((-(2 * c0 + M) + 3 - 1) / 3))) : (2 * c0 + M) / 3)) < c0?(((2 * c0 + M) * 3 < 0?((3 < 0?-((-(2 * c0 + M) + 3 + 1) / 3) : -((-(2 * c0 + M) + 3 - 1) / 3))) : (2 * c0 + M) / 3)) : c0));

#pragma omp parallel for private(c2)
      for (c1 = c1s; c1 <= c1e; c1++) {
        B[-2 * c0 + 3 * c1][1] = 0.2 * (A[-2 * c0 + 3 * c1][1] + A[-2 * c0 + 3 * c1][1 - 1] + A[-2 * c0 + 3 * c1][1 + 1] + A[1 + (-2 * c0 + 3 * c1)][1] + A[-2 * c0 + 3 * c1 - 1][1]);
        for (c2 = 2 * c0 + -2 * c1 + 2; c2 <= 2 * c0 + -2 * c1 + M; c2++) {
          A[-2 * c0 + 3 * c1 + -1][-2 * c0 + 2 * c1 + c2 + -1] = B[-2 * c0 + 3 * c1 + -1][-2 * c0 + 2 * c1 + c2 + -1];
          B[-2 * c0 + 3 * c1][-2 * c0 + 2 * c1 + c2] = 0.2 * (A[-2 * c0 + 3 * c1][-2 * c0 + 2 * c1 + c2] + A[-2 * c0 + 3 * c1][-2 * c0 + 2 * c1 + c2 - 1] + A[-2 * c0 + 3 * c1][1 + (-2 * c0 + 2 * c1 + c2)] + A[1 + (-2 * c0 + 3 * c1)][-2 * c0 + 2 * c1 + c2] + A[-2 * c0 + 3 * c1 - 1][-2 * c0 + 2 * c1 + c2]);
        }
        A[-2 * c0 + 3 * c1 + -1][M] = B[-2 * c0 + 3 * c1 + -1][M];
      }
      if (c0 >= M+1) {
        if ((2 * c0 + 1) % 3 == 0) {
          for (c2 = 1; c2 <= M; c2++) {
            A[M][c2] = B[M][c2];
          }
        }
      }
    }
    for (c2 = 1; c2 <= M; c2++) {
      A[M][c2] = B[M][c2];
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
  double (A)[N + 0][N + 0];
  double (B)[N + 0][N + 0];
/* Initialize array(s). */
  init_array(n, A, B);
/* Start timer. */
  // polybench_timer_start();
  // ;
/* Run kernel. */
  kernel_jacobi_2d_imper(tsteps,n, A, B);
/* Stop and print timer. */
  // polybench_timer_stop();
  // ;
  // polybench_timer_print();
  // ;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  // if (argc > 42 && !strcmp(argv[0],"")) 
  //  print_array(n, *A);
/* Be clean. */
  return 0;
}
