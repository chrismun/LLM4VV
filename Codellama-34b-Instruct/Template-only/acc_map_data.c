#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(sizeof(int) * 10);
    int *map = (int *)malloc(sizeof(int) * 10);

    // Initialize data and map
    for (int i = 0; i < 10; i++) {
        data[i] = i;
        map[i] = i;
    }

    // Map data to the device
    acc_map_data(data, map, 10);

    // Verify that the data has been mapped correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != map[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(data);
    free(map);

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