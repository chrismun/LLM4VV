#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

int test(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * acc_a;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n])
    {
        acc_a = acc_deviceptr(a);
    }

    acc_a = acc_copyin(a, n * sizeof(real_t));
    acc_unmap_data(a);
    // The device address should be deleted; hence, an error should be raised when it is called
    if( acc_is_present(&a, sizeof(real_t)) )
    {
        printf("Test failed\n");
        exit(1);
    }  
    printf("Test passed\n");
    return 0;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    failed = failed + test();
    if (failed != 0){
        failcode = failcode + 1;
    }
    return failcode;
}