/**
 * adi.c: This file is part of the PolyBench/C 3.2 test suite.
 * Alternating Direction Implicit solver with tiling and nested SIMD.
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

/**
 * polybench.h: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 * License: /LICENSE.OSU.txt
 */
/*
 * Polybench header for instrumentation.
 *
 * Programs must be compiled with `-I utilities utilities/polybench.c'
 *
 * Optionally, one can define:
 *
 * -DPOLYBENCH_TIME, to report the execution time,
 *   OR (exclusive):
 * -DPOLYBENCH_PAPI, to use PAPI H/W counters (defined in polybench.c)
 *
 *
 * See README or utilities/polybench.c for additional options.
 *
 */
#ifndef POLYBENCH_H
# define POLYBENCH_H

# include <stdlib.h>

/* Array padding. By default, none is used. */
# ifndef POLYBENCH_PADDING_FACTOR
/* default: */
#  define POLYBENCH_PADDING_FACTOR 0
# endif


/* C99 arrays in function prototype. By default, do not use. */
# ifdef POLYBENCH_USE_C99_PROTO
#  define POLYBENCH_C99_SELECT(x,y) y
# else
/* default: */
#  define POLYBENCH_C99_SELECT(x,y) x
# endif


/* Scalar loop bounds in SCoPs. By default, use parametric loop bounds. */
# ifdef POLYBENCH_USE_SCALAR_LB
#  define POLYBENCH_LOOP_BOUND(x,y) x
# else
/* default: */
#  define POLYBENCH_LOOP_BOUND(x,y) y
# endif


/* Macros to reference an array. Generic for heap and stack arrays
   (C99).  Each array dimensionality has his own macro, to be used at
   declaration or as a function argument.
   Example:
   int b[x] => POLYBENCH_1D_ARRAY(b, x)
   int A[N][N] => POLYBENCH_2D_ARRAY(A, N, N)
*/
# ifndef POLYBENCH_STACK_ARRAYS
#  define POLYBENCH_ARRAY(x) *x
#  define POLYBENCH_FREE_ARRAY(x) free((void*)x);
#  define POLYBENCH_DECL_VAR(x) (*x)
# else
#  define POLYBENCH_ARRAY(x) x
#  define POLYBENCH_FREE_ARRAY(x)
#  define POLYBENCH_DECL_VAR(x) x
# endif
/* Macros for using arrays in the function prototypes. */
# define POLYBENCH_1D(var, dim1,ddim1) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_2D(var, dim1, dim2, ddim1, ddim2) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_3D(var, dim1, dim2, dim3, ddim1, ddim2, ddim3) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_4D(var, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim4,ddim4) + POLYBENCH_PADDING_FACTOR]
# define POLYBENCH_5D(var, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) var[POLYBENCH_C99_SELECT(dim1,ddim1) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim2,ddim2) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim3,ddim3) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim4,ddim4) + POLYBENCH_PADDING_FACTOR][POLYBENCH_C99_SELECT(dim5,ddim5) + POLYBENCH_PADDING_FACTOR]


/* Macros to allocate heap arrays.
   Example:
   polybench_alloc_2d_array(N, M, double) => allocates N x M x sizeof(double)
					  and returns a pointer to the 2d array
 */
# define POLYBENCH_ALLOC_1D_ARRAY(n1, type)	\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data (n1 + POLYBENCH_PADDING_FACTOR, sizeof(type))
# define POLYBENCH_ALLOC_2D_ARRAY(n1, n2, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_3D_ARRAY(n1, n2, n3, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_4D_ARRAY(n1, n2, n3, n4, type)			\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR][n4 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR) * (n4 + POLYBENCH_PADDING_FACTOR), sizeof(type))
# define POLYBENCH_ALLOC_5D_ARRAY(n1, n2, n3, n4, n5, type)		\
  (type(*)[n1 + POLYBENCH_PADDING_FACTOR][n2 + POLYBENCH_PADDING_FACTOR][n3 + POLYBENCH_PADDING_FACTOR][n4 + POLYBENCH_PADDING_FACTOR][n5 + POLYBENCH_PADDING_FACTOR])polybench_alloc_data ((n1 + POLYBENCH_PADDING_FACTOR) * (n2 + POLYBENCH_PADDING_FACTOR) * (n3 + POLYBENCH_PADDING_FACTOR) * (n4 + POLYBENCH_PADDING_FACTOR) * (n5 + POLYBENCH_PADDING_FACTOR), sizeof(type))

