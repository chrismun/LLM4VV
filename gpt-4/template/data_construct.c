#include "acc_testsuite.h"
#ifndef T1
// Test for the data construct in OpenACC
int test1(){
    int err = 0;
    srand(SEED);
    int size = 100;
    int a[size];

    // Fill the array with random numbers
    for (int i=0; i < size; ++i)
        a[i] = rand();

    #pragma acc data copy(a)
    {
        #pragma acc parallel loop
        for (int i=0; i < size; ++i)
            a[i] *= 2;
    }

    // Validate the results
    for(int i=0; i < size; ++i)
    {
        if(a[i] != 2 * a[i]){
            err = 1;
        }
    }

    // Return error, 1 means there was an error, 0 means successful
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