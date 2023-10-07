#include "acc_testsuite.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <openacc.h>

#ifndef T1
/*T1:data construct detach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1000;
    std::vector<int> host_array(N, 0);
    int* device_array;
    acc_malloc(&device_array, N * sizeof(int));

    for (int x = 0; x < N; ++x) {
        host_array[x] = rand() % 100;
    }

    acc_memcpy(device_array, host_array.data(), N * sizeof(int));

    int* detached_array = nullptr;
    acc_attach(&detached_array, device_array);

    if (detached_array != device_array) {
        err = 1;
    }

    acc_detach(device_array);

    acc_free(device_array);

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