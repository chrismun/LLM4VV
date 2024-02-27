#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct independent clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int * a = (unsigned int *)malloc(10 * n * sizeof(unsigned int));
    unsigned int * b = (unsigned int *)malloc(10 * n * sizeof(unsigned int));
    unsigned int * c = (unsigned int *)malloc(10 * n * sizeof(unsigned int));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = (unsigned int) rand() / (real_t)(RAND_MAX / 10);
        b[x] = (unsigned int) rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            c[x * n + y] = a[x * n + y] + b[x * n + y];
        }
    }
    #pragma acc data copyin(a[0:10*n], b[0:10*n], c[0:10*n])
    {
      #pragma acc parallel loop independent
      for (int x = 0; x < 10; ++x){
        #pragma acc loop independent
        for (int y = 0; y < n; ++y){
          c[x * n + y] = a[x * n + y] + b[x * n + y];
        }
      }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (c[x] - (a[x] + b[x]) > 0.01){
            err += 1;
        }
    }

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