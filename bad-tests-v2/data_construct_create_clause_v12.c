#include "acc_testsuite.h"

#ifndef TEST_CREATE_CLAUSE
#define TEST_CREATE_CLAUSE

//Test Create clause, V:2.7-3.3
int test_create_clause(){
    int err = 0;
    srand(SEED);

    int *host_data = (int*)malloc(10000 * sizeof(int));
    int *device_data;

    for (int i = 0; i < 10000; ++i){
        host_data[i] = rand() % 10000;
    }

    #pragma acc data create(device_data[0:10000])
    {
        #pragma acc parallel loop
        for (int i = 0; i < 10000; ++i){
            device_data[i] = host_data[i];
        }
    }

    // Compare host and device results.
    for (int i = 0; i < 10000; ++i) {
        if (host_data[i] != device_data[i]) {
            err = 1;
        }
    }

    free(host_data);
    return err;
}

#endif

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_create_clause();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}