#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:acc deviceptr,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(10 * sizeof(int));
    int *device_data = (int *)acc_malloc(10 * sizeof(int));

    if (acc_deviceptr(host_data) != host_data) {
        err = 1;
    }

    if (acc_deviceptr(device_data) != (int *)acc_deviceptr(device_data)) {
        err = 1;
    }

    acc_free(device_data);
    free(host_data);

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