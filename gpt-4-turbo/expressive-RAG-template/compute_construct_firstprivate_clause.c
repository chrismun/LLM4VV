#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assuming acc_testsuite.h contains necessary environment setup.
#include "acc_testsuite.h"

#ifndef T1
// T1:compute construct firstprivate clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Variables
    int a = 5; // Initial value before entering the parallel region
    int gangs = 0;
    int value_after = 0;
    
    // Using OpenACC to identify the number of gangs dynamically
    #pragma acc parallel firstprivate(a)
    {
        // In a real-world test, this would be more complex to properly isolate gangs and ensure non-colliding execution
        #pragma acc atomic update
        gangs++;
        
        // Local modification of 'a' to test firstprivate
        a = a + 1;
    }
    
    // Any changes to 'a' inside the parallel region should not affect 'value_after'
    value_after = a;

    // 'a' should remain as its initial value since the modifications were local to each gang
    if(value_after != 5){
        err += 1;
        printf("Firstprivate clause did not work as intended.\n");
    }

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
    return failcode;
}