#include "acc_testsuite.h"
#ifndef T1
// T1: declare directive link clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Creating array A on the device
    int *A = (int*) acc_malloc(N * sizeof(int));

    // Linking the device array A to the host array B
    int *B;
    acc_map_data(B, A);

    // Initializing the device array A with random values
    for (int i = 0; i < N; ++i){
        A[i] = rand() % 100;
    }

    // Calculating the sum of elements in the device array A
    int sum = 0;
    for (int i = 0; i < N; ++i){
        sum += A[i];
    }

    // Mapping the sum back to the host variable
    int hostSum;
    #pragma acc update self(hostSum) async(1)
    #pragma acc host_data use_device(B)
    hostSum = sum;

    // Checking if the sum matches the host variable
    if (sum != hostSum){
        err = 1;
    }

    // Freeing the device memory
    acc_free(A);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}