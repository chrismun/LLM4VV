#include "acc_testsuite.h"
#include <stdlib.h>

#define GANGS 8
#define THREADS 8
#define SIZE (GANGS*THREADS)

//T1: loop construct tile clause, V:2.7-3.3
int test1(){
    int err = 0;
    int i, j;
    int *host_array = (int*)malloc(SIZE*sizeof(int));
    int *device_array = (int*)malloc(SIZE*sizeof(int));

    // Initialize the array
    for(i=0; i<SIZE; i++)
        host_array[i] = i;

    #pragma acc data copyout(device_array[0:SIZE])
    {
        #pragma acc parallel loop gang tile(GANGS, THREADS)
        for(i=0; i<SIZE; i++)
            device_array[i] = host_array[i] * 2;
    }

    // Check the results
    for(i=0; i<SIZE; i++) {
        if(device_array[i] != host_array[i] * 2){
            err = 1;
        }
    }

    free(host_array);
    free(device_array);

    return err;
}

int main() {
    int error_code = 0;
    int passed;
    
    passed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        passed = passed + test1();
    }
    if (passed != 0){
        error_code = error_code + (1 << 0);
    }

    return error_code;
}