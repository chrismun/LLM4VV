#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:serial,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *a = (float *)malloc(size * sizeof(float));
    float sum_serial = 0;
    float sum_acc = 0;

    // Initialize array with random values
    for(int i = 0; i < size; ++i){
        a[i] = (float)rand() / RAND_MAX;
        sum_serial += a[i]; // Calculate sum in serial for comparison
    }

    // Use OpenACC serial construct to calculate sum
    #pragma acc data copyin(a[0:size])
    {
        #pragma acc serial
        {
            for(int i =0; i < size; ++i){
                sum_acc += a[i];
            }
        }
    }

    if(fabs(sum_serial - sum_acc) > 1e-5){ // Check if the sums are significantly different
        err += 1;
    }

    free(a);
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