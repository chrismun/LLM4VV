#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
using namespace std;

#ifndef T1
/*T1:acc map data,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *host_data = (int *)malloc(10 * sizeof(int));
    int *device_data = (int *)acc_malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x) {
        host_data[x] = rand() % 100;
    }

    acc_map_data(host_data, device_data, 10 * sizeof(int));

    int *host_data_copy = (int *)malloc(10 * sizeof(int));
    acc_copyout(host_data_copy, device_data, 10 * sizeof(int));

    for (int x = 0; x < 10; ++x) {
        if (host_data[x] != host_data_copy[x]) {
            err = 1;
            break;
        }
    }

    acc_unmap_data(host_data);
    acc_free(device_data);
    free(host_data);
    free(host_data_copy);

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