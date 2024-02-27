#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T2
//T2:declare,construct-independent,V:2.6-2.7
int test2(){
    int err = 0;
    srand(SEED);
    const int n = 100;
    real_t *a, *b;
    a = (real_t *)malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc declare copyout(b[0:n])

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    for(int x = 0; x < n; ++x){
        if(fabs(b[x] - a[x]) > PRECISION){
            err++;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if(failed != 0){
        failcode += (1 << 1);
    }
#endif
    return failcode;
}