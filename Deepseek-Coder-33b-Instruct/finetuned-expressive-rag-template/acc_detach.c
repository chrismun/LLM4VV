#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define T1
#define NUM_TEST_CALLS 10
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    #pragma acc data copyin(host_ptr[0:1])
    {
        #pragma acc detach(host_ptr)
        {
            #pragma acc update device(host_ptr[0:1])
        }

        #pragma acc exit data detach(host_ptr)

        if (*host_ptr != 10) {
            err = 1;
        }
    }

    free(host_ptr);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}