/* Macros for array declaration. */
# ifndef POLYBENCH_STACK_ARRAYS
#  define POLYBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1)		\
  type POLYBENCH_1D(POLYBENCH_DECL_VAR(var), dim1, ddim1); \
  var = POLYBENCH_ALLOC_1D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), type);
#  define POLYBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2)	\
  type POLYBENCH_2D(POLYBENCH_DECL_VAR(var), dim1, dim2, ddim1, ddim2); \
  var = POLYBENCH_ALLOC_2D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), type);
#  define POLYBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
  type POLYBENCH_3D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, ddim1, ddim2, ddim3); \
  var = POLYBENCH_ALLOC_3D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), type);
#  define POLYBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) \
  type POLYBENCH_4D(POLYBENCH_DECL_VAR(var), dim1, dim2, ,dim3, dim4, ddim1, ddim2, ddim3, ddim4); \
  var = POLYBENCH_ALLOC_4D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), POLYBENCH_C99_SELECT(dim4, ddim4), type);
#  define POLYBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) \
  type POLYBENCH_5D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5); \
  var = POLYBENCH_ALLOC_5D_ARRAY(POLYBENCH_C99_SELECT(dim1, ddim1), POLYBENCH_C99_SELECT(dim2, ddim2), POLYBENCH_C99_SELECT(dim3, ddim3), POLYBENCH_C99_SELECT(dim4, ddim4), POLYBENCH_C99_SELECT(dim5, ddim5), type);
# else
#  define POLYBENCH_1D_ARRAY_DECL(var, type, dim1, ddim1)		\
  type POLYBENCH_1D(POLYBENCH_DECL_VAR(var), dim1, ddim1);
#  define POLYBENCH_2D_ARRAY_DECL(var, type, dim1, dim2, ddim1, ddim2)	\
  type POLYBENCH_2D(POLYBENCH_DECL_VAR(var), dim1, dim2, ddim1, ddim2);
#  define POLYBENCH_3D_ARRAY_DECL(var, type, dim1, dim2, dim3, ddim1, ddim2, ddim3) \
  type POLYBENCH_3D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, ddim1, ddim2, ddim3);
#  define POLYBENCH_4D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4) \
  type POLYBENCH_4D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, ddim1, ddim2, ddim3, ddim4);
#  define POLYBENCH_5D_ARRAY_DECL(var, type, dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5) \
  type POLYBENCH_5D(POLYBENCH_DECL_VAR(var), dim1, dim2, dim3, dim4, dim5, ddim1, ddim2, ddim3, ddim4, ddim5);
# endif


/* Dead-code elimination macros. Use argc/argv for the run-time check. */
# ifndef POLYBENCH_DUMP_ARRAYS
#  define POLYBENCH_DCE_ONLY_CODE    if (argc > 42 && ! strcmp(argv[0], ""))
# else
#  define POLYBENCH_DCE_ONLY_CODE
# endif

# define polybench_prevent_dce(func)		\
  POLYBENCH_DCE_ONLY_CODE			\
  func


/* Performance-related instrumentation. See polybench.c */
# define polybench_start_instruments
# define polybench_stop_instruments
# define polybench_print_instruments


/* PAPI support. */
# ifdef POLYBENCH_PAPI
extern const unsigned int polybench_papi_eventlist[];
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_set_papi_thread_report(x)	\
   polybench_papi_counters_threadid = x;
#  define polybench_start_instruments				\
  polybench_prepare_instruments();				\
  polybench_papi_init();					\
  int evid;							\
  for (evid = 0; polybench_papi_eventlist[evid] != 0; evid++)	\
    {								\
      if (polybench_papi_start_counter(evid))			\
	continue;						\

#  define polybench_stop_instruments		\
      polybench_papi_stop_counter(evid);	\
    }						\
  polybench_papi_close();			\

#  define polybench_print_instruments polybench_papi_print();
# endif


/* Timing support. */
# if defined(POLYBENCH_TIME) || defined(POLYBENCH_GFLOPS)
#  undef polybench_start_instruments
#  undef polybench_stop_instruments
#  undef polybench_print_instruments
#  define polybench_start_instruments polybench_timer_start();
#  define polybench_stop_instruments polybench_timer_stop();
#  define polybench_print_instruments polybench_timer_print();
extern double polybench_program_total_flops;
extern void polybench_timer_start();
extern void polybench_timer_stop();
extern void polybench_timer_print();
# endif

