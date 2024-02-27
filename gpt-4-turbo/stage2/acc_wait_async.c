#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc wait async,V:2.7-3.3
#define SEED 12345
#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    
    // Initializing data
    int data_size = 1024;
    float *a = (float *)malloc(data_size * sizeof(float));
    float *b = (float *)malloc(data_size * sizeof(float));
    for(int i = 0; i < data_size; i++) {
        a[i] = i * 1.0f;
        b[i] = 0.0f;
    }
    
    // Using two async queues
    int async1 = 1, async2 = 2;

    // Enqueue first operation on async1
    #pragma acc parallel loop async(async1)
    for(int i = 0; i < data_size; i++) {
        b[i] = a[i] + 1.0f;
    }

    // Wait for completion of operations on async1 before starting operations on async2
    acc_wait_async(async1, async2);

    // Enqueue second operation on async2, which should only execute after async1 operations are complete
    #pragma acc parallel loop async(async2)
    for(int i = 0; i < data_size; i++) {
        b[i] += 1.0f;
    }

    // Ensuring all operations complete
    acc_wait_all();

    // Verification
    for(int i = 0; i < data_size; i++) {
        if(b[i] != a[i] + 2.0f) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    return failcode;
}