#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int original_value = rand();
    int data = original_value;

    #pragma acc parallel self(data)
    {
        data = 999; // Attempt to modify, but due to self, this shouldn't affect the host view automatically.
    }

    /* Since 'data' is in self, the change within the parallel region might not be reflected back to the host variable
       without explicit data management. 'data' should hold its original value if the self clause is respected correctly. */
    if (data != original_value) {
        err++;
        printf("Error: Data modified to %d but should be %d due to self clause.\n", data, original_value);
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