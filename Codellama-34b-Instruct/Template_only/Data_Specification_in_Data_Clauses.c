#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a data clause that specifies the array as executable data
    acc_data_clause_t data_clause;
    data_clause.type = ACC_DATA_CLAUSE_EXECUTABLE;
    data_clause.data = arr;
    data_clause.size = sizeof(int) * 10;

    // Create a data region that uses the data clause
    acc_data_region_t data_region;
    data_region.type = ACC_DATA_REGION_EXECUTABLE;
    data_region.data = arr;
    data_region.size = sizeof(int) * 10;

    // Run the kernel with the data region
    acc_kernel_t kernel;
    kernel.type = ACC_KERNEL_EXECUTABLE;
    kernel.data = arr;
    kernel.size = sizeof(int) * 10;
    kernel.function = (void*)test1_kernel;

    // Run the kernel
    acc_run_kernel(&kernel, &data_region);

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (arr[i] != i) {
            err = 1;
            break;
        }
    }

    // Free the memory
    free(arr);

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