#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the input data
    int *input = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        input[i] = rand() % 100;
    }

    // Initialize the output data
    int *output = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        output[i] = 0;
    }

    // Set the tile size
    int tile_size = 16;

    // Call the kernel with the tile size
    kernel(input, output, tile_size);

    // Verify the output data
    for (int i = 0; i < N; i++) {
        if (output[i] != input[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(input);
    free(output);

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