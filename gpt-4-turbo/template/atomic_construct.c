#include "acc_testsuite.h"
#ifndef T1
//T1:atomic,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int num_elements = 100;
    int* a = (int*)malloc(num_elements * sizeof(int));
    int total = 0;
    int host_total = 0;

    // Initialize array with random values and compute host total for verification
    for(int i = 0; i < num_elements; ++i){
        a[i] = rand() % 10; // Assign a random value between 0 and 9
        host_total += a[i];
    }

    #pragma acc data copy(a[0:num_elements])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for(int i = 0; i < num_elements; ++i){
                #pragma acc atomic
                total += a[i];
            }
        }
    }

    // Verify the total computed on the device against the host
    if(host_total != total){
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