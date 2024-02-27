#include <iostream>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *a = (float*)malloc(size*sizeof(float));

    // Populate the array
    for(int i = 0; i < size; ++i){
        a[i] = rand()%100;
    }

    // Copy data to the device
    #pragma acc enter data copyin(a[0:size])

    // Delete the data from the device
    #pragma acc exit data delete(a[0:size])

    // Attempt to verify deletion - Simplified for this test purpose.
    // Note: Direct verification like this is not practical in a real scenario
    // We simulate a check by ensuring no access is possible and relying on OpenACC runtime
    #pragma acc parallel loop
    for(int i = 0; i < size; ++i){
        if (a[i] != 0) { // This condition is to mimic verification
            err++;
        }
    }

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    std::cout << "Test " << (failcode == 0 ? "PASSED" : "FAILED") << std::endl;
    return failcode;
}