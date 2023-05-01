#include <stdio.h>
#include <omp.h>
#include <assert.h>

typedef _Bool flag_t;

flag_t f0, f1;
const int n = 100;
int x = 1;

int main() {
  // init(&f0);
  f0 = 0;
  // init(&f1);
  f1 = 0;
#pragma omp parallel num_threads(2)
  {
    int tid = omp_get_thread_num();
    for (int i=0; i<n; i++) {
      printf("Thread %d: phase 1, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      assert(x==1);
      // mybarrier(tid);
      if (tid == 0) {
	// raise(&f0);
#pragma omp critical
	{
	  assert(f0 == 0);
	  f0 = 1;
	}
	// lower(&f1);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f1 == 1) {
	      f1 = 0;
	      done = 1;
	    }
	  }
	}
      } else if (tid == 1) {
	// lower(&f0);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f0 == 1) {
	      f0 = 0;
	      done = 1;
	    }
	  }
	}
	// raise(&f1);
#pragma omp critical
	{
	  assert(f1 == 0);
	  f1 = 1;
	}
      }
      //printf("Thread %d: phase 2, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      if (tid == 0) x=0;
      // mybarrier(tid);
      if (tid == 0) {
	// raise(&f0);
#pragma omp critical
	{
	  assert(f0 == 0);
	  f0 = 1;
	}
	// lower(&f1);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f1 == 1) {
	      f1 = 0;
	      done = 1;
	    }
	  }
	}
      } else if (tid == 1) {
	// lower(&f0);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f0 == 1) {
	      f0 = 0;
	      done = 1;
	    }
	  }
	}
	// raise(&f1);
#pragma omp critical
	{
	  assert(f1 == 0);
	  f1 = 1;
	}
      }
      printf("Thread %d: phase 3, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      assert(x==0);
      // mybarrier(tid);
      if (tid == 0) {
	// raise(&f0);
#pragma omp critical
	{
	  assert(f0 == 0);
	  f0 = 1;
	}
	// lower(&f1);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f1 == 1) {
	      f1 = 0;
	      done = 1;
	    }
	  }
	}
      } else if (tid == 1) {
	// lower(&f0);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f0 == 1) {
	      f0 = 0;
	      done = 1;
	    }
	  }
	}
	// raise(&f1);
#pragma omp critical
	{
	  assert(f1 == 0);
	  f1 = 1;
	}
      }
      //printf("Thread %d: phase 4, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      if (tid == 1) x=1;
      // mybarrier(tid);
      if (tid == 0) {
	// raise(&f0);
#pragma omp critical
	{
	  assert(f0 == 0);
	  f0 = 1;
	}
	// lower(&f1);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f1 == 1) {
	      f1 = 0;
	      done = 1;
	    }
	  }
	}
      } else if (tid == 1) {
	// lower(&f0);
	{
	  _Bool done = 0;
	  while (!done) {
#pragma omp critical
	    if (f0 == 1) {
	      f0 = 0;
	      done = 1;
	    }
	  }
	}
	// raise(&f1);
#pragma omp critical
	{
	  assert(f1 == 0);
	  f1 = 1;
	}
      }
    }
  } // end of parallel construct
  printf("Done: x=%d\n", x);  
}
