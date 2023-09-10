#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:acc hostptr, V:2.0-2.7*/

int test1() {

    int err = 0;
    srand(SEED);
    float *a;
    float *a_d;
    int i = 0;

    a = (float *) malloc(4 * sizeof(float));
    for(i=0; i<4; i++) {
        a[i] = (float)i;
    }

    /* Copy the host memory to the device */
    a_d = acc_copyin(a, 4 * sizeof(float));

    /* Test acc_hostptr */
    if(a != acc_hostptr(a_d)) {
        err = 1;
    }

    /* Cleanup */
    acc_delete(a, 4 * sizeof(float));
    free(a);
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}