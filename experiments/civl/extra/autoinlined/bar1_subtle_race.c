/* Data race on printf's which read x with writes to x */
__include__ <stdio.h>
__include__ <omp.h>
__include__ <assert.h>

typedef _Bool flag_t;

flag_t f0, f1;
const int n = 100;
int x = 1;

#define init(f) __NL__ \
{ __NL__ \
  *(f) = 0; __NL__ \
}

#define raise(f) __NL__ \
{ __NL__ \
__pragma__ omp critical __NL__ \
  { __NL__ \
    assert(*(f) == 0); __NL__ \
    *(f) = 1; __NL__ \
  } __NL__ \
}

#define lower(f)  __NL__ \
{ __NL__ \
  _Bool done = 0; __NL__ \
  while (!done) { __NL__ \
__pragma__ omp critical __NL__ \
    if (*(f) == 1) { __NL__ \
      *(f) = 0; __NL__ \
      done = 1; __NL__ \
    } __NL__ \
  } __NL__ \
}

#define mybarrier(tid) __NL__ \
{ __NL__ \
  if ((tid) == 0) { __NL__ \
    raise(&f0); __NL__ \
    lower(&f1); __NL__ \
  } else if ((tid) == 1) { __NL__ \
    lower(&f0); __NL__ \
    raise(&f1); __NL__ \
  } __NL__ \
}

int main() {
  init(&f0);
  init(&f1);
#pragma omp parallel num_threads(2)
  {
    int tid = omp_get_thread_num();
#pragma omp barrier
    for (int i=0; i<n; i++) {
      printf("Thread %d: phase 1, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      assert(x==1);
      mybarrier(tid);
      printf("Thread %d: phase 2, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      if (tid == 0) x=0;
      mybarrier(tid);
      printf("Thread %d: phase 3, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      assert(x==0);
      mybarrier(tid);
      printf("Thread %d: phase 4, i=%d, x=%d\n", tid, i, x); fflush(stdout);
      if (tid == 1) x=1;
      mybarrier(tid);
    }
  } // end of parallel construct
  printf("Done: x=%d\n", x);  
}
