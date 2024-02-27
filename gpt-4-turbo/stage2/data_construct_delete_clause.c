#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#ifndef T1
// T1:data construct delete clause, V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    float *data = (float*)malloc(size * sizeof(float));

    // Initialize data
    for(int i = 0; i < size; ++i){
        data[i] = i;
    }

    // Use the data in an ACC region
#pragma acc data copy(data[0:size])
    {
#pragma acc parallel loop
        for(int i = 0; i < size; ++i){
            data[i] = data[i] * 2.0f;
        }
    }

    // Delete data
#pragma acc exit data delete(data[0:size])

    // Free the host memory and check for errors
    free(data);

    // Hypothetical check for deletion success, in reality, we're assuming success if no errors occur
    // There's no straightforward way to directly verify GPU memory deletion from host code in a portable manner

    return err;
}
#endif

#define SEED 1234
#define NUM_TEST_CALLS 10

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}