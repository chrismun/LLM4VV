#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:kernels construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int arr_size = 1024;
    int *a = (int *) malloc(sizeof(int) * arr_size);
    int *b = (int *) malloc(sizeof(int) * arr_size);
    for(int i = 0; i < arr_size; ++i){
        a[i] = rand() % 100;
    }

    // First kernels region: populate array b based on array a
    #pragma acc kernels copyin(a[0:arr_size]) copyout(b[0:arr_size])
    {
        for (int i = 0; i < arr_size; ++i) {
            b[i] = a[i] + 1;
        }
    }

    // Wait for the completion of the first kernels region
    #pragma acc wait

    // Second kernels region: validate that the previous operation is completed
    #pragma acc kernels copyin(b[0:arr_size])
    {
        for (int i = 0; i < arr_size; ++i) {
            if(b[i] != a[i] + 1){
                #pragma acc atomic update
                err++;
            }
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