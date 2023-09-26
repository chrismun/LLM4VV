#include "acc_testsuite.h"
#include <stdlib.h>

#define SIZE 1000
#define VALUE 3

int test_copyin(){
    int err = 0;
    int *data_host = (int*) malloc(SIZE*sizeof(int));
    int *data_device;
    
    // initialize host data
    for (int i = 0; i < SIZE; ++i){
        data_host[i] = VALUE;
    }

    // use acc_copyin to copy data to device
    data_device = (int*) acc_copyin(data_host, SIZE * sizeof(int));

    // test by launching a parallel kernel
    #pragma acc parallel present(data_device[0:SIZE])
    {
        for (int i = 0; i < SIZE; ++i){
            if (data_device[i] != VALUE){
                err = 1;  // device memory doesn't match what we copied in
            }
        }
    }

    free(data_host);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_copyin();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}