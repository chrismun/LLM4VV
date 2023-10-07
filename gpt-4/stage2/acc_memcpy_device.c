#include "acc_testsuite.h"
#include <stdlib.h>
#ifndef T1
/*T1:acc memcpy device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
   
    // Allocate memory on the device
    float* mem1 = (float*) acc_malloc(sizeof(float) * 100);
    float* mem2 = (float*) acc_malloc(sizeof(float) * 100);

    // Initialize mem1 with random float numbers
    for(int i = 0; i < 100; i++) {
        mem1[i] = rand();
    }

    // Perform memcpy
    acc_memcpy_device(mem2, mem1, sizeof(float) * 100);

    // Verify that mem1 and mem2 are identical
    for(int i = 0; i < 100; i++) {
        if(mem1[i] != mem2[i]) {
            err = 1;
            break;
        }
    }

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