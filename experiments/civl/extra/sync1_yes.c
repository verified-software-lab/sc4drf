// race: t1 sets, unsets.  then t0 sets.  both are at assignment to x.
#include <stdio.h>
#include <omp.h>
#include <assert.h>

omp_lock_t l;
int x = 1;

int main() {
  omp_init_lock(&l);
#pragma omp parallel num_threads(2)
  {
    int tid = omp_get_thread_num();
#pragma omp barrier
    if (tid == 0) {
      omp_set_lock(&l);
      x=0;
      omp_unset_lock(&l);
    } else if (tid == 1) {
      omp_set_lock(&l);
      omp_unset_lock(&l);
      x=1;
    }
#pragma omp barrier
  } // end of parallel construct
  omp_destroy_lock(&l);
  printf("Done: x=%d\n", x);  
}
