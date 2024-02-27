#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:parallel,firstprivate,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t init_val = rand() / (real_t)(RAND_MAX / 10);
    real_t gang_results[NUM_GANGS];

    // Assuming NUM_GANGS is a defined macro indicating how many gangs to test
    for (int i = 0; i < NUM_GANGS; ++i){
        gang_results[i] = 0.0;
    }

    #pragma acc parallel num_gangs(NUM_GANGS) vector_length(1) firstprivate(init_val)
    {
        real_t local_copy = init_val;
        // Simulating work by modifying the local copy
        local_copy += 1.0;
        #pragma acc atomic write
        gang_results[__pgi_gangidx()] = local_copy; 
    }

    for (int i = 0; i < NUM_GANGS; ++i){
        if (fabs(gang_results[i] - (init_val + 1.0)) > PRECISION){
            err += 1;
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}