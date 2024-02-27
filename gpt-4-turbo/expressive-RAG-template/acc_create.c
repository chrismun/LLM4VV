#include <stdio.h>
#include <stdlib.h>
#include "openacc.h"

#ifndef T1
//T1:acc create,V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Fixed seed for reproducibility

    const int size = 1024;
    float *data = (float *)malloc(size * sizeof(float));
    // Initialize data to ensure we have a known state if acc_create copies (which it shouldn't)
    for(int i = 0; i < size; i++) {
        data[i] = (float)rand()/RAND_MAX;
    }

    // Use acc_create to allocate space on the device.
    #pragma acc enter data create(data[0:size])

    // Dummy operation to indirectly verify access to created space
    #pragma acc parallel loop present(data[0:size])
    for(int i = 0; i < size; i++) {
        data[i] += 1.0f; // Test action: increment every element, should not affect host data.
    }

    // Verify that no data was copied back to host (values should remain unchanged)
    for(int i = 0; i < size; i++) {
        if (data[i] >= 1.0f) { // Considering original data was <1.0, any >=1 would indicate an issue.
            err++;
        }
    }

    // Cleanup: Exit data region
    #pragma acc exit data delete(data[0:size])
    free(data);
    return err;
}
#endif

int main() {
    int failcode = 0;
#ifndef T1
    int failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if(failcode == 0){
        printf("Test Passed\n");
    }else{
        printf("Test Failed\n");
    }
    return failcode;
}