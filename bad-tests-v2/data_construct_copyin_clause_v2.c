#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:data construct copyin clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int a = rand();
    int b;

#pragma acc data copyin(a)
    {
        #pragma acc parallel 
        {
            b = a;
        }
    }

    // Verify if data is correctly copied in
    if (a != b) {
        err = 1;
        printf("The values of 'a' and 'b' are not the same. Test failed.\n");
    }

    return err;
}
#endif

// Main function
int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
        printf("copyin clause test failed\n");
    }
    else {
        printf("copyin clause test passed\n");
    }
#endif

    return failcode;
}