#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int size = 1024;
    int* data_host = (int*)malloc(size * sizeof(int));
    int* data_dev = (int*)acc_malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        data_host[i] = rand() % 100;
    }

    acc_memcpy_to_device(data_dev, data_host, size * sizeof(int));

    acc_memcpy_device(data_dev, data_dev, size * sizeof(int));

    acc_memcpy_from_device(data_host, data_dev, size * sizeof(int));

    for (int i = 0; i < size; i++) {
        if (data_host[i] != rand() % 100) {
            err = 1;
            break;
        }
    }

    acc_free(data_dev);
    free(data_host);

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