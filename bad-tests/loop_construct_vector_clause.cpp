#include "acc_testsuite.h"
#include <vector>

#ifndef T1
/*T1: loop construct vector clause,V:2.0-2.7*/
int test1() {
    const int size = 100;
    int err = 0;
    std::vector<int> host_array(size), device_array(size);
    for (int i = 0; i < size; ++i) {
        host_array[i] = i;
        device_array[i] = 0;
    }

    #pragma acc data copyin(host_array[0:size]) copyout(device_array[0:size])
    {
        #pragma acc parallel loop vector
        for (int i = 0; i < size; ++i) {
            device_array[i] = host_array[i] * i;
        }
    }

    for (int i = 0; i < size; ++i) {
        if (device_array[i] != host_array[i] * i) {
            ++err;
            break;
        }
    }

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