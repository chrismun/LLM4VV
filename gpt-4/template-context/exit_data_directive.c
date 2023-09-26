#include "acc_testsuite.h"
#include <stdlib.h>
#ifndef T1
//T1:exit data directive,V:2.7-3.3
#define SIZE 100
int test1() {
    int err = 0;
    int *data = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    #pragma acc enter data create(data[0:SIZE])
    #pragma acc parallel loop present(data[0:SIZE])
    for (int i = 0; i < SIZE; i++) {
        data[i] += 1;
    }
    #pragma acc exit data delete(data[0:SIZE])

    // Check if data on the host is unchanged
    for (int i = 0; i < SIZE; i++) {
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

    free(data);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}