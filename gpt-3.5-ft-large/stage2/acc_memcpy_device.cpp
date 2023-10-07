#include "acc_testsuite.h"
#ifndef T1
//T1: acc_memcpy
int test1(){
    int* a = (int *)malloc(n * sizeof(int));
    int* a_copy = (int *)malloc(n * sizeof(int));

    real_t dt = ((1.0) + rand() / (real_t)(RAND_MAX)) * 100;
    real_t temp = 0;
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_copy[x] = 0;
    }

    acc_copyin(a[0:n]);
    #pragma acc data copy(a_copy[0:n])
    {
        #pragma acc parallel
        {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] += 10;
        }
        }
        acc_memcpy_device(a_copy, a, n * sizeof(int));
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a_copy[x] - a[x]) > PRECISION){
            temp += 1;
        }
    }

    free(a);
    free(a_copy);

    if (temp > 0){
        return 1;
    }
    else {
        return 0;
    }
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