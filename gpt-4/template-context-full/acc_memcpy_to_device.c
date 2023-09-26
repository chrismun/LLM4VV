#include "acc_testsuite.h"
#include <stdlib.h>

#define SIZE 1024
#define SEED 100
#define NUM_TEST_CALLS 100

#ifndef T1
/*T1:acc_memcpy_to_device, V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);
    int* host_data = (int*) malloc(SIZE * sizeof(int));
    int* device_data = (int*) acc_malloc(SIZE * sizeof(int));

    for(int i = 0; i < SIZE; ++i) {
        host_data[i] = rand();
    }

    acc_memcpy_to_device(device_data, host_data, SIZE * sizeof(int));

    #pragma acc parallel loop present(device_data)
    for(int i = 0; i < SIZE; ++i) {
        if(device_data[i] != host_data[i]) {
            err = 1;
        }
    }

    acc_free(device_data);
    free(host_data);
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