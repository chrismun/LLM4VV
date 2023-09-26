#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *host_array = (int *)malloc(N * sizeof(int));
    int *device_array = (int *)malloc(N * sizeof(int));

    if (host_array == NULL || device_array == NULL) {
        err = 1;
    }

    #pragma acc data copyin(host_array[0:N]) copyout(device_array[0:N])
    {
        #pragma acc host_data use_device(host_array, device_array)
        {
            #pragma acc parallel loop
            for (int i = 0; i < N; i++) {
                host_array[i] = 1;
                device_array[i] = 2;
            }

            #pragma acc parallel loop
            for (int i = 0; i < N; i++) {
                if (host_array[i] != 1 || device_array[i] != 2) {
                    err = 1;
                    break;
                }
            }
        }
    }

    free(host_array);
    free(device_array);

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
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}