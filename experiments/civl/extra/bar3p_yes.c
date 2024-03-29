/* This version of bar3_yes adds printfs to provide diagnostic information
   on the data race.   Run:
     civl verify -min -checkDeadlock=none bar3p_yes.c
     civl replay bar3p_yes.c
*/
#include <stdio.h>
#include <omp.h>
#include <assert.h>

omp_lock_t l0, l1, l2;
const int n = 2;
int x = 1;

void barrier_init() {
  omp_init_lock(&l0);
  omp_init_lock(&l1);
  omp_init_lock(&l2);
}

void barrier_destroy() {
  omp_destroy_lock(&l0);
  omp_destroy_lock(&l1);
  omp_destroy_lock(&l2);
}

void barrier_start(int tid) {
  if (tid == 0) {
    omp_set_lock(&l0);
    omp_set_lock(&l2);
  } else if (tid == 1) {
    omp_set_lock(&l1);
  }
}

void barrier_stop(int tid) {
  if (tid == 0) {
    omp_unset_lock(&l0);
    omp_unset_lock(&l2);
  } else if (tid == 1) {
    omp_unset_lock(&l1);
  }
}

void barrier_wait(int tid) {
  if (tid == 0) {
    omp_unset_lock(&l0);
    printf("t0 released l0\n");
    omp_set_lock(&l1);
    printf("t0 obtained l1\n");
    //omp_unset_lock(&l2);
    omp_set_lock(&l0);
    printf("t0 obtained l0\n");
    omp_unset_lock(&l1);
    printf("t0 released l1\n");
    //omp_set_lock(&l2);
  } else if (tid == 1) {
    omp_set_lock(&l0);
    printf("t1 obtained l0\n");
    omp_unset_lock(&l1);
    printf("t1 released l1\n"); 
    //omp_set_lock(&l2);
    omp_unset_lock(&l0);
    printf("t1 released l0\n");
    omp_set_lock(&l1);
    printf("t1 obtained l1\n");
    //omp_unset_lock(&l2);
  }
}

int main() {
  barrier_init();
#pragma omp parallel num_threads(2)
  {
    int tid = omp_get_thread_num();
    barrier_start(tid);
#pragma omp barrier
    for (int i=0; i<n; i++) {
      printf("Thread %d: phase 1, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      //assert(x==1);
      barrier_wait(tid);
      if (tid == 0) { x=0; printf("Thread 0 wrote\n"); }
      barrier_wait(tid);
      printf("Thread %d: phase 3, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      //assert(x==0);
      barrier_wait(tid);
      if (tid == 1) { x=1; printf("Thread 1 wrote\n"); }
      barrier_wait(tid);
    }
#pragma omp barrier
    barrier_stop(tid);
  } // end of parallel construct
  barrier_destroy();
  printf("Done: x=%d\n", x);  
}
