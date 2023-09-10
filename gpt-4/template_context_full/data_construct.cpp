#include "acc_testsuite.h"
#include <cstdlib>

// Skip T1 tests if already set via flags
#ifndef T1
/**
   Testing OpenACC data construct with copy clause.
*/
int test1() {
    int err = 0;
    int* a;
    int* b;
  
    const int arraySize = 1000;
    // Creating and initializing the arrays
    a = (int*)malloc(arraySize * sizeof(int));
    b = (int*)malloc(arraySize * sizeof(int));
    srand(SEED);
  
    // filling array a with random values and array b with zeros
    for (int i = 0; i < arraySize; ++i) {
        a[i] = rand() % 50;
        b[i] = 0;
    }

    // Use OpenACC data construct
    #pragma acc data copy(a[0:arraySize]) copyout(b[0:arraySize])
    {
        #pragma acc parallel loop
        for (int i = 0; i < arraySize; ++i) {
            b[i] = a[i] + 5;
        }
    }

    // Verify the results
    for (int i = 0; i < arraySize; ++i) {
        if (b[i] != a[i] + 5) {
            err++;
        }
    }

    // Cleaning up
    free(a);
    free(b);

    return err;
}
#endif

// Driver function
int main() {
    int failcode = 0;

    // Skip T1 tests if already set via flags
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}