/* Function declaration. */
# ifdef POLYBENCH_TIME
extern void polybench_timer_start();
extern void polybench_timer_stop();
extern void polybench_timer_print();
# endif

# ifdef POLYBENCH_PAPI
extern void polybench_prepare_instruments();
extern int polybench_papi_start_counter(int evid);
extern void polybench_papi_stop_counter(int evid);
extern void polybench_papi_init();
extern void polybench_papi_close();
extern void polybench_papi_print();
# endif

/* Function prototypes. */
extern void* polybench_alloc_data(unsigned long long int n, int elt_size);


#endif /* !POLYBENCH_H */


/* Include benchmark-specific header. */
/* Default data type is double, default size is 10x1024x1024. */


/**
 * adi.h: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 * License: /LICENSE.OSU.txt
 */
#ifndef ADI_H
# define ADI_H

/* Default to STANDARD_DATASET. */
# if !defined(TINY_DATASET) && !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#  define STANDARD_DATASET
# endif

/* Do not define anything if the user manually defines the size. */
# if !defined(TSTEPS) && ! defined(N)
/* Define the possible dataset sizes. */
#  ifdef TINY_DATASET
#   define TSTEPS 2
#   define N 16
#  endif

#  ifdef MINI_DATASET
#   define TSTEPS 2
#   define N 32
#  endif

#  ifdef SMALL_DATASET
#   define TSTEPS 10
#   define N 500
#  endif

#  ifdef STANDARD_DATASET /* Default if unspecified. */
#   define TSTEPS 50
#   define N 1024
#  endif

#  ifdef LARGE_DATASET
#   define TSTEPS 50
#   define N 2000
#  endif

#  ifdef EXTRALARGE_DATASET
#   define TSTEPS 100
#   define N 4000
#  endif
# endif /* !N */

# define _PB_TSTEPS POLYBENCH_LOOP_BOUND(TSTEPS,tsteps)
# define _PB_N POLYBENCH_LOOP_BOUND(N,n)

# ifndef DATA_TYPE
#  define DATA_TYPE double
#  define DATA_PRINTF_MODIFIER "%0.2lf "
# endif


#endif /* !ADI */

/* Array initialization. */

static void init_array(int n,double X[500 + 0][500 + 0],double A[500 + 0][500 + 0],double B[500 + 0][500 + 0])
{
  //int i;
  //int j;
{
    int c1;
    int c3;
    int c2;
    int c4;
    if (n >= 1) {
#pragma omp parallel for private(c4, c2, c3)
      for (c1 = 0; c1 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c1++) {
        for (c2 = 0; c2 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c2++) {
          for (c3 = 16 * c1; c3 <= ((16 * c1 + 15 < n + -1?16 * c1 + 15 : n + -1)); c3++) {
#pragma omp simd
            for (c4 = 16 * c2; c4 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c4++) {
              X[c3][c4] = (((double )c3) * (c4 + 1) + 1) / n;
              A[c3][c4] = (((double )c3) * (c4 + 2) + 2) / n;
              B[c3][c4] = (((double )c3) * (c4 + 3) + 3) / n;
            }
          }
        }
      }
    }
  }
}
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int n,double X[500 + 0][500 + 0])
{
  int i;
  int j;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      fprintf(stderr,"%0.2lf ",X[i][j]);
      if ((i * 500 + j) % 20 == 0) 
        fprintf(stderr,"\n");
    }
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

