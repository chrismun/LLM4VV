#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef T1
/*T1: Testing OpenACC detach clause */
bool test1(){
    int err = 0;

    int size = 1000;
    float *arr;
    float total = 0.0;

    arr = (float*)malloc(size * sizeof(float));

    /* Initialize array with some dummy data */
    for(int i = 0; i < size; i++) 
        arr[i] = (float)i;

    #pragma acc data create(arr[0:size])
    {
        #pragma acc parallel loop reduction(+:total)
        for(int i = 0; i < size; i++) 
        {
            total += arr[i];
        }

        #pragma acc exit data copyout(arr[0:size])
    }

    /* Validate results */
    float expected_total = (size - 1)*(size / 2.0f); // The formula for the sum of the first N numbers

    if(total != expected_total)
        err = 1;

    free(arr);

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