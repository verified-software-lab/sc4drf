// racy version of bar3.  one synchronization commented out.
__include__ <stdio.h>
__include__ <omp.h>
__include__ <assert.h>

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

#define barrier_start(tid) __NL__ \
{ __NL__ \
  if ((tid) == 0) { __NL__ \
    omp_set_lock(&l0); __NL__ \
    omp_set_lock(&l2); __NL__ \
  } else if ((tid) == 1) { __NL__ \
    omp_set_lock(&l1); __NL__ \
  } __NL__ \
}

#define barrier_stop(tid) __NL__ \
{ __NL__ \
  if ((tid) == 0) { __NL__ \
    omp_unset_lock(&l0); __NL__ \
    omp_unset_lock(&l2); __NL__ \
  } else if ((tid) == 1) { __NL__ \
    omp_unset_lock(&l1); __NL__ \
  } __NL__ \
}

#define barrier_wait(tid) __NL__ \
{ __NL__ \
  if ((tid) == 0) { __NL__ \
    omp_unset_lock(&l0); __NL__ \
    omp_set_lock(&l1); __NL__ \
    omp_set_lock(&l0); __NL__ \
    omp_unset_lock(&l1); __NL__ \
  } else if ((tid) == 1) { __NL__ \
    omp_set_lock(&l0); __NL__ \
    omp_unset_lock(&l1); __NL__ \
    omp_unset_lock(&l0); __NL__ \
    omp_set_lock(&l1); __NL__ \
  } __NL__ \
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
      barrier_wait(tid);
      if (tid == 0) x=0;
      barrier_wait(tid);
      printf("Thread %d: phase 3, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      barrier_wait(tid);
      if (tid == 1) x=1;
      barrier_wait(tid);
    }
#pragma omp barrier
    barrier_stop(tid);
  } // end of parallel construct
  barrier_destroy();
  printf("Done: x=%d\n", x);  
}