static void kernel_adi(int tsteps,int n,double X[500 + 0][500 + 0],double A[500 + 0][500 + 0],double B[500 + 0][500 + 0])
{
  //int t;
  //int i1;
  //int i2;
  
  //#pragma scop
{
    int c0;
    int c2;
    int c8;
    int c9;
    int c15;
    if (n >= 1 && tsteps >= 1) {
      for (c0 = 0; c0 <= tsteps + -1; c0++) {
        if (n >= 2) {
#pragma omp parallel for private(c15, c9, c8)
          for (c2 = 0; c2 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c2++) {
            for (c8 = 0; c8 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c8++) {
              for (c9 = (1 > 16 * c8?1 : 16 * c8); c9 <= ((16 * c8 + 15 < n + -1?16 * c8 + 15 : n + -1)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  B[c15][c9] = B[c15][c9] - A[c15][c9] * A[c15][c9] / B[c15][c9 - 1];
                }
              }
            }
            for (c8 = 0; c8 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c8++) {
              for (c9 = (1 > 16 * c8?1 : 16 * c8); c9 <= ((16 * c8 + 15 < n + -1?16 * c8 + 15 : n + -1)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  X[c15][c9] = X[c15][c9] - X[c15][c9 - 1] * A[c15][c9] / B[c15][c9 - 1];
                }
              }
            }
            for (c8 = 0; c8 <= (((n + -3) * 16 < 0?((16 < 0?-((-(n + -3) + 16 + 1) / 16) : -((-(n + -3) + 16 - 1) / 16))) : (n + -3) / 16)); c8++) {
              for (c9 = 16 * c8; c9 <= ((16 * c8 + 15 < n + -3?16 * c8 + 15 : n + -3)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  X[c15][n - c9 - 2] = (X[c15][n - 2 - c9] - X[c15][n - 2 - c9 - 1] * A[c15][n - c9 - 3]) / B[c15][n - 3 - c9];
                }
              }
            }
          }
        }
#pragma omp parallel for private(c15)
        for (c2 = 0; c2 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c2++) {
#pragma omp simd
          for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
            X[c15][n - 1] = X[c15][n - 1] / B[c15][n - 1];
          }
        }
        if (n >= 2) {
#pragma omp parallel for private(c15, c9, c8)
          for (c2 = 0; c2 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c2++) {
            for (c8 = 0; c8 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c8++) {
              for (c9 = (1 > 16 * c8?1 : 16 * c8); c9 <= ((16 * c8 + 15 < n + -1?16 * c8 + 15 : n + -1)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  B[c9][c15] = B[c9][c15] - A[c9][c15] * A[c9][c15] / B[c9 - 1][c15];
                }
              }
            }
            for (c8 = 0; c8 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c8++) {
              for (c9 = (1 > 16 * c8?1 : 16 * c8); c9 <= ((16 * c8 + 15 < n + -1?16 * c8 + 15 : n + -1)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  X[c9][c15] = X[c9][c15] - X[c9 - 1][c15] * A[c9][c15] / B[c9 - 1][c15];
                }
              }
            }
            for (c8 = 0; c8 <= (((n + -3) * 16 < 0?((16 < 0?-((-(n + -3) + 16 + 1) / 16) : -((-(n + -3) + 16 - 1) / 16))) : (n + -3) / 16)); c8++) {
              for (c9 = 16 * c8; c9 <= ((16 * c8 + 15 < n + -3?16 * c8 + 15 : n + -3)); c9++) {
#pragma omp simd
                for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
                  X[n - 2 - c9][c15] = (X[n - 2 - c9][c15] - X[n - c9 - 3][c15] * A[n - 3 - c9][c15]) / B[n - 2 - c9][c15];
                }
              }
            }
          }
        }
#pragma omp parallel for private(c15)
        for (c2 = 0; c2 <= (((n + -1) * 16 < 0?((16 < 0?-((-(n + -1) + 16 + 1) / 16) : -((-(n + -1) + 16 - 1) / 16))) : (n + -1) / 16)); c2++) {
#pragma omp simd
          for (c15 = 16 * c2; c15 <= ((16 * c2 + 15 < n + -1?16 * c2 + 15 : n + -1)); c15++) {
            X[n - 1][c15] = X[n - 1][c15] / B[n - 1][c15];
          }
        }
      }
    }
  }
  
//#pragma endscop
}

int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 500;
  int tsteps = 10;
/* Variable declaration/allocation. */
  double (*X)[500 + 0][500 + 0];
  X = ((double (*)[500 + 0][500 + 0])(polybench_alloc_data(((500 + 0) * (500 + 0)),(sizeof(double )))));
  ;
  double (*A)[500 + 0][500 + 0];
  A = ((double (*)[500 + 0][500 + 0])(polybench_alloc_data(((500 + 0) * (500 + 0)),(sizeof(double )))));
  ;
  double (*B)[500 + 0][500 + 0];
  B = ((double (*)[500 + 0][500 + 0])(polybench_alloc_data(((500 + 0) * (500 + 0)),(sizeof(double )))));
  ;
/* Initialize array(s). */
  init_array(n, *X, *A, *B);
/* Start timer. */
  polybench_timer_start();
  ;
/* Run kernel. */
  kernel_adi(tsteps,n, *X, *A, *B);
/* Stop and print timer. */
  polybench_timer_stop();
  ;
  polybench_timer_print();
  ;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  if (argc > 42 && !strcmp(argv[0],"")) 
    print_array(n, *X);
/* Be clean. */
  free(((void *)X));
  ;
  free(((void *)A));
  ;
  free(((void *)B));
  ;
  return 0;
}
