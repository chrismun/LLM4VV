#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand() % 100; // Variable to be copied as firstprivate
    int b = 0; // Variable to verify correctness of firstprivate behavior

    // Kernel to demonstrate firstprivate usage
    #pragma acc parallel firstprivate(a)
    {
        // Each gang should have its own copy of 'a' initialized to the same value as outside the construct
        // Let's modify 'a' to see if it is indeed private to each gang without affecting the original 'a'
        a = a + 1;

        // Use 'atomic' to avoid race condition when updating 'b'
        #pragma acc atomic update
        b += a;
    }

    // We expect 'b' to approximate 'NUM_GANGS * (a + 1)' since 'a' was incremented in parallel by each gang
    // Adjust the expected value based on your knowledge of the number of gangs used by the compiler,
    // This simplistic check assumes 'NUM_GANGS' but adjust as needed based on your system and compiler.
    // Here 'NUM_GANGS' is assumed to be a macro defined elsewhere or adjust the check according to your environment.
    
    if (b < NUM_GANGS * (a + 1) || b >= NUM_GANGS * (a+2)){
        err += 1;
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