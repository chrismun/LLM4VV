#include "acc_testsuite.h"
#ifndef T1
//T1:acc detach,V:2.7-3.3
int test1(){
  int err = 0;
  srand(SEED);
  int *a = (int *)malloc(n * sizeof (int));
  int *b = (int *)malloc(n * sizeof (int));
  int *tot = (int *)malloc(10 * sizeof (int));

  for (int x = 0; x < n; ++x){
    a[x] = rand() / (real_t)(RAND_MAX / 10);
    b[x] = rand() / (real_t)(RAND_MAX / 10);
  }
  #pragma acc enter data copyin(a[0:n], b[0:n]) create(tot[0:10])
  for (int x = 0; x < 10; ++x){
    tot[x] = 0;
  }
  #pragma acc parallel present(a[0:n], b[0:n], tot[0:10])
  {
    #pragma acc loop
    for (int x = 0; x < n; ++x){
      #pragma acc atomic
      tot[x%10] += a[x] + b[x];
    }
  }
  acc_detach(a);
  acc_detach(b);
  acc_detach(tot);
  for (int x = 0; x < n; ++x){
    a[x] = 0;
    b[x] = 0;
  }
  for (int x = 0; x < 10; ++x){
    if (tot[x] != 2 * (((n - 1) / 10) * ((n - 1) / 10 + 1)) / 2){
      err += 1;
    }
  }
  #pragma acc exit data copyout(tot[0:10]) delete(a[0:n], b[0:n])
  return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}