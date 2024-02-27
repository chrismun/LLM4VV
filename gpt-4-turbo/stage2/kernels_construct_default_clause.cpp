#include <cstdlib>
#include <iostream>

// Assuming acc_testsuite.h provides necessary OpenACC testing support
// In this case, it's just conceptual.
#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 100;
    int a[size];
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100; // Assign random numbers
    }

    int scalar = 5; // A scalar variable to test capture by value

    #pragma acc kernels default(present) copy(scalar)
    for (int i = 0; i < size; ++i) {
        a[i] += scalar; // Should add 'scalar' value to each element of 'a'
        scalar = 999; // Try to change scalar inside the kernels region
    }

    // Since 'scalar' should be captured by value, changes inside the
    // kernel region should not affect the original 'scalar' variable.
    if (scalar != 5) {
        err++;
    }

    // Verifying if 'a' array has been correctly modified
    for (int i = 0; i < size; ++i) {
        if (a[i] < 5 || a[i] > 104) { // Since random was from 0 to 99
            err++;
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