#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    a = (int *)acc_malloc(sizeof(int));
    *a = 10;

    #pragma acc declare device_resident(a)

    #pragma acc data copy(a)
    {
        *a = 20;
    }

    if (*a != 20){
        err = 1;
    }

    acc_free(a);

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