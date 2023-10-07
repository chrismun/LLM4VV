#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
/*T1:parallel construct self clause, V:2.0-2.7*/
int test1(){
    int err = 0;
    const int N = 100;
    float *host_array, *device_array;

    /* Allocate the host and device arrays */
    host_array = (float*) malloc(N * sizeof(float));
    device_array = (float*) malloc(N * sizeof(float));

    /* Initialize the host array with some values */
    for (int i = 0; i < N; ++i) {
        host_array[i] = i + 1;
    }

    /* Transfer the data to the device and do the computation */
#pragma acc parallel self copyout(device_array[0:N]) copyin(host_array[0:N])
    {
        for (int i = 0; i < N; ++i) {
            device_array[i] = host_array[i] * 2;
        }
    }

    /* Check if the computation is done correctly */
    for (int i = 0; i < N; ++i) {
        if (device_array[i] != host_array[i] * 2) {
            err = 1;
            break;
        }
    }

    /* Free the host and device arrays */
    free(host_array);
    free(device_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < ACC_TESTSUITE_NUM_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}