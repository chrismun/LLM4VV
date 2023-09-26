#include "acc_testsuite.h"
#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    int a = 0;
    srand(SEED);
    
    // Here, 100 random integers will be added to 'a' in parallel.
    // Atomic directive ensures that each addition is done atomically.
    #pragma acc parallel loop num_gangs(100)
    for (int i = 0; i < 100; ++i) {
        #pragma acc atomic update
        a += rand() % 100;
    }

    // Atomic construct should ensure the 'a' to have a valid value as per above 
    // computations. If 'err' is non-zero, there was an error in the compiler's atomic 
    // construct implementation.
    if(a < 0 || a > 9900){
        err = 1;